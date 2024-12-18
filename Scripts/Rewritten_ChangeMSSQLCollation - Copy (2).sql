-- Initialize the temporary table to store variables
IF OBJECT_ID('tempdb..##TempVariables') IS NOT NULL
    DROP TABLE ##TempVariables;

CREATE TABLE ##TempVariables (
    VariableName NVARCHAR(255),
    VariableValue NVARCHAR(MAX)
);

-- Insert variable values
INSERT INTO ##TempVariables (VariableName, VariableValue)
VALUES
    ('DatabaseName', 'ROW_TEST'),
    ('CollationName', 'SQL_Latin1_General_CP1_CI_AS'),
    ('ShouldBackup', '0');

GO

-- Retrieve variables into local variables for the current batch
DECLARE @DatabaseName NVARCHAR(255);
DECLARE @CollationName NVARCHAR(255);
DECLARE @ShouldBackup BIT;
DECLARE @SQL NVARCHAR(MAX);

SELECT @DatabaseName = VariableValue FROM ##TempVariables WHERE VariableName = 'DatabaseName';
SELECT @CollationName = VariableValue FROM ##TempVariables WHERE VariableName = 'CollationName';
SELECT @ShouldBackup = CAST(VariableValue AS BIT) FROM ##TempVariables WHERE VariableName = 'ShouldBackup';

SET NOCOUNT ON;

-- Step 1: Backup Computed Columns that start with U_
PRINT 'Backing up computed columns that start with U_...';

IF OBJECT_ID('tempdb..##ComputedColumnsBackup') IS NOT NULL DROP TABLE ##ComputedColumnsBackup;
CREATE TABLE ##ComputedColumnsBackup (
    TableName NVARCHAR(255),
    ColumnName NVARCHAR(255),
    Definition NVARCHAR(MAX),
    IsComputed BIT
);

INSERT INTO ##ComputedColumnsBackup (TableName, ColumnName, Definition, IsComputed)
SELECT 
    QUOTENAME(SCHEMA_NAME(t.schema_id)) + '.' + QUOTENAME(t.name) AS TableName,
    QUOTENAME(c.name) AS ColumnName,
    cc.definition AS Definition,
    1 AS IsComputed
FROM sys.computed_columns cc
JOIN sys.columns c ON cc.object_id = c.object_id AND cc.column_id = c.column_id
JOIN sys.tables t ON cc.object_id = t.object_id
WHERE c.name LIKE 'U_%';  -- Filter for computed columns starting with U_

-- Step 2: Drop Dependencies and Schema-Bound Objects
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

-- Drop computed columns that start with U_
PRINT 'Dropping computed columns that start with U_...';

DECLARE @DropComputedColumns NVARCHAR(MAX) = '';

SELECT @DropComputedColumns += 'ALTER TABLE ' + TableName + ' DROP COLUMN ' + ColumnName + ';' + CHAR(13)
FROM ##ComputedColumnsBackup
WHERE IsComputed = 1;

IF @DropComputedColumns <> ''
BEGIN
    PRINT 'Executing drop commands for computed columns:';
    PRINT @DropComputedColumns;
    EXEC sp_executesql @DropComputedColumns;  -- Execute the drop commands
END

-- Step 3: Change Database Collation
PRINT 'Changing database collation...';

SET @SQL = 'ALTER DATABASE ' + QUOTENAME(@DatabaseName) + ' SET SINGLE_USER WITH ROLLBACK IMMEDIATE;';
EXEC sp_executesql @SQL;  -- Execute the command

SET @SQL = 'ALTER DATABASE ' + QUOTENAME(@DatabaseName) + ' COLLATE ' + @CollationName + ';';
EXEC sp_executesql @SQL;  -- Execute the command

SET @SQL = 'ALTER DATABASE ' + QUOTENAME(@DatabaseName) + ' SET MULTI_USER;';
EXEC sp_executesql @SQL;  -- Execute the command

-- Step 4: Recreate Computed Columns
PRINT 'Recreating computed columns...';

DECLARE @RecreateComputedColumns NVARCHAR(MAX) = '';

SELECT @RecreateComputedColumns += 'ALTER TABLE ' + TableName + ' ADD ' + ColumnName + ' AS ' + Definition + ';' + CHAR(13)
FROM ##ComputedColumnsBackup
WHERE IsComputed = 1
ORDER BY TableName, ColumnName;  -- Ensure the order is preserved

IF @RecreateComputedColumns <> ''
BEGIN
    PRINT 'Executing recreate commands for computed columns:';
    PRINT @RecreateComputedColumns;
    EXEC sp_executesql @RecreateComputedColumns;  -- Execute the recreate commands
END
GO

-- Step 5: Backup Database w today's date and time added to backup name
DECLARE @BackupFileName NVARCHAR(255);
DECLARE @DateTime NVARCHAR(20);
DECLARE @ErrorMessage NVARCHAR(MAX);
DECLARE @ErrorSeverity INT;
DECLARE @ErrorState INT;

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

-- Step 6: Backup Schema-Bound Objects
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

-- Step 7: Drop all dependent indexes and constraints
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

-- Step 8: Cleanup Temporary Tables
DROP TABLE IF EXISTS ##BackupSchemaBoundObjects;
DROP TABLE IF EXISTS ##ComputedColumnsBackup;
DROP TABLE IF EXISTS ##IndexesBackup;
PRINT 'Script completed successfully.';
GO