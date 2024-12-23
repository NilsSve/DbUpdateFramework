-- Step 1: Query the default backup folder path
DECLARE @BackupPath NVARCHAR(255);
DECLARE @DataPath NVARCHAR(255);
DECLARE @LogPath NVARCHAR(255);
DECLARE @BackupFile NVARCHAR(255);
DECLARE @RestoreCommand NVARCHAR(MAX);
DECLARE @LogicalDataFile NVARCHAR(128);
DECLARE @LogicalLogFile NVARCHAR(128);

-- Query the default backup folder path
EXEC master.dbo.xp_instance_regread
    N'HKEY_LOCAL_MACHINE',
    N'Software\Microsoft\MSSQLServer\MSSQLServer',
    N'BackupDirectory',
    @BackupPath OUTPUT;

-- Check for errors
IF (@BackupPath IS NULL)
BEGIN
    RAISERROR('Failed to get the BackupDirectory path', 16, 1);
    RETURN;
END

-- Construct the backup file path
SET @BackupFile = @BackupPath + '\ROW_TESTOld.bak';

-- Get the logical file names from the backup
DECLARE @FileList TABLE (
    LogicalName NVARCHAR(128),
    PhysicalName NVARCHAR(260),
    Type CHAR(1),
    FileGroupName NVARCHAR(128),
    Size BIGINT,
    MaxSize BIGINT,
    FileId INT,
    CreateLSN NUMERIC(25,0),
    DropLSN NUMERIC(25,0),
    UniqueId UNIQUEIDENTIFIER,
    ReadOnlyLSN NUMERIC(25,0),
    ReadWriteLSN NUMERIC(25,0),
    BackupSizeInBytes BIGINT,
    SourceBlockSize INT,
    FileGroupId INT,
    LogGroupGUID UNIQUEIDENTIFIER,
    DifferentialBaseLSN NUMERIC(25,0),
    DifferentialBaseGUID UNIQUEIDENTIFIER,
    IsReadOnly BIT,
    IsPresent BIT,
    TDEThumbprint VARBINARY(32));

INSERT INTO @FileList
EXEC('RESTORE FILELISTONLY FROM DISK = ''' + @BackupFile + '''');

SELECT @LogicalDataFile = LogicalName FROM @FileList WHERE Type = 'D';
SELECT @LogicalLogFile = LogicalName FROM @FileList WHERE Type = 'L';

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

-- Extract the data and log paths from the SQL arguments
SET @DataPath = REVERSE(SUBSTRING(REVERSE(@DataPath), CHARINDEX('\', REVERSE(@DataPath)) + 1, LEN(@DataPath)));
SET @LogPath = REVERSE(SUBSTRING(REVERSE(@LogPath), CHARINDEX('\', REVERSE(@LogPath)) + 1, LEN(@LogPath)));

-- Construct the restore command
SET @RestoreCommand = N'
RESTORE DATABASE ROW_TEST
FROM DISK = ''' + @BackupFile + '''
WITH REPLACE,
MOVE ''' + @LogicalDataFile + ''' TO ''' + @DataPath + 'ROW_TEST.mdf'',
MOVE ''' + @LogicalLogFile + ''' TO ''' + @LogPath + 'ROW_TEST_log.ldf'';
';

-- Execute the restore command
BEGIN TRY
    EXEC sp_executesql @RestoreCommand;
    -- Set the database back to multi-user mode
    ALTER DATABASE ROW_TEST
    SET MULTI_USER;
END TRY
BEGIN CATCH
    PRINT 'Error: ' + ERROR_MESSAGE();
END CATCH;
GO