-- Step 1: Query the default backup folder path
DECLARE @BackupPath NVARCHAR(255);
DECLARE @DataPath NVARCHAR(255);
DECLARE @LogPath NVARCHAR(255);
DECLARE @BackupFile NVARCHAR(255);
DECLARE @RestoreCommand NVARCHAR(MAX);

EXEC master.dbo.xp_instance_regread
    N'HKEY_LOCAL_MACHINE',
    N'Software\Microsoft\MSSQLServer\MSSQLServer',
    N'BackupDirectory',
    @BackupPath OUTPUT;

-- Query the default data and log file paths
EXEC master.dbo.xp_instance_regread
    N'HKEY_LOCAL_MACHINE',
    N'Software\Microsoft\MSSQLServer\MSSQLServer\Parameters',
    N'SQLArg0',
    @DataPath OUTPUT;

EXEC master.dbo.xp_instance_regread
    N'HKEY_LOCAL_MACHINE',
    N'Software\Microsoft\MSSQLServer\MSSQLServer\Parameters',
    N'SQLArg1',
    @LogPath OUTPUT;

-- Construct the backup file path
SET @BackupFile = @BackupPath + '\ROW_TESTOld.bak';

-- Construct the restore command
SET @RestoreCommand = N'
RESTORE DATABASE ROW_TEST
FROM DISK = ''' + @BackupFile + '''
WITH REPLACE,
MOVE ''ROW_TEST'' TO ''' + @DataPath + '\ROW_TEST.mdf'',
MOVE ''ROW_TEST_log'' TO ''' + @LogPath + '\ROW_TEST_log.ldf'';
';

-- Execute the restore command
EXEC sp_executesql @RestoreCommand;
GO

-- Set the database back to multi-user mode
ALTER DATABASE ROW_TEST
SET MULTI_USER;
GO
