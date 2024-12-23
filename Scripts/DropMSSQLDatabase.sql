-- Step 1: Close existing connections and drop the existing database
USE master;
GO

DECLARE @DatabaseName NVARCHAR(255);
DECLARE @sql NVARCHAR(MAX);

SET @DatabaseName = 'DATABASE_NAME_XXX';

-- Close existing connections
SET @sql = 'ALTER DATABASE ' + QUOTENAME(@DatabaseName) + ' SET SINGLE_USER WITH ROLLBACK IMMEDIATE';
EXEC sp_executesql @sql;

-- Drop the database
SET @sql = 'DROP DATABASE ' + QUOTENAME(@DatabaseName);
EXEC sp_executesql @sql;
GO