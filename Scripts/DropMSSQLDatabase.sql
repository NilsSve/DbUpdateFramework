-- Step 1: Close existing connections and drop the existing database
USE master;
GO

DECLARE @DatabaseName NVARCHAR(255);
SET @DatabaseName = 'ROW_TEST'
ALTER DATABASE (@DatabaseName)
SET SINGLE_USER WITH ROLLBACK IMMEDIATE;
GO
DECLARE @DatabaseName NVARCHAR(255);
SET @DatabaseName = 'ROW_TEST'
DROP DATABASE QUOTENAME(@DatabaseName);
GO

