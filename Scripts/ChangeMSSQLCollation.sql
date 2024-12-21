SET NOCOUNT ON;
GO

-- Step 1: Initialize Temporary Table for Variables
IF OBJECT_ID('tempdb..##TempVariables') IS NOT NULL DROP TABLE ##TempVariables;

CREATE TABLE ##TempVariables (
    VariableName NVARCHAR(255),
    VariableValue NVARCHAR(MAX)
);

-- Insert initial variable values
INSERT INTO ##TempVariables (VariableName, VariableValue)
VALUES
--    ('DatabaseName', 'DATABASE_NAME_XXX'),  -- Replace with your actual database name
--    ('CollationName', 'COLLATION_NAME_XXX'),  -- Replace with your desired collation
    ('DatabaseName', 'ROW_TEST'),  -- Replace with your actual database name
    ('CollationName', 'Finnish_Swedish_100_CI_AI_SC_UTF8'),  -- Replace with your desired collation
    ('ShouldBackup', '0');  -- Set to 1 to enable backup, 0 to disable

GO

-- Step 2: Backup Database w today's date and time added to backup name
DECLARE @DatabaseName NVARCHAR(255);
DECLARE @CollationName NVARCHAR(255);
DECLARE @BackupFileName NVARCHAR(255);
DECLARE @ShouldBackup BIT;
DECLARE @DateTime NVARCHAR(20);
DECLARE @SQL NVARCHAR(MAX);

-- Retrieve the database name and backup control variable from the temporary table
SELECT @DatabaseName = VariableValue FROM ##TempVariables WHERE VariableName = 'DatabaseName';
SELECT @CollationName = VariableValue FROM ##TempVariables WHERE VariableName = 'CollationName';
SELECT @ShouldBackup = CAST(VariableValue AS BIT) FROM ##TempVariables WHERE VariableName = 'ShouldBackup';

IF @ShouldBackup = 1
BEGIN
    PRINT 'Backing up database';
    -- Get current DateTime in the format YYYYMMDD_HHMMSS
    SET @DateTime = CONVERT(NVARCHAR, GETDATE(), 112) + '_' + REPLACE(CONVERT(NVARCHAR, GETDATE(), 108), ':', '');
    SET @BackupFileName = @DatabaseName + '_' + @DateTime + '.bak';

    -- Construct the backup SQL command
    SET @SQL = 'BACKUP DATABASE ' + QUOTENAME(@DatabaseName) + 
                ' TO DISK = ''' + @BackupFileName + ''' WITH FORMAT, ' + 
                'MEDIANAME = ''SQLServerBackups'', NAME = ''Full Backup of ' + @DatabaseName + ''';';

    -- Execute the backup command
    EXEC(@SQL);
    PRINT 'Database Backup created: ' + @BackupFileName;
END
GO

-- Step 3: Backup Schema-Bound Objects
PRINT 'Backing up schema-bound object definitions...';
IF OBJECT_ID('tempdb..##BackupSchemaBoundObjects') IS NOT NULL DROP TABLE ##BackupSchemaBoundObjects;
CREATE TABLE ##BackupSchemaBoundObjects (ObjectType NVARCHAR(50), ObjectName NVARCHAR(255), Definition NVARCHAR(MAX));

-- Retrieve object names dynamically, e.g., schema-bound functions and views
INSERT INTO ##BackupSchemaBoundObjects (ObjectType, ObjectName, Definition)
SELECT 
    o.type_desc AS ObjectType,
    QUOTENAME(SCHEMA_NAME(o.schema_id)) + '.' + QUOTENAME(o.name) AS ObjectName,
    OBJECT_DEFINITION(o.object_id) AS Definition
FROM sys.objects o
WHERE o.is_ms_shipped = 0
AND OBJECT_DEFINITION(o.object_id) IS NOT NULL
AND o.TYPE IN ('FN', 'IF', 'TF', 'V');  -- Function types: Scalar (FN), Inline Table-Valued (IF), Multi-Statement Table-Valued (TF), and Views (V)
GO

-- Step 4: Drop Dependencies and Schema-Bound Objects
PRINT 'Dropping dependencies and schema-bound objects...';
DECLARE @drop_deps_sql NVARCHAR(MAX) = N'';
SELECT @drop_deps_sql += 
    CASE 
        WHEN ObjectType = 'VIEW' THEN 'DROP VIEW ' + ObjectName + ';'
        WHEN ObjectType LIKE '%FUNCTION' THEN 'DROP FUNCTION ' + ObjectName + ';'
    END + CHAR(13)
FROM ##BackupSchemaBoundObjects;

-- Execute drop statements for schema-bound objects
IF @drop_deps_sql <> N'' EXEC sp_executesql @drop_deps_sql;
PRINT 'Dependencies and schema-bound objects dropped successfully.';
GO

-- Step 5: Backup all index information
PRINT 'Backup ALL indexes including PKs and unique constraints that depend on computed columns...';
IF OBJECT_ID('tempdb..##IndexesBackup') IS NOT NULL DROP TABLE ##IndexesBackup;
CREATE TABLE ##IndexesBackup (
    TableName NVARCHAR(255),
    IndexName NVARCHAR(255),
    IndexDefinition NVARCHAR(MAX),
    IsPrimaryKey BIT,
    IsUnique BIT,
    DropStatement NVARCHAR(MAX)
);

INSERT INTO ##IndexesBackup
SELECT 
    QUOTENAME(SCHEMA_NAME(t.schema_id)) + '.' + QUOTENAME(t.name) AS TableName,
    i.name AS IndexName,
    CASE 
        WHEN i.is_primary_key = 1 THEN 
            'ALTER TABLE ' + QUOTENAME(SCHEMA_NAME(t.schema_id)) + '.' + QUOTENAME(t.name) + 
            ' ADD CONSTRAINT ' + QUOTENAME(i.name) + ' PRIMARY KEY ' +
            CASE i.TYPE WHEN 1 THEN 'CLUSTERED ' ELSE 'NONCLUSTERED ' END +
            ' (' + key_col.columns + ')'
        WHEN i.is_unique_constraint = 1 THEN
            'ALTER TABLE ' + QUOTENAME(SCHEMA_NAME(t.schema_id)) + '.' + QUOTENAME(t.name) + 
            ' ADD CONSTRAINT ' + QUOTENAME(i.name) + ' UNIQUE ' +
            CASE i.TYPE WHEN 1 THEN 'CLUSTERED ' ELSE 'NONCLUSTERED ' END +
            ' (' + key_col.columns + ')'
        ELSE 
            'CREATE ' + 
            CASE WHEN i.is_unique = 1 THEN 'UNIQUE ' ELSE '' END +
            CASE i.TYPE 
                WHEN 1 THEN 'CLUSTERED '
                WHEN 2 THEN 'NONCLUSTERED '
            END + ' INDEX ' + QUOTENAME(i.name) + ' ON ' + 
            QUOTENAME(SCHEMA_NAME(t.schema_id)) + '.' + QUOTENAME(t.name) + 
            ' (' + key_col.columns + ')' +
            CASE WHEN include_col.columns IS NOT NULL THEN ' INCLUDE (' + include_col.columns + ')' ELSE '' END
    END AS IndexDefinition,
    i.is_primary_key,
    i.is_unique_constraint,
    CASE 
        WHEN i.is_primary_key = 1 OR i.is_unique_constraint = 1 THEN
            'ALTER TABLE ' + QUOTENAME(SCHEMA_NAME(t.schema_id)) + '.' + QUOTENAME(t.name) + 
            ' DROP CONSTRAINT ' + QUOTENAME(i.name)
        ELSE 
            'DROP INDEX ' + QUOTENAME(i.name) + ' ON ' + QUOTENAME(SCHEMA_NAME(t.schema_id)) + '.' + QUOTENAME(t.name)
    END AS DropStatement
FROM sys.indexes i
INNER JOIN sys.tables t ON i.object_id = t.object_id
CROSS APPLY (
    SELECT STUFF((
        SELECT ', ' + QUOTENAME(c.name)
        FROM sys.index_columns ic
        JOIN sys.columns c ON ic.object_id = c.object_id AND ic.column_id = c.column_id
        WHERE ic.object_id = i.object_id AND ic.index_id = i.index_id AND ic.is_included_column = 0
        ORDER BY ic.key_ordinal
        FOR XML PATH('')
    ), 1, 2, '') AS columns
) key_col
LEFT JOIN (
    SELECT i2.object_id, i2.index_id, STRING_AGG(QUOTENAME(c.name), ', ') AS columns
    FROM sys.index_columns ic
    JOIN sys.columns c ON ic.object_id = c.object_id AND ic.column_id = c.column_id
    JOIN sys.indexes i2 ON ic.object_id = i2.object_id AND ic.index_id = i2.index_id
    WHERE ic.is_included_column = 1
    GROUP BY i2.object_id, i2.index_id
) include_col ON i.object_id = include_col.object_id AND i.index_id = include_col.index_id
WHERE i.TYPE IN (1,2) -- Only clustered and nonclustered indexes
AND EXISTS (
    SELECT 1 
    FROM sys.index_columns ic2
    JOIN sys.columns c ON ic2.object_id = c.object_id AND ic2.column_id = c.column_id
    WHERE ic2.object_id = i.object_id 
    AND ic2.index_id = i.index_id
    AND c.is_computed = 1
);
GO

-- Step 6: Drop all dependent indexes and constraints
PRINT 'Dropping dependent indexes and constraints...';
DECLARE @DropIndexes NVARCHAR(MAX) = '';
SELECT @DropIndexes += DropStatement + ';' + CHAR(13)
FROM ##IndexesBackup
ORDER BY IsPrimaryKey DESC, IsUnique DESC;

IF @DropIndexes <> ''
BEGIN
    PRINT 'Executing drop commands:';
    PRINT @DropIndexes;
    EXEC sp_executesql @DropIndexes;
END
GO

-- Step 7: Backup and Drop Computed and regular columns
PRINT 'Backing up computed columns and regular columns...';
IF OBJECT_ID('tempdb..##ComputedColumnsBackup') IS NOT NULL DROP TABLE ##ComputedColumnsBackup;
CREATE TABLE ##ComputedColumnsBackup (
    TableName NVARCHAR(255),
    ColumnName NVARCHAR(255),
    Definition NVARCHAR(MAX),
    IsComputed BIT,
    OrdinalPosition INT
);

INSERT INTO ##ComputedColumnsBackup (TableName, ColumnName, Definition, IsComputed, OrdinalPosition)
SELECT 
    QUOTENAME(SCHEMA_NAME(t.schema_id)) + '.' + QUOTENAME(t.name) AS TableName,
    QUOTENAME(c.name) AS ColumnName,
    cc.definition AS Definition,
    1 AS IsComputed,
    c.column_id AS OrdinalPosition
FROM sys.computed_columns cc
JOIN sys.columns c ON cc.object_id = c.object_id AND cc.column_id = c.column_id
JOIN sys.tables t ON cc.object_id = t.object_id;

-- Also backup regular columns
INSERT INTO ##ComputedColumnsBackup (TableName, ColumnName, Definition, IsComputed, OrdinalPosition)
SELECT 
    QUOTENAME(SCHEMA_NAME(t.schema_id)) + '.' + QUOTENAME(t.name) AS TableName,
    QUOTENAME(c.name) AS ColumnName,
    'CAST(' + QUOTENAME(c.name) + ' AS ' + 
    CASE WHEN typ.name IN ('char', 'varchar', 'nchar', 'nvarchar')
         THEN typ.name + '(' + 
              CASE WHEN c.max_length = -1 
                   THEN 'MAX'
                   ELSE CAST(CASE WHEN typ.name LIKE 'n%' 
                                 THEN c.max_length/2 
                                 ELSE c.max_length 
                            END AS VARCHAR(10))
              END + ')'
         ELSE typ.name
    END + ')' AS Definition,
    0 AS IsComputed,
    c.column_id AS OrdinalPosition
FROM sys.columns c
JOIN sys.tables t ON c.object_id = t.object_id
JOIN sys.types typ ON c.user_type_id = typ.user_type_id
WHERE c.is_computed = 0;

PRINT 'Backed up all columns:';
SELECT * FROM ##ComputedColumnsBackup ORDER BY TableName, OrdinalPosition;
GO

PRINT 'Dropping computed columns...';
DECLARE @DropComputedColumns NVARCHAR(MAX) = '';
SELECT @DropComputedColumns += 'ALTER TABLE ' + TableName + ' DROP COLUMN ' + ColumnName + ';' + CHAR(13)
FROM ##ComputedColumnsBackup
WHERE IsComputed = 1;

IF @DropComputedColumns <> ''
BEGIN
    PRINT 'Executing drop commands:';
    PRINT @DropComputedColumns;
    EXEC sp_executesql @DropComputedColumns;
END
GO

-- Step 8: Drop Other Schema-Bound Objects
PRINT 'Dropping other schema-bound objects...';

-- Drop views that may depend on the collation
DECLARE @DropViews NVARCHAR(MAX) = '';

SELECT @DropViews += 'DROP VIEW ' + QUOTENAME(s.name) + '.' + QUOTENAME(o.name) + ';' + CHAR(13)
FROM sys.objects o
JOIN sys.schemas s ON o.schema_id = s.schema_id
WHERE o.type IN ('V')  -- Only views
AND o.is_ms_shipped = 0;  -- Exclude system views

IF @DropViews <> ''
BEGIN
    PRINT 'Executing drop commands for views:';
    PRINT @DropViews;
    EXEC sp_executesql @DropViews;  -- Execute the drop commands
END
GO

-- Step 9: Change Database Collation
PRINT 'Changing database collation...';
-- Declare variables again after GO
DECLARE @DatabaseName NVARCHAR(255);
DECLARE @CollationName NVARCHAR(255);
DECLARE @SQL NVARCHAR(MAX);

-- Retrieve variables again after GO
SELECT @DatabaseName = VariableValue FROM ##TempVariables WHERE VariableName = 'DatabaseName';
SELECT @CollationName = VariableValue FROM ##TempVariables WHERE VariableName = 'CollationName';

SET @SQL = 'ALTER DATABASE ' + QUOTENAME(@DatabaseName) + ' SET SINGLE_USER WITH ROLLBACK IMMEDIATE;';
EXEC sp_executesql @SQL;  -- Execute the command

SET @SQL = 'ALTER DATABASE ' + QUOTENAME(@DatabaseName) + ' COLLATE ' + @CollationName + ';';
EXEC sp_executesql @SQL;  -- Execute the command

SET @SQL = 'ALTER DATABASE ' + QUOTENAME(@DatabaseName) + ' SET MULTI_USER;';
EXEC sp_executesql @SQL;  -- Execute the command
GO

-- Step 10: Recreate Computed Columns
PRINT 'Recreating computed columns...';
DECLARE @RecreateComputedColumns NVARCHAR(MAX) = '';

SELECT @RecreateComputedColumns += 'ALTER TABLE ' + TableName + ' ADD ' + ColumnName + ' AS ' + Definition + ';' + CHAR(13)
FROM ##ComputedColumnsBackup
WHERE IsComputed = 1
ORDER BY TableName, OrdinalPosition;  -- Ensure the order is preserved

IF @RecreateComputedColumns <> ''
BEGIN
    PRINT 'Executing recreate commands for computed columns:';
    PRINT @RecreateComputedColumns;
    EXEC sp_executesql @RecreateComputedColumns;  -- Execute the recreate commands
END
GO

-- Step 11: Recreate indexes and constraints
PRINT 'Recreating indexes and constraints...';
DECLARE @RecreateIndexes NVARCHAR(MAX) = '';
SELECT @RecreateIndexes += IndexDefinition + ';' + CHAR(13)
FROM ##IndexesBackup
ORDER BY IsPrimaryKey ASC, IsUnique ASC;

-- Check for NULL or empty string
IF @RecreateIndexes IS NOT NULL AND @RecreateIndexes <> ''
BEGIN
    EXEC sp_executesql @RecreateIndexes;
END
GO

-- Step 12: Recreate Schema-Bound Objects
PRINT 'Recreating schema-bound objects...';
DECLARE @recreate_deps_sql NVARCHAR(MAX);
DECLARE deps_cursor CURSOR FOR 
SELECT Definition
FROM ##BackupSchemaBoundObjects;

OPEN deps_cursor;
FETCH NEXT FROM deps_cursor INTO @recreate_deps_sql;

WHILE @@FETCH_STATUS = 0
BEGIN
    BEGIN TRY
        EXEC sp_executesql @recreate_deps_sql;
    END TRY
    BEGIN CATCH
        PRINT 'Error recreating object: ' + ERROR_MESSAGE();
    END CATCH
    FETCH NEXT FROM deps_cursor INTO @recreate_deps_sql;
END

CLOSE deps_cursor;
DEALLOCATE deps_cursor;
PRINT 'Schema-bound objects recreation completed.';
GO

-- Step 13: Cleanup Temporary Tables
DROP TABLE IF EXISTS ##BackupSchemaBoundObjects;
DROP TABLE IF EXISTS ##ComputedColumnsBackup;
DROP TABLE IF EXISTS ##IndexesBackup;
DROP TABLE IF EXISTS ##TempVariables;
PRINT 'Script completed successfully.';
GO
