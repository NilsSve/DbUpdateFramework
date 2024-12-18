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
    ('DatabaseName', 'ROW_TEST'),  -- Replace with your actual database name
    ('CollationName', 'SQL_Latin1_General_CP1_CI_AS'),  -- Replace with your desired collation
    ('ShouldBackup', '0');  -- Set to 1 to enable backup, 0 to disable

GO

-- Step 2: Initialize Backup Control Variable
DECLARE @ShouldBackup BIT;
DECLARE @DatabaseName NVARCHAR(255);
DECLARE @BackupFileName NVARCHAR(255);
DECLARE @DateTime NVARCHAR(20);
DECLARE @SQL NVARCHAR(MAX);

-- Retrieve the database name and backup control variable from the temporary table
SELECT @DatabaseName = VariableValue FROM ##TempVariables WHERE VariableName = 'DatabaseName';
SELECT @ShouldBackup = CAST(VariableValue AS BIT) FROM ##TempVariables WHERE VariableName = 'ShouldBackup';

-- Step 3: Backup Database if ShouldBackup is set
IF @ShouldBackup = 1
BEGIN
    PRINT 'Backing up the database...';

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

-- Step 4: Backup All User-Defined Columns
PRINT 'Backing up all user-defined columns...';

IF OBJECT_ID('tempdb..##ColumnsBackup') IS NOT NULL DROP TABLE ##ColumnsBackup;
CREATE TABLE ##ColumnsBackup (
    TableName NVARCHAR(255),
    ColumnName NVARCHAR(255),
    DataType NVARCHAR(255),
    IsComputed BIT,
    Definition NVARCHAR(MAX)
);

INSERT INTO ##ColumnsBackup (TableName, ColumnName, DataType, IsComputed, Definition)
SELECT 
    QUOTENAME(SCHEMA_NAME(t.schema_id)) + '.' + QUOTENAME(t.name) AS TableName,
    QUOTENAME(c.name) AS ColumnName,
    ty.name AS DataType,
    CASE WHEN cc.object_id IS NOT NULL THEN 1 ELSE 0 END AS IsComputed,
    cc.definition AS Definition
FROM sys.columns c
JOIN sys.tables t ON c.object_id = t.object_id
JOIN sys.types ty ON c.user_type_id = ty.user_type_id
LEFT JOIN sys.computed_columns cc ON c.object_id = cc.object_id AND c.column_id = cc.column_id
WHERE t.is_ms_shipped = 0;  -- Exclude system tables

-- Step 5: Drop All Computed Columns
PRINT 'Dropping all computed columns...';

DECLARE @DropComputedColumns NVARCHAR(MAX) = '';

SELECT @DropComputedColumns += 'ALTER TABLE ' + TableName + ' DROP COLUMN ' + ColumnName + ';' + CHAR(13)
FROM ##ColumnsBackup
WHERE IsComputed = 1;  -- Only drop computed columns

IF @DropComputedColumns <> ''
BEGIN
    PRINT 'Executing drop commands for computed columns:';
    PRINT @DropComputedColumns;
    EXEC sp_executesql @DropComputedColumns;  -- Execute the drop commands
END
GO

-- Step 6: Drop Other Dependencies (Views, etc.)
PRINT 'Dropping other dependencies...';

-- Here you would need to drop any views or other objects that depend on the collation.
-- This part is highly specific to your database schema and needs to be customized.
-- Example:
-- DROP VIEW [YourViewName];

-- Step 7: Change Database Collation
PRINT 'Changing database collation...';

-- Declare variables again after GO
DECLARE @CollationName NVARCHAR(255);
DECLARE @DatabaseName NVARCHAR(255);  -- Re-declare @DatabaseName
DECLARE @SQL NVARCHAR(MAX);  -- Re-declare @SQL

-- Retrieve collation name from the temporary table
SELECT @CollationName = VariableValue FROM ##TempVariables WHERE VariableName = 'CollationName';

-- Retrieve database name from the temporary table
SELECT @DatabaseName = VariableValue FROM ##TempVariables WHERE VariableName = 'DatabaseName';

SET @SQL = 'ALTER DATABASE ' + QUOTENAME(@DatabaseName) + ' SET SINGLE_USER WITH ROLLBACK IMMEDIATE;';
EXEC sp_executesql @SQL;  -- Execute the command

SET @SQL = 'ALTER DATABASE ' + QUOTENAME(@DatabaseName) + ' COLLATE ' + @CollationName + ';';
EXEC sp_executesql @SQL;  -- Execute the command

SET @SQL = 'ALTER DATABASE ' + QUOTENAME(@DatabaseName) + ' SET MULTI_USER;';
EXEC sp_executesql @SQL;  -- Execute the command
GO

-- Step 8: Recreate All User-Defined Columns
PRINT 'Recreating all user-defined columns...';

DECLARE @RecreateColumns NVARCHAR(MAX) = '';

SELECT @RecreateColumns += 
    'ALTER TABLE ' + TableName + 
    ' ADD ' + ColumnName + 
    ' ' + DataType + 
    CASE WHEN IsComputed = 1 THEN ' AS ' + Definition ELSE '' END + ';' + CHAR(13)
FROM ##ColumnsBackup
ORDER BY TableName, ColumnName;  -- Ensure the order is preserved

IF @RecreateColumns <> ''
BEGIN
    PRINT 'Executing recreate commands for columns:';
    PRINT @RecreateColumns;
    EXEC sp_executesql @RecreateColumns;  -- Execute the recreate commands
END
GO