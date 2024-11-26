-- Step 1: Backup Notice
-- PRINT 'Ensure you have a full database backup before proceeding!';
GO

-- Step 2: Capture Definitions of Dependent Objects

-- Save captured objects to a temporary table
IF OBJECT_ID('tempdb..#TempObjects') IS NOT NULL DROP TABLE #TempObjects;
CREATE TABLE #TempObjects (ObjectType NVARCHAR(50), Definition NVARCHAR(MAX));

-- Capture views
DECLARE @views NVARCHAR(MAX) = N'';
SELECT @views += OBJECT_DEFINITION(o.object_id) + CHAR(13) + CHAR(13) + 'GO' + CHAR(13)
FROM sys.objects o
WHERE o.type = 'V';

INSERT INTO #TempObjects (ObjectType, Definition)
SELECT 'VIEW', @views;

-- Capture functions
DECLARE @functions NVARCHAR(MAX) = N'';
SELECT @functions += OBJECT_DEFINITION(o.object_id) + CHAR(13) + CHAR(13) + 'GO' + CHAR(13)
FROM sys.objects o
WHERE o.type IN ('FN', 'TF', 'IF'); -- Scalar, Table-Valued, and Inline Functions

INSERT INTO #TempObjects (ObjectType, Definition)
SELECT 'FUNCTION', @functions;

-- Capture computed columns
DECLARE @computed_columns NVARCHAR(MAX) = N'';
SELECT @computed_columns += 'ALTER TABLE ' + QUOTENAME(SCHEMA_NAME(t.schema_id)) + '.' + QUOTENAME(t.name) +
    ' ADD ' + QUOTENAME(c.name) + ' AS ' + c.definition + ';' + CHAR(13) + CHAR(13) + 'GO' + CHAR(13)
FROM sys.computed_columns c
INNER JOIN sys.tables t ON c.object_id = t.object_id;

INSERT INTO #TempObjects (ObjectType, Definition)
SELECT 'COMPUTED_COLUMN', @computed_columns;

-- Capture constraints
DECLARE @constraints NVARCHAR(MAX) = N'';
SELECT @constraints += 'ALTER TABLE ' + QUOTENAME(SCHEMA_NAME(t.schema_id)) + '.' + QUOTENAME(t.name) +
    ' ADD CONSTRAINT ' + QUOTENAME(o.name) + ' ' + OBJECT_DEFINITION(o.object_id) + ';' + CHAR(13) + CHAR(13) + 'GO' + CHAR(13)
FROM sys.objects o
INNER JOIN sys.tables t ON o.parent_object_id = t.object_id
WHERE o.type_desc IN ('CHECK_CONSTRAINT', 'DEFAULT_CONSTRAINT');

INSERT INTO #TempObjects (ObjectType, Definition)
SELECT 'CONSTRAINT', @constraints;

-- Capture indexes
DECLARE @indexes NVARCHAR(MAX) = N'';
SELECT @indexes += 'CREATE ' + 
    CASE WHEN i.is_unique = 1 THEN 'UNIQUE ' ELSE '' END +
    i.type_desc + ' INDEX ' + QUOTENAME(i.name) +
    ' ON ' + QUOTENAME(SCHEMA_NAME(t.schema_id)) + '.' + QUOTENAME(t.name) +
    ' (' + STUFF((SELECT ', ' + QUOTENAME(c.name) + 
                    CASE WHEN ic.is_descending_key = 1 THEN ' DESC' ELSE ' ASC' END
                  FROM sys.index_columns ic
                  INNER JOIN sys.columns c ON ic.object_id = c.object_id AND ic.column_id = c.column_id
                  WHERE ic.object_id = i.object_id AND ic.index_id = i.index_id
                  FOR XML PATH('')), 1, 2, '') + ')' +
    ISNULL(' INCLUDE (' + STUFF((SELECT ', ' + QUOTENAME(c.name)
                  FROM sys.index_columns ic
                  INNER JOIN sys.columns c ON ic.object_id = c.object_id AND ic.column_id = c.column_id
                  WHERE ic.object_id = i.object_id AND ic.index_id = i.index_id AND ic.is_included_column = 1
                  FOR XML PATH('')), 1, 2, '') + ')', '') +
    ';' + CHAR(13) + CHAR(13) + 'GO' + CHAR(13)
FROM sys.indexes i
INNER JOIN sys.tables t ON i.object_id = t.object_id
WHERE i.is_primary_key = 0 AND i.is_unique_constraint = 0;

INSERT INTO #TempObjects (ObjectType, Definition)
SELECT 'INDEX', @indexes;

-- PRINT 'Dependent objects captured (Views, Functions, Computed Columns, Constraints, Indexes).';

-- Step 3: Drop Dependencies

-- Drop views
DECLARE @drop_views NVARCHAR(MAX) = N'';
SELECT @drop_views += 'DROP VIEW ' + QUOTENAME(SCHEMA_NAME(o.schema_id)) + '.' + QUOTENAME(o.name) + ';' + CHAR(13)
FROM sys.objects o
WHERE o.type = 'V';

EXEC sp_executesql @drop_views;

-- Drop functions
DECLARE @drop_functions NVARCHAR(MAX) = N'';
SELECT @drop_functions += 'DROP FUNCTION ' + QUOTENAME(SCHEMA_NAME(o.schema_id)) + '.' + QUOTENAME(o.name) + ';' + CHAR(13)
FROM sys.objects o
WHERE o.type IN ('FN', 'TF', 'IF');

EXEC sp_executesql @drop_functions;

-- Drop computed columns
DECLARE @drop_computed NVARCHAR(MAX) = N'';
SELECT @drop_computed += 'ALTER TABLE ' + QUOTENAME(SCHEMA_NAME(t.schema_id)) + '.' + QUOTENAME(t.name) +
    ' DROP COLUMN ' + QUOTENAME(c.name) + ';' + CHAR(13)
FROM sys.computed_columns c
INNER JOIN sys.tables t ON c.object_id = t.object_id;

EXEC sp_executesql @drop_computed;

-- Drop constraints
DECLARE @drop_constraints NVARCHAR(MAX) = N'';
SELECT @drop_constraints += 'ALTER TABLE ' + QUOTENAME(SCHEMA_NAME(t.schema_id)) + '.' + QUOTENAME(t.name) +
    ' DROP CONSTRAINT ' + QUOTENAME(o.name) + ';' + CHAR(13)
FROM sys.objects o
INNER JOIN sys.tables t ON o.parent_object_id = t.object_id
WHERE o.type_desc IN ('CHECK_CONSTRAINT', 'DEFAULT_CONSTRAINT');

EXEC sp_executesql @drop_constraints;

-- Drop indexes
DECLARE @drop_indexes NVARCHAR(MAX) = N'';
SELECT @drop_indexes += 'DROP INDEX ' + QUOTENAME(i.name) + ' ON ' + QUOTENAME(SCHEMA_NAME(t.schema_id)) + '.' + QUOTENAME(t.name) + ';' + CHAR(13)
FROM sys.indexes i
INNER JOIN sys.tables t ON i.object_id = t.object_id
WHERE i.is_primary_key = 0 AND i.is_unique_constraint = 0;

EXEC sp_executesql @drop_indexes;

-- Step 4: Set Database to SINGLE_USER and Change Collation
USE master;
GO

ALTER DATABASE DUF_DATABASE_NAME_XXX SET SINGLE_USER WITH ROLLBACK IMMEDIATE;
GO

ALTER DATABASE DUF_DATABASE_NAME_XXX COLLATE DUF_COLLATION_CI_AS_XXX;
GO

ALTER DATABASE DUF_DATABASE_NAME_XXX SET MULTI_USER;
GO

-- Step 5: Update Column Collation
DECLARE @update_columns NVARCHAR(MAX) = N'';
SELECT @update_columns += N'
    ALTER TABLE ' + QUOTENAME(SCHEMA_NAME(t.schema_id)) + '.' + QUOTENAME(t.name) + 
    ' ALTER COLUMN ' + QUOTENAME(c.name) + ' ' + 
    UPPER(tp.name) +
    CASE 
        WHEN tp.name IN ('nchar', 'nvarchar') THEN '(' + 
            CASE 
                WHEN c.max_length = -1 THEN 'MAX' 
                ELSE CAST(c.max_length / 2 AS NVARCHAR(10)) 
            END + ')'
        WHEN tp.name IN ('char', 'varchar') THEN '(' + 
            CASE 
                WHEN c.max_length = -1 THEN 'MAX' 
                ELSE CAST(c.max_length AS NVARCHAR(10)) 
            END + ')'
        ELSE ''
    END + 
    ' COLLATE DUF_COLLATION_CI_AS_XXX ' + 
    CASE WHEN c.is_nullable = 1 THEN 'NULL' ELSE 'NOT NULL' END + ';' + CHAR(13)
FROM sys.columns c
INNER JOIN sys.tables t ON c.object_id = t.object_id
INNER JOIN sys.schemas s ON t.schema_id = s.schema_id
INNER JOIN sys.types tp ON c.user_type_id = tp.user_type_id
WHERE tp.name IN ('char', 'varchar', 'nchar', 'nvarchar')
AND c.collation_name IS NOT NULL
AND c.collation_name <> 'DUF_COLLATION_CI_AS_XXX';

EXEC sp_executesql @update_columns;

-- Step 6: Recreate Dropped Objects
DECLARE @recreate_sql NVARCHAR(MAX);
DECLARE recreate_cursor CURSOR FOR 
SELECT Definition FROM #TempObjects;

OPEN recreate_cursor;
FETCH NEXT FROM recreate_cursor INTO @recreate_sql;

WHILE @@FETCH_STATUS = 0
BEGIN
    EXEC (@recreate_sql); -- Proper batch execution
    FETCH NEXT FROM recreate_cursor INTO @recreate_sql;
END

CLOSE recreate_cursor;
DEALLOCATE recreate_cursor;

-- Cleanup
DROP TABLE #TempObjects;

-- PRINT 'Collation change and object restoration completed successfully.';
GO
