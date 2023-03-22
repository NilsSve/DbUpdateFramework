//*************************************************************************
//*                                                                       *
//*  Confidential Trade Secret.                                           *
//*  Copyright (c) 1997-2014 Mertech Data Systems Inc, Miami Florida      *
//*  All rights reserved.                                                 *
//*  DataFlex is a registered trademark of Data Access Corporation.       *
//*                                                                       *
//*************************************************************************
Use UI
Use SEQ_CHNL.PKG

#REM -----------------------------------------------
#REM Mertech Data Systems Inc. - www.mertechdata.com
#REM mertech.inc Version 3.1.1
#REM -----------------------------------------------

//=============================================================================
// #DEFINE's
//=============================================================================

//Currently Unsupported Attribute
Define DF_FILE_PRIMARY_KEY                          For (DF_FILE_RECORD_REREAD+1)

// TODO: This is probably deprecated. Investigate.
Define DF_FILE_NUMBER_INVERSE_KEYS                  For (DF_FILE_RECORD_REREAD+3)

//=============================================================================
/// @Name        DF_FILE_SET_MODE
/// @Description Allows switching between set-oriented and record oriented fetch modes.
///
/// If DF_FILE_SET_MODE is set to True, the driver will fetch a set of records
/// for each find. If DF_FILE_SET_MODE is False, the driver will fetch only one
/// record at a time. This attribute can also be specified in the .INT file during
/// migration through Flex2SQL. This settings is normally used alongside
/// DF_FILE_MAX_ROWS to set the number of rows to return and DF_FILE_CACHE_MODE
/// to turn on local caching.
///
/// Note: Turning off set-mode can have a detrimental impact on performance. Unless
/// there is a specific reason to do otherwise, this option should be left on.
///
/// Default value: True
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-07-15 by Oliver Nelson
/// @See DF_FILE_MAX_ROWS DF_FILE_CACHE_MODE
/// @INTOPT OPTIMIZE {FOR_SET | ONE_ROW}
///
/// @Syntax Set_Attribute DF_FILE_SET_MODE of {FileNumber} to {variable}
/// @Syntax Get_Attribute DF_FILE_SET_MODE of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Mode for the FileNumber. True for set-mode, False for one-row mode.
/// @Example
/// Open Orderhea
/// Set_Attribute DF_FILE_SET_MODE of Orderhea.File_Number to True
/// Get_Attribute DF_FILE_SET_MODE of Orderhea.File_Number to boolVar
///
Define DF_FILE_SET_MODE                             For (DF_FILE_RECORD_REREAD+5)

//=============================================================================
/// @Name        DF_FILE_DATABASENAME
/// @Description Returns a string containing the name of the database where the
/// table referenced by the passed File Number resides. This is a READ ONLY
/// attribute. Note that because Oracle doesn't support the concept of multiple
/// databases on one server, this attribute is not valid for Oracle.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex, MySQLFlex, PGFlex
/// @VersionNote Last Revised: 2013-07-15 by Oliver Nelson
/// @See
///
/// @Syntax Get_Attribute DF_FILE_DATABASENAME of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Name of the Database
/// @Example
/// Open Orderhea
/// Get_Attribute DF_FILE_DATABASENAME of Orderhea.File_Number to strVal
Define DF_FILE_DATABASENAME                         For (DF_FILE_RECORD_REREAD+6)

//=============================================================================
/// @Name        DF_FILE_MAX_ROWS
/// @Description Controls the maximum number of rows retrieved by a Find GT/LT
/// operation. The driver will automatically retrieve and cache this many rows
/// for future find GT/LT operations. Setting this property to a very high
/// value can be inefficient from a UI perspective but may be advisable for
/// local processing of rows (such as in a batch process).
///
/// Default value: 10
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-07-15 by Oliver Nelson
/// @See DF_FILE_SET_MODE DF_FILE_CACHE_MODE
/// @INTOPT MAX_ROWS_TO_QUERY {integer}
///
/// @Syntax Set_Attribute DF_FILE_DATABASENAME of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Attribute Value
/// @Example
/// Open Orderhea
/// Set_Attribute DF_FILE_MAX_ROWS of Orderhea.File_Number to 10
/// Get_Attribute DF_FILE_MAX_ROWS of Orderhea.File_Number to intVal
Define DF_FILE_MAX_ROWS                             For (DF_FILE_RECORD_REREAD+7)

//=============================================================================
/// @Name        DF_FILE_TABLE_NAME
/// @Description Use this attribute to set or get the name of the SQL table
/// corresponding to the specified file number. In a restructure operation
/// this attribute may be used to permanently change the table that a filelist
/// entry is pointing to.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-07-15 by Oliver Nelson
/// @See
/// @INTOPT DATABASE_NAME {string}
///
/// @Syntax Get_Attribute DF_FILE_TABLE_NAME of {FileNumber} to {variable}
/// @Syntax Set_Attribute DF_FILE_TABLE_NAME of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Name of the SQL Table.
/// @Example
/// Open Orderhea
/// Get_Attribute DF_FILE_TABLE_NAME of Orderhea.File_Number to strVal
Define DF_FILE_TABLE_NAME                           For (DF_FILE_RECORD_REREAD+8)

//=============================================================================
/// @Name        DF_FILE_CACHE_MODE
/// @Description Activates or deactivates the local cache for set-oriented searches.
///
/// Through the DF_FILE_CACHE_MODE attribute, we can activate or deactivate the
/// local cache. When the cache is active in a set-oriented search, a fixed
/// number of records are pre-fetched and kept in the local cache. If a record
/// is not found in the local cache, a new set is fetched. The number of records
/// fetched is controlled via the DF_FILE_MAX_ROWS attribute. Set-mode vs. one-row
/// mode is controlled via the DF_FILE_SET_MODE attribute.
///
/// Note: Turning off the cache can have significant detrimental effects on performance.
///
/// Default value: True
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-07-15 by Oliver Nelson
/// @See         DF_FILE_MAX_ROWS DF_FILE_SET_MODE
///
/// @Syntax Set_Attribute DF_FILE_CACHE_MODE of {FileNumber} to {variable}
/// @Syntax Get_Attribute DF_FILE_CACHE_MODE of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Mode for FileNumber. True for active. False for inactive.
/// @Example
/// Open Orderhea
/// Set_Attribute DF_FILE_CACHE_MODE of Orderhea.File_Number to True
/// Get_Attribute DF_FILE_CACHE_MODE of Orderhea.File_Number to boolVal
Define DF_FILE_CACHE_MODE                           For (DF_FILE_RECORD_REREAD+9)

//Currently Unsupported Attribute
Define DF_FILE_STORAGE_BASE                         For (DF_FILE_RECORD_REREAD+10)

//=============================================================================
/// @Name        DF_FILE_STATIC
/// @Description Activates or deactivates a special table mode where all rows
/// from the table are loaded into a local cache. When active, all searches are
/// done in memory and the actual table is not accessed.  The driver does not allow
/// editing of a table in static mode.  This is a very useful feature especially
/// when a table contains configuration or static information used in
/// calculations, (i.e., Tax Rate tables, etc.) By keeping this table locally
/// in memory, network round trips are saved resulting in significant
/// performance improvements. This attribute is also useful for batch
/// processes that make extensive table IO requests for reading static information.
///
/// Note: Because the entire table is loaded into memory, it is inadvisable to use
/// this on very large tables.
///
/// Default value: False
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-07-15 by Oliver Nelson
/// @See
///
/// @Syntax Set_Attribute DF_FILE_STATIC of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Static Mode for FileNumber. True for static. False for dynamic.
/// @Example
/// Open Orderhea
/// Set_Attribute DF_FILE_STATIC of Orderhea.File_Number to True
/// Get_Attribute DF_FILE_STATIC of Orderhea.File_Number to boolVal
Define DF_FILE_STATIC                               For (DF_FILE_RECORD_REREAD+11)

//=============================================================================
/// @Name        DF_FILE_SERVER_NAME
/// @Description Use this attribute to set or get the name of the database server
/// corresponding to the specified file number. In a restructure operation
/// this attribute may be used to permanently change the server that a filelist
/// entry is pointing to.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-07-15 by Oliver Nelson
/// @See
/// @INTOPT SERVER_NAME {string}
///
/// @Syntax Get_Attribute DF_FILE_SERVER_NAME of {FileNumber} to {variable}
/// @Syntax Set_Attribute DF_FILE_SERVER_NAME of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Name of the database server.
/// @Example
/// Open Orderhea
/// Set_Attribute DF_FILE_SERVER_NAME of Orderhea.File_Number to "(localdb)\v11.0"
/// Get_Attribute DF_FILE_SERVER_NAME of Orderhea.File_Number to strVal
Define DF_FILE_SERVER_NAME                          For (DF_FILE_RECORD_REREAD+12)

//=============================================================================
/// @Name        DF_FETCH_FIELD_COUNT
/// @Description This attribute is used to get the number of fields or columns
/// in the given table. Note that this is referring to the columns in the SQL
/// backend and may not necessarily reflect the number of columns in DataFlex.
///
/// This is a readonly attribute.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     MsSQLFlex MySQLFlex
/// @VersionNote Last Revised: 2013-08-14 by Aaron Gulack
/// @See
/// @INTOPT
///
/// @Syntax Get_Attribute DF_FETCH_FIELD_COUNT of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Name of the Tablespace.
/// @Example

/// Get_Attribute DF_FETCH_FIELD_COUNT of hFile To "INDXS"
Define DF_FETCH_FIELD_COUNT                         For (DF_FILE_RECORD_REREAD+13)

//=============================================================================
/// @Name        DF_FILE_TABLESPACE_NAME
/// @Description A tablespace is a container of segments (objects that have an
/// allotted amount of space), i.e. tables and indexes. This attribute is
/// used to get or set the name of the tablespace being used for the data tables.
/// To set or get the tablespace name for indexes, use the DF_FILE_INDEXTABLESPACE_NAME
/// attribute. Setting the tablespace name can only be done during a Structure_Start
/// (during table creation).  Getting the name, however can be done at
/// anytime.  Note that when setting the tablespace name, it must be set to an
/// already existing tablespace, this attribute does not create the tablespace itself.
/// Even though MYSQL uses tablespaces, this this attribute is only supported
/// in Oracle and PostgreSQL.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     ORAFlex PGFlex
/// @VersionNote Last Revised: 2013-07-25 by Aaron Gulack
/// @See         DF_FILE_INDEXTABLESPACE_NAME
/// @INTOPT
///
/// @Syntax Get_Attribute DF_FILE_TABLESPACE_NAME of {FileNumber} to {variable}
/// @Syntax Set_Attribute DF_FILE_TABLESPACE_NAME of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Name of the Tablespace.
/// @Example
/// Handle hFile
/// move 0 to hFile
/// Structure_Start hFile "ORA_DRV"
///     Set_Attribute DF_FILE_TABLESPACE_NAME      of hFile To "USERS"
///     Set_Attribute DF_FILE_INDEXTABLESPACE_NAME of hFile To "INDXS"
///
///		// More table creation here
///
/// Structure_End hFile DF_STRUCTEND_OPT_NONE "." 0
Define DF_FILE_TABLESPACE_NAME                      For (DF_FILE_RECORD_REREAD+14)

// TODO: This is probably deprecated. Investigate.
Define DF_FETCH_FIELDNUMBER                         For (DF_FILE_RECORD_REREAD+15)

//=============================================================================
/// @Name        DF_FILE_INDEXTABLESPACE_NAME
/// @Description This attribute is used to get or set the name of the tablespace
/// being used for the index segment of a database. For a description of tablespaces,
/// see the description above for DF_FILE_TABLESPACE_NAME. Similar to the Tablespace
/// name attribute, setting the index tablespace name can only be done during creation
/// and must use an already existing tablespace as the variable. This attribute is
/// only available for Oracle and Postgre.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     ORAFlex PGFlex
/// @VersionNote Last Revised: 2013-07-25 by Aaron Gulack
/// @See         DF_FILE_TABLESPACE_NAME
/// @INTOPT
///
/// @Syntax Get_Attribute DF_FILE_INDEXTABLESPACE_NAME of {File Number} to {variable}
/// @Syntax Set_Attribute DF_FILE_INDEXTABLESPACE_NAME of {File Number} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Name of the Tablespace
/// @Example
/// Handle hFile
/// move 0 to hFile
/// Structure_Start hFile "ORA_DRV"
///     Set_Attribute DF_FILE_TABLESPACE_NAME      of hFile To "USERS"
///     Set_Attribute DF_FILE_INDEXTABLESPACE_NAME of hFile To "INDXS"
///
///		// More table creation here
///		//
/// Structure_End hFile DF_STRUCTEND_OPT_NONE "." 0
Define DF_FILE_INDEXTABLESPACE_NAME                 For (DF_FILE_RECORD_REREAD+16)

//=============================================================================
/// @Name        DF_FILE_RETRIEVE_RECNUM
/// @Description When creating records on a table with RECNUM support, the
/// record number is returned after creation. When this attribute is false, the newly
/// created record's RECNUM is not returned from the server. This could result in a
/// slight performance improvement when many records are being created in a loop.
/// The optimization, however, is negligible.  Having this attribute set to false can
/// have detrimental effects if used improperly; i.e. DD-based saves or UI-based
/// operations. Thus, this should almost always be set to true unless there is a
/// compelling reason to do otherwise.
///
/// Default Value: True
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-07-31 by Aaron Gulack
/// @See
/// @INTOPT
///
/// @Syntax Get_Attribute DF_FILE_RETRIEVE_RECNUM of {FileNumber} to {variable}
/// @Syntax Set_Attribute DF_FILE_RETRIEVE_RECNUM of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Boolean variable. false to not retrieve record number, true otherwise.

/// @Example
/// open ORDERHEA
/// Handle  hFile
/// Boolean bRetrieve
///
/// Set_Attribute DF_FILE_RETRIEVE_RECNUM of hFile to false
/// Get_Attribute DF_FILE_RETRIEVE_RECNUM of hFile To bRetrieve
Define DF_FILE_RETRIEVE_RECNUM                      For (DF_FILE_RECORD_REREAD+17)

//=============================================================================
/// @Name        DF_FILE_NAME_SPACE
/// @Description In Postgres, schemas are objects where all the tables,views and indexes
/// are stored. Separate schemas are used to specify relational data. This attribute is
/// used to set the name of the schema where a table is created. Schema's do not account
/// for any physical space but are merely used as theory to explain the order of a database.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     PGFlex
/// @VersionNote Last Revised: 2013-07-25 by Aaron Gulack
/// @See
/// @INTOPT
///
/// @Syntax Get_Attribute DF_FILE_NAME_SPACE of {FileNumber} to {variable}
/// @Syntax Set_Attribute DF_FILE_NAME_SPACE of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Name of the Schema
/// @Example
/// open ORDERHEA
/// Handle hFile
/// String sSchemaName
///
/// Set_Attribute DF_FILE_NAME_SPACE of hFile to "ORDERHEA"
/// Get_Attribute DF_FILE_NAME_SPACE of hFile To sSchemaName
Define DF_FILE_NAME_SPACE                           For (DF_FILE_RECORD_REREAD+18)

// Currently does not serve any function. May be included in future versions.
Define DF_FILE_STORAGE_PCTFREE                      For (DF_FILE_RECORD_REREAD+19)

// Currently does not serve any function. May be included in future versions.
Define DF_FILE_STORAGE_PCTUSED                      For (DF_FILE_RECORD_REREAD+21)

// Currently does not serve any function. May be included in future versions.
Define DF_FILE_STORAGE_INITIAL                      For (DF_FILE_RECORD_REREAD+23)

// Currently does not serve any function. May be included in future versions.
Define DF_FILE_STORAGE_NEXT                         For (DF_FILE_RECORD_REREAD+25)

// Currently does not serve any function. May be included in future versions.
Define DF_FILE_ALLOW_NULL                           For (DF_FILE_RECORD_REREAD+27)

//=============================================================================
/// @Name        DF_FILE_GET_SERVERNAME_FROM_LOGIN
/// @Description Use this attribute to specify whether the SERVER_NAME option will
/// be included in the INT file.  If set to True, the SERVER_NAME option will not
/// be included in the INT file, if set to false, the SERVER_NAME option will be
/// included in the INT file. This has two uses. The first is during a Structure_Start
/// i.e. table creation/modification. The other is when using the OUTPUT_INT_FILE
/// command. Set this attribute before the OUTPUT_INT_FILE to indicate how the INT
/// file will be written. This name indicates a backwards logic so take note that
/// setting it to true will NOT include the SERVER_NAME in the INT file.
///
/// Default Value: False
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-01 by Aaron Gulack
/// @See         DF_FILE_SUPPRESS_SERVERNAME_OUTPUT
/// @INTOPT		 SERVER_NAME
///
/// @Syntax Get_Attribute DF_FILE_GET_SERVERNAME_FROM_LOGIN of {FileNumber} to {variable}
/// @Syntax Set_Attribute DF_FILE_GET_SERVERNAME_FROM_LOGIN of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Boolean variable. True to not include, false to include in INT.
/// @Example
/// Open Customer
///
/// 	Set_Attribute DF_FILE_GET_SERVERNAME_FROM_LOGIN of Customer.File_Number to True
///
/// 	OUTPUT_INT_FILE for Customer.File_Number to "c:\temp\test.int"
///
/// Close Customer
Define DF_FILE_GET_SERVERNAME_FROM_LOGIN            For (DF_FILE_RECORD_REREAD+29)

//=============================================================================
/// @Name        DF_FILE_SUPPRESS_SERVERNAME_OUTPUT
/// @Description Use this attribute to specify whether the SERVER_NAME option will be included
/// in the INT file.  If set to True, the server name will not be included in the INT file,
/// if set to false, the server name will be included in the INT file. This has two uses.
/// The first is during a Structure_Start i.e. table creation/modification. The other is
/// when using the OUTPUT_INT_FILE command. Set this attribute before the OUTPUT_INT_FILE
/// to indicate how the INT file will be written.
///
/// Default Value: False
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-01 by Aaron Gulack
/// @See         DF_FILE_SUPPRESS_DATABASENAME_OUTPUT DF_FILE_SUPPRESS_SCHEMANAME_OUTPUT
/// @INTOPT		 SERVER_NAME
///
/// @Syntax Get_Attribute DF_FILE_SUPPRESS_SERVERNAME_OUTPUT of {FileNumber} to {variable}
/// @Syntax Set_Attribute DF_FILE_SUPPRESS_SERVERNAME_OUTPUT of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Boolean variable. True to not include, false to include in INT.
/// @Example
/// Open Customer
///
///   Set_Attribute DF_FILE_SUPPRESS_SERVERNAME_OUTPUT of Customer.File_Number to True
///
///   OUTPUT_INT_FILE for Customer.File_Number to "c:\temp\test.int"
///
/// Close Customer
Define DF_FILE_SUPPRESS_SERVERNAME_OUTPUT			For DF_FILE_GET_SERVERNAME_FROM_LOGIN

//=============================================================================
/// @Name        DF_FILE_GET_DATABASENAME_FROM_LOGIN
/// @Description Use this attribute to specify whether the DATABASE_NAME option will
/// be included in the INT file.  If set to True, the DATABASE_NAME option will not
/// be included in the INT file, if set to false, the DATABASE_NAME option will be
/// included in the INT file. This has two uses. The first is during a Structure_Start
/// i.e. table creation/modification. The other is when using the OUTPUT_INT_FILE
/// command. Set this attribute before the OUTPUT_INT_FILE to indicate how the INT
/// file will be written. This name indicates a backwards logic so take note that
/// setting it to true will NOT include the DATABASE_NAME in the INT file.
///
/// Default Value: False
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     PGFlex SQLFlex MySQLFlex
/// @VersionNote Last Revised: 2013-08-01 by Aaron Gulack
/// @See         DF_FILE_SUPPRESS_DATABASENAME_OUTPUT
/// @INTOPT		 DATABASE_NAME
///
/// @Syntax Get_Attribute DF_FILE_GET_DATABASENAME_FROM_LOGIN of {FileNumber} to {variable}
/// @Syntax Set_Attribute DF_FILE_GET_DATABASENAME_FROM_LOGIN of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Boolean variable. True to not include, false to include in INT.
/// @Example
/// Open Customer
///
/// 	Set_Attribute DF_FILE_GET_DATABASENAME_FROM_LOGIN of Customer.File_Number to True
///
/// 	OUTPUT_INT_FILE for Customer.File_Number to "c:\temp\test.int"
///
/// Close Customer
Define DF_FILE_GET_DATABASENAME_FROM_LOGIN          For (DF_FILE_RECORD_REREAD+31)

//=============================================================================
/// @Name        DF_FILE_SUPPRESS_DATABASENAME_OUTPUT
/// @Description Use this attribute to specify whether the DATABASE_NAME option will
/// be included in the INT file.  If set to True, the DATABASE_NAME option will not
/// be included in the INT file, if set to false, the DATABASE_NAME option will be
/// included in the INT file. This has two uses. The first is during a Structure_Start
/// i.e. table creation/modification. The other is when using the OUTPUT_INT_FILE
/// command. Set this attribute before the OUTPUT_INT_FILE to indicate how the INT
/// file will be written. This name indicates a backwards logic so take note that
/// setting it to true will NOT include the DATABASE_NAME in the INT file.
///
/// Default Value: False
///
/// @Assumptions
/// @Status      Public
/// @Drivers     PGFlex SQLFlex MySQLFlex
/// @VersionNote Last Revised: 2013-08-01 by Aaron Gulack
/// @See         DF_FILE_SUPPRESS_SERVERNAME_OUTPUT DF_FILE_SUPPRESS_SCHEMANAME_OUTPUT
/// @INTOPT		 DATABASE_NAME
///
/// @Syntax Get_Attribute DF_FILE_SUPPRESS_DATABASENAME_OUTPUT of {FileNumber} to {variable}
/// @Syntax Set_Attribute DF_FILE_SUPPRESS_DATABASENAME_OUTPUT of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Boolean variable. True to not include, false to include in INT.
/// @Example
/// Open Customer
///
/// 	Set_Attribute DF_FILE_SUPPRESS_DATABASENAME_OUTPUT of Customer.File_Number to True
///
/// 	OUTPUT_INT_FILE for Customer.File_Number to "c:\temp\test.int"
///
/// Close Customer
Define DF_FILE_SUPPRESS_DATABASENAME_OUTPUT			For DF_FILE_GET_DATABASENAME_FROM_LOGIN

//=============================================================================
/// @Name        DF_FILE_GET_SCHEMANAME_FROM_LOGIN
/// @Description Use this attribute to specify whether the SCHEMA_NAME option will
/// be included in the INT file.  If set to True, the SCHEMA_NAME option will not
/// be included in the INT file, if set to false, the SCHEMA_NAME option will be
/// included in the INT file. This has two uses. The first is during a Structure_Start
/// i.e. table creation/modification. The other is when using the OUTPUT_INT_FILE
/// command. Set this attribute before the OUTPUT_INT_FILE to indicate how the INT
/// file will be written. This name indicates a backwards logic so take note that
/// setting it to true will NOT include the SCHEMA_NAME in the INT file.
///
/// Default Value: False
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-01 by Aaron Gulack
/// @See         DF_FILE_SUPPRESS_SCHEMANAME_OUTPUT
/// @INTOPT		 SCHEMA_NAME
///
/// @Syntax Get_Attribute DF_FILE_GET_SCHEMANAME_FROM_LOGIN of {FileNumber} to {variable}
/// @Syntax Set_Attribute DF_FILE_GET_SCHEMANAME_FROM_LOGIN of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Boolean variable. True to not include, false to include in INT.
/// @Example
/// Open Customer
///
/// 	Set_Attribute DF_FILE_GET_SCHEMANAME_FROM_LOGIN of Customer.File_Number to True
///
/// 	OUTPUT_INT_FILE for Customer.File_Number to "c:\temp\test.int"
///
/// Close Customer
Define DF_FILE_GET_SCHEMANAME_FROM_LOGIN            For (DF_FILE_RECORD_REREAD+33)

//=============================================================================
/// @Name        DF_FILE_SUPPRESS_SCHEMANAME_OUTPUT
/// @Description Use this attribute to specify whether the SCHEMA_NAME option will
/// be included in the INT file.  If set to True, the SCHEMA_NAME option will not
/// be included in the INT file, if set to false, the SCHEMA_NAME option will be
/// included in the INT file. This has two uses. The first is during a Structure_Start
/// i.e. table creation/modification. The other is when using the OUTPUT_INT_FILE
/// command. Set this attribute before the OUTPUT_INT_FILE to indicate how the INT
/// file will be written. This name indicates a backwards logic so take note that
/// setting it to true will NOT include the SCHEMA_NAME in the INT file.
///
/// Default Value: False
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-01 by Aaron Gulack
/// @See         DF_FILE_SUPPRESS_DATABASENAME_OUTPUT DF_FILE_SUPPRESS_SERVERNAME_OUTPUT
/// @INTOPT		 SCHEMA_NAME
///
/// @Syntax Get_Attribute DF_FILE_SUPPRESS_SCHEMANAME_OUTPUT of {FileNumber} to {variable}
/// @Syntax Set_Attribute DF_FILE_SUPPRESS_SCHEMANAME_OUTPUT of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Boolean variable. True to not include, false to include in INT.
/// @Example
/// Open Customer
///
/// 	Set_Attribute DF_FILE_SUPPRESS_SCHEMANAME_OUTPUT of Customer.File_Number to True
///
/// 	OUTPUT_INT_FILE for Customer.File_Number to "c:\temp\test.int"
///
/// Close Customer
Define DF_FILE_SUPPRESS_SCHEMANAME_OUTPUT           For DF_FILE_GET_SCHEMANAME_FROM_LOGIN

//TODO
Define DF_FILE_PRESERVE_RECNUM                      For 184

// Currently Unsupported Attribute
Define DF_FILE_NATIVE_RECORD_LENGTH                 For 194

//=============================================================================
/// @Name        DF_FILE_OEM_TRANSLATION
/// @Description There are two sets of code pages used in windows, ANSI and
/// OEM. ANSI is what is commonly used now, but some data still uses the OEM
/// code pages. When migrating data, this attribute is used to determine whether
/// the OEM data will be translated to ANSI during the migration. For example,
/// migrating passwords with special characters may call for different code pages.
/// Setting this attribute to true will convert the OEM data to ANSI, setting it
/// to false will not.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-15 by Aaron Gulack
/// @See
/// @INTOPT
///
/// @Syntax Set_Attribute DF_FILE_OEM_TRANSLATION of {FileNumber} to {variable}
/// @Syntax Get_Attribute DF_FILE_OEM_TRANSLATION of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable         	  Indicates if OEM data will be converted to ANSI. True converts it, false does not.
/// @Example
/// open Customer
///
/// Handle hFile
/// Boolean bTranslate
///
/// Move Customer.File_Number to hFile
///
/// Structure_Start hFile
/// 	Set_Attribute DF_FILE_OEM_TRANSLATION of hFile to True
///    	Get_Attribute DF_FILE_OEM_TRANSLATION of hFile to bTranslate
/// Structure_End hFile
Define DF_FILE_OEM_TRANSLATION                      For (DF_FILE_RECORD_REREAD+51)

//=============================================================================
/// @Name        DF_FILE_EPOCH_YEAR
/// @Description When dealing with two-digit years, an epoch year must be used
/// to determine which century the date is referring to. For example if the
/// epoch year is set to 30, then any two digit year greater than 30 will be
/// considered in the 20th Century, anything less than or equal to 30 will be
/// considered in the 21st Century.  This attribute is used to turn on or off
/// this feature. To use this feature, set this attribute to whatever the epoch
/// year is expected to be. To disable this feature, set this attribute to 0
/// or false. Note that setting this attribute must be done at table creation
/// or inside of a Structure_Start.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-15 by Aaron Gulack
/// @See
/// @INTOPT      EPOCH_YEAR
///
/// @Syntax Set_Attribute DF_FILE_EPOCH_YEAR of {FileNumber} to {variable}
/// @Syntax Get_Attribute DF_FILE_EPOCH_YEAR of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable         	  Indicates what the epoch year is. 0 to disable
/// @Example
/// open Customer
///
/// Handle hFile
/// Boolean bEpoch
///
/// Move Customer.File_Number to hFile
///
/// Structure_Start hFile
/// 	Set_Attribute DF_FILE_EPOCH_YEAR of hFile to 30
///    	Get_Attribute DF_FILE_EPOCH_YEAR of hFile to bEpoch
/// Structure_End hFile
Define DF_FILE_EPOCH_YEAR                           For (DF_FILE_RECORD_REREAD+53)

Define DF_FILE_USE_ROWCOUNT_IN_TRANSACTIONS         For 628
Define DF_FILE_ICF_STATUS                           For 630

//=============================================================================
/// @Name        DF_FILE_LOCK_RECORD_STATUS
/// @Description Table locking is done during transactions to maintain atomicity.
/// In DataFlex, this is usually done with the REREAD/UNLOCK commands. This
/// attribute is used to get the status of a table lock. If a table is currently
/// in a REREAD, or locked, then the attribute will return true. Otherwise, it
/// returns false. It is a read-only attribute so no setting can be done.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-06 by Aaron Gulack
/// @See
/// @INTOPT
///
/// @Syntax Get_Attribute DF_FILE_LOCK_RECORD_STATUS of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable         	  Indicates the status of the file lock
/// @Example
/// open Customer
/// Handle hFile
/// Integer bLocked
///
/// Move Customer.File_Number to hFile
///
/// Get_Attribute DF_FILE_LOCK_RECORD_STATUS of hFile to bLocked
Define DF_FILE_LOCK_RECORD_STATUS                   For 632

//=============================================================================
/// @Name        DF_FILE_CASING
/// @Description Controls the filename and column name casing.
/// You can set this to either keep the file case, force to lower case or force
/// to uppercase.
///
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2014-04-28 by Wil van Antwerpen
/// @See
/// @INTOPT
///
/// @Syntax Set_Attribute DF_FILE_CASING of {FileNumber} to {FILE_CASING_KEEP|FILE_CASING_LOWER|FILE_CASING_UPPER}
/// @Syntax Get_Attribute DF_FILE_CASING of {FileNumber} to {variable}
/// @Param  FileNumber          Number of the file
/// @Param  variable         	  integer set to one of the above values.
/// @Example
/// open Customer
/// Handle hFile
/// Integer eCasing
///
/// Move Customer.File_Number to hFile
///
/// Structure_Start hFile "ORA_DRV"
///    Set_Attribute DF_FILE_CASING of hFile to FILE_CASING_KEEP
/// Structure_End hFile
///
///
/// Get_Attribute DF_FILE_CASING of hFile to eCasing


Define DF_FILE_CASING                               For 634

Define DF_FIELD_INVERSE_KEY_NAME                    For (DF_FIELD_NATIVE_LENGTH+1)
Define DF_FIELD_INVERSE_KEY_TYPE                    For (DF_FIELD_NATIVE_LENGTH+2)

//TODO
Define DF_FIELD_TEXT_SEGMENT_NAME                   For (DF_FIELD_NATIVE_LENGTH+3)

//TODO
Define DF_FIELD_TEXT_NUM_SEGMENTS                   For (DF_FIELD_NATIVE_LENGTH+4)

//=============================================================================
/// @Name        DF_FIELD_DEFAULT_VALUE
/// @Description Use this attribute to get or set the default value for a given column.
/// Setting the default value can only be done during a structure_start or during table
/// creation. If this attribute is not set, it is defaulted to the driver default.
/// See Mertech.cfg
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-06 by Aaron Gulack
/// @See
/// @INTOPT
///
/// @Syntax Set_Attribute DF_FIELD_DEFAULT_VALUE of {FileNumber} {FieldNumber} to {variable}
/// @Syntax Get_Attribute DF_FIELD_DEFAULT_VALUE of {FileNumber} {FieldNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  FieldNumber           Number of the field
/// @Param  variable         	  Variable for the default value of the field
/// @Example
/// open Customer
/// String sDefault
/// Handle hFile
/// Integer iColumn
///
/// Move "California" to sDefault
/// Move Customer.File_Number to hFile
/// Move 3 to iColumn
///
/// Structure_Start hFile "ORA_DRV"
///    Set_Attribute DF_FIELD_DEFAULT_VALUE of hFile iColumn to sDefault
/// Structure_End hFile
///
/// Get_Attribute DF_FIELD_DEFAULT_VALUE of hFile iColumn to sDefault
Define DF_FIELD_DEFAULT_VALUE                       For (DF_FIELD_NATIVE_LENGTH+5)

// Currently Unsupported Attribute
Define DF_FIELD_TEXT_LENGTH_SEGMENT                 For (DF_FIELD_NATIVE_LENGTH+6)

//TODO
//=============================================================================
/// @Name        DF_FIELD_TIME_ON
/// @Description Assign a field to retrieve Time Stamp value from a DATETIME
/// column in a table.
///
/// This option was implemented because some versions of DataFlex do not support
/// DATETIME fields normally supported by SQL databases.
///
/// To use this: Change the type of a date field in your FD to string type,
/// Set the attribute DF_FIELD_TIME_ON of this field to TRUE and
/// recompile your program.
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote
/// @See
///
/// @Syntax Set_Attribute DF_FIELD_TIME_ON of <FileNumber|FileName FieldNumber> to DFTRUE | DFFALSE
/// @Param  FileNumber            Number of the file
/// @Param  FileName              Name of the file
/// @Param  FieldNumber           Number of the field
/// @Example
/// #INCLUDE MERTECH.INC
/// string sDateTime sDatabaseName
/// open ORDERHEA
/// Set_Attribute DF_FIELD_TIME_ON of 30 3 to dfTrue
/// find GE ORDERHEA by recnum
/// move ORDERHEA.ORDER_DATE to sDateTime
/// showln "sDateTime: " sDateTime
Define DF_FIELD_TIME_ON                             For (DF_FIELD_NATIVE_LENGTH+8)

//=============================================================================
/// @Name        DF_FIELD_NATIVE_NAME
/// @Description This attribute is used to get the name of the desired column
/// on the SQL backend. Currently this attribute is ReadOnly and so setting
/// or modifying a column name cannot be done using this attribute.  In most
/// cases, the field name on the SQL backend will be the same as the Dataflex name.
///
/// This is a ReadOnly attribute.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-09 by Aaron Gulack
/// @See
/// @INTOPT
///
/// @Syntax Get_Attribute DF_FIELD_NATIVE_NAME of {FileNumber} {FieldNumber} to {variable}
/// @Param  FileNumber          Number of the file
/// @Param  FieldNumber			Number of the Field
/// @Param  variable			String containing the name of the field
/// @Example
/// Open Customer
///
/// String sName
///
/// Get_Attribute DF_FIELD_NATIVE_NAME of Customer.File_Number 3 to sName
Define DF_FIELD_NATIVE_NAME                         For (DF_FIELD_NATIVE_LENGTH+9)

//=============================================================================
/// @Name        DF_FIELD_NULL
/// @Description Use this attribute to get or set whether a column in a table will
/// allow null values. When set to true, the column accepts null values. Setting
/// this attribute to false will keep it from accepting null values. Although,
/// getting the value of this attribute can be done at anytime, setting it must
/// be done in a Structure_Start or during table creation.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-09 by Aaron Gulack
/// @See
/// @INTOPT
///
/// @Syntax Get_Attribute DF_FIELD_NULL of {FileNumber} {FieldNumber} to {variable}
/// @Syntax Set_Attribute DF_FIELD_NULL of {FileNumber} {FieldNumber} to {variable}
/// @Param  FileNumber          Number of the file
/// @Param  FieldNumber			Number of the Field
/// @Param  variable			Boolean variable
/// @Example
/// Open Customer
/// Handle hFile
/// Integer iColumn
/// Boolean bAllowNull
///
/// Move Customer.File_Number to hFile
/// Move 3 to iColumn
///
/// Structure_Start hFile "ORA_DRV"
///    Set_Attribute DF_FIELD_NULL of hFile iColumn to True
/// Structure_End hFile
///
/// Get_Attribute DF_FIELD_NULL of hFile iColumn to bAllowNull
Define DF_FIELD_NULL                                For (DF_FIELD_NATIVE_LENGTH+10)


//=============================================================================
/// @Name        DF_FIELD_NATIVE_TYPE
/// @Description Use this attribute to get or set the Native type for a specific
/// field in a table.  The native type refers to the data type of the field on the
/// SQL backend. Setting this attribute can only be done during table creation or
/// inside of a Structure_Start. When setting this attribute, it is good practice
/// to use the constants mentioned below instead of the integers. For a list of
/// these constants, refer to the sections: "Oracle Data Types", "MySQL Data Types",
/// "PostgreSQL Data Types", and "SQL Server Data Types" included in this document.
/// Note that when getting the value for this attribute, an integer will be returned
/// so these lists of constants can again prove useful.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-09 by Aaron Gulack
/// @See
/// @INTOPT 	 FIELD_TYPE
///
/// @Syntax Set_Attribute DF_FIELD_NATIVE_TYPE of {FileNumber} {FieldNumber} to {variable}
/// @Syntax Get_Attribute DF_FIELD_NATIVE_TYPE of {FileNumber} {FieldNumber} to {variable}
/// @Param  FileNumber          Number of the file
/// @Param  FieldNumber         Number of the field
/// @Param  variable			variable for the native data type
/// @Example
/// open Customer
///
/// Integer iColumn iType
/// Handle hFile
///
/// Move Customer.File_Number to hFile
/// Structure_Start hFile
/// 	Set_Attribute DF_FIELD_NATIVE_TYPE of hFile iColumn to "eSQLServer_DATE"
///    	Get_Attribute DF_FIELD_NATIVE_TYPE of hFile iColumn to iType
///	Structure_End hFile
Define DF_FIELD_NATIVE_TYPE                         For (DF_FIELD_NATIVE_LENGTH+12)

// Currently Unsupported Attribute (readOnly used by DataFlex 18.0 Studio)
Define DF_FIELD_NATIVE_TYPE_NAME                    For 711

// Currently Unsupported Attribute
Define DF_FIELD_NATIVE_OFFSET                       For (DF_FIELD_NATIVE_LENGTH+14)

//=============================================================================
/// @Name        DF_FIELD_AUTO_INCREMENT
/// @Description Auto incrementing is a technique used in Dataflex usually for
/// fields that are set as the unique identifier. Instead of generating a value
/// or manually inserting data into the column, when a field auto increments,
/// the value of the field increases by one (usually) with each record.  This
/// field is used to get or set whether the field uses this technique or not.
/// The attribute, however, can only be set inside of a Structure_Start or during
/// table creation. Getting the attribute's value can be done at anytime. The
/// value is stored as a boolean, either true or false.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-12 by Aaron Gulack
/// @See
/// @INTOPT 	 FIELD_AUTOINCREMENT_TYPE
///
/// @Syntax Set_Attribute DF_FIELD_AUTO_INCREMENT of {FileNumber} {FieldNumber} to {variable}
/// @Syntax Get_Attribute DF_FIELD_AUTO_INCREMENT of {FileNumber} {FieldNumber} to {variable}
/// @Param  FileNumber          Number of the file
/// @Param  FieldNumber         Number of the field
/// @Param  variable			Boolean variable indicating if the field auto increments.
/// @Example
/// open Customer
///
/// Integer iColumn
/// Boolean bIncrement
/// Handle hFile
///
/// Move Customer.File_Number to hFile
///
/// Structure_Start hFile
/// 	Set_Attribute DF_FIELD_AUTO_INCREMENT of hFile iColumn to True
///    	Get_Attribute DF_FIELD_AUTO_INCREMENT of hFile iColumn to bIncrement
///	Structure_End hFile
Define DF_FIELD_AUTO_INCREMENT                      For (DF_FIELD_NATIVE_LENGTH+16)

//Currently Unsupported Attribute
Define DF_FIELD_GENERATE_ALWAYS                     For (DF_FIELD_NATIVE_LENGTH+18)

// Currently Unsupported Attribute
Define DF_FIELD_SEND_LONG_DATA                      For 702

//=============================================================================
/// @Name        DF_INDEX_NATIVE_CREATED
/// @Description Use this attribute to verify if the index that maps to the DataFlex
/// index was created correctly at the SQL backend
///
/// This is a ReadOnly attribute
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2014-04-30 by Wil van Antwerpen
/// @See
/// @INTOPT
///
/// @Syntax Get_Attribute DF_INDEX_NATIVE_CREATED of {FileNumber} {IndexNumber} to variable
/// @Param  FileNumber            Number of the file
/// @Param  IndexNumber           Number of the index
/// @Param  variable              True if created, false if not
/// @Example
/// Open Customer
///
/// Handle  hFile
/// Integer iIndex
/// Boolean bCreated
///
/// Move Customer.File_Number to hFile
/// Move 1 To iIndex
/// Get_Attribute DF_INDEX_NATIVE_CREATED of hFile iIndex to bCreated
Define DF_INDEX_NATIVE_CREATED                      For (DF_INDEX_KEY_LENGTH+1)

//=============================================================================
/// @Name        DF_INDEX_NAME
/// @Description Use this attribute to get the name of the index on the SQL backend
/// that maps to the numbered index in Dataflex.  This is because, unlike Dataflex,
/// all indexes in SQL are stored as names, not numbers. Since this attribute is
/// currently only a ReadOnly attribute, it can not be used to set or modify a named
/// index.
///
/// This is a ReadOnly attribute
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-09 by Aaron Gulack
/// @See
/// @INTOPT
///
/// @Syntax Get_Attribute DF_INDEX_NAME of {FileNumber} {IndexNumber} to variable
/// @Param  FileNumber            Number of the file
/// @Param  IndexNumber           Number of the index
/// @Param  variable              Name of the index
/// @Example
///
/// Integer iFile iIndex iIndexes
///
/// Open Orderhea
/// Move Orderhea.File_Number to iFile
/// Get_Attribute DF_FILE_LAST_INDEX_NUMBER of iFile to iIndexes
///
/// For iIndex From 0 to iIndexes
///     Get_Attribute DF_INDEX_NAME of iFile iIndex to sIndexName
///     Showln "Orderhea.Index." iIndex " : " sIndexName
/// Loop
Define DF_INDEX_NAME                                For (DF_INDEX_KEY_LENGTH+2)

//=============================================================================
/// @Name        DF_PRIMARY_KEY
/// @Description This attribute is used to get or set the index number
/// being used for the primary key. Getting the index number can be
/// done at any time, but setting the index must be during a
/// Structure_Start or during table creation.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-09 by Aaron Gulack
/// @See		 DF_INDEX_PRIMARY_KEY
/// @INTOPT
///
/// @Syntax Get_Attribute DF_PRIMARY_KEY of {FileNumber} to {variable}
/// @Syntax Set_Attribute DF_PRIMARY_KEY of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Index number being used with primary key
/// @Example
/// Open Customer
///
/// Integer iKey
/// Handle hFile
///
/// Move Customer.File_Number to hFile
///
/// Structure_Start hFile
/// 	Set_Attribute DF_PRIMARY_KEY of hFile to 2
/// 	Get_Attribute DF_PRIMARY_KEY of hFile to iKey
/// Structure_End hFile
Define DF_PRIMARY_KEY                               For (DF_INDEX_KEY_LENGTH+3)

//=============================================================================
/// @Name        DF_INDEX_PRIMARY_KEY
/// @Description This attribute is used to get or set the index number
/// being used for the primary key. Getting the index number can be
/// done at any time, but setting the index must be during a
/// Structure_Start or during table creation.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-09 by Aaron Gulack
/// @See
/// @INTOPT		 PRIMARY_KEY
///
/// @Syntax Get_Attribute DF_INDEX_PRIMARY_KEY of {FileNumber} to {variable}
/// @Syntax Set_Attribute DF_INDEX_PRIMARY_KEY of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable              Index number being used with primary key
/// @Example
/// Open Customer
///
/// Integer iKey
/// Handle hFile
///
/// Move Customer.File_Number to hFile
///
/// Structure_Start hFile
/// 	Set_Attribute DF_INDEX_PRIMARY_KEY of hFile to 2
/// 	Get_Attribute DF_INDEX_PRIMARY_KEY of hFile to iKey
/// Structure_End hFile
Define DF_INDEX_PRIMARY_KEY                         For (DF_INDEX_KEY_LENGTH+3)

//=============================================================================
/// @Name        DF_INDEX_STATUS
/// @Description Oracle has an attribute for indexes called "STATUS" which indicates
/// whether or not an index is valid for use. This attribute can only be used to get
/// the value of the "STATUS" property in Oracle. It currently does not support setting
/// the attribute. The two values for this attribute are "VALID" or "UNUSABLE".
///
/// This is a ReadOnly attribute
///
/// @Assumptions
/// @Status      Public
/// @Drivers     ORAFlex
/// @VersionNote Last Revised: 2013-08-09 by Aaron Gulack
/// @See
/// @INTOPT
///
/// @Syntax Get_Attribute DF_INDEX_STATUS of {FileNumber} {IndexNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  FieldNumber           Number of the index
/// @Param  variable           	  String indicating validity
/// @Example
/// Open Customer
///
/// String sIndexStatus
///
/// Get_Attribute DF_INDEX_STATUS of Customer.File_Number 1 to sIndexStatus
Define DF_INDEX_STATUS                              For (DF_INDEX_KEY_LENGTH+4)

//Currently Unsupported Attribute
Define DF_INDEX_STORAGE_PCTFREE                     For (DF_INDEX_KEY_LENGTH+5)

//=============================================================================
/// @Name        DF_INDEX_UNIQUE
/// @Description An index on a column that is unique is considered so if it
/// does not have two equal values in that column in two different rows. This
/// attribute is used to find out whether or not the specified index is unique.
/// If it is, this attribute will return "U" indicating that it is indeed unique.
/// This is important to note because when getting the value of this attribute,
/// a string variable must be used. Since this is a ReadOnly attribute, setting
/// an idex to unique cannot be done with this attribute.
///
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-14 by Aaron Gulack
/// @See
/// @INTOPT
///
/// @Syntax Get_Attribute DF_INDEX_UNIQUE of {FileNumber} {IndexNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  FieldNumber           Number of the index
/// @Param  variable           	  String indicating if unique
/// @Example
/// Open Customer
///
/// String sIndexUnique
///
/// Get_Attribute DF_INDEX_UNIQUE of Customer.File_Number 1 to sIndexUnique
Define DF_INDEX_UNIQUE                              For (DF_INDEX_KEY_LENGTH+6)

//Currently Unsupported Attribute
Define DF_INDEX_STORAGE_BASE                        For (DF_INDEX_KEY_LENGTH+7)

//Currently Unsupported Attribute
Define DF_INDEX_STORAGE_INITIAL                     For (DF_INDEX_KEY_LENGTH+8)

//Currently Unsupported Attribute
Define DF_INDEX_STORAGE_NEXT                        For (DF_INDEX_KEY_LENGTH+10)

//Currently Unsupported Attribute
Define DF_INDEX_NATIVE_TYPE                         For (DF_INDEX_KEY_LENGTH+13)

//TODO
Define DF_INDEX_TABLESPACE                          For (DF_INDEX_KEY_LENGTH+14)

//TODO
Define DF_FIELD_PROGRAMMATIC_DEFAULT                For 701
Define DF_FIELD_TIME                                For 703
Define DF_FIELD_IS_NULL                             For 704

//=============================================================================
/// @Name        DF_FIELD_IS_LOB
/// @Description In databases a LOB data type is any type that is considered
/// a "Large Object" i.e. XML types, Binary types etc.  This attribute is a
/// ReadOnly attribute used to indicate whether the given field is considered
/// a LOB data type. Since it is ReadOnly, this attribute cannot set a field
/// to a LOB data type.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-13 by Aaron Gulack
/// @See
/// @INTOPT
///
/// @Syntax Get_Attribute DF_FIELD_IS_LOB of {FileNumber} {FieldNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param	FieldNumber			  Number of the field
/// @Param  variable           	  Boolean variable indicating if LOB
/// @Example
/// Open Customer
///
/// Boolean bIsLOB
///
/// Get_Attribute DF_FIELD_IS_LOB of Customer.File_Number 6 to bIsLOB
Define DF_FIELD_IS_LOB                              For 706
Define DF_FIELD_DEFAULT_FUNCTION                    For 707

//Currently Unsupported Attribute
Define DF_FIELD_HANDLE_AS_LOB                       For 708

//TODO
Define DF_FIELD_PARTIAL_OVERLAP                     For 710

//=============================================================================
/// @Name        DF_FILE_NUMBER_SQL_RELATIONS
/// @Description This attribute is used to get the number of foreign keys
/// for a given table on the SQL backend. Foreign keys are used to specify
/// relationships between tables. Since this attribute is ReadOnly, it cannot
/// be used to set the number of foreign keys in a table.  Note that this
/// attribute returns only the number of foreign keys, no other information
/// is provided with this attribute.
///
/// This is a ReadOnly attribute
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-13 by Aaron Gulack
/// @See
/// @INTOPT
///
/// @Syntax Get_Attribute DF_FILE_NUMBER_SQL_RELATIONS of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable           	  Integer variable showing number of relationships
/// @Example
/// Open Customer
///
/// Integer iRelations
///
/// Get_Attribute DF_FILE_NUMBER_SQL_RELATIONS of Customer.File_Number to iRelations
Define DF_FILE_NUMBER_SQL_RELATIONS                 For 626

//TODO
Define DF_SQL_RELATION_COLUMN                       For 716
Define DF_SQL_RELATION_RELATED_SCHEMA               For 717
Define DF_SQL_RELATION_RELATED_TABLE                For 719
Define DF_SQL_RELATION_RELATED_COLUMN               For 721
Define DF_SQL_RELATION_NAME                         For 723
Define DF_SQL_RELATION_STATUS                       For 724
Define DF_SQL_RELATION_DELETE_REF_ACTION            For 726

//Currently Unsupported Attribute
Define DF_FIELD_OVERLAP_START                       For 728

//Currently Unsupported Attribute
Define DF_FIELD_OVERLAP_END                         For 730

//Currently Unsupported Attribute
Define DF_FIELD_OVERLAP_OFFSET_START                For 732

//Currently Unsupported Attribute
Define DF_FIELD_OVERLAP_OFFSET_END                  For 734

//=============================================================================
/// @Name        DF_FILE_RECNUM_TABLE
/// @Description Dataflex's embedded database, by default, uses a Recnum column
/// as the unique identifier for a table instead of a primary key. A table can
/// easily be changed to use another column though and this attribute gets or
/// sets whether the Recnum is being used for a table. Getting the value of this
/// attribute can be done at any time for any driver. The setting of this attribute,
/// however, can only be done in certain situations. Only if an alternative primary
/// key is set up already can this attribute be set to false and only during a
/// Structure_Start. Also, the attribute can only be turned off (set to false),
/// it can not be turned back on (set to True).
///
/// Note: In Postgres, this attribute is a ReadOnly attribute and can not be set.
///
/// @Assumptions
/// @Status      Public (PGFlex ReadOnly)
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-12 by Aaron Gulack
/// @See		 DF_FILE_RECNUM_NAME DF_FILE_PRIMARY_INDEX
/// @INTOPT
///
/// @Syntax Get_Attribute DF_FILE_RECNUM_TABLE of {FileNumber} to {variable}
/// @Syntax Set_Attribute DF_FILE_RECNUM_TABLE of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable           	  Boolean variable indicating if recnum is used
/// @Example
/// Open Customer
///
/// Boolean bRecnum
/// Handle hFile
///
/// Move Customer.File_Number to hFile
///
/// Structure_Start hFile
/// 	Set_Attribute DF_FILE_RECNUM_TABLE of Customer.File_Number to False
/// 	Get_Attribute DF_FILE_RECNUM_TABLE of Customer.File_Number to bRecnum
/// Structure_End hFile
Define DF_FILE_RECNUM_TABLE                         For 1401

//=============================================================================
/// @Name        DF_FILE_PRIMARY_INDEX
/// @Description This attribute gets or sets the index which is used as the
/// primary key for a table. The variable used for this attribute is an integer
/// containing the numbered index used. Getting the value of this attribute can
/// be done at any time, whereas setting can only be done at table creation or
/// during a Structure_Start. If a RECNUM is used as the unique identifier then
/// 0 is returned.
///
/// Note: In Postgres this attribute is ReadOnly, so it can only be used to get
/// the index used as the primary key.
///
/// @Assumptions
/// @Status      Public (PGFlex ReadOnly)
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-12 by Aaron Gulack
/// @See		 DF_FILE_RECNUM_NAME
/// @INTOPT
///
/// @Syntax Get_Attribute DF_FILE_PRIMARY_INDEX of {FileNumber} to {variable}
/// @Syntax Set_Attribute DF_FILE_PRIMARY_INDEX of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable           	  Boolean variable indicating if a primary key is used
/// @Example
/// Open Customer
///
/// Boolean bPrimary
/// Handle hFile
///
/// Move Customer.File_Number to hFile
///
/// Structure_Start hFile
/// 	Set_Attribute DF_FILE_PRIMARY_INDEX of Customer.File_Number to False
/// 	Get_Attribute DF_FILE_PRIMARY_INDEX of Customer.File_Number to bPrimary
/// Structure_End hFile
Define DF_FILE_PRIMARY_INDEX                        For 1402

//=============================================================================
/// @Name        DF_FILE_RECNUM_NAME
/// @Description This attribute is used to get the name of the Recnum field
/// in the table, if one exists. It is a ReadOnly attribute so it can only
/// be used in getting the name of the recnum field to a string variable.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-12 by Aaron Gulack
/// @See		 DF_FILE_RECNUM_TABLE
/// @INTOPT
///
/// @Syntax Get_Attribute DF_FILE_RECNUM_NAME of {FileNumber} to {variable}
/// @Param  FileNumber            Number of the file
/// @Param  variable           	  String name of recnum field
/// @Example
/// Open Customer
///
/// String sRecnum
///
/// Get_Attribute DF_FILE_RECNUM_NAME of Customer.File_Number to sRecnum
Define DF_FILE_RECNUM_NAME                          For 1403

Define DF_FETCH_ALL                                 For -1
Define DF_FETCH_TRUE                                For "TRUE"
Define DF_FETCH_FALSE                               For "FALSE"
Define DF_BIND_ALL_COLUMNS                          For -1

// SQLFlex Lock Type
Define DF_LOCK_TYPE_PAGE                            For 3

// Extended Callback Types
Define DF_MESSAGE_ERROR                             For 9
Define DF_MESSAGE_PROGRESS_STATUS                   For 20
Define DF_MESSAGE_PROGRESS_CONTINUE                 For 21

//Drivers
Define ORAFLEX                                      For "ORA_DRV"
Define SQLFLEX                                      For "SQL_DRV"
Define MDSDB2                                       For "MDS_DB2"
Define MDSPgSQL                                     For "MDSPGSQL"
Define PgFlex                                       For "MDSPGSQL"
Define MDSMySQL                                     For "MDSMYSQL"
Define MySQLFlex                                    For "MDSMYSQL"

// Delimiter for SQL ID objects
Define DB2_ID_DELIM                                 For '"'
Define MYSQL_ID_DELIM                               For "`"
Define ORACLE_ID_DELIM                              For '"'
Define PGSQL_ID_DELIM                               For '"'
Define SQLSERVER_ID_DELIM                           For '"'

// dfStructureEnd Option bits
Define DF_STRUCTEND_OPT_INDEX_ONLY                  For 16    // Internal Use Only
Define DF_STRUCTEND_OPT_FORCE_INVK                  For 32
Define DF_STRUCTEND_OPT_OLD_INVK_NAME               For 64
Define DF_STRUCTEND_OPT_FORCE_NOT_NULL              For 128
Define DF_STRUCTEND_OPT_CREATE_ROWID_TABLE          For 256

//Additional Data Types
Define DF_DATETIME                                  For 7

//Call_Driver Functions
Define CALLDRV_LICENSE_ENVIRONMENT_SET              For 0
Define CALLDRV_ORA_CURRENT_SQL_SERVER               For 6
Define CALLDRV_SQL_ERROR_MESSAGE                    For 14
Define CALLDRV_CURRENT_SQL_SERVER                   for 19
Define CALLDRV_SQL_NEXT_RESULTSET					for 22
Define CALLDRV_BIND_PARAMETER                       for 23
Define CALLDRV_SQL_MAX_CURSORS                      For 26
Define CALLDRV_SQLLOADER_FIELDS_TERM                For 30
Define CALLDRV_CREATE_TABLE_FROM_DAT                For 30
Define CALLDRV_SQLLOADER_DECIMAL_SEP                For 31
Define CALLDRV_CONVERT_DAT_FILE                     For 32
Define CALLDRV_SQLFLEX_MAX_CURSORS                  For 37
Define CALLDRV_NATIVE_OPTIMIZATION                  For 38
Define CALLDRV_GET_RETURNED_COLUMNS                 For 39
Define CALLDRV_GET_RETURNED_ROWS                    For 40
Define CALLDRV_GET_COLUMN_ATTRIBUTE                 For 41
Define CALLDRV_START_TXTGEN_AFTER_RECNUM            For 42
Define CALLDRV_FINISH_TXTGEN_AFTER_RECNUM           For 43
Define CALLDRV_SET_ISOLATION_LEVEL                  For 44
Define CALLDRV_GET_SERVER_CFG                       For 45
Define CALLDRV_SET_SQL_LOCK_TIMEOUT                 For 46
Define CALLDRV_GET_SQL_LOCK_TIMEOUT                 For 47
Define CALLDRV_GET_RESULTS                          For 48
Define CALLDRV_GET_MORE_RESULTS                     For 49
Define CALLDRV_GET_CURRENT_USER_NAME                For 50
Define CALLDRV_OPEN_EMBEDDED_CURSOR                 For 51
Define CALLDRV_CLOSE_EMBEDDED_CURSOR                For 52
Define CALLDRV_SET_CURRENT_EMBEDDED_CURSOR          For 53
Define CALLDRV_GET_CURRENT_EMBEDDED_CURSOR          For 54
Define CALLDRV_SET_MAX_EMBEDDED_CURSOR              For 55
Define CALLDRV_GET_MAX_EMBEDDED_CURSOR              For 56
Define CALLDRV_SQL_TRANSACTION                      For 57
Define CALLDRV_LOCAL_TD_PATH                        For 58
Define CALLDRV_CREATE_DB                            For 59
Define CALLDRV_ESCAPE_STRING                        For 60
Define CALLDRV_SET_PROC_ATTRIBUTE_TYPE              For 61
Define CALLDRV_SQL_REFRESH_CACHE                    For 62
Define CALLDRV_GET_SQL_STMT                         For 63
Define CALLDRV_DIRECT_PATH_LOAD                     For 64

Define CALLDRV_READ_LOB                             For 65
Define CALLDRV_WRITE_LOB                            For 66
Define CALLDRV_APPEND_LOB                           For 67
Define CALLDRV_LENGTH_LOB                           For 68
Define CALLDRV_LOADFROMFILE_LOB                     For 69
Define CALLDRV_ERASE_LOB                            For 70
Define CALLDRV_TRUNCATE_LOB                         For 71
Define CALLDRV_INITIALIZE_SEQUENCE                  For 72
Define CALLDRV_CLIENT_CFG                           For 73
Define CALLDRV_END_SAVERECORD                       For 74
Define CALLDRV_ENABLE_RECONNECT                     For 75
Define CALLDRV_ENUMERATE_SERVER                     For 76
Define CALLDRV_USE_ROWCOUNT_IN_TRANSACTIONS         For 77
Define CALLDRV_USE_DFLEX_DATE_FORMAT                For 78
Define CALLDRV_FORCE_FIELDS_NOT_NULL                For 79
Define CALLDRV_ORA_CREATE_TABLE_FROM_DAT            For 80
Define CALLDRV_MAX_DATA_SIZE                        For 81
Define CALLDRV_CHUNK_SIZE                           For 82
Define CALLDRV_GET_DATA_CHUNK                       For 83
Define CALLDRV_MIRROR_SERVER                        For 84
Define CALLDRV_COPY_DATA                            For 85
Define CALLDRV_SET_SQL_CURSOR_TYPE                  For 86
Define CALLDRV_ICF                                  For 87
Define CALLDRV_CLEAR_INT_CACHE                      For 88
Define CALLDRV_GET_CURRENT_USER_PASSWORD            For 89
Define CALLDRV_FORCE_FIELDS_NULL                    For 90
Define CALLDRV_TRANSACTIONS_ALLOWED                 For 91
Define CALLDRV_SQL_ERROR_MESSAGE2                   For 92
Define CALLDRV_PGSQL_NAME_SPACE                     For 93
Define CALLDRV_EMBEDDED_SQL_TYPE                    For 94
Define CALLDRV_CREATE_INVK_FUNCTIONS                For 95
Define CALLDRV_DEFAULT_FILE_CASING                  For 96
Define CALLDRV_GLOBAL_SETTING                       For 97
Define CALLDRV_RESTRUCTURE_SCRIPT                   For 98
Define CALLDRV_CURRENT_SQL_SERVER_CONNECTION        For 99
Define CALLDRV_100                                  For 100
Define CALLDRV_FILE_STRUCT_DYNAMIC_ONLINE           For 101
Define CALLDRV_SET_FIXED_FILE_RECORDS_USED          For 102
Define CALLDRV_GET_FIXED_FILE_RECORDS_USED          For 103
Define CALLDRV_LOB_EX_WRITE                         For 104
Define CALLDRV_LOB_EX_APPEND                        For 105
Define CALLDRV_LOB_EX_READ                          For 106
Define CALLDRV_LOB_EX_GET_LENGTH                    For 107
Define CALLDRV_LOB_EX_SET_LENGTH                    For 108
Define CALLDRV_LOB_EX_TEST                          For 109
Define CALLDRV_LOB_EX_SET_NULL                      For 110

// License and environment settings
Define CALLDRV_DRIVER_REVISION                      For 0
Define CALLDRV_COMPANY_NAME                         For 1
Define CALLDRV_SERIAL_NUMBER                        For 2
Define CALLDRV_LICENSED_USERS                       For 3
Define CALLDRV_MAJOR_REVISION                       For 4
Define CALLDRV_VERSION_COMMENTS                     For 5
Define CALLDRV_OLEDB_OEM_TRANSLATION                For 6
Define CALLDRV_SET_DB_PORT                          For 7
Define CALLDRV_GET_DB_PORT                          For 8
Define CALLDRV_SET_DB_SOCKET                        For 9
Define CALLDRV_GET_DB_SOCKET                        For 10
Define CALLDRV_SET_AS_SYSDBA                        For 11
Define CALLDRV_OEM_TRANSLATION_STATE                For 12
Define CALLDRV_TIME_TO_LIC_EXPIRATION               For 13
Define CALLDRV_LICENSE_EXPIRATION_WARN              For 14
Define CALLDRV_LICENSE_PATH                         For 15
Define CALLDRV_AUTO_NUMERIC_REMAPPING               For 16
Define CALLDRV_FORCE_DATE_FORMAT_INIT               For 17
Define CALLDRV_STATIC_TABLE_OPT                     For 18
Define CALLDRV_MAX_OBJECT_NAME_LENGTH               For 19
Define CALLDRV_USE_LAZY_OPEN_MODE                   For 20
Define CALLDRV_SET_CUSTOM_OEM_TO_ANSI               For 21
Define CALLDRV_GET_CUSTOM_OEM_TO_ANSI               For 22

//CALLDRV_ENUMERATE_SERVER_OPTION
Define CALLDRV_ENUMERATE_SERVER_COUNT               For 0
Define CALLDRV_ENUMERATE_SERVER_SERVER              For 1

//CALLDRV_DEFAULT_FILE_CASING
Define FILE_CASING_UPPER                            For 0
Define FILE_CASING_LOWER                            For 1
Define FILE_CASING_KEEP                             For 2

// CALLDRV_GLOBAL_SETTING
Define GLOBAL_SETTING_TABLESPACE_SET                For 0
Define GLOBAL_SETTING_TABLESPACE_GET                For 1
Define GLOBAL_SETTING_INDEX_TABLESPACE_SET          For 2
Define GLOBAL_SETTING_INDEX_TABLESPACE_GET          For 3

// CALLDRV_RESTRUCTURE_SCRIPT
Define CALLDRV_RESTRUCTURE_SCRIPT_ENABLE            For 0
Define CALLDRV_RESTRUCTURE_SCRIPT_DISABLE           For 1
Define CALLDRV_RESTRUCTURE_SCRIPT_GET_CHUNK_SQL     For 2
Define CALLDRV_RESTRUCTURE_SCRIPT_GET_CHUNK_INT     For 3

// DF_SQL_RELATION_STATUS attributes
Define FOREIGN_KEY_NONE                             For -1
Define FOREIGN_KEY_CREATE                           For  0
Define FOREIGN_KEY_ENABLE                           For  1
Define FOREIGN_KEY_DISABLE                          For  2
Define FOREIGN_KEY_DROP                             For  3

// DF_SQL_RELATION_DELETE_REF_ACTION attributes
Define DELETE_REF_NONE                              For 0
Define DELETE_REF_CASCADE                           For 1
Define DELETE_REF_SET_NULL                          For 2
Define DELETE_REF_SET_DEFAULT                       For 3
Define DELETE_REF_RESTRICT                          For 4

//Embedded SQL Cursor Types
Define CALLDRV_ENUMERATE_CURSOR_TYPE_NONE           For 0
Define CALLDRV_ENUMERATE_CURSOR_TYPE_CLIENT         For 1
Define CALLDRV_ENUMERATE_CURSOR_TYPE_SERVER         For 2
Define CALLDRV_ENUMERATE_CURSOR_TYPE_PARAMETERIZED  For 3

//Driver Call Direction
Define CALLDRV_VALUE_GET                            For 0
Define CALLDRV_VALUE_SET                            For 1

//Inverse Key types
Define REGULAR_SEG                                  For -1
Define INVK_CASE_SEG                                For 0
Define INVK_DESC_SEG                                For 1
Define INVK_DESC_AND_CASE_SEG                       For 2

//DB2 Index Types
Define REG_INDEX                                    For 0
Define REV_INDEX                                    For 1
Define CLUST_INDEX                                  For 2
Define REV_CLUST_INDEX                              For 3

//Oracle Procedure Arguments type
Define IS_NONE                                      For 0
Define IS_IN                                        For 1
Define IS_OUT                                       For 2
Define IS_IN_OUT                                    For 3
Define IS_RSET                                      For 4

// SQL_GET_COL Attributes
Define SQL_GET_COL_ATTRIB_SIZE                      For 1
Define SQL_GET_COL_ATTRIB_DECIMALS                  For 2
Define SQL_GET_COL_ATTRIB_LABEL                     For 3
Define SQL_GET_COL_ATTRIB_COLUMN_NAME               For 4
Define SQL_GET_COL_ATTRIB_TABLE_NAME                For 5
Define SQL_GET_COL_ATTRIB_SQLTYPE                   For 6
Define SQL_GET_COL_ATTRIB_NULLABLE                  For 7
Define SQL_GET_COL_ATTRIB_DFTYPE                    For 8
Define SQL_GET_COL_ATTRIB_DATA_LENGTH               For 9

// MySQL Data Types
Define eMySQL_DECIMAL                               For 0
Define eMySQL_TINY                                  For 1
Define eMySQL_SHORT                                 For 2
Define eMySQL_LONG                                  For 3
Define eMySQL_FLOAT                                 For 4
Define eMySQL_DOUBLE                                For 5
Define eMySQL_NULL                                  For 6
Define eMySQL_TIMESTAMP                             For 7
Define eMySQL_LONGLONG                              For 8
Define eMySQL_INT24                                 For 9
Define eMySQL_DATE                                  For 10
Define eMySQL_TIME                                  For 11
Define eMySQL_DATETIME                              For 12
Define eMySQL_YEAR                                  For 13
Define eMySQL_NEWDATE                               For 14
Define eMySQL_BIT                                   For 16
Define eMySQL_NEWDECIMAL                            For 246
Define eMySQL_ENUM                                  For 247
Define eMySQL_SET                                   For 248
Define eMySQL_TINY_BLOB                             For 249
Define eMySQL_MEDIUM_BLOB                           For 250
Define eMySQL_LONG_BLOB                             For 251
Define eMySQL_BLOB                                  For 252
Define eMySQL_VAR_STRING                            For 253
Define eMySQL_STRING                                For 254
Define eMySQL_TINY_TEXT                             For -249
Define eMySQL_MEDIUM_TEXT                           For -250
Define eMySQL_LONG_TEXT                             For -251
Define eMySQL_TEXT                                  For -252

// Oracle Data Types
Define eOracle_VARCHAR2                             For   1
Define eOracle_NUMBER                               For   2
Define eOracle_INT                                  For   3
Define eOracle_FLOAT                                For   4
Define eOracle_STRING                               For   5
Define eOracle_LONG                                 For   8
Define eOracle_ROWID                                For  11
Define eOracle_DATE                                 For  12
Define eOracle_RAW                                  For  23
Define eOracle_LONGRAW                              For  24
Define eOracle_CHAR                                 For  96
Define eOracle_MSLABEL                              For 106
Define eOracle_CLOB                                 For 112
Define eOracle_BLOB                                 For 113
Define eOracle_TIMESTAMP                            For 187
Define eOracle_TIMESTAMPTZ                          For 188
Define eOracle_INTERVALYM                           For 189
Define eOracle_INTERVALDS                           For 190
Define eOracle_TIMESTAMPLTZ                         For 232
Define eOracle_NCHAR                                For 286
Define eOracle_NVARCHAR2                            For 287
Define eOracle_NCLOB                                For 288

// PostgreSQL Data Types
Define ePgSQL_CIRCLE                                For  718
Define ePgSQL_MONEY                                 For  790
Define ePgSQL_BOOL                                  For   16
Define ePgSQL_BYTEA                                 For   17
Define ePgSQL_CHAR                                  For   18
Define ePgSQL_INT2                                  For   21
Define ePgSQL_INT4                                  For   23
Define ePgSQL_REGPROC                               For   24
Define ePgSQL_REGPROCEDURE                          For 2202
Define ePgSQL_REGOPER                               For 2203
Define ePgSQL_REGOPERATOR                           For 2204
Define ePgSQL_REGCLASS                              For 2205
Define ePgSQL_REGTYPE                               For 2206
Define ePgSQL_TEXT                                  For   25
Define ePgSQL_CITEXT                                For  -25
Define ePgSQL_OID                                   For   26
Define ePgSQL_TID                                   For   27
Define ePgSQL_XID                                   For   28
Define ePgSQL_CID                                   For   29
Define ePgSQL_XML                                   For  142
Define ePgSQL_BPCHAR                                For 1042
Define ePgSQL_VARCHAR                               For 1043
Define ePgSQL_INT8                                  For   20
Define ePgSQL_PATH                                  For  602
Define ePgSQL_FLOAT4                                For  700
Define ePgSQL_FLOAT8                                For  701
Define ePgSQL_ABSTIME                               For  702
Define ePgSQL_RELTIME                               For  703
Define ePgSQL_TINTERVAL                             For  704
Define ePgSQL_POINT                                 For  600
Define ePgSQL_LINE                                  For  628
Define ePgSQL_LSEG                                  For  601
Define ePgSQL_BOX                                   For  603
Define ePgSQL_POLYGON                               For  604
Define ePgSQL_ACLITEM                               For 1033
Define ePgSQL_MACADDR                               For  829
Define ePgSQL_INET                                  For  869
Define ePgSQL_CIDR                                  For  650
Define ePgSQL_TIMESTAMP                             For 1114
Define ePgSQL_DATE                                  For 1082
Define ePgSQL_TIME                                  For 1083
Define ePgSQL_TIMESTAMPTZ                           For 1184
Define ePgSQL_INTERVAL                              For 1186
Define ePgSQL_NUMERIC                               For 1700
Define ePgSQL_TIMETZ                                For 1266
Define ePgSQL_BIT                                   For 1560
Define ePgSQL_VARBIT                                For 1562
Define ePgSQL_UUID                                  For 2950

// SQL Server Data Types
Define eSQLServer_NA                                For    0
Define eSQLServer_CHAR                              For    1
Define eSQLServer_NUMERIC                           For    2
Define eSQLServer_DECIMAL                           For    3
Define eSQLServer_INT                               For    4
Define eSQLServer_SMALLINT                          For    5
Define eSQLServer_FLOAT                             For    6
Define eSQLServer_REAL                              For    7
Define eSQLServer_DOUBLE                            For    8
Define eSQLServer_DATETIME                          For   11
Define eSQLServer_VARCHAR                           For   12
Define eSQLServer_DATE                              For   40
Define eSQLServer_TIME                              For   41
Define eSQLServer_DATETIME2                         For   42
Define eSQLServer_DATETIMEOFFSET                    For   43
Define eSQLServer_SMALLDATETIME                     For   58
Define eSQLServer_TIMESTAMP                         For   93
Define eSQLServer_HIERARCHYID                       For  128
Define eSQLServer_GEOMETRY                          For  129
Define eSQLServer_GEOGRAPHY                         For  130
Define eSQLServer_TEXT                              For   -1
Define eSQLServer_BINARY                            For   -2
Define eSQLServer_VARBINARY                         For   -3
Define eSQLServer_IMAGE                             For   -4
Define eSQLServer_BIGINT                            For   -5
Define eSQLServer_TINYINT                           For   -6
Define eSQLServer_BIT                               For   -7
Define eSQLServer_NCHAR                             For   -8
Define eSQLServer_NVARCHAR                          For   -9
Define eSQLServer_NTEXT                             For  -10
Define eSQLServer_GUID                              For  -11
Define eSQLServer_VARBINARYMAX                      For  -98
Define eSQLServer_VARCHARMAX                        For  -99
Define eSQLServer_NVARCHARMAX                       For -100
Define eSQLServer_SQLVARIANT                        For -150
Define eSQLServer_XML                               For -370

//=============================================================================
//Error Text
//==========

//=============================================================================
//Define Self if needed
//=====================

#IFDEF SELF
#ELSE
    #REPLACE SELF |VI85  // as of vdf12.0 this is now part of fmac
#ENDIF

//=============================================================================
//Define varibles we need
//=======================

#IFDEF MertechInc_Variables_Defined
#ELSE
    Define MertechInc_Variables_Defined

    Indicator MertechInc_bThereIsBinding

    Integer MertechInc_FileNumber      //Replaces _SAVEFILENUMBER# and FILENUMBER
    Integer MertechInc_iArg            //Replaces _LLONG#
    Integer MertechInc_iCallBack       //Replaces _CALLBACK#
    Integer MertechInc_iCount          //General loop limit integer
    Integer MertechInc_iDecSep         //Holds the decimal seperator
    Integer MertechInc_iFunction       //Replaces _FID#    ??? check is this is need when tidy is complete
    Integer MertechInc_iLoop           //General loop integer
    Integer Mertech_iMySQLParam        //Replaces _ALL_PAR_POS#
    Integer MertechInc_iParamCount     //Replaces _NPAR#
    Integer MertechInc_iRet            //Replaces _RET#
    Integer MertechInc_iSaveCount      //Replaces _NPOS#
    Integer MertechInc_iWork           //General work integer
    Integer MertechInc_iWork2

    String MertechInc_Blank            //Replaces _BLANK#
    String MertechInc_DriverName       //Replaces _DRIVERNAME#
    String MertechInc_sArg1 255        //Replaces _ARG1#
    String MertechInc_sArg2 255        //Replaces _ARG2#
    String MertechInc_sWork 255        //General work string

    String MertechInc_CurrentDriver    //Keep the current driver name
    //Global string are created pre-filled with spaces. We need an empty string
    Move "" to MertechInc_Blank
    Move "" to MertechInc_CurrentDriver

    #Replace MertechInc_Invalid_Driver -1
#ENDIF

//=============================================================================
//Use Obsolete Code
//=================

#COMMAND MertechInc_Use_Obsolete_Code
    Define MertechInc_Obsolete_Code
#ENDCOMMAND

#COMMAND MertechInc_Error_Obsolete_Code
    #ERROR 4400 Obsolete code used. Recode or Add statement MertechInc_Use_Obsolete_Code after including Mertech.inc
#ENDCOMMAND

//=============================================================================
//Comment Block Template
//======================

/// @Name {Name of the command for indexing} (used for documentation)
/// @Description {Short Command Description} (used for documentation)
///     The description can be multiple lines, and contain HTML tags.
///     The other tokens will have HTML encoded so we can show stuff
///     like <param1> properly. A blank line will automatically be
///	    translated into a paragraph break in the documentation, so
/// 	no need for <br> or <p> tags.
///
/// @Assumptions {Assumptions made in order for the command to work}
/// @Status {Obsolete, Internal, or Public} (used for documentation)
/// @Drivers {DB2Flex, MySQLFlex, ORAFlex, PgFlex, SQLFlex or All} (used for documentation)
/// @VersionNote {Date and author of the last revision}
/// @See {list of related commands}
///
/// @Syntax {Syntax of use} (used for documentation)
/// @Param {Each parameter with a brief description} (used for documentation)
/// @DBMS {List of supported databases}
/// @DataFlex {List of supported DataFlex versions}
/// @Usage {Different uses command can have multiple syntaxes} (used for documentation)
///
/// @Example {An example of the command being used} (used for documentation)

//=============================================================================
/// @Name        DO_GETFILENUMBER_DRIVERNAME
/// @Description Retrieves the current driver name and or the file number
/// that will be used by the macro commands.
///
/// @Assumptions
/// @Status      Internal Use Only
/// @Drivers     All
/// @VersionNote Last Revised: 2009-07-14 By Ian Smith
/// @See
#COMMAND DO_GETFILENUMBER_DRIVERNAME R .
    //Get file number from parameter
    #IFDEF !1
        MOVE !1 TO MertechInc_FileNumber
    #ELSE
        #IFDEF !1.RECNUM
            #SET Q$ !1.RECNUM
        #ELSE
            #SET Q$ !1.FILE_NUMBER
        #ENDIF
        !A [] $82 |CI!q MertechInc_FileNumber
    #ENDIF

    Send MertechInc_Get_Driver_name
#ENDCOMMAND

//Most commands use DO_GETFILENUMBER_DRIVERNAME so this code was being duplicated
//all the time. It has been moved to this method to remove that duplication.
Procedure MertechInc_Get_Driver_name Global
    //If we have a file number get its driver, else find first loaded Mertech driver
    If MertechInc_FileNumber GT 0 ;
        Get_Attribute DF_FILE_DRIVER of MertechInc_FileNumber to MertechInc_DriverName
    Else Begin
        If (MertechInc_CurrentDriver > "") Move MertechInc_CurrentDriver to MertechInc_DriverName
        Else Begin
            Get_Attribute DF_NUMBER_DRIVERS to MertechInc_iCount
            For MertechInc_iLoop from 1 to MertechInc_iCount
                Get_Attribute DF_DRIVER_NAME of MertechInc_iLoop to MertechInc_DriverName
                Move (UPPERCASE(MertechInc_DriverName)) to MertechInc_DriverName
                If (MertechInc_DriverName EQ ORAFLEX  or MertechInc_DriverName EQ SQLFLEX or MertechInc_DriverName EQ MDSDB2 or ;
                    MertechInc_DriverName EQ MDSPgSQL or MertechInc_DriverName EQ MDSMySQL) Move MertechInc_iCount to MertechInc_iLoop
                Else Move "" to MertechInc_DriverName
            Loop
        End
    End

    //Ensure that we return a valid Mertech driver.
    If (MertechInc_DriverName NE ORAFLEX  and ;
        MertechInc_DriverName NE SQLFLEX  and ;
        MertechInc_DriverName NE MDSDB2   and ;
        MertechInc_DriverName NE MDSPgSQL and ;
        MertechInc_DriverName NE MDSMySQL     ) ;
        Begin

        //Report invalid driver
//        Error 25100 ("Invalid Driver - file" * String(MertechInc_FileNumber))
//        Error 25100 ("Mertech.inc - Not a Mertech driver (file number " * String(MertechInc_FileNumber) * ")")
        Error 25100 ("Mertech.inc - Not a Mertech driver. File" * String(MertechInc_FileNumber) * "Driver" * Trim(MertechInc_DriverName) )

        //Set MertechInc_FileNumber to MertechInc_Invalid_Driver so that the commands can
        //determine if the driver is valid. MertechInc_FileNumber is use instead of
        //MertechInc_DriverName as integer conparisons are quicker than string conparisons
        Move MertechInc_Invalid_Driver to MertechInc_FileNumber
    End
End_Procedure

//=============================================================================
/// @Name        MertechInc_Pre_Size_String
/// @Description Returns a string full of spaces.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     n/a
/// @VersionNote Last Revised: 2009-12-02 By Gandalf Hernandez
/// @See
Function MertechInc_Pre_Size_String Global Integer iSize Returns String
   String sWork
   Integer iBlocks iRemainder

   If (iSize <= 1) Begin
      // marcelo 06/28/2000 implemented logic to avoid VDF 7 crashing problems
      #IFDEF FMAC_VERSION
          If FMAC_VERSION eq 7 Move 1000 to iSize
          Else Move 16384 to iSize
      #ELSE
          Move 16384 to iSize
      #ENDIF
   End

   // Build the string in blocks of 32, to speed things up
   // If the string is less than 32 bytes, just fill it up regularly
   Move (iSize / 32) to iBlocks
   Move (Mod(iSize, 32)) to iRemainder

   If (iBlocks > 0) Begin
      Move (Repeat("                                ", iBlocks)) to sWork
      Move (Append (sWork, (Repeat(" ", iRemainder)))) to sWork
   End
   Else Move (Repeat(" ", iSize)) to sWork

   Function_Return sWork
End_Function

//=============================================================================
/// @Name        MertechInc_Set_DecSep
/// @Description Saves the current decimal separator and sets the decimal
/// separator to '.'.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     n/a
/// @VersionNote Last Revised: 2009-08-17 By Ian Smith
Procedure MertechInc_Set_DecSep Global
    Get_Attribute DF_DECIMAL_SEPARATOR to MertechInc_iDecSep
    If MertechInc_iDecSep Ne 46 Set_Attribute DF_DECIMAL_SEPARATOR to 46 // (.) WILL BE DECIMAL SEPARATOR
End_Procedure

//=============================================================================
/// @Name        MertechInc_Reset_DecSep
/// @Description Sets the decimal separator to the saved value.
///
/// @Status      Internal
/// @Drivers     n/a
/// @VersionNote Last Revised: 2009-08-17 By Ian Smith
///
Procedure MertechInc_Reset_DecSep Global
    If MertechInc_iDecSep Ne 46 Set_Attribute DF_DECIMAL_SEPARATOR to MertechInc_iDecSep
End_Procedure

//=============================================================================
/// @Name        FETCH_FIELD
/// @Description Selects or de-selects the fields to be fetched during the
/// next FIND (query).
///
/// @Status      Internal
/// @Drivers     All
/// @VersionNote Last Revised: 2009-07-16 By Ian Smith
///
/// @Syntax FETCH_FIELD <FileNum> <FieldStart> THRU <FieldEnd> TO DF_FETCH_TRUE
/// @Param  FileNum    is the File Number
/// @Param  FieldStart is the Field Name or Number that will start the selection range
/// @Param  FieldEnd   is the Field Name or Number that will finish the selection range
///
/// @Syntax FETCH_FIELD <FileNum> <Field1> TO DF_FETCH_TRUE
/// @Param  FileNum  is the File Number
/// @Param  Field1 Fields Name or Number to be selected
///
#COMMAND FETCH_FIELD
    DO_GETFILENUMBER_DRIVERNAME !1
    If (MertechInc_FileNumber <> -1) Begin
        #IFSAME !3 to   //Single Field
            #IFTYPE !2 "I"  //Number passed
                Move !2 to MertechInc_iArg
            #ELSE   //name passed so workout number
                Move (Length(|CS'!2')) to MertechInc_iArg
                Move (MertechInc_iArg - POS(",",|CS'!2')) to MertechInc_iArg
                Move (Right(|CS'!2',MertechInc_iArg)) to MertechInc_iArg
            #ENDIF
            Move (Uppercase(!4)) to MertechInc_sArg1
            Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 7 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
            If MertechInc_iRet EQ -1 Indicate ERR True
        #ELSE
            #IFSAME !3 THRU //multiple fields
                #CHECK !2 RLGU#
                #CHECK !4 RLGU#
                Move (Uppercase(!6)) to MertechInc_sArg1
                If (!2>!4) Error 77
                Else ;
                    For MertechInc_iArg from !2 to !4  //compiler sorts out from to field numbers
                        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 7 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
                        If MertechInc_iRet EQ -1 Indicate ERR True
                    Loop
            #ENDIF
        #ENDIF
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_TEXT_MESSAGE
/// @Description Use this command to manually insert a string into a trace
/// file. This can be useful for readability within the trace file to log
/// what is actually happening at certain points.
///
/// @Assumptions The text string is less than 80 characters long.
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 20013-08-19 by Aaron Gulack
/// @See         ENABLE_TRACE_ON DISABLE_TRACE_ON
///
/// @Syntax SQL_TEXT_MESSAGE {variable}
/// @Param  {variable}		The string to insert into the trace file.
///
/// @Example
/// Login "localhost" "mds" "mertech" "ora_drv"
///
/// ENABLE_TRACE_ON to "c:\trace.txt" DEBUG_LEVEL
/// open Customer
/// SQL_TEXT_MESSAGE "The table has been opened"
#COMMAND SQL_TEXT_MESSAGE R .
    MOVE !1 TO MertechInc_sArg1
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Call_Driver 0 MertechInc_DriverName Function 17 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    End
#ENDCOMMAND

//=============================================================================
/// @Name       SELECT_COLUMNS_FIND
/// @Description This command is used to fetch only a certain number of fields
/// while doing a "find". When specifying the field number to start from and
/// field number to end on, the find will only fetch the given fields from the
/// record. It is important to always use this command after first deselecting
/// all columns i.e. setting RESET_FETCH_FIELDS to DF_FETCH_FALSE. Also, after
/// using this command, all columns need to be reselected i.e. setting
/// RESET_FETCH_FIELDS to DF_FETCH_TRUE. Note that fields used as a part the
/// index segment associated with the find will always be fetched regardless.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 20014-04-30 by Marcello Yo
/// @See         RESET_FETCH_FIELDS DISABLE_SELECT_COLUMNS_ERRORS
///
/// @Syntax SELECT_COLUMNS_FIND {FileNumber} {fieldStart} THRU {fieldEnd}
/// @Param  FileNumber    	The number of the file
/// @Param  fieldStart 		The field number to start the fetch from
/// @Param  FieldEnd   		The field number to end the fetch at
///
/// @Example
/// Open Customer
/// RESET_FETCH_FIELDS  CUSTOMER DF_FETCH_FALSE
/// SELECT_COLUMNS_FIND CUSTOMER CUSTOMER_NUMBER NAME
/// DISABLE_SELECT_COLUMNS_ERRORS DISABLED
///
/// Clear Customer
/// Repeat
///    Find Gt Customer by Index.1
///    If (Found) Showln Customer.Customer_Number '-' Customer.Name
/// Until (Not(Found))
///
/// RESET_FETCH_FIELDS Customer DF_FETCH_TRUE
#COMMAND SELECT_COLUMNS_FIND
    #IFCLASS !1 "V"
        #IFDEF !2
        #ELSE
            CHECK !1 "F"
        #ENDIF
    #ENDIF
    #IFSAME !3 THRU
        #IFDEF !2
            #IFDEF !4
                FETCH_FIELD !1 !2 THRU !4 TO DF_FETCH_TRUE
            #ELSE
                FETCH_FIELD !1 !2 THRU !1.!4 TO DF_FETCH_TRUE
            #ENDIF
        #ELSE
            #IFDEF !4
                FETCH_FIELD !1 !1.!2 THRU !4 TO DF_FETCH_TRUE
            #ELSE
                FETCH_FIELD !1 !1.!2 THRU !1.!4 TO DF_FETCH_TRUE
            #ENDIF
        #ENDIF
    #ELSE
        #IFDEF !2
          #IFCLASS !2 "F"
              FETCH_FIELD !1 !2 TO DF_FETCH_TRUE
          #ELSE
              #CHECK !2 _G#L
              FETCH_FIELD !1 !2 TO DF_FETCH_TRUE
          #ENDIF
        #ELSE
            FETCH_FIELD !1 !1.!2 TO DF_FETCH_TRUE
        #ENDIF
        #IF !0>2
            SELECT_COLUMNS_FIND !1 !3 !4 !5 !6 !7 !8 !9
        #ENDIF
    #ENDIF
#ENDCOMMAND

#REPLACE SET_FETCH_FIELDS SELECT_COLUMNS_FIND

//=============================================================================
/// @Name        RESET_FETCH_FIELDS
/// @Description This command is used to specify whether to retrieve all columns
/// or no columns when performing a find. It is usually used with the command
/// SELECT_COLUMNS_FIND to reset the column fetching. This command can either be
/// set to DF_FETCH_TRUE, which will fetch all columns or set to DF_FETCH_FALSE,
/// which will fetch no columns.
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2014-04-30 by Marcello Yo
/// @See         SELECT_COLUMNS_FIND DISABLE_SELECT_COLUMNS_ERRORS
///
/// @Syntax RESET_FETCH_FIELDS {FileNumber} {DF_FETCH_TRUE/DF_FETCH_FALSE}
/// @Param  FileNumber			The number of the file
/// @Param  DF_FETCH_TRUE  		fetch all columns
/// @Param  DF_FETCH_FALSE 		fetch no columns
///
/// @Example
/// Open Customer
/// RESET_FETCH_FIELDS  CUSTOMER DF_FETCH_FALSE
/// SELECT_COLUMNS_FIND CUSTOMER CUSTOMER_NUMBER NAME
/// DISABLE_SELECT_COLUMNS_ERRORS DISABLED
///
/// Clear Customer
/// Repeat
///    Find Gt Customer by Index.1
///    If (Found) Showln Customer.Customer_Number '-' Customer.Name
/// Until (Not(Found))
///
/// RESET_FETCH_FIELDS Customer DF_FETCH_TRUE
#COMMAND RESET_FETCH_FIELDS R R .
    FETCH_FIELD !1 DF_FETCH_ALL TO !2
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_FOR_ONEROW
/// @Description This command will instruct the driver to fetch one row
/// per query
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-19 by Aaron Gulack
/// @See
///
/// @Syntax SQL_FOR_ONEROW {FileNumber}
/// @Param  FileNumber		The number of the file
/// @Example
///     open Customer
///     SQL_FOR_ONEROW Customer.File_Number
///     Repeat
///     	find gt Customer by Recnum
///         If (Found) Begin
///             showln "Sales name is " Customer.FirstName
///         end
///     until (Customer.ID = 10)
#COMMAND SQL_FOR_ONEROW R .
    #IFDEF MertechInc_Obsolete_Code
        DO_GETFILENUMBER_DRIVERNAME !1
        If (MertechInc_FileNumber <> -1) Begin
            Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 12 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
            If MertechInc_iRet EQ -1 INDICATE ERR True
        End
    #ELSE
        MertechInc_Error_Obsolete_Code
    #ENDIF
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_REFRESH_CACHE
/// @Description For optimization during record retrieval, a set number of
/// records are stored in a local cache. This command forces a refresh, by
/// making the next find retrieve the record from the database instead of
/// the cache.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-19 by Aaron Gulack
/// @See
///
/// @Syntax SQL_REFRESH_CACHE OF {FileNumber}
/// @Param  FileNumber		The number of the file
/// @Example
/// Open Customer
///
/// Find gt Customer by Index.1
/// While (Found) Begin
///     showln "Customer name is " CUSTOMER.CUSTOMER
/// Loop
///
/// SQL_REFRESH_CACHE of CUSTOMER
#COMMAND SQL_REFRESH_CACHE OF R .
    DO_GETFILENUMBER_DRIVERNAME !2
    If (MertechInc_FileNumber <> -1) Begin
        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function CALLDRV_SQL_REFRESH_CACHE CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_FOR_SET
/// @Description Use this command during LT or GT finds to only fetch a set
/// number of rows. An option is also available for this command to disable
/// the local cash by passing NOCACHE at the end of the command call. Note
/// that if the rowcount is set low, too many round-trips to the server may
/// result, effecting performance significantly. Also, if the rowcount is set
/// too high a large number of records can be pre-fetched and end up not being
/// used by the application. Because of this, the default of 10 rows and a cache
/// will be adequate for most situations.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-20 by Aaron Gulack
/// @See
///
/// @Syntax SQL_FOR_SET {FileNumber} MAXROWS {variable} {CACHE/NOCACHE}
/// @Param  FileNumber		The number of the file
/// @Param  variable  		The maximum number of rows to retrieve
/// @Param  CACHE       	fetched rows will be kept at the local cache
/// @Param  NOCACHE     	fetched rows will not be kept at the local cache
/// @Example
/// Open Customer
///
/// SQL_FOR_SET Customer MAXROWS 15 CACHE
/// find gt Customer by Index.1
#COMMAND SQL_FOR_SET R "MAXROWS" R "CACHE""NOCACHE"
    DO_GETFILENUMBER_DRIVERNAME !1
    If (MertechInc_FileNumber <> -1) Begin
        #IFSAME !4 CACHE
            Move "CACHE" to MertechInc_sArg1
        #ELSE
            Move "NOCACHE" to MertechInc_sArg1
        #ENDIF
        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 13 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank !3 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_SET
/// @Description Initializes and sets an initial statement for embedded
/// sql execution.
///
/// @Assumptions Parameter may be more than 255 characters long so redirect to method.
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-20 by Aaron Gulack
/// @See    	 SQL_SET_STMT
///
/// @Syntax SQL_SET {FileNumber}
/// @Param  FileNumber		The number of the file
#COMMAND SQL_SET R .
    #IFDEF MertechInc_Obsolete_Code
        DO_GETFILENUMBER_DRIVERNAME 0
        If (MertechInc_FileNumber <> -1) Begin
            INDICATE ERR False
            Send MertechInc_SQL_SET !1
            If MertechInc_iRet EQ -1 INDICATE ERR True
        End
    #ELSE
        MertechInc_Error_Obsolete_Code
    #ENDIF
#ENDCOMMAND

Procedure MertechInc_SQL_SET Global String sStatement
    Call_Driver 0 MertechInc_DriverName Function 1 CALLBACK 0 PASSING MertechInc_Blank sStatement 0 RESULT MertechInc_iRet
End_Procedure

//=============================================================================
/// @Name        SQL_APPEND
/// @Description Appends a string value to the current embedded sql statement
/// already set.
///
/// @Assumptions Parameter may be more than 255 characters long so redirect to method.
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-20 by Aaron Gulack
/// @See		 SQL_APPEND_STMT
#COMMAND SQL_APPEND R
    #IFDEF MertechInc_Obsolete_Code
        DO_GETFILENUMBER_DRIVERNAME 0
        If (MertechInc_FileNumber <> -1) Begin
            Send MertechInc_SQL_APPEND !1
            If MertechInc_iRet EQ -1 INDICATE ERR True

            #IF (!0>1)
                SQL_APPEND !2 !3 !4 !5 !6 !7 !8 !9
            #ENDIF
        End
    #ELSE
        MertechInc_Error_Obsolete_Code
    #ENDIF
#ENDCOMMAND

Procedure MertechInc_SQL_APPEND Global String sStatement
    Call_Driver 0 MertechInc_DriverName Function 2 CALLBACK 0 PASSING MertechInc_Blank sStatement 0 RESULT MertechInc_iRet
End_Procedure

//=============================================================================
/// @Name        SQL_EXECUTE
/// @Description Executes the current embedded SQL statement set and commits
/// finishing any pending transaction.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-20 by Aaron Gulack
/// @See	  	 SQL_EXECUTE_STMT
#COMMAND SQL_EXECUTE
    #IFDEF MertechInc_Obsolete_Code
        #IF (!0>0)
            SQL_SET !1
            #IF (!0>1)
                SQL_APPEND !2 !3 !4 !5 !6 !7 !8 !9
            #ENDIF
        #ENDIF

        DO_GETFILENUMBER_DRIVERNAME 0
        If (MertechInc_FileNumber <> -1) Begin
            Call_Driver 0 MertechInc_DriverName Function 3 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
            If MertechInc_iRet EQ -1 INDICATE ERR True
        End
    #ELSE
        MertechInc_Error_Obsolete_Code
    #ENDIF
#ENDCOMMAND

//=============================================================================
/// @Name        LOCK_TABLE
/// @Description Locks a table. This is equivalent to locking a DAT file.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     DB2Flex, and ORAFlex 3.x
/// @VersionNote Last Revised: 2013-08-20 by Aaron Gulack
/// @See
///
/// @Syntax LOCK_TABLE {FileName} {FileName1} {FileName2} {FileName3}...
/// @Param  FileName 		The name of file to be locked. Can be more than one
#COMMAND LOCK_TABLE R
    #IFDEF MertechInc_Obsolete_Code
        DO_GETFILENUMBER_DRIVERNAME !1
        //DbDKDriver states that function is only vaid for ORAFLEX and not MDSDB2!!!
        If (MertechInc_DriverName EQ ORAFLEX or MertechInc_DriverName EQ MDSDB2) Begin
            Lock
            Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 16 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
            If MertechInc_iRet EQ -1 INDICATE ERR True
        End
        #IF !0>1
            LOCK_TABLE !2 !3 !4 !5 !6 !7 !8 !9
        #ENDIF
    #ELSE
        MertechInc_Error_Obsolete_Code
    #ENDIF
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_CHECK_TABLE
/// @Description Use this command to verify that a given table exists on the
/// SQL backend. This command takes three arguments, a string containing the
/// name of the database, a string containing the name of the user and finally
/// a string containing the name of the table being checked. If the table exists,
/// the program proceeds normally. If the table does not exist then the flag
/// "finderr" is set to true. Note that in order to handle the error a check must
/// be done on the "finderr" variable.
///
/// @Assumptions All three parameters are less than 256 characters long.
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-20 by Aaron Gulack
/// @See
///
/// @Syntax SQL_CHECK_TABLE {database} {username} {table}
/// @Param  database		Name of the database
/// @Param  username     	Name of the user
/// @Param  table			Name of the table being checked
///
/// @Example
/// SQL_CHECK_TABLE "testDB" "user" "Customer"
/// If (finderr) Begin
///     Showln "This table does not exist"
/// End
#COMMAND SQL_CHECK_TABLE R R
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Move !1 to MertechInc_sArg1
        #IF (!0>2)
            Append MertechInc_sArg1 "*" !2
            Move !3 to MertechInc_sArg2
        #ELSE
            Move !2 to MertechInc_sArg2
        #ENDIF
        Call_Driver 0 MertechInc_DriverName Function 4 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 0 RESULT MertechInc_iRet
        If MertechInc_iRet EQ 0 INDICATE Found False
        Else INDICATE Found True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SET_SQL_CONSTRAINT
/// @Description This command allows you to put an additional constraint on
/// your finds, moving filtering to the SQL backend. Using this command can
/// result in significantly improved performance, since the server network traffic
/// reduced. Note that the SQL statement passed for this command is added onto
/// the predefined Database SQL statement so treat it as such. Because of this,
/// it will almost always begin with "AND" followed by the desired constraint.
///
/// @Assumptions Parameter may be more than 255 characters long so redirect to method.
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-20 by Aaron Gulack
/// @See    	 SQL_CONSTRAINT GET_SQL_CONSTRAINT DF_FIELD_PROGRAMMATIC_DEFAULT
///
/// @Syntax SET_SQL_CONSTRAINT of {file} to {variable}
/// @Param  file			Name or Number of the file.
/// @Param  variable		A SQL expression that constrains the data
///
/// @Example
/// Open Customer
///
/// SET_SQL_CONSTRAINT of 1 to (SFormat('AND "%1"."%2" = ' + "'%3'", "Customer", "Status", "Active"))
///
/// For_All Customer by Index.1 do
///    	Showln Customer.FirstName
/// End_For_All
#COMMAND SET_SQL_CONSTRAINT "OF" R "TO""FROM_PROGRAMMATIC_DEFAULTS"
    DO_GETFILENUMBER_DRIVERNAME !2
    If (MertechInc_DriverName EQ SQLFLEX or MertechInc_DriverName EQ ORAFLEX or MertechInc_DriverName EQ MDSMySQL or MertechInc_DriverName EQ MDSPgSQL) Begin
        #IFSAME !3 to
            // We will leave the driver to take care of the constrain expression
            If MertechInc_DriverName EQ SQLFLEX Send MertechInc_SET_SQL_CONSTRAINT 36 !4
            Else                                Send MertechInc_SET_SQL_CONSTRAINT 37 !4
            If MertechInc_iRet EQ -1 INDICATE ERR True
        #ELSE
            If MertechInc_DriverName EQ SQLFLEX Send MertechInc_SET_SQL_CONSTRAINT_PROGRAMMATIC 36
            Else                                Send MertechInc_SET_SQL_CONSTRAINT_PROGRAMMATIC 37
            If MertechInc_iRet EQ -1 INDICATE ERR True
        #ENDIF
    End
#ENDCOMMAND

Procedure MertechInc_SET_SQL_CONSTRAINT Global Integer iFunction String sConstraint
    Call_Driver MertechInc_FileNumber MertechInc_DriverName Function iFunction CALLBACK 0 PASSING sConstraint MertechInc_Blank 0 RESULT MertechInc_iRet
End_Procedure

Procedure MertechInc_SET_SQL_CONSTRAINT_PROGRAMMATIC Global Integer iFunction
    Call_Driver MertechInc_FileNumber MertechInc_DriverName Function iFunction CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 4 RESULT MertechInc_iRet
End_Procedure

//=============================================================================
/// @Name        GET_SQL_CONSTRAINT
/// @Description This command returns the current SQL constraint for the given
/// table.  If there is no current constraint, then a blank string is returned.
///
/// @Assumptions Parameter may be more than 255 characters long so redirect to method.
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-20 by Aaron Gulack
/// @See    	 SQL_CONSTRAINT SET_SQL_CONSTRAINT
///
/// @Syntax GET_SQL_CONSTRAINT of {File} to {variable}
/// @Param  File			Name or number of the file
/// @Param  variable		The string containing the constraining SQL expression
///
/// @Example
/// Open Customer
///
/// String sCon
///
/// SET_SQL_CONSTRAINT of Customer to (SFormat('AND "%1"."%2" = ' + "'%3'", "Customer", "Status", "Active"))
/// GET_SQL_CONSTRAINT of Customer to sCon
///
/// For_All Customer by Index.1 do
///    	Showln Customer.FirstName
///    	Showln sCon
/// End_For_All
#COMMAND GET_SQL_CONSTRAINT "OF" R "TO" R .
    DO_GETFILENUMBER_DRIVERNAME !2
    If (MertechInc_FileNumber <> -1) Begin
        If MertechInc_DriverName EQ SQLFLEX Get MertechInc_GET_SQL_CONSTRAINT 36 TO !4
        Else                                Get MertechInc_GET_SQL_CONSTRAINT 37 TO !4

        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    END
#ENDCOMMAND

Function MertechInc_GET_SQL_CONSTRAINT Global Integer iFunction Returns String
    String sConstraint
    Get MertechInc_Pre_Size_String 0 to sConstraint

    Call_Driver MertechInc_FileNumber MertechInc_DriverName Function iFunction CALLBACK 0 PASSING sConstraint MertechInc_Blank 3 RESULT MertechInc_iRet
    Function_Return sConstraint
End_Function

//=============================================================================
/// @Name        SQL_CONSTRAINT
/// @Description This command is used to toggle on or off the current SQL
/// constraint that is set for a table. To deactivate the current constraint,
/// pass the constant DEACTIVATE to this command. to reactivate the constraint,
/// pass ACTIVATE to this command.
///
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-20 by Aaron Gulack
/// @See         SET_SQL_CONSTRAINT GET_SQL_CONSTRAINT
///
/// @Syntax SQL_CONSTRAINT of {File} to {Activate|Deactivate}
/// @Param  File			Name or Number of the file
/// @Param  Activate  		Activates the constraint
/// @Param  Deactivate 		Deactivates the constraint
///
/// @Example
/// Open Customer
///
/// SET_SQL_CONSTRAINT of Customer to (SFormat('AND "%1"."%2" = ' + "'%3'", "Customer", "FirstName", "Aaron"))
/// SQL_CONSTRAINT of Customer to Deactivate
///
/// For_All Customer by Index.1 do
///     Showln Customer.FirstName
/// End_For_All
#COMMAND SQL_CONSTRAINT "OF" R TO "ACTIVATE""DEACTIVATE" .
    DO_GETFILENUMBER_DRIVERNAME !2
    If (MertechInc_FileNumber <> -1) Begin
        If MertechInc_DriverName EQ SQLFLEX Move 36 to MertechInc_iFunction
        Else                                Move 37 to MertechInc_iFunction

        #IFSAME !4 ACTIVATE
            Call_Driver MertechInc_FileNumber MertechInc_DriverName Function MertechInc_iFunction CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 1 RESULT MertechInc_iRet
        #ELSE
            Call_Driver MertechInc_FileNumber MertechInc_DriverName Function MertechInc_iFunction CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 2 RESULT MertechInc_iRet
        #ENDIF
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        CREATE_TD_FILE
/// @Description A .TD file is created when the attribute is set to True.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-20 by Aaron Gulack
/// @See
///
/// @Syntax CREATE_TD_FILE {variable}
/// @Param  variable		True to create the .TD file, false doesn't create it.
#COMMAND CREATE_TD_FILE R
    #IFDEF MertechInc_Obsolete_Code
        DO_GETFILENUMBER_DRIVERNAME 0
        If (MertechInc_FileNumber <> -1) Begin
            Call_Driver 0 MertechInc_DriverName Function 5 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank !1 RESULT MertechInc_iRet
            If MertechInc_iRet EQ -1 INDICATE ERR True
        End
    #ELSE
        MertechInc_Error_Obsolete_Code
    #ENDIF
#ENDCOMMAND

//=============================================================================
/// @Name        OPEN_INT
/// @Description This command is used to replace the OPEN command in DataFlex.
/// It can be useful when accessing tables that are not in the current filelist.
/// To access these tables, the INT and FD files must be in the directory. From
/// there, all that is needed is to open the table using this command under an
/// alias name. If the command is executed successfully then the table can be
/// queried normally as if it were a standard table. Note that if the desired
/// table is already in the filelist or doesn't have an INT file then this
/// command will act as a normal open command.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-21 by Aaron Gulack
/// @See
///
/// @Syntax OPEN_INT {variable} as {aliasName}
/// @Param  variable		The name of the int file without the extension.
/// @Param  aliasName		The alias name being used to query this table.
/// @Example
/// OPEN_INT "customer" as Customer
///
/// For_All Customer by Index.1 do
///     Showln Customer.FirstName
/// End_For_All
#COMMAND OPEN_INT
    #IFSAME !2 as   // CHECK IF THERE IS AN INTERMEDIATE FILE TO OPEN
        Move (UPPERCASE(!1)) to MertechInc_sWork
        Get Seq_New_Channel  to MertechInc_iWork

        If (MertechInc_iWork <> DF_SEQ_CHANNEL_NOT_AVAILABLE) Begin
            If (POS(".INT",MertechInc_sWork) EQ 0) Begin
                Direct_Input channel MertechInc_iWork (!1 + ".INT")
                [ not SeqEof ] Begin // OPEN THE INTERMEDIATE FILE
                    Close_Input channel MertechInc_iWork
                    DO_GETFILENUMBER_DRIVERNAME 0
                    If (MertechInc_FileNumber <> -1) Begin
                        API_OPEN (MertechInc_DriverName + ":" + !1) !2 !3 !4 !5 !6 !7 !8 !9
                    End
                End
                [ SeqEof ] Begin // THERE ISN'T INTERMEDIATE FILE
                    INDICATE ERR False
                    Close_Input channel MertechInc_iWork
                    API_OPEN !1 !2 !3 !4 !5 !6 !7 !8 !9
                End
            End
            Else Begin
                REPLACE ".INT" IN MertechInc_sWork WITH ""
                DO_GETFILENUMBER_DRIVERNAME 0
                If (MertechInc_FileNumber <> -1) Begin
                    API_OPEN (MertechInc_DriverName + ":" + !1) !2 !3 !4 !5 !6 !7 !8 !9
                End
            End

            Send Seq_Release_Channel MertechInc_iWork
        End
        Else Begin
            Error 25000 "No free channels are available to use for the OPEN_INT command."
        End
    #ELSE
        Declare_Datafile !1

        #IFDEF !1
            Move !1 to FILENUMBER
        #ELSE
            #IFDEF !1.RECNUM
                #SET Q$ !1.RECNUM
            #ELSE
                #SET Q$ !1.FILE_NUMBER
            #ENDIF
            !A [] $82 |CI!q FILENUMBER
        #ENDIF

        Get_Attribute DF_FILE_ROOT_NAME of FILENUMBER to MertechInc_sWork
        Move (UPPERCASE(MertechInc_sWork)) to MertechInc_sWork

        If (POS(".INT",MertechInc_sWork) NE 0) Begin
            REPLACE ".INT" IN MertechInc_sWork WITH ""
            DO_GETFILENUMBER_DRIVERNAME 0
            If (MertechInc_FileNumber <> -1) Begin
                API_OPEN (MertechInc_DriverName + ":" + MertechInc_sWork) as !1
            End
        End
        Else Begin
            API_OPEN !1 !2 !3 !4 !5 !6 !7 !8 !9
        End
    #ENDIF
#ENDCOMMAND

//=============================================================================
/// @Name        SET_OPEN_MODE
/// @Description This command is used to enable an option known as "Lazy Open
/// Mode". When turned on the table's metadata i.e. table, columns, index
/// descriptions, is deferred until a field is accessed, even if a OPEN has
/// already been done. This can significantly improve an application's initial
/// performance, especially when a large number of files are opened when the
/// program is launched. By default, tables are set to open normally, but by
/// passing the constant LAZY_MODE to this command, it can be altered to use
/// this mode. Note that when this mode is activated, it effects all tables
/// that are opened. To deactivate this feature, pass the constant "DEFAULT"
/// to this command at any time. This is the preferred method to activate or
/// deactive this feature but it can also be set globally in the .INI file.
///
/// Default Value: DEFAULT (Off)
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-21 by Aaron Gulack
/// @See
///
/// @Syntax SET_OPEN_MODE to {DEFAULT/LAZY_MODE}
/// @Param  DEFAULT			Used to turn of the lazy mode feature.
/// @Param  LAZY_MODE		Turns on the lazy mode feature
///
/// @Example
/// SET_OPEN_MODE TO LAZY_MODE
/// Open "customer.int" as Customer
/// ...
/// ...
/// Find gt Customer by Index.1
#COMMAND SET_OPEN_MODE "TO" "DEFAULT""LAZY_MODE" .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        #IFSAME !4 DEFAULT
            MOVE 0 to MertechInc_sArg1
        #ELSE
            MOVE 1 to MertechInc_sArg1
        #ENDIF

        Call_Driver 0 MertechInc_DriverName Function CALLDRV_LICENSE_ENVIRONMENT_SET CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank CALLDRV_USE_LAZY_OPEN_MODE RESULT MertechInc_iRet
        If MertechInc_iRet EQ 0 INDICATE Found False
        Else INDICATE Found True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_SET_STMT
/// @Description Use this command to set an SQL statement to be executed on the
/// desired table. The string passed to this command must be a valid SQL
/// expression and must be on a table that has already been opened. Note that
/// when using this command, the SQL_PREPARE_STMT and SQL_EXECUTE_STMT must be
/// used in addition to carry out the expression. The option to pass the file
/// name as an extra parameter is used in cases where the data needs to be
/// fetched directly into the record buffer of the specified file.
///
/// @Assumptions Parameter may be more than 255 characters long so redirect to method.
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-21 by Aaron Gulack
/// @See		 SQL_APPEND_STMT SQL_PREPARE_STMT SQL_EXECUTE_STMT SQL_CANCEL_QUERY_STMT SQL_FETCH_NEXT_ROW SQL_BINDCOLUMNS_STMT
///
/// @Syntax SQL_SET_STMT [of {file}] to {variable}
/// @Param file				Name or number of the file (optional)
/// @Param variable			String containing the SQL statement
///
/// @Usage SQL_SET_STMT of Customer to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active'"
/// @Usage SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active'"
///
/// @Example
/// Open Customer
///
/// String sID sFirstName sLastName sDOB
///
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active'"
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// While (Found)
/// SQL_FETCH_NEXT_ROW into sID sFirstName sLastName sDOB
/// 	Showln sID
///     Showln sFirstName
///     Showln sLastName
///     Showln sDOB
/// Loop
/// SQL_CANCEL_QUERY_STMT
#COMMAND SQL_SET_STMT "OF""TO"""
    #IFSAME !1 OF
        #CHECK !3 "TO"
        DO_GETFILENUMBER_DRIVERNAME !2
        If (MertechInc_FileNumber <> -1) Begin
            Send MertechInc_SQL_SET_STMT !4
            IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
        END
        #IF (!0>4)
            SQL_APPEND_STMT !1 !2 !3 !5 !6 !7 !8 !9
        #ENDIF
    #ELSE
        #CHECK !1 "TO"
        DO_GETFILENUMBER_DRIVERNAME 0
        If (MertechInc_FileNumber <> -1) Begin
            Send MertechInc_SQL_SET_STMT !2
            IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
        END
        #IF (!0>2)
            SQL_APPEND_STMT !1 !3 !4 !5 !6 !7 !8 !9
        #ENDIF
    #ENDIF
#ENDCOMMAND

Procedure MertechInc_SQL_SET_STMT Global String sStatment
    Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 22 CALLBACK 0 PASSING MertechInc_Blank sStatment 0 RESULT MertechInc_iRet
End_Procedure

//=============================================================================
/// @Name        SQL_APPEND_STMT
/// @Description This command is used to append a command string to the
/// command buffer initialized by SQL_SET_STMT. SQL_APPEND_STMT was added
/// so that long SQL expressions could be broken into smaller strings and
/// appended to a dynamic command buffer, which is then passed to the server.
/// The SQL_APPEND_STMT will concatenate a string to the command buffer
/// initialized by the SQL_SET_STMT command. SQL_APPEND_STMT can be called as
/// many times as necessary to complete the SQL expression. Subsequently, the
/// SQL_EXECUTE_STMT command executes the completed command.  The option to
/// pass the file name as an extra parameter is used in cases where the data
/// needs to be fetched directly into the record buffer of the specified file.
///
/// @Assumptions Parameter may be more than 255 characters long so redirect to method.
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-22 by Aaron Gulack
/// @See		 SQL_SET_STMT SQL_PREPARE_STMT SQL_EXECUTE_STMT SQL_CANCEL_QUERY_STMT SQL_FETCH_NEXT_ROW SQL_BINDCOLUMNS_STMT
///
/// @Syntax SQL_APPEND_STMT [of {file}] to {variable}
/// @Param file				The name or number of the file (optional)
/// @Param variable			The string to be appended to the current SQL expression
///
/// @Usage SQL_APPEND_STMT to " CUSTOMER.PHONE_NUMBER, CUSTOMER.FAX_NUMBER"
/// @Usage SQL_APPEND_STMT of Customer to " CUSTOMER.PHONE_NUMBER, CUSTOMER.FAX_NUMBER"
///
/// @Example
/// Open Customer
///
/// String sID sFirstName sLastName sDOB
///
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active'"
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// While (Found)
/// 	SQL_FETCH_NEXT_ROW into sID sFirstName sLastName sDOB
/// 	Showln sID
///     Showln sFirstName
///     Showln sLastName
///     Showln sDOB
/// Loop
/// SQL_CANCEL_QUERY_STMT
#COMMAND SQL_APPEND_STMT "OF""TO"""
    #IFSAME !1 OF
        #CHECK !3 "TO"
        DO_GETFILENUMBER_DRIVERNAME !2
        If (MertechInc_FileNumber <> -1) Begin
            Send MertechInc_SQL_APPEND_STMT !4
            IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
        END
        #IF (!0>4)
            SQL_APPEND_STMT !1 !2 !3 !5 !6 !7 !8 !9
        #ENDIF
    #ELSE
        #CHECK !1 "TO"
        DO_GETFILENUMBER_DRIVERNAME 0
        If (MertechInc_FileNumber <> -1) Begin
            Send MertechInc_SQL_APPEND_STMT !2
            IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
        END
        #IF (!0>2)
            SQL_APPEND_STMT !1 !3 !4 !5 !6 !7 !8 !9
        #ENDIF
    #ENDIF
#ENDCOMMAND

Procedure MertechInc_SQL_APPEND_STMT Global String sStatement
    Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 22 CALLBACK 0 PASSING MertechInc_Blank sStatement 1 RESULT MertechInc_iRet
End_Procedure

//=============================================================================
/// @Name        APPEND_UPDATE_COLUMN
/// @Description Append a given string to the existing SQL statement
/// already set.
///
/// @Assumptions Parameter may be more than 255 characters long so redirect to method
/// @Status      Internal
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-23 by Aaron Gulack
/// @See
///
/// @Syntax APPEND_UPDCOL_STMT {variable} for {fileName}.{fieldName} {fields...}
/// @Param variable				SQL expression to be appended
/// @Param fileName				Name of the file
/// @Param fieldName			Name of the field
/// @Param fields...			Any additional fields, use the file.field format
#COMMAND APPEND_UPDATE_COLUMN R "FOR" R
    Move (LENGTH(|CS'!3')) to MertechInc_iWork                                     //GET FIELDNUMBER
    Move (MertechInc_iWork - POS(",",|CS'!3')) to MertechInc_iWork
    Move (RIGHT(|CS'!3',MertechInc_iWork)) to MertechInc_iWork
    Get_Attribute DF_FIELD_NAME of MertechInc_FileNumber MertechInc_iWork to MertechInc_sWork    //GET COLUMN NAME
    Send MertechInc_APPEND_UPDATE_COLUMN (","*MertechInc_sWork*"="*String(!1))            //WRITE , COLUMN NAME = VALUE

    If MertechInc_iRet EQ -1 INDICATE ERR True

    #IF (!0>3)
        APPEND_UPDATE_COLUMN !1 FOR !4 !5 !6 !7 !8 !9
    #ENDIF
#ENDCOMMAND

Procedure MertechInc_APPEND_UPDATE_COLUMN Global String sStatement
    Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 22 CALLBACK 0 PASSING MertechInc_Blank sStatement 1 RESULT MertechInc_iRet
End_Procedure

//=============================================================================
/// @Name        SQL_APPEND_UPDCOL_STMT
/// @Description Used to optimize the update process of columns being loaded
/// with the same value.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-23 by Aaron Gulack
/// @See
///
/// @Syntax SQL_APPEND_UPDCOL_STMT [of {file}] Value {variable} for {fileName}.{fieldName} {fields...}
/// @Param file				The name or number of the file (optional)
/// @Param variable			The value being uploaded
/// @Param fileName			The name of the file
/// @Param fieldName		The name of the field
/// @Param fields...		Any additional fields, use the file.field format
///
/// @Example
/// Open Customer
///
/// SQL_SET_STMT    of Customer to "UPDATE CUSTOMER SET"
/// SQL_APPEND_STMT of Customer to " ASC11='x', ASC12='y', ASC13='z'"
///
/// SQL_APPEND_UPDCOL_STMT of Customer value 0 ;
///     for Customer.ID Customer.Purchases Customer.Credit ;
///
/// SQL_APPEND_STMT of Customer to " WHERE RECNUM=1"
///
/// SQL_PREPARE_STMT of Customer
/// SQL_EXECUTE_STMT of Customer
#COMMAND SQL_APPEND_UPDCOL_STMT "OF" R "VALUE" R "FOR" R
    DO_GETFILENUMBER_DRIVERNAME !2
    If (MertechInc_FileNumber <> -1) Begin
        APPEND_UPDATE_COLUMN !4 for !6 !7 !8 !9
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_SET_CURSOR_TYPE
/// @Description Specify the SQL cursor type to be used during the next
/// embedded SQL statement execution.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-08-23 by Aaron Gulack
/// @See
///
/// @Syntax SQL_SET_CURSOR_TYPE to {TYPE_NONE/TYPE_CLIENT/TYPE_SERVER}
/// @Param TYPE_NONE			the default cursor type should be used
/// @Param TYPE_CLIENT 			a client side cursor should be used
/// @Param TYPE_SERVER 			a server side cursor should be used
#COMMAND SQL_SET_CURSOR_TYPE "TO" "TYPE_NONE""TYPE_CLIENT""TYPE_SERVER"""
    If MertechInc_DriverName EQ SQLFLEX Begin
        Move 0 to MertechInc_iArg
        #IFSAME !2 TYPE_CLIENT
            Move CALLDRV_ENUMERATE_CURSOR_TYPE_CLIENT to MertechInc_iArg
        #ELSE
            #IFSAME !2 TYPE_SERVER
                Move CALLDRV_ENUMERATE_CURSOR_TYPE_SERVER to MertechInc_iArg
            #ELSE
                Move CALLDRV_ENUMERATE_CURSOR_TYPE_NONE to MertechInc_iArg
            #ENDIF
        #ENDIF

        Call_Driver 0 MertechInc_DriverName Function CALLDRV_SET_SQL_CURSOR_TYPE CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        CLEAR_INT_CACHE
/// @Description Clears all memory-cached INT info. This is used in the
/// test framework to force a "reload" of int info which the framework
/// modifies for its tests. This is a different cache than the TD files
/// which are a file based cache of the structure for use at file open.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-23 by Aaron Gulack
/// @See
///
/// @Syntax CLEAR_INT_CACHE
#COMMAND CLEAR_INT_CACHE
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_CLEAR_INT_CACHE CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        CREATE_INVERSE_KEY_FUNCTIONS
/// @Description Create SQL Functions to handle Inverse Key columns.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     All (v10.1 and above)
/// @VersionNote Last Revised: 2013-08-23 by Aaron Gulack
/// @See
///
/// @Syntax CREATE_INVERSE_KEY_FUNCTIONS
#COMMAND CREATE_INVERSE_KEY_FUNCTIONS .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_CREATE_INVK_FUNCTIONS CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_PREPARE_STMT
/// @Description Prepares a statement and opens a cursor to be executed by
/// SQL_EXECUTE_STMT. This command tells the server to parse the SQL statement
/// created by the respective SQL_SET_STMT and all subsequent SQL_APPEND_STMT
/// statements and to allocate cursor handles to be used to fetch the data.
/// A cursor can be thought of as a pointer to a record set. The CURSOR_TYPE
/// argument is only supported by SQLFlex and by default SQLFLex is using a
/// TYPE_SERVER cursor type to all embedded SQL. TYPE_CLIENT should be used only
/// for the statements that are querying LOB columns i.e. TEXT, NVARCHAR(MAX),
/// VARCHAR(MAX), IMAGE, VARBINARY(MAX), XML. If the cursor type is
/// TYPE_SERVER and a LOB type column is selected, MS SQL Server will not be
/// able to get into a transaction, either explicitly or implicitly through a
/// REREAD, LOCK, SAVERECORD, etc.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-23 by Aaron Gulack
/// @See		 SQL_SET_STMT SQL_APPEND_STMT SQL_EXECUTE_STMT SQL_CANCEL_QUERY_STMT SQL_FETCH_NEXT_ROW SQL_BINDCOLUMNS_STMT
///
/// @Syntax SQL_PREPARE_STMT [of {file}] CURSOR_TYPE {TYPE_NONE/TYPE_CLIENT/TYPE_SERVER}
/// @Param file				The name or number of the file (optional)
/// @Param CURSOR_TYPE 		Used if the cursor type is being set, do not include otherwise
/// @Param TYPE_NONE   		Default cursor will be used
/// @Param TYPE_CLIENT 		A client side cursor should be used
/// @Param TYPE_SERVER 		A server side cursor should be used (Default)
///
/// @Usage SQL_PREPARE_STMT
/// @Usage SQL_PREPARE_STMT of Customer
/// @Usage SQL_PREPARE_STMT CURSOR_TYPE TYPE_SERVER
/// @Usage SQL_PREPARE_STMT of Customer CURSOR_TYPE TYPE_CLIENT
///
/// @Example
/// Open Customer
///
/// String sID sFirstName
///
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active'"
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// SQL_FETCH_NEXT_ROW into sID sFirstName
#COMMAND SQL_PREPARE_STMT "OF""CURSOR_TYPE"""
    #IFSAME !1 of
        DO_GETFILENUMBER_DRIVERNAME !2
        If (MertechInc_FileNumber <> -1) Begin
            #IFSAME !3 CURSOR_TYPE
                SQL_SET_CURSOR_TYPE to !4
            #ENDIF
            Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 22 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 2 RESULT MertechInc_iRet
            If MertechInc_iRet EQ -1 INDICATE ERR True
        End
    #ELSE
        DO_GETFILENUMBER_DRIVERNAME 0
        If (MertechInc_FileNumber <> -1) Begin
            #IFSAME !1 CURSOR_TYPE
                SQL_SET_CURSOR_TYPE to !2
            #ELSE
                #CHECK !1 .
            #ENDIF
            Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 22 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 2 RESULT MertechInc_iRet
            If MertechInc_iRet EQ -1 INDICATE ERR True
        End
    #ENDIF
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_BIND_COLUMN
/// @Description Clears all cached INT info. This should be merged with
/// SQL_BINDCOLUMNS_STMT, but has to remain as a separate command for
/// compatibility.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-26 by Aaron Gulack
/// @See
///
/// @Syntax SQL_BIND_COLUMN FileNumber FieldNumber | DF_BIND_ALL_COLUMNS
/// @Param FileNumber			The number of the file
/// @Param FieldNumber			The number of the field
#COMMAND SQL_BIND_COLUMN R R .
    DO_GETFILENUMBER_DRIVERNAME !1
    If (MertechInc_FileNumber <> -1) Begin
        #IFTYPE !2 "I"
            Move !2 to MertechInc_iWork
        #ELSE
            Move (LENGTH(|CS'!2')) to MertechInc_iWork
            Move (MertechInc_iWork - POS(",",|CS'!2')) to MertechInc_iWork
            Move (RIGHT(|CS'!2',MertechInc_iWork)) to MertechInc_iWork
        #ENDIF
        Move MertechInc_iWork to MertechInc_sArg1
        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 22 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 3 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_BINDCOLUMNS_STMT
/// @Description This command is used to fetch the returned data of a
/// specified SQL expression into the given field in the record buffer. By
/// passing any number of fields to this command, the fetched record will then
/// be put into the subsequent fields in the record buffer. The order of the
/// fields must be the same as the order of the columns being retrieved from
/// the SQL expression. SQL_FETCH_NEXT_ROW can then be called to take the data
/// retrieved from the server and place it into the corresponding fields in the
/// buffer. Instead of specifying each field, DF_BIND_ALL_COLUMNS can be passed,
/// which will retrieve every column in the table.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-26 by Aaron Gulack
/// @See 		 SQL_SET_STMT SQL_APPEND_STMT SQL_PREPARE_STMT SQL_EXECUTE_STMT SQL_CANCEL_QUERY_STMT SQL_FETCH_NEXT_ROW
///
/// @Syntax SQL_BINDCOLUMNS_STMT of {file} to {field/DF_BIND_ALL_COLUMNS}
///
/// @Param file              	Name or number of the file
/// @Param field        		Name or number of the field (can be multiple)
/// @Param DF_BIND_ALL_COLUMNS  Used instead of the field to retrieve all columns in the file
///
/// @Example
/// Open Customer
///
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active' "
/// SQL_PREPARE_STMT
/// SQL_BINDCOLUMNS_STMT of Customer to DF_BIND_ALL_COLUMNS
/// SQL_EXECUTE_STMT of Customer
/// While (Found)
///     SQL_FETCH_NEXT_ROW of Customer
///     Showln Customer.ID
///     Showln Customer.FirstName
///     Showln Customer.LastName
///     Showln Customer.DOB
/// Loop
/// SQL_CANCEL_QUERY_STMT
#COMMAND SQL_BINDCOLUMNS_STMT "OF" !R "TO" !R
    #IFDEF !4
        SQL_BIND_COLUMN !2 !4
    #ELSE
        SQL_BIND_COLUMN !2 !2.!4
    #ENDIF
    #IF (!0>4)
        SQL_BINDCOLUMNS_STMT !1 !2 !3 !5 !6 !7 !8 !9
    #ENDIF
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_EXECUTE_STMT
/// @Description This command is used to execute the SQL expression created
/// by the SQL_SET_STMT and any subsequent SQL_APPEND_STMT commands issued
/// after a SQL_PREPARE_STMT. If the results will be sent to the record
/// buffer directly, then the file must be specified. An optional parameter
/// can also be passed, indicating the maximum number of rows to be sent to
/// the local cache. This is done by adding the constant ROWCOUNT followed
/// by the maximun number.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-26 by Aaron Gulack
/// @See		 SQL_SET_STMT SQL_APPEND_STMT SQL_PREPARE_STMT SQL_CANCEL_QUERY_STMT SQL_FETCH_NEXT_ROW SQL_BINDCOLUMNS_STMT
///
/// @Syntax SQL_EXECUTE_STMT [of {file} ROWCOUNT {variable}]
/// @Param file				Name or number of the file (optional)
/// @Param variable			Maximum number of rows to send to the local cache (optional)
///
/// @Usage SQL_EXECUTE_STMT
/// @Usage SQL_EXECUTE_STMT of Customer
/// @Usage SQL_EXECUTE_STMT of Customer ROWCOUNT 10
///
/// @Example
/// Open Customer
///
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active' "
/// SQL_PREPARE_STMT
/// SQL_BINDCOLUMNS_STMT of Customer to DF_BIND_ALL_COLUMNS
/// SQL_EXECUTE_STMT of Customer
/// While (Found)
///     SQL_FETCH_NEXT_ROW of Customer
///     Showln Customer.ID
///     Showln Customer.FirstName
///     Showln Customer.LastName
///     Showln Customer.DOB
/// Loop
/// SQL_CANCEL_QUERY_STMT
#COMMAND SQL_EXECUTE_STMT "OF""ROWCOUNT"""
    Move 10 to MertechInc_sArg1         // Initialize the Row_Count value

    #IFSAME !1 OF
        DO_GETFILENUMBER_DRIVERNAME !2
        If (MertechInc_FileNumber <> -1) Begin
            #IFSAME !3 ROWCOUNT
                Move !4 to MertechInc_sArg1
            #ENDIF
            Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 22 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 5 RESULT MertechInc_iRet
            If MertechInc_iRet EQ -1 INDICATE ERR True
            else indicate found true
        End
    #ELSE
        DO_GETFILENUMBER_DRIVERNAME 0
        If (MertechInc_FileNumber <> -1) Begin
            #IFSAME !1 ROWCOUNT
                Move !2 to MertechInc_sArg1
            #ELSE
                #IF (!0>0)
                    SQL_SET_STMT to !1
                    #IF (!0>1)
                        SQL_APPEND_STMT to !2 !3 !4 !5 !6 !7 !8 !9
                    #ENDIF
                #ENDIF
            #ENDIF
            Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 22 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 5 RESULT MertechInc_iRet
            If MertechInc_iRet EQ -1 INDICATE ERR True
            else indicate found true
        End
    #ENDIF
#ENDCOMMAND

#Replace SQL_PROCEDURE_EXECUTE SQL_EXECUTE_STMT
#Replace MDS_PROCEDURE_EXECUTE SQL_EXECUTE_STMT

//This alias may be redundant. Is was only called from MertechInc_SQL_FUNCTION_EXECUTE
//which has been recoded to directly call SQL_EXECUTE_STMT - I.S. 2009-09-19
Procedure MertechInc_SQL_PROCEDURE_EXECUTE Global
    SQL_EXECUTE_STMT
End_Procedure

//=============================================================================
/// @Name        SQL_START_TRANSACTION_STMT
/// @Description Transactions in SQL are used to maintain atomicity within
/// an process. If one procedure in the transaction fails, then they all
/// will fail. This command is used to start an SQL transaction. Inside of
/// a transaction, there can be any number of SQL statements, none of which
/// will be executed until SQL_COMMIT_STMT is called. Note that transactions
/// are generally only needed when a table is being altered.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-26 by Aaron Gulack
/// @See         SQL_COMMIT_STMT SQL_ROLLBACK_STMT
///
/// @Syntax SQL_START_TRANSACTION_STMT
///
/// @Example
/// SQL_START_TRANSACTION_STMT
/// SQL_SET_STMT to "UPDATE CUSTOMER SET STATUS = 'Inactive'"
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// SQL_COMMIT_STMT
#COMMAND SQL_START_TRANSACTION_STMT .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_DriverName EQ ORAFlex) Begin
        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 22 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 9 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
    Else If (MertechInc_DriverName EQ SQLFlex or MertechInc_DriverName EQ MDSMySQL or MertechInc_DriverName EQ MDSPgSQL) Begin
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_SQL_TRANSACTION CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_COMMIT_STMT
/// @Description Just as the SQL_EXECUTE_STMT is used to execute the SQL
/// statement in the block, this command is used to commit the transaction
/// started by SQL_START_TRANSACTION_STMT. When this command is called, any
/// preceding statements or procedures that are apart of the transaction will
/// be committed. If one or more of these statements fail, then none of them
/// will be successful, thus maintaining atomicity.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-27 by Aaron Gulack
/// @See		 SQL_START_TRANSACTION_STMT SQL_ROLLBACK_STMT
///
/// @Syntax SQL_COMMIT_STMT
///
/// @Example
/// SQL_START_TRANSACTION_STMT
/// SQL_SET_STMT to "UPDATE CUSTOMER SET STATUS = 'Inactive'"
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// SQL_COMMIT_STMT
#COMMAND SQL_COMMIT_STMT .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_DriverName EQ ORAFlex) Begin
        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 22 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 7 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
    Else If (MertechInc_DriverName EQ SQLFlex or MertechInc_DriverName EQ MDSPgSQL or MertechInc_DriverName EQ MDSMySQL) Begin
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_SQL_TRANSACTION CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 1 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_ROLLBACK_STMT
/// @Description Rolls back an SQL transaction, any data changes inside the
/// transaction will not be committed by the server.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-27 by Aaron Gulack
/// @See		 SQL_START_TRANSACTION_STMT SQL_COMMIT_STMT
///
/// @Syntax SQL_ROLLBACK_STMT
///
/// @Example
/// SQL_START_TRANSACTION_STMT
/// SQL_SET_STMT to "DELETE FROM CUSTOMER WHERE ID = 2145"
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// If (Err) Begin
///		SQL_ERROR_MESSAGE errorString
///     Showln errorString
///     SQL_ROLLBACK_STMT
/// End
/// Else
/// 	Showln "SQL Statement successful - committing"
/// 	SQL_COMMIT_STMT
#COMMAND SQL_ROLLBACK_STMT .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_DriverName EQ ORAFlex) Begin
        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 22 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 8 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
    Else If (MertechInc_DriverName EQ SQLFlex or MertechInc_DriverName EQ MDSPgSQL or MertechInc_DriverName EQ MDSMySQL) Begin
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_SQL_TRANSACTION CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 2 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SET_TRANSACTIONS_ALLOWED
/// @Description This command is used to toggle on or off the ability to
/// complete transaction to the server. Passing false to this command will
/// not allow transactions to be made, passing true will allow the transactions.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-27 by Aaron Gulack
/// @See
///
/// @Syntax SET_TRANSACTIONS_ALLOWED of {server} to {variable}
/// @Param server				The name of the server being used
/// @Param variable 			Boolean to enable or disable transactions
///
/// @Example
/// SET_TRANSACTIONS_ALLOWED of "localhost" to True
#COMMAND SET_TRANSACTIONS_ALLOWED "OF" R "TO" R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        MOVE !2 to MertechInc_sArg1
        MOVE !4 to MertechInc_iArg
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_TRANSACTIONS_ALLOWED CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_FETCH_NEXT_ROW
/// @Description This command is used to fetch the next row returned by the
/// associated SQL statement. The SQL statement is created from the
/// SQL_SET_STMT and executed with the SQL_EXECUTE_STMT. This command can be
/// used in two ways. If the results are to be attached to variables, then no
/// file needs to be specified, just the variables for each column in the row.
/// If the results are to be inserted into the record buffer directly, then the
/// file must be specified. From there, a SQL_BINDCOLUMNS_STMT can be used to
/// bind the fetched row to the specific fields in the file. Note that the
/// columns are fecthed in the order that the SQL statement generates them, so
/// the variables must follow the same order. The two constants, "found" and
/// "finderr" are set depending on whether the next row was found.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-27 by Aaron Gulack
/// @See 		 SQL_SET_STMT SQL_APPEND_STMT SQL_PREPARE_STMT SQL_EXECUTE_STMT SQL_CANCEL_QUERY_STMT SQL_BINDCOLUMNS_STMT
///
/// @Syntax SQL_FETCH_NEXT_ROW [of {file}] into {variable}
/// @Param  file				The name or number of the file
/// @Param  variable			The variable that the next column in the fetched row will be put into (can be multiple)
///
/// @Usage SQL_FETCH_NEXT_ROW of Customer
/// @Usage SQL_FETCH_NEXT_ROW into sRecnum sID
///
/// @Example
/// String sID sRecnum
///
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER ID"
/// SQL_APPEND_STMT to " BY NAME DESC"
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// While (found)
/// 	SQL_FETCH_NEXT_ROW into sRecnum sID
///     If (found) Begin
/// 		Showln sID
///    End
/// Loop
/// SQL_CANCEL_QUERY_STMT
///
/// @Example
/// Open Customer
///
/// SQL_SET_STMT of Customer to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active'"
/// SQL_PREPARE_STMT of Customer
/// SQL_BINDCOLUMNS_STMT of Customer to DF_BIND_ALL_COLUMNS
/// SQL_EXECUTE_STMT of Customer
/// While (Found)
/// 	SQL_FETCH_NEXT_ROW of Customer
///    	Showln Customer.ID
/// 	Showln Customer.FirstName
///		Showln Customer.LastName
/// Loop
/// SQL_CANCEL_QUERY_STMT
#COMMAND SQL_FETCH_NEXT_ROW """OF""INTO"
    #IFSAME !1 OF
        DO_GETFILENUMBER_DRIVERNAME !2
        #CHECK !3 .
    #ELSE
        DO_GETFILENUMBER_DRIVERNAME 0
    #ENDIF
    If (MertechInc_FileNumber <> -1) Begin
        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 22 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 6 RESULT MertechInc_iRet
        If MertechInc_iRet NE 0 INDICATE Found False
        Else Begin
            INDICATE Found True
            Move 0 to MertechInc_iParamCount
            #IFSAME !1 INTO
                DDO_GET_BIND_RSPARAMETERS !2 !3 !4 !5 !6 !7 !8 !9
            #ENDIF
        End
    End
#ENDCOMMAND


//=============================================================================
/// @Name        GET_RESULT_SET
/// @Description Fetches the next row in the result set returned by a
/// query or stored procedure.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-27 by Aaron Gulack
/// @See
///
/// @Syntax GET_RESULT_SET into {variable}
/// @Param variable			The variable receiving the result (can be multiple)
#COMMAND GET_RESULT_SET "INTO" R
    SQL_FETCH_NEXT_ROW !1 !2 !3 !4 !5 !6 !7 !8 !9
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_GET_DATA_CHUNK
/// @Description This command is used to get a chunk of data from a column
/// retrieved through an embedded SQL statement. By passing the column number
/// and the offset number, the chunk will be put into the specified variable.
/// To specify how big of a chunk to get, use the SQL_SET_CHUNK_SIZE command.
/// Otherwise the maximum length will be retrieved. An optional variable can
/// also be passed which will store the length of the chunk. Note that unlike
/// LOB_READ, this command works for any column type, not just LOB columns.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-04 by Aaron Gulack
/// @See 		 SQL_SET_CHUNK_SIZE SQL_GET_CHUNK_SIZE SQL_SET_MAX_DATA_SIZE SQL_GET_MAX_DATA_SIZE
///
/// @Syntax SQL_GET_DATA_CHUNK COLUMN {column} OFFSET {offset} to {variable} {length}
/// @Param column				Column number to get chunk from
/// @Param offset   			Offset to start at for the chunk
/// @Param variable 			Variable to hold the returned chunk
/// @Param length   			Variable to hold the chunk length
///
/// @Example
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active' "
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// SQL_FETCH_NEXT_ROW into sID sBio
/// If (Found) Begin
///     SQL_SET_CHUNK_SIZE to 150
///     SQL_GET_DATA_CHUNK COLUMN 6 OFFSET 1 to sChunk iLength
///     Showln sChunk
///     Showln iLength
/// End
#COMMAND SQL_GET_DATA_CHUNK "COLUMN" R "OFFSET" R "TO" R
    DO_GETFILENUMBER_DRIVERNAME 0

    If (MertechInc_DriverName EQ SQLFLEX) Begin
        Get MertechInc_SQL_GET_DATA_CHUNK !2 !4 to !6
        If MertechInc_iRet EQ -1 INDICATE ERR True
        Else Begin
            #IF (!0 > 6)
                Move MertechInc_sArg1 to !7
            #ENDIF
        End
    End
#ENDCOMMAND

Function MertechInc_SQL_GET_DATA_CHUNK Global Integer iColumn Integer iOffset Returns String
    Integer iChuck_Size
    String sChunk

    //Get current Chuck size and pre size string
    Call_Driver 0 MertechInc_DriverName Function CALLDRV_CHUNK_SIZE CALLBACK 0 PASSING iChuck_Size MertechInc_Blank 1 RESULT MertechInc_iRet
    Get MertechInc_Pre_Size_String iChuck_Size to sChunk

    //Get data
    Call_Driver 0 MertechInc_DriverName Function CALLDRV_GET_DATA_CHUNK CALLBACK 0 PASSING iColumn sChunk iOffset RESULT MertechInc_iRet

    //sArg1 (iColumn) contains the number of bytes returned, so move it to
    //MertechInc_Arg1 to pass the value back
    Move iColumn to MertechInc_sArg1

    Function_Return sChunk
End_Function

//=============================================================================
/// @Name        SQL_SET_CHUNK_SIZE
/// @Description This command sets the size of the chunk to retrieve when
/// using SQL_GET_DATA_CHUNK. Whatever number is set here will be the
/// length of the chunk that is retrieved, as long as it does not exceed
/// the maximum chunk size.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-04 by Aaron Gulack
/// @See 		 SQL_GET_DATA_CHUNK SQL_GET_CHUNK_SIZE SQL_SET_MAX_DATA_SIZE SQL_GET_MAX_DATA_SIZE
///
/// @Syntax SQL_SET_CHUNK_SIZE to {variable}
/// @Param variable			Length of chunk to retrive
///
/// @Example
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active' "
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// SQL_FETCH_NEXT_ROW into sID sBio
/// If (Found) Begin
///     SQL_SET_CHUNK_SIZE to 150
///     SQL_GET_DATA_CHUNK COLUMN 6 OFFSET 1 to sChunk iLength
///     Showln sChunk
///     Showln iLength
/// End
#COMMAND SQL_SET_CHUNK_SIZE "TO" R
    DO_GETFILENUMBER_DRIVERNAME 0
    IF (MertechInc_DriverName EQ SQLFLEX ) BEGIN
        Get_argument_size to MertechInc_iArg

        //Note this is not good. Setting the Argument size to a large value can impact on performance.
        If (MertechInc_iArg < !2) Set_Argument_Size !2

        Move !2 to MertechInc_sArg1
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_CHUNK_SIZE CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    END
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_GET_CHUNK_SIZE
/// @Description This command gets the size of the chunk being retrieved
/// from SQL_GET_DATA_CHUNK and puts it into the specified variable.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-04 by Aaron Gulack
/// @See 		 SQL_SET_CHUNK_SIZE SQL_GET_DATA_CHUNK SQL_SET_MAX_DATA_SIZE SQL_GET_MAX_DATA_SIZE
///
/// @Syntax SQL_GET_CHUNK_SIZE to {variable}
/// @Param variable 		Variable to hold the chunk size
///
/// @Example
/// SQL_GET_CHUNK_SIZE to iLength
#COMMAND SQL_GET_CHUNK_SIZE "TO" R
    DO_GETFILENUMBER_DRIVERNAME 0
    IF (MertechInc_DriverName EQ SQLFLEX ) BEGIN
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_CHUNK_SIZE CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 1 RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
        Else MOVE MertechInc_sArg1 to !2
    END
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_SET_MAX_DATA_SIZE
/// @Description This command sets the maximum size for data chunks
/// retrieved through SQL_GET_DATA_CHUNK. If SQL_SET_CHUNK_SIZE is higher
/// than the maximum size set with this command, then this will override
/// it and the chunk will be no longer than the maximum size set here.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-04 by Aaron Gulack
/// @See		 SQL_SET_CHUNK_SIZE SQL_GET_CHUNK_SIZE SQL_GET_DATA_CHUNK SQL_GET_MAX_DATA_SIZE
///
/// @Syntax SQL_SET_MAX_DATA_SIZE to {variable}
/// @Param variable			Max length to allow for chunks
///
/// @Example
/// SQL_SET_MAX_DATA_SIZE to 1000
#COMMAND SQL_SET_MAX_DATA_SIZE "TO" R
    DO_GETFILENUMBER_DRIVERNAME 0
    IF (MertechInc_DriverName EQ SQLFLEX ) BEGIN
        MOVE !2 TO MertechInc_sArg1
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_MAX_DATA_SIZE CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    END
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_GET_MAX_DATA_SIZE
/// @Description This command returns the maximum chunk size allowed
/// for SQL_GET_DATA_CHUNK.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-04 by Aaron Gulack
/// @See		 SQL_SET_CHUNK_SIZE SQL_GET_CHUNK_SIZE SQL_GET_DATA_CHUNK SQL_SET_MAX_DATA_SIZE
///
/// @Syntax SQL_GET_MAX_DATA_SIZE to {variable}
/// @Param variable 		Variable to hold the maximum chunk size
///
/// @Example
/// SQL_GET_MAX_DATA_SIZE to iLength
#COMMAND SQL_GET_MAX_DATA_SIZE "TO" R
    DO_GETFILENUMBER_DRIVERNAME 0
    IF (MertechInc_DriverName EQ SQLFLEX ) BEGIN
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_MAX_DATA_SIZE CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 1 RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
        Else MOVE MertechInc_sArg1 to !2
    END
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_GET_NUM_COLS
/// @Description This command is used to get the number of columns retrieved
/// from an SQL expression result set. Since the column number is based on
/// the result set, this command cannot be used when the results are being
/// bound to the record buffer.  If this command is used with the record
/// buffer or if no columns are found, -1 is returned.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-28 by Aaron Gulack
/// @See   		 SQL_PREPARE_STMT SQL_EXECUTE_STMT SQL_SET_STMT
///
/// @Syntax SQL_GET_NUM_COLS to {variable}
/// @Param variable			Variable to hold the number of columns.
///
/// @Example
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE FIRSTNAME = 'Aaron'"
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// GET_RESULT_SET_NUM_COLS to iNumCols
/// Showln iNumCols
#COMMAND SQL_GET_NUM_COLS "OF""TO"
    #IFSAME !1 OF
        DO_GETFILENUMBER_DRIVERNAME !2
        #CHECK !5 .
    #ELSE
        DO_GETFILENUMBER_DRIVERNAME 0
        #CHECK !3 .
    #ENDIF
    If (MertechInc_FileNumber <> -1) Begin
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_GET_RETURNED_COLUMNS CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
        #IF !0=2
            Move MertechInc_iRet to !2
        #ELSE
            Move MertechInc_iRet to !4
        #ENDIF
    End
#ENDCOMMAND

#Replace GET_SQL_NUM_COLS SQL_GET_NUM_COLS

//=============================================================================
/// @Name        GET_RESULT_SET_NUM_COLS
/// @Description Returns the number of columns in the result set.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-28 by Aaron Gulack
/// @See 		 SQL_GET_NUM_COLS
///
/// @Syntax GET_RESULT_SET_NUM_COLS to {variable}
/// @Param variable			Variable to hold the number of columns
///
/// @Example
/// Integer iNumCols
///
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE FIRSTNAME = 'Aaron'"
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// GET_RESULT_SET_NUM_COLS to iNumCols
/// Showln iNumCols
#COMMAND GET_RESULT_SET_NUM_COLS "TO"
    SQL_GET_NUM_COLS !1 !2
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_GET_NUM_ROWS
/// @Description This command is used to get the number of rows retrieved
/// from a result set of an SQL expression. It cannot be used when binding
/// the result set to the record buffer.
///
/// Note: The number of rows may not always be available, depending
/// on server and cursor types.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-30 by Aaron Gulack
/// @See		 SQL_PREPARE_STMT SQL_EXECUTE_STMT
///
/// @Syntax SQL_GET_NUM_ROWS to {variable}
/// @Param variable			Variable to hold the number of rows
///
/// @Example
/// Integer iNumRows
///
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active'"
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// SQL_GET_NUM_ROWS to iNumRows
/// Showln iNumRows
#COMMAND SQL_GET_NUM_ROWS "OF""TO"
    #IFSAME !1 OF
        DO_GETFILENUMBER_DRIVERNAME !2
        #CHECK !5 .
    #ELSE
        DO_GETFILENUMBER_DRIVERNAME 0
        #CHECK !3 .
    #ENDIF
    If (MertechInc_FileNumber <> -1) Begin
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_GET_RETURNED_ROWS CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
        #IF !0=2
            Move MertechInc_iRet to !2
        #ELSE
            Move MertechInc_iRet to !4
        #ENDIF

    End
#ENDCOMMAND

#Replace GET_SQL_NUM_ROWS SQL_GET_NUM_ROWS

//=============================================================================
/// @Name        SQL_GET_COL_NAME
/// @Description This command is used to retrieve the name of a specified
/// column within an SQL result set. An optional second variable can be used
/// to retrieve the size of the specified column. Note that this command
/// cannot be used when the results are being directly binded to the record
/// buffer, it can only be used for the results of an SQL statement.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-30 by Aaron Gulack
/// @See		 SQL_GET_NUM_COLS
///
/// @Syntax SQL_GET_COL_NAME {columnNumber} to {variable} [{length}]
/// @Param columnNumber			The column number being used
/// @Param variable	 			String variable for the column name
/// @Param length   			Variable to hold the column length (optional)
///
/// @Example
/// Open Customer
///
/// String sColumnName
/// Integer iLength
///
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active'"
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// SQL_GET_COL_NAME 1 to sColumnName iLength
/// showln sColumnName
/// showln iLength
#COMMAND SQL_GET_COL_NAME
    #IFSAME !1 OF
        DO_GETFILENUMBER_DRIVERNAME !2
        #CHECK !7 .
        MOVE !3 TO MertechInc_iArg
    #ELSE
        #IFSAME !2 TO
            DO_GETFILENUMBER_DRIVERNAME 0
            #CHECK !5 .
            MOVE !1 TO MertechInc_iArg
        #ELSE
            #ERROR 4514
        #ENDIF
    #ENDIF

    If (MertechInc_FileNumber <> -1) Begin
        Move (Repeat(" ", 255)) to MertechInc_sArg1

        Call_Driver 0 MertechInc_DriverName Function CALLDRV_GET_COLUMN_ATTRIBUTE CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
        Else Begin
            #IFSAME !1 of
                Move MertechInc_sArg1 to !5
                #IF !0=6
                    Move MertechInc_iRet to !6
                #ENDIF
            #ELSE
                Move MertechInc_sArg1 to !3
                #IF !0=4
                    Move MertechInc_iRet to !4
                #ENDIF
            #ENDIF
        End
    End
#ENDCOMMAND

#Replace GET_SQL_COL_NAME SQL_GET_COL_NAME

//=============================================================================
/// @Name        GET_RESULT_SET_COL_NAME
/// @Description Returns the column name being populated from the result set.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-30 by Aaron Gulack
/// @See 		 SQL_GET_COL_NAME
///
/// @Syntax GET_RESULT_SET_COL_NAME {columnNumber} to {variable} [{length}]
/// @Param columnNumber			The column number being used
/// @Param variable	 			String variable for the column name
/// @Param length   			Variable receiving the column length (optional)
#COMMAND GET_RESULT_SET_COL_NAME R "TO"
    SQL_GET_COL_NAME !1 !2 !3 !4
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_GET_COL_ATTRIBUTE
/// @Description This command is used to get specific column information from
/// the columns in a result set of an SQL statement. By passing one of the
/// supported attributes below, the command will return the desired information.
/// Note that some attributes only work with specific drivers. See the list
/// below for more information.
///
/// Supported attributes are:
/// <dl>
/// <dt>SIZE        </dt><dd>The maximum length of the column</dd>
/// <dt>DATA_LENGTH </dt><dd>Length of data currently in the column</dd>
/// <dt>DECIMALS    </dt><dd>If numeric, shows number of decimal places</dd>
/// <dt>LABEL       </dt><dd>Returns the column name in ORAFlex and MySQLFlex</dd>
/// <dt>COLUMN_NAME </dt><dd>Returns the name of the column</dd>
/// <dt>TABLE_NAME  </dt><dd>Returns the name of the table (MySQLFlex only)</dd>
/// <dt>SQLTYPE     </dt><dd>Returns the number representing the SQL data type</dd>
/// <dt>NULLABLE    </dt><dd>Returns true if null is allowed, false otherwise (doesn't work in PostgreSQL)</dd>
/// <dt>DFTYPE      </dt><dd>Dataflex type column is mapped to</dd>
/// </dl>
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-09-05 by Aaron Gulack
/// @See
///
/// @Syntax SQL_GET_COL_ATTRIBUTE of {columnNumber} {attribute} to {variable}
/// @Param columnNumber			The number of the column that is being examined
/// @Param attribute			The attribute being checked (see list)
/// @Param variable				Variable to hold the attribute value
///
/// @Example
/// String sFirstName sLastName sColumn1Name sColumn2Name
///
/// Open Customer
///
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active' "
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// SQL_FETCH_NEXT_ROW into sFirstName sLastName
/// If (Found) Begin
///     SQL_GET_COL_ATTRIBUTE of 1 COLUMN_NAME to sColumn1Name
///     SQL_GET_COL_ATTRIBUTE of 2 COLUMN_NAME to sColumn2Name
///     Showln (sColumn1Name + " = " + sFirstName)
///     Showln (sColumn2Name + " = " + sLastName)
/// End
#COMMAND SQL_GET_COL_ATTRIBUTE "OF" R "SIZE""DATA_LENGTH""DECIMALS""LABEL""COLUMN_NAME""TABLE_NAME""SQLTYPE""NULLABLE""DFTYPE" "TO" R
    DO_GETFILENUMBER_DRIVERNAME 0

    If (MertechInc_FileNumber <> -1) Begin
        #IFSAME !3 SIZE
            Move SQL_GET_COL_ATTRIB_SIZE to MertechInc_sArg2
        #ELSE
            #IFSAME !3 DATA_LENGTH
                Move SQL_GET_COL_ATTRIB_DATA_LENGTH to MertechInc_sArg2
            #ELSE
               #IFSAME !3 DECIMALS
                    Move SQL_GET_COL_ATTRIB_DECIMALS to MertechInc_sArg2
                #ELSE
                    #IFSAME !3 LABEL
                        Move SQL_GET_COL_ATTRIB_LABEL to MertechInc_sArg2
                    #ELSE
                        #IFSAME !3 COLUMN_NAME
                            Move SQL_GET_COL_ATTRIB_COLUMN_NAME to MertechInc_sArg2
                        #ELSE
                            #IFSAME !3 TABLE_NAME
                                Move SQL_GET_COL_ATTRIB_TABLE_NAME to MertechInc_sArg2
                            #ELSE
                                #IFSAME !3 SQLTYPE
                                    Move SQL_GET_COL_ATTRIB_SQLTYPE to MertechInc_sArg2
                                #ELSE
                                    #IFSAME !3 NULLABLE
                                        MOVE SQL_GET_COL_ATTRIB_NULLABLE TO MertechInc_sArg2
                                    #ELSE
                                        MOVE SQL_GET_COL_ATTRIB_DFTYPE TO MertechInc_sArg2
                                    #ENDIF
                                #ENDIF
                            #ENDIF
                        #ENDIF
                    #ENDIF
                #ENDIF
            #ENDIF
        #ENDIF

        Move !2 to MertechInc_iArg
        Move (Repeat(" ", 255)) to MertechInc_sArg1
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_GET_COLUMN_ATTRIBUTE CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 MertechInc_iArg RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
        Else Move MertechInc_sArg1 to !5
    End
#ENDCOMMAND

//=============================================================================
/// @Name        DDO_GET_BIND_RSPARAMETERS
/// @Description Recursively calls DO_GET_BIND_RSPARAMETERS.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-30 by Aaron Gulack
/// @See
#COMMAND DDO_GET_BIND_RSPARAMETERS
    DO_GET_BIND_RSPARAMETERS !1
    #IF !0>1
        DDO_GET_BIND_RSPARAMETERS !2 !3 !4 !5 !6 !7 !8 !9
    #ENDIF
#ENDCOMMAND

//=============================================================================
/// @Name        DO_GET_BIND_RSPARAMETERS
/// @Description Gets bound parameters values for result set call.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     All
/// @VersionNote Last Revised: 2013-08-30 by Aaron Gulack
/// @See
#COMMAND DO_GET_BIND_RSPARAMETERS
    #IFSAME !1 BINDING
        // Stop - do not process any more arugments
    #ELSE
        #IFSAME !1 SQLOUT
            // Do nothing, just recurse if more arguments
        #ELSE
            Increment MertechInc_iParamCount
            #IFCLASS !1 _CE
                // Just need to increment the parameter count (done above)
            #ELSE
                DO_GETFILENUMBER_DRIVERNAME 0
                Send MertechInc_Set_DecSep     //Check Decimal Seperator and change to '.' if required
                Get MertechInc_DO_GET_BIND_RSPARAMETERS False MertechInc_Blank MertechInc_Blank MertechInc_iParamCount to !1
                Send MertechInc_Reset_DecSep   //Reset Decimal Seperator if required

                If MertechInc_iRet EQ -1 INDICATE ERR True    // Set the error indicator if anything went wrong
            #ENDIF
        #ENDIF
        #IF (!0>1)
              DO_GET_BIND_RSPARAMETERS !2 !3 !4 !5 !6 !7 !8 !9
        #ENDIF
    #ENDIF
#ENDCOMMAND

Function MertechInc_DO_GET_BIND_RSPARAMETERS Global Integer bSQLFlex String sArg1 String sArg2 Integer iArg Returns String
    String sReturnValue
    Integer iSize

    move 0 to iSize
	SQL_GET_COL_ATTRIBUTE of iArg DATA_LENGTH to iSize

    Get MertechInc_Pre_Size_String (iSize+1) to sReturnValue
    Move (|CI$10000 * iArg) To iArg // Shift column number 16 bits to the left
    Call_Driver 0 MertechInc_DriverName Function 24 CALLBACK 0 PASSING sReturnValue MertechInc_Blank iArg RESULT MertechInc_iRet

    Function_Return sReturnValue
End_Function


//=============================================================================
/// @Name        SQL_NEXT_RESULT_SET
/// @Description This command is used when working with SQL statements that
/// return multiple result sets. In that scenario, calling this command will
/// move to the next result set. That set can now be fetched or binded to
/// columns on a table.
///
/// @See
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-09-02 by Aaron Gulack
/// @See
///
/// @Syntax SQL_NEXT_RESULT_SET [of {file}]
/// @Param file			Name or number of the file (optional)
///
/// @Example
/// SQL_SET_STMT to "SP_HELP CUSTOMER"
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// SQL_FETCH_NEXT_ROW into sTable sOwner sTableType dtCreated
/// If (Found) Begin
///     Showln sTable
///     Showln sOwner
///     Showln sTableType
///     Showln dtCreated
/// End
/// SQL_NEXT_RESULT_SET
/// SQL_FETCH_NEXT_ROW into sColumnName sColumnType sComputed sLength
/// If (Found) Begin
///     Showln sColumnName
///     Showln sColumnType
///     Showln sComputed
///     Showln sLength
/// End
#COMMAND SQL_NEXT_RESULT_SET """OF"
    #IFSAME !1 OF
        DO_GETFILENUMBER_DRIVERNAME !2
        #CHECK !3 .
    #ELSE
        DO_GETFILENUMBER_DRIVERNAME 0
    #ENDIF
    Call_Driver MertechInc_FileNumber MertechInc_DriverName Function CALLDRV_SQL_NEXT_RESULTSET CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 11 RESULT MertechInc_iRet
    If MertechInc_iRet NE 0 INDICATE Found False
    Else INDICATE Found True
#ENDCOMMAND

//=============================================================================
/// @Name        DDO_PASS_ARGUMENTS
/// @Description Calls DO_PASS_ARGUMENTS until the argument is "BINDING" and
/// then stops.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     All
/// @VersionNote Last Revised: 2013-09-05 by Aaron Gulack
/// @See
#COMMAND DDO_PASS_ARGUMENTS
    DO_PASS_ARGUMENTS !1
    #IF !0>1
        #IFSAME !1 BINDING
        #ELSE
            DDO_PASS_ARGUMENTS !2 !3 !4 !5 !6 !7 !8 !9
        #ENDIF
    #ENDIF
#ENDCOMMAND

//=============================================================================
/// @Name        DO_PASS_ARGUMENTS
/// @Description Builds parameter statements for stored procedures and adds
/// them to the current query.
///
/// @Assumptions
/// @Status      internal
/// @Drivers     All
/// @VersionNote Last Revised: 2013-09-05 by Aaron Gulack
/// @See
#COMMAND DO_PASS_ARGUMENTS
    // This command is used to BUILD the query statement.  It DOES NOT link the query statement
    // to the actual parameters.  That is handled by DO_BIND_PARAMETERS.

    #IFSAME !1 BINDING  // DON'T DO ANYTHING ELSE
    #ELSE
        #IFSAME !1 SQLOUT
        // The reason this is no-op'd is because SQLOUT is handled elsewhere.  See DO_GET_SQLSERVER_PARAMETERS
        // or DO_BIND_SQLSERVER_PARAMETERS for an example of it being used to actually retrieve the out value.
        #ELSE
          #IFSAME !1 PASSING
              IF (MertechInc_iParamCount = 0 AND MertechInc_DriverName = SQLFLEX OR MertechInc_DriverName = MDSDB2 OR MertechInc_DriverName = MYSQLFLEX) MOVE "(" TO MertechInc_sArg1
          #ELSE
              IF (MertechInc_iParamCount > 0) SQL_APPEND_STMT TO ", "
              INCREMENT MertechInc_iParamCount

              // So for each driver, the method by which parameters are passed is different.  For MS-SQL, all we need to pass
              // is a question mark per param.  For other servers, the parameters are passed differently.
              If (MertechInc_DriverName EQ PGFLEX) Move ("$"+String(MertechInc_iParamCount)) to MertechInc_sArg1
                Else If (MertechInc_DriverName = MYSQLFLEX ) Move ("@"+String(MertechInc_iParamCount)) to MertechInc_sArg1
                    Else If MertechInc_DriverName EQ ORAFLEX Move (":PAR"+String(MertechInc_iParamCount)) to MertechInc_sArg1
                        Else Move "? " to MertechInc_sArg1
          #ENDIF
              SQL_APPEND_STMT to MertechInc_sArg1
        #ENDIF
        #IF (!0 > 1)
            DO_PASS_ARGUMENTS !2 !3 !4 !5 !6 !7 !8 !9
        #ENDIF
    #ENDIF
#ENDCOMMAND

//=============================================================================
/// @Name        DDO_BIND_PARAMETERS
/// @Description Recursively calls DO_BIND_PARAMETERS until the keyword
/// "BINDING" is encountered.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     All
/// @VersionNote Last Revised: 2013-09-05 by Aaron Gulack
/// @See
#COMMAND DDO_BIND_PARAMETERS
//    DO_BIND_PARAMETERS !1
    #IFSAME !1 BINDING
        DO_BIND_PARAMETERS !1
    #ELSE
        #IFSAME !1 PASSING
            DO_BIND_PARAMETERS !1
        #ELSE
            #IFSAME !1 SQLOUT
                DO_BIND_PARAMETERS !1
            #ELSE
                DO_BIND_PARAMETERS (!1)
            #ENDIF
        #ENDIF
    #ENDIF

    #IF !0>1
        #IFSAME !1 BINDING
            // DON'T DO ANYTHING ELSE
        #ELSE
            DDO_BIND_PARAMETERS !2 !3 !4 !5 !6 !7 !8 !9
        #ENDIF
    #ENDIF
#ENDCOMMAND

//=============================================================================
/// @Name        DO_BIND_PARAMETERS
/// @Description Binds parameters for a stored procedure call.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     All
/// @VersionNote Last Revised: 2013-09-05 by Aaron Gulack
/// @See
#COMMAND DO_BIND_PARAMETERS
    //MertechInc_iWork         - Integer - Size of return buffer
    //MertechInc_sWork         - String  - Default value
    //MertechInc_iParamCount   - Integer - Allocates sequential number for parameter.
    //                              This will have been set to zero somewhere else.

    #IFSAME !1 BINDING
        // DON'T DO ANYTHING ELSE
    #ELSE
        #IFSAME !1 PASSING
        #ELSE
            #IFSAME !1 SQLOUT
            #ELSE
                #IFCLASS !1 _C
                    MOVE !1 TO MertechInc_sArg1
                    Move (LENGTH(MertechInc_sArg1)+1) to MertechInc_iWork

                    #IFTYPE !1 "I"
                        Move 20 to MertechInc_iWork
                    #ELSE
                        #IFTYPE !1 "N"
                            Move 50 to MertechInc_iWork
                        #ELSE
                            #IFTYPE !1 "D"
                                MOVE 24 TO MertechInc_iWork
                            #ELSE
                                #IFTYPE !1 "S"
                                    IF (POS("|VS",|CS'!1') NE 0 OR POS("|WS",|CS'!1') NE 0) MOVE 255 TO MertechInc_iWork
                                    ELSE MOVE 16384 TO MertechInc_iWork
                                #ENDIF
                            #ENDIF
                        #ENDIF
                    #ENDIF

                    // MARCELO 12/14/2006
                    // We will change the default value here due a stored procedure call in ORAFlex
                    // MOVE " " TO MertechInc_sWork
                    MOVE "" TO MertechInc_sWork
                #ELSE
                    #IFTYPE !1 "I"
                        MOVE 20 TO MertechInc_iWork
                        MOVE 0 TO MertechInc_sWork
                    #ELSE
                        #IFTYPE !1 "N"
                            MOVE 50 TO MertechInc_iWork
                            MOVE 0 TO MertechInc_sWork
                        #ELSE
                            #IFTYPE !1 "D"
                                MOVE 24 TO MertechInc_iWork
                                MOVE "" TO MertechInc_sWork
                            #ELSE
                                #IFTYPE !1 "S"
                                    IF (POS("|VS",|CS'!1') NE 0 OR POS("|WS",|CS'!1') NE 0) MOVE 255 TO MertechInc_iWork
                                    ELSE MOVE 16384 TO MertechInc_iWork
                                    MOVE "" TO MertechInc_sWork
                                #ENDIF
                            #ENDIF
                        #ENDIF
                    #ENDIF
                #ENDIF

                Increment MertechInc_iParamCount
                IF MertechInc_DriverName EQ ORAFLEX MOVE (":PAR"+STRING(MertechInc_iParamCount)) TO MertechInc_sArg2
                ELSE IF MertechInc_DriverName EQ MYSQLFLEX MOVE ("@"+STRING(MertechInc_iParamCount)) TO MertechInc_sArg2
                    Else If MertechInc_DriverName EQ PgFlex Move ("$"+String(MertechInc_iParamCount)) to MertechInc_sArg2
                         Else Move " " to MertechInc_sArg2

                If (LENGTH(!1) = 0) Begin
                    Send MertechInc_DO_BIND_PARAMETERS MertechInc_sWork MertechInc_sArg2 MertechInc_iWork
                End
                Else Begin
                    Send MertechInc_Set_DecSep     //Check Decimal Seperator and change to '.' if required
                    Send MertechInc_DO_BIND_PARAMETERS !1 MertechInc_sArg2 MertechInc_iWork
                    Send MertechInc_Reset_DecSep   //Reset Decimal Seperator if required
                End
            #ENDIF
        #ENDIF
        #IF (!0>1)
            DO_BIND_PARAMETERS !2 !3 !4 !5 !6 !7 !8 !9
        #ENDIF
    #ENDIF
#ENDCOMMAND

Procedure MertechInc_DO_BIND_PARAMETERS Global String sValue String sName Integer iLength
    Call_Driver 0 MertechInc_DriverName Function CALLDRV_BIND_PARAMETER CALLBACK 0 PASSING sValue sName iLength RESULT MertechInc_iRet
End_Procedure

//=============================================================================
/// @Name        DO_BIND_PAR_RET
/// @Description Binds parameters for a stored procedure call.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     OraFlex
/// @VersionNote Last Revised: 2013-09-05 by Aaron Gulack
/// @See
#COMMAND DO_BIND_PAR_RET
    //MertechInc_iWork - Integer - Size of return buffer
    //MertechInc_sWork - String  - Default value

    Move !1 to MertechInc_sArg1

    #IFCLASS !1 _C
        Move (LENGTH(MertechInc_sArg1)+1) to MertechInc_iWork
        Move " " to MertechInc_sWork
    #ELSE
        #IFTYPE !1 "I"
            Move 10 to MertechInc_iWork
            Move 0 to MertechInc_sWork
        #ELSE
            #IFTYPE !1 "N"
                Move 25 to MertechInc_iWork
                Move 0 to MertechInc_sWork
            #ELSE
                #IFTYPE !1 "D"
                    Move 11 to MertechInc_iWork
                    Move "" to MertechInc_sWork
                #ELSE
                    #IFTYPE !1 "S"
                        If (POS("|VS",|CS'!1') NE 0 or POS("|WS",|CS'!1') NE 0) Move 255 to MertechInc_iWork
                        Else Move 16384 to MertechInc_iWork
                        Move "" to MertechInc_sWork
                    #ENDIF
                #ENDIF
            #ENDIF
        #ENDIF
    #ENDIF

    Move (":PAR_RET") to MertechInc_sArg2
    If (LENGTH(MertechInc_sArg1) = 0) Move MertechInc_sWork to MertechInc_sArg1

    Call_Driver 0 MertechInc_DriverName Function CALLDRV_BIND_PARAMETER CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 MertechInc_iWork RESULT MertechInc_iRet
#ENDCOMMAND

//=============================================================================
/// @Name        DDO_GET_BIND_PARAMETERS
/// @Description Recursively calls DO_GET_BIND_PARAMETERS.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     All
/// @VersionNote Last Revised: 2013-09-05 by Aaron Gulack
/// @See
#COMMAND DDO_GET_BIND_PARAMETERS
    DO_GET_BIND_PARAMETERS !1
    #IF !0>1
        DDO_GET_BIND_PARAMETERS !2 !3 !4 !5 !6 !7 !8 !9
    #ENDIF
#ENDCOMMAND

//=============================================================================
/// @Name        DO_GET_BIND_PARAMETERS
/// @Description Gets bound parameter values for a stored procedure call.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     All
/// @VersionNote Last Revised: 2013-09-05 by Aaron Gulack
/// @See
#COMMAND DO_GET_BIND_PARAMETERS
    #IFSAME !1 BINDING
        // Stop - do not process any more arugments
    #ELSE
        #IFSAME !1 SQLOUT
            // Do nothing, just recurse if more arugments
        #ELSE
            Increment MertechInc_iParamCount
            #IFCLASS !1 _CE
                // Just need to increment the parameter count (done above)
            #ELSE
                DO_GETFILENUMBER_DRIVERNAME 0
                Send MertechInc_Set_DecSep     //Check Decimal Seperator and change to '.' if required
                Get MertechInc_DO_GET_BIND_PARAMETERS False MertechInc_Blank MertechInc_Blank MertechInc_iParamCount to !1
                Send MertechInc_Reset_DecSep   //Reset Decimal Seperator if required
                If MertechInc_iRet EQ -1 INDICATE ERR True    // Set the error indicator if anything went wrong
            #ENDIF
        #ENDIF
        #IF (!0>1)
            DO_GET_BIND_PARAMETERS !2 !3 !4 !5 !6 !7 !8 !9
        #ENDIF
    #ENDIF
#ENDCOMMAND

Function MertechInc_DO_GET_BIND_PARAMETERS Global Integer bSQLFlex String sArg1 String sArg2 Integer iArg Returns String
    String sReturnValue
    Integer iSize

    if (MertechInc_DriverName = SQLFLEX) ;
	  	move (iArg+1) to iArg
//	  SQL_GET_COL_ATTRIBUTE of iArg DATA_LENGTH to iSize

    Get MertechInc_Pre_Size_String (iSize+1) to sReturnValue
    Call_Driver 0 MertechInc_DriverName Function 24 CALLBACK 0 PASSING sReturnValue MertechInc_Blank iArg RESULT MertechInc_iRet

    Function_Return sReturnValue
End_Function

//=============================================================================
/// @Name        SQL_GET_OUTPUT_VALUE
/// @Description This command is used to get the value of a specific
/// parameter associated with a stored procedure.  Although this
/// command will work with any parameter, it is mostly used with
/// IN/OUT or OUT parameters as their value will more often be important
/// once returned. When multiple values are returned, this command can be
/// more efficient than other options. Note that the specified parameter
/// must first be defined using the SQL_SET_PROCEDURE_PARAMETER command
/// in order to work properly.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See 		 SQL_GET_PROCEDURE_PARAMETER
///
/// @Syntax SQL_GET_OUTPUT_VALUE {parameter} to {variable}
/// @Param parameter		Number of the parameter
/// @Param variable			Variable to hold the parameter's value
///
/// @Example
/// SQL_SET_PROCEDURE_NAME "user.getCustomerStatus" NUMPAR 1
/// SQL_SET_PROCEDURE_PARAMETER 1 to sCustomerID IN_OUT
/// SQL_PROCEDURE_EXECUTE
/// SQL_GET_OUTPUT_VALUE 1 to sStatus
///
/// Showln sStatus
///
/// @Example
/// SQL_SET_PROCEDURE_NAME "user.getCustomerStatus" NUMPAR 2
/// SQL_SET_PROCEDURE_PARAMETER 1 to sCustomerID IN
/// SQL_SET_PROCEDURE_PARAMETER 2 to sStatus OUT
/// SQL_PROCEDURE_EXECUTE
/// SQL_GET_OUTPUT_VALUE 2 to sStatus
///
/// Showln sStatus
// OLI:
// This function is identical in operation to SQL_GET_PROCEDURE_PARAMETER, so just do a replace
#Replace SQL_GET_OUTPUT_VALUE SQL_GET_PROCEDURE_PARAMETER
#Replace MDS_GET_OUTPUT_VALUE SQL_GET_PROCEDURE_PARAMETER

//=============================================================================
/// @Name        SQL_FETCH_COLUMN
/// @Description This command is used to retrieve a specified column from a
/// result set of an SQL statement. Note that this command cannot be used to
/// replace SQL_FETCH_NEXT_ROW but is used in addition to it when only one
/// column is needed. For most cases, SQL_FETCH_NEXT_ROW can be used alone
/// to retrieve the columns desired so this should only be used if there is
/// a specific reason to do so.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-09-05 by Aaron Gulack
/// @See 		 SQL_FETCH_NEXT_ROW
///
/// @Syntax SQL_FETCH_COLUMN {columnNumber} into {variable}
/// @Param columnNumber    Number of the column to fetch
/// @Param variable        Variable to hold the fetched value
///
/// @Example
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active' "
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// SQL_FETCH_NEXT_ROW
/// SQL_GET_NUM_COLS to iCols
/// For fieldIndex from 1 to iCols
///     SQL_FETCH_COLUMN fieldIndex into sValue
///     Showln sValue
/// Loop
#COMMAND SQL_FETCH_COLUMN R "INTO" R
    DO_GETFILENUMBER_DRIVERNAME 0

    Send MertechInc_Set_DecSep     //Check Decimal Seperator and change to '.' if required
    Get MertechInc_SQL_FETCH_COLUMN MertechInc_Blank MertechInc_Blank !1 to !3
    Send MertechInc_Reset_DecSep   //Reset Decimal Seperator if required
#ENDCOMMAND

Function MertechInc_SQL_FETCH_COLUMN Global String sArg1 String sArg2 Integer iArg Returns String
    String sReturnValue
    Integer iSize

    Move 0 to iSize
	SQL_GET_COL_ATTRIBUTE of iArg DATA_LENGTH to iSize

    Get MertechInc_Pre_Size_String (iSize+1) to sReturnValue
    Move (|CI$10000 * iArg) to iArg // Shift column number 16 bits to the left
    Call_Driver 0 MertechInc_DriverName Function 24 CALLBACK 0 PASSING sReturnValue MertechInc_Blank iArg RESULT MertechInc_iRet

    Function_Return sReturnValue
End_Function

//=============================================================================
/// @Name        SET_SCHEMA_NAME
/// @Description This command is used to set the schema name to be used when
/// opening tables. Note that this command will override the schema name that
/// is set in the INT file.  The default schema for the current user is used
/// when no name is set.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex and ORAFlex
/// @VersionNote Last Revised: 2013-09-24 by Aaron Gulack
/// @See 		 GET_SCHEMA_NAME
///
/// @Syntax SET_SCHEMA_NAME to {schema}
/// @Param variable			Name of the schema
///
/// @Example
/// SET_SCHEMA_NAME to 'CustomerSchema'
/// OPEN "CUSTOMER.INT" as CUSTOMER
/// SET_SCHEMA_NAME to 'SalesSchema'
/// OPEN "SALESP.INT" as SALESP
#COMMAND SET_SCHEMA_NAME "TO" R .
    DO_GETFILENUMBER_DRIVERNAME 0
    INDICATE ERR False
    Move !2 to MertechInc_sArg1
    If MertechInc_DriverName EQ SQLFLEX      Call_Driver 0 SQLFlex Function 10 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
    Else If MertechInc_DriverName EQ ORAFLEX Call_Driver 0 ORAFlex Function  8 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
    If MertechInc_iRet EQ -1 INDICATE ERR True
#ENDCOMMAND

//=============================================================================
/// @Name        GET_SCHEMA_NAME
/// @Description This command is used to get the name of the schema being
/// used to open tables.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex and ORAFlex
/// @VersionNote Last Revised: 2013-09-24 by Aaron Gulack
/// @See 		 SET_SCHEMA_NAME
///
/// @Syntax GET_SCHEMA_NAME to {variable}
/// @Param variable			variable to hold the schema name
///
/// @Example
/// GET_SCHEMA_NAME to sName
/// Showln sName
#COMMAND GET_SCHEMA_NAME "TO" #CRUG .
    DO_GETFILENUMBER_DRIVERNAME 0
    INDICATE ERR False
    Move (Repeat(" ",255)) to MertechInc_sArg1
    If MertechInc_DriverName EQ SQLFLEX Call_Driver 0 SQLFlex Function 10 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 1 RESULT MertechInc_iRet
    Else                                Call_Driver 0 ORAFlex Function  8 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 1 RESULT MertechInc_iRet
    If MertechInc_iRet EQ -1 INDICATE ERR True
    [  ERR ] Move ""     to !2
    [ ~ERR ] Move MertechInc_sArg1 to !2
#ENDCOMMAND

//=============================================================================
/// @Name        CALL_ORACLE_STORED_PROCEDURE
/// @Description This command is used to call a stored procedure on the SQL
/// backend. To successfully call a procedure with this command, a string
/// must be passed containing a valid procedure name. In addition, if the
/// procedure takes any arguments, they must also be passed using the constant
/// "passing" along with all of the needed arguments. If the procedure has a
/// return value, then SQL_GET_FUNCTION_RETURN or SQL_FETCH_NEXT_ROW can be
/// used to get the value(s). If an error is found then the indicator "Err"
/// is set to true.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     ORAFLex
/// @VersionNote Last Revised: 2013-09-25 by Aaron Gulack
/// @See		 CALL_STORED_PROCEDURE
///
/// @Syntax CALL_ORACLE_STORED_PROCEDURE {procedure} Passing {variable}
/// @Param procedure		Full name of the procedure
/// @Param variable			Argument being passed to procedure (can be multiple)
///
/// @Example
/// CALL_ORACLE_STORED_PROCEDURE "sys.sp_addmessage" passing 50003 15 "Please enter a valid date"
#REPLACE CALL_ORACLE_STORED_PROCEDURE CALL_STORED_PROCEDURE

//=============================================================================
/// @Name        SQL_SET_PROCEDURE_NAME
/// @Description This command is used to set the procedure to be executed.
/// This is used when the procedure is being split up into multiple lines
/// as shown below. When using this command, SQL_PROCEDURE_EXECUTE must be
/// called after all parameters have been set to successfully execute the
/// procedure. The constant "NUMPAR" is used to indicate how many parameters
/// will be passed.
///
/// @Assumptions The procedure is a valid procedure in the SQL database
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-09-25 by Aaron Gulack
/// @See 		 SQL_SET_PROCEDURE_PARAMETER SQL_PROCEDURE_EXECUTE
///
/// @Syntax SQL_SET_PROCEDURE_NAME {procedure} NUMPAR {variable}
/// @Param procedure		Full name of the procedure
/// @Param variable			Number of parameters to be passed
///
/// @Example
/// SQL_SET_PROCEDURE_NAME "sys.sp_addmessage" NUMPAR 3
/// SQL_SET_PROCEDURE_PARAMETER 1 to 500004 IN
/// SQL_SET_PROCEDURE_PARAMETER 2 to 15 IN
/// SQL_SET_PROCEDURE_PARAMETER 3 to "Please enter a valid Date" IN
/// SQL_PROCEDURE_EXECUTE
#COMMAND SQL_SET_PROCEDURE_NAME R "NUMPAR" R
    DO_GETFILENUMBER_DRIVERNAME 0
    Move 0 to MertechInc_iParamCount
    INDICATE ERR False

    If      (MertechInc_DriverName = ORAFlex)   Send MertechInc_SQL_SET_ORAPROCEDURE_NAME !1 !3
    Else If (MertechInc_DriverName = MYSQLFLEX) Send MertechInc_SQL_SET_MYPROCEDURE_NAME !1 !3
    Else If (MertechInc_DriverName = SQLFLEX)   Send MertechInc_SQL_SET_MSPROCEDURE_NAME !1 !3
    Else If (MertechInc_DriverName = PgFlex)   Send MertechInc_SQL_SET_PGPROCEDURE_NAME !1 !3

    Move !3 to MertechInc_iParamCount  // Make sure MertechInc_iParamCount will have the proper value
#ENDCOMMAND

#Replace MDS_SET_PROCEDURE_NAME SQL_SET_PROCEDURE_NAME

Procedure MertechInc_SQL_SET_ORAPROCEDURE_NAME Global String strProcName Integer iNumpar
    Integer iParam

    Move 0 to MertechInc_iParamCount       //Redundant, but left in incase called
    INDICATE ERR False              //directly and not via SQL_SET_PROCEDURE_NAME
    Move ORAFlex to MertechInc_DriverName  //

    SQL_SET_STMT to "BEGIN "
    SQL_APPEND_STMT to strProcName
    SQL_APPEND_STMT to "( "
    For iParam from 1 to iNumpar
        DO_PASS_ARGUMENTS iParam
    Loop
    SQL_APPEND_STMT to  " ); END;"
    SQL_PREPARE_STMT
 End_Procedure

Procedure MertechInc_SQL_SET_MYPROCEDURE_NAME Global String strProcName Integer iNumpar
    Integer iParam

    Move 0 to MertechInc_iParamCount           //Redundant, but left in incase called
    INDICATE ERR False                  //directly and not via SQL_SET_PROCEDURE_NAME
    Move MySQLFlex to MertechInc_DriverName    //

    SQL_SET_STMT to "CALL "
    SQL_APPEND_STMT to strProcName
    SQL_APPEND_STMT to "("
    For iParam from 1 to iNumpar
        DO_PASS_ARGUMENTS iParam
    Loop
    SQL_APPEND_STMT to ")"
    SQL_PREPARE_STMT
End_Procedure

Procedure MertechInc_SQL_SET_MSPROCEDURE_NAME Global String strProcName Integer iNumpar
    Integer iParam
    String  sParam

    Move SQLFlex to MertechInc_DriverName

    // This calling syntax is referred to as the "ODBC CALL escape sequence".  This syntax is
    // advised over the execute command since CALL allows for the retrieval of the return codes
    // from the call.
    SQL_SET_STMT to "{? = CALL "
    SQL_APPEND_STMT to strProcName

    // Note that DO_PASS_ARGUMENTS can add the open paren for us, but only if the keyword "PASSING"
    // is passed to it first time through.  This is a bit weird, so we ignore that and just add
    // the open and close parens ourself to make things more clear.
    If (iNumpar > 0) SQL_APPEND_STMT to " ("

    For iParam from 1 to iNumpar
        DO_PASS_ARGUMENTS iParam
    Loop

    If (iNumpar > 0) SQL_APPEND_STMT to ")"
    SQL_APPEND_STMT to  " };"

    SQL_PREPARE_STMT

    // This bind parameter is for the "{? = " which is technically the first parameter even though
    // it is the return value.  The driver will bind MertechInc_iWork to it.
    DO_BIND_PARAMETERS MertechInc_iWork
End_Procedure

Procedure MertechInc_SQL_SET_PGPROCEDURE_NAME Global String strProcName Integer iNumpar
    Integer iParam
    String  sParam

    Move PgFlex to MertechInc_DriverName

    // For Postgres, you can call a function just by passing the function name and
    // open/close parens
    SQL_SET_STMT to strProcName

    // Note that DO_PASS_ARGUMENTS can add the open paren for us, but only if the keyword "PASSING"
    // is passed to it first time through.  This is a bit weird, so we ignore that and just add
    // the open and close parens ourself to make things more clear.
    SQL_APPEND_STMT to "( "

    For iParam from 1 to iNumpar
        DO_PASS_ARGUMENTS iParam
    Loop

    SQL_APPEND_STMT to ")"

    SQL_PREPARE_STMT
    // Indicate that a stored function will be executed - Query = 0, Procedure = 1, Function = 2
    Call_Driver 0 MertechInc_DriverName Function CALLDRV_EMBEDDED_SQL_TYPE CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 1 RESULT MertechInc_iRet
End_Procedure

//=============================================================================
/// @Name        SQL_GET_STMT
/// @Description This command returns the last embedded SQL statement that
/// was executed into a string. Optional parameters can be passed to specify
/// what character to start the string at and also the maximum number of
/// characters to allow for the string.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-09-24 by Aaron Gulack
/// @See 		 SQL_GET_STATEMENT
///
/// @Syntax SQL_GET_STMT to {variable} [{max} {start}]
/// @Param variable			SQL statement to be executed
/// @Param max				Indicates the maximum number of characters to get (optional)
/// @Param start			Indicates what character to start at for the returned string (optional)
///
/// @Example
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active' "
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// SQL_FETCH_NEXT_ROW into sFirstName sLastName
/// If (Found) Begin
///     Showln sFirstName
///     Showln sLastName
/// End
///
/// SQL_GET_STATEMENT to sValue
/// Showln sValue
#COMMAND SQL_GET_STMT "TO" #UGRLEC #L%U #L% .
    //MertechInc_iArg  - integer - Length (number of char to return)
    //MertechInc_iWork - integer - Start  (start character)
    #IF !0>2
        Move !3 to MertechInc_iArg   // Length

        #IF !0>3            // Start Position
            Move !4 to MertechInc_iWork
        #ELSE
            Move 0 to MertechInc_iWork
        #ENDIF
    #ELSE
        Move 0 to MertechInc_iArg
        Move 0 to MertechInc_iWork
    #ENDIF

    Get MertechInc_SQL_GET_STATEMENT MertechInc_iArg MertechInc_iWork to !2
#ENDCOMMAND

#Replace SQL_GET_STATEMENT SQL_GET_STMT

Function MertechInc_SQL_GET_STATEMENT Global Integer iLength Integer iStart Returns String
    String sStatement

    DO_GETFILENUMBER_DRIVERNAME 0

    If (MertechInc_FileNumber <> -1) Begin
        Get MertechInc_Pre_Size_String 0 to sStatement
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_GET_SQL_STMT CALLBACK 0 PASSING sStatement iStart iLength RESULT MertechInc_iRet
    End
    Function_Return sStatement
End_Function

//=============================================================================
/// @Name        SQL_SET_FUNCTION_NAME
/// @Description This command is used in the same way as SQL_SET_PROCEDURE_NAME
/// and SQL_SET_STMT to set the name of the function to be executed. When
/// calling SQL functions in this fashion, this command must be used along with
/// SQL_FUNCTION_EXECUTE (to execute the function), SQL_SET_FUNCTION_PARAMETER
/// (to set the needed parameters) and SQL_GET_FUNCTION_RETURN (to get any
/// returned value). The number of parameters must be set using the constant,
/// NUMPAR, followed by the number of parameters. Note that when setting the
/// name of the function, the user can be specified or, if left blank, the
/// current user will be inserted before the function name.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See 		 SQL_FUNCTION_EXECUTE SQL_SET_FUNCTION_PARAMETER SQL_GET_FUNCTION_RETURN
///
/// @Syntax SQL_SET_FUNCTION_NAME {function} NUMPAR {parameters}
/// @Param function			Full name of the function
/// @Param parameters		Number of parameters to pass
///
/// @Example
/// SQL_SET_FUNCTION_NAME "getCustomerStatus" NUMPAR 1
/// SQL_SET_FUNCTION_PARAMETER 1 to 'Jones' IN
/// SQL_FUNCTION_EXECUTE
/// SQL_GET_FUNCTION_RETURN to dDOB
/// Showln dDOB
#COMMAND SQL_SET_FUNCTION_NAME R "NUMPAR" R
    DO_GETFILENUMBER_DRIVERNAME 0
    MOVE 0 TO MertechInc_iParamCount
    INDICATE ERR FALSE

    If      (MertechInc_DriverName = ORAFlex)   Send MertechInc_SQL_SET_ORAFUNCTION_NAME !1 !3
    Else If (MertechInc_DriverName = MYSQLFLEX) Send MertechInc_SQL_SET_MYFUNCTION_NAME  !1 !3
    Else If (MertechInc_DriverName = SQLFLEX)   Send MertechInc_SQL_SET_SQLFUNCTION_NAME !1 !3
    Else If (MertechInc_DriverName = PgFlex)    Send MertechInc_SQL_SET_PGFUNCTION_NAME !1 !3

    // Make sure MertechInc_iParamCount will have the proper value
    If (MertechInc_DriverName = ORAFlex) MOVE (!3 + 1) TO MertechInc_iParamCount
    Else MOVE !3 TO MertechInc_iParamCount
#ENDCOMMAND

Procedure MertechInc_SQL_SET_ORAFUNCTION_NAME Global String strProcName Integer iNumpar
    Integer iParam

    SQL_SET_STMT to "BEGIN "
    SQL_APPEND_STMT to ":PAR_RET := "
    SQL_APPEND_STMT to strProcName
    SQL_APPEND_STMT to "( "
    For iParam from 1 to iNumpar
        DO_PASS_ARGUMENTS iParam
    Loop
    SQL_APPEND_STMT to  " ); END;"
    SQL_PREPARE_STMT

    Move IS_OUT to MertechInc_iArg
    Call_Driver 0 ORAFLEX Function CALLDRV_SET_PROC_ATTRIBUTE_TYPE CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet

    Increment MertechInc_iParamCount
    Move ":PAR_RET" to MertechInc_sArg2
    Call_Driver 0 MertechInc_DriverName Function CALLDRV_BIND_PARAMETER CALLBACK 0 PASSING MertechInc_Blank MertechInc_sArg2 16384 RESULT MertechInc_iRet
End_Procedure

Procedure MertechInc_SQL_SET_MYFUNCTION_NAME Global String strProcName Integer iNumpar
    Integer iParam

    Move MySQLFlex to MertechInc_DriverName

    SQL_SET_STMT to "SELECT "
    SQL_APPEND_STMT to strProcName
    SQL_APPEND_STMT to "("
    For iParam from 1 to iNumpar
        DO_PASS_ARGUMENTS iParam
    Loop
    SQL_APPEND_STMT to ")"
    SQL_PREPARE_STMT
End_Procedure

Procedure MertechInc_SQL_SET_SQLFUNCTION_NAME Global String strProcName Integer iNumpar
    Integer iParam

    Move SQLFlex to MertechInc_DriverName

    If (not(strProcName contains ".")) Begin
        String schema
        GET_SCHEMA_NAME to schema
        Move (schema + "." + strProcName) to strProcName
    End

    SQL_SET_STMT    to "SELECT "
    SQL_APPEND_STMT to strProcName
    SQL_APPEND_STMT to "("
End_Procedure

Procedure MertechInc_SQL_SET_PGFUNCTION_NAME Global String strProcName Integer iNumpar
    Integer iParam

    Move PgFlex to MertechInc_DriverName

    SQL_SET_STMT    to "SELECT "
    SQL_APPEND_STMT to strProcName
    SQL_APPEND_STMT to "("
End_Procedure

//=============================================================================
/// @Name        SQL_SET_PROCEDURE_PARAMETER
/// @Description
/// With this command you can pass one or more parameters to predefined
/// stored procedures on a MySQL or Oracle server. The SQL_SET_PROCEDURE_PARAMETER
/// command enables you to add a parameter to a stored procedure which you are
/// planning to call. You can pass multiple parameters by calling the command
/// for each parameter.
///
/// When passing parameters you'll have to inform the driver which variable
/// you are passing, starting with 1 from left-to-right in the parameter list.
///
/// For each parameter you'll have to indicate if the variable is to be
/// regarded as input, output or both.
///
///@Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-09-27 by Aaron Gulack
/// @See 		 SQL_SET_PROCEDURE_NAME SQL_PROCEDURE_EXECUTE
///
/// @Syntax SQL_SET_PROCEDURE_PARAMETER {number} to {variable} {direction}
/// @Param number			Index number of the parameter being defined.
/// @Param variable			Variable holding the parameter to be passed.
/// @Param direction		IN, OUT, IN_OUT, RSET, or leave blank
///
/// @Example
/// SQL_SET_PROCEDURE_NAME "sys.sp_addmessage" NUMPAR 3
/// SQL_SET_PROCEDURE_PARAMETER 1 to 500004 IN
/// SQL_SET_PROCEDURE_PARAMETER 2 to 15 IN
/// SQL_SET_PROCEDURE_PARAMETER 3 to "Please enter a valid Date" IN
/// SQL_PROCEDURE_EXECUTE
#COMMAND SQL_SET_PROCEDURE_PARAMETER R "TO" R """IN""OUT""IN_OUT""RSET"
    #IFTYPE !3 "D"
        Move DF_DATE to MertechInc_sArg1
    #ELSE
        Move " " to MertechInc_sArg1
    #ENDIF

    If (!1 <= MertechInc_iParamCount) Begin
        Move MertechInc_iParamCount to MertechInc_iSaveCount       // Save MertechInc_iParamCount
        Move (!1 -1) to MertechInc_iParamCount

        #IFDEF MertechInc_iArg
        #ELSE
            Integer MertechInc_iArg
        #ENDIF

        #IF (!0 = 4)
            #IFSAME !4 IN
                Move IS_IN to MertechInc_iArg
            #ELSE
                #IFSAME !4 OUT
                    Move IS_OUT to MertechInc_iArg
                #ELSE
                    #IFSAME !4 IN_OUT
                        Move IS_IN_OUT to MertechInc_iArg
                    #ELSE
                        Move IS_RSET to MertechInc_iArg
                    #ENDIF
                #ENDIF
            #ENDIF
        #ELSE
            Move IS_NONE to MertechInc_iArg
        #ENDIF

        Call_Driver 0 MertechInc_DriverName Function CALLDRV_SET_PROC_ATTRIBUTE_TYPE CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet

        DO_BIND_PARAMETERS (!3)
        Move MertechInc_iSaveCount to MertechInc_iParamCount
    End
    Else Begin
        Error 4099                  // Bad Parameter
    End
#ENDCOMMAND

#Replace MDS_SET_PROCEDURE_PARAMETER SQL_SET_PROCEDURE_PARAMETER

#COMMAND SQL_SET_FUNCTION_PARAMETER R "TO" R """IN""OUT""IN_OUT"
    If (MertechInc_DriverName <> SQLFLEX and MertechInc_DriverName <> PgFlex) Begin
        #IF !0=4
            SQL_SET_PROCEDURE_PARAMETER !1 to !3 !4
        #ELSE
            SQL_SET_PROCEDURE_PARAMETER !1 to !3 IN
        #ENDIF
    End
    Else Begin
        If (!1 > 1) sql_append_stmt to ", "
        sql_append_stmt to "'"
        sql_append_stmt to (!3)
        sql_append_stmt to "'"
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_GET_PROCEDURE_PARAMETER
/// @Description This command is used to get the value of a specific
/// parameter associated with a stored procedure.  Although this
/// command will work with any parameter, it is mostly be used with
/// IN/OUT or OUT parameters as their value will more often be important
/// once returned. When multiple values are returned, this command can be
/// more efficient than other options. Note that the specified parameter
/// must first be defined using the SQL_SET_PROCEDURE_PARAMETER command
/// in order to work properly.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See 		 SQL_SET_PROCEDURE_NAME SQL_SET_PROCEDURE_PARAMETER SQL_PROCEDURE_EXECUTE
///
/// @Syntax SQL_GET_PROCEDURE_PARAMETER {parameter} to {variable}
/// @Param parameter		Number of paramater to return
/// @Param variable			Variable to hold the value of the parameter
///
/// @Example
/// SQL_SET_PROCEDURE_NAME "user.getCustomerStatus" NUMPAR 1
/// SQL_SET_PROCEDURE_PARAMETER 1 to sCustomerID IN_OUT
/// SQL_PROCEDURE_EXECUTE
/// SQL_GET_PROCEDURE_PARAMETER 1 to sStatus
///
/// Showln sStatus
///
/// @Example
/// SQL_SET_PROCEDURE_NAME "user.getCustomerStatus" NUMPAR 2
/// SQL_SET_PROCEDURE_PARAMETER 1 to sCustomerID IN
/// SQL_SET_PROCEDURE_PARAMETER 2 to sStatus OUT
/// SQL_PROCEDURE_EXECUTE
/// SQL_GET_PROCEDURE_PARAMETER 2 to sStatus
///
/// Showln sStatus
#COMMAND SQL_GET_PROCEDURE_PARAMETER R "TO" R
    If (!1 <= MertechInc_iParamCount) Begin
        Move MertechInc_iParamCount to MertechInc_iSaveCount  // Save MertechInc_iParamCount

        // For Postgres, we need to pass starting at 1, not 0 because there is ALWAYS a return
        // value at index 0. MS SQL is -1 based in the driver, so we need to subtract 2 for it
        // to start at the proper index.
        If (MertechInc_DriverName = PgFlex) ;
            Move (!1) to MertechInc_iParamCount
        Else If (MertechInc_DriverName = SQLFLEX) ;
            Move (!1 -2) to MertechInc_iParamCount
        Else ;
            Move (!1 -1) to MertechInc_iParamCount

        DO_GET_BIND_PARAMETERS !3
        Move MertechInc_iSaveCount to MertechInc_iParamCount
    End
    Else Begin
        Error 4099  // Bad Parameter
    End
#ENDCOMMAND

#Replace MDS_GET_PROCEDURE_PARAMETER SQL_GET_PROCEDURE_PARAMETER

#COMMAND SQL_GET_FUNCTION_PARAMETER R "TO" R
    SQL_GET_PROCEDURE_PARAMETER (!1 + 1) TO !3
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_GET_FUNCTION_RETURN
/// @Description This variable is used to get the value returned from a SQL
/// function call. After the function has been successfully called, this
/// command takes the returned value and inserts it the given variable.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See 		 SQL_SET_FUNCTION_NAME SQL_SET_FUNCTION_PARAMETER SQL_FUNCTION_EXECUTE
///
/// @Syntax SQL_GET_FUNCTION_RETURN to {variable}
/// @Param variable			Variable to hold the returned value
///
/// @Example
/// SQL_SET_FUNCTION_NAME "getCustomerStatus" NUMPAR 1
/// SQL_SET_FUNCTION_PARAMETER 1 to 'Jones' IN
/// SQL_FUNCTION_EXECUTE
/// SQL_GET_FUNCTION_RETURN to dDOB
/// Showln dDOB
#COMMAND SQL_GET_FUNCTION_RETURN "TO" R
    If (MertechInc_DriverName = ORAFlex) ;
        SQL_GET_PROCEDURE_PARAMETER 1 to !2
    else ;
        SQL_FETCH_COLUMN 1 into !2
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_FUNCTION_EXECUTE
/// @Description This command is used to execute the function statement
/// that was built by the SQL_SET_FUNCTION_NAME and subsequent
/// SQL_SET_FUNCTION_PARAMETER commands. This works similarly to the
/// SQL_EXECUTE_STMT command. Note that executing the function with this
/// command will not get any returned values but will simply execute the
/// function.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See 		 SQL_SET_FUNCTION_NAME SQL_SET_FUNCTION_PARAMETER SQL_GET_FUNCTION_RETURN
///
/// @Syntax SQL_FUNCTION_EXECUTE
///
/// @Example
/// SQL_SET_FUNCTION_NAME "getCustomerStatus" NUMPAR 1
/// SQL_SET_FUNCTION_PARAMETER 1 to 'Jones' IN
/// SQL_FUNCTION_EXECUTE
/// SQL_GET_FUNCTION_RETURN to dDOB
/// Showln dDOB
#COMMAND SQL_FUNCTION_EXECUTE
    send MertechInc_SQL_FUNCTION_EXECUTE MertechInc_DriverName
#ENDCOMMAND

Procedure MertechInc_SQL_FUNCTION_EXECUTE Global String sDriverName
    Integer iParam
    String  sParam

    If (sDriverName = SQLFLEX or sDriverName = PgFlex) Begin
       SQL_APPEND_STMT to ')'
       SQL_PREPARE_STMT
    End

    SQL_EXECUTE_STMT
    If (sDriverName <> ORAFLEX) Begin
        SQL_FETCH_NEXT_ROW
    End
End_Procedure

//=============================================================================
/// @Name        REEXEC_ORACLE_STORED_PROCEDURE
/// @Description This command is used to re-execute a stored procedure
/// when using Oracle. Although it follows the same format as
/// CALL_STORED_PROCEDURE, it can be useful because it does not need to
/// prepare the procedure again before executing. This can cause speed
/// improvements when calling a stored procedure multiple times.
///
/// @Assumptions A procedure has already been created through CALL_STORED_PROCEDURE
/// @Status      Public
/// @Drivers     ORAFLex
/// @VersionNote Last Revised: 2013-10-04 by Aaron Gulack
/// @See 		 CALL_STORED_PROCEDURE
///
/// @Syntax CALL_ORACLE_STORED_PROCEDURE {procedure} Passing {variable}
/// @Param procedure		Full name of the procedure
/// @Param variable			Parameter to pass (optional and can be multiple)
///
/// @Example
/// CALL_STORED_PROCEDURE "user.getCustomerStatus" Passing sCustomerID sStatus
/// Showln sStatus
///
/// Move (sCustomerID + 1) to sCustomerID
///
/// REEXEC_ORACLE_STORED_PROCEDURE "user.getCustomerStatus" passing sCustomerID sStatus
/// Showln sStatus
#COMMAND REEXEC_ORACLE_STORED_PROCEDURE R "PASSING"""
    MOVE 0 TO MertechInc_iParamCount
    SQL_SET_STMT TO " "
    INDICATE ERR FALSE
    #IF (!0>2)
        DO_PASS_ARGUMENTS !3 !4 !5 !6 !7 !8 !9
        [ NOT ERR ] BEGIN
            IF MertechInc_iParamCount GT 0 BEGIN
                MOVE 0 TO MertechInc_iParamCount
                DO_BIND_PARAMETERS !3 !4 !5 !6 !7 !8 !9
            END
        END
    #ENDIF
    //SQL_EXECUTE_STMT
    Move 1 to MertechInc_sArg1         // Initialize the Row_Count value
    Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 22 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 5 RESULT MertechInc_iRet
    If MertechInc_iRet EQ -1 INDICATE ERR True
    [ NOT ERR ] BEGIN
        If ( MertechInc_iParamCount GT 0 ) BEGIN
            MOVE 0 TO MertechInc_iParamCount
            DO_GET_BIND_PARAMETERS !3 !4 !5 !6 !7 !8 !9
        END
    END
#ENDCOMMAND

#COMMAND REEXEC_STORED_PROCEDURE R "PASSING"""
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        REEXEC_ORACLE_STORED_PROCEDURE !1 !2 !3 !4 !5 !6 !7 !8 !9
    End
#ENDCOMMAND

//=============================================================================
/// @Name        CALL_STORED_FUNCTION
/// @Description This command is used to execute a function stored in the
/// SQL backend. This is an alternative to building a function with the
/// SQL_SET_FUNCTION_NAME, SQL_SET_FUNCTION_PARAMETER and SQL_FUNCTION_EXECUTE
/// commands. This command builds and executes the function by setting the full
/// function name, the parameter(s) to pass and the variable to hold the
/// returned value. Note that this command can only return a single value
/// so SQL_SET_FUNCTION_PARAMETER and SQL_SET_FUNCTION_NAME must be used when
/// dealing with multiple return values.
///
/// Assumptions
/// @Status      Public
/// @Drivers     ORAFLex MySQLFlex PgFlex
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See
///
/// @Syntax CALL_STORED_FUNCTION {function} Returns {variable} Passing {parameters}
/// @Param function			Full name of the function
/// @Param variable		  	Variable to hold the returned value
/// @Param parameters		Parameter to pass to the function (can be multiple)
///
/// @Example
/// Move 5 to sCustomerID
/// CALL_STORED_FUNCTION "getCustomerStatus" Returns sStatus Passing sCustomerID
/// Showln sStatus
#COMMAND CALL_STORED_FUNCTION R "RETURNS" R "PASSING"""
    DO_GETFILENUMBER_DRIVERNAME 0

    If      (MertechInc_DriverName EQ MDSPGSQL)  CALL_PGSQL_STORED_FUNCTION  !1 !2 !3 !4 !5 !6 !7 !8 !9
    Else If (MertechInc_DriverName EQ MySQLFlex) CALL_MYSQL_STORED_FUNCTION  !1 !2 !3 !4 !5 !6 !7 !8 !9
    Else                                         CALL_ORACLE_STORED_FUNCTION !1 !2 !3 !4 !5 !6 !7 !8 !9
#ENDCOMMAND

//=============================================================================
/// @Name        OUTPUT_INT_FILE
/// @Description This command is used to output the int file of an opened
/// table. If the file to be output to does not exist, it will be created
/// upon execution of this command. Note that the INT file can be output
/// into multiple types of files i.e. .doc, .txt, .int.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See
///
/// @Syntax OUTPUT_INT_FILE for {FileNumber} to {variable}
/// @Param FileNumber		The file number
/// @Param variable			Path of the file being output to
///
///@Example
/// OUTPUT_INT_FILE for Customer.File_Number to "C:\Temp\Customer.int"
#COMMAND OUTPUT_INT_FILE "FOR" R "TO" R .
    DO_GETFILENUMBER_DRIVERNAME !2
    If (MertechInc_FileNumber <> -1) Begin
        MOVE !4 TO MertechInc_sArg1

        IF (MertechInc_DriverName EQ ORAFLEX OR MertechInc_DriverName EQ MDSDB2) ;
            Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 19 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
        ELSE ;
            Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 16 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    END
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_ERROR_MESSAGE
/// @Description This command is used to get an error message
/// from a given SQL statement. If the given statement is executed with
/// no errors, the variable specified with this command will be blank.
/// Otherwise the message will be stored in the given variable. Note that
/// unless specified, strings have a size limit of 80 characters, so using
/// a variant can ensure the full message is retrieved.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See         SQL_ERROR_MESSAGE2
///
/// @Syntax SQL_ERROR_MESSAGE {variable}
/// @Param variable			Variable to hold the error message
///
/// @Example
/// SQL_ERROR_MESSAGE sError
#COMMAND SQL_ERROR_MESSAGE R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Get MertechInc_SQL_ERROR_MESSAGE to !1

        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

Function MertechInc_SQL_ERROR_MESSAGE Global Returns String
    String sMessage

    Get MertechInc_Pre_Size_String 0 to sMessage
    Call_Driver 0 MertechInc_DriverName Function CALLDRV_SQL_ERROR_MESSAGE CALLBACK 0 PASSING MertechInc_Blank sMessage 0 RESULT MertechInc_iRet

    Function_Return sMessage
End_Function

//=============================================================================
/// @Name        SQL_ERROR_MESSAGE2
/// @Description This command is used to get the last error message used
/// for the specified server. This can be useful once a transaction has
/// already been completed and any error messages need to be retrieved.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See         SQL_ERROR_MESSAGE SQL_ERROR_MESSAGE2
///
/// @Syntax SQL_ERROR_MESSAGE2 of {server} to {variable}
/// @Param server			Name of the server
/// @Param variable			Variable to hold the error message
///
/// @Example
/// SQL_ERROR_MESSAGE2 of "localhost" to sError
#COMMAND SQL_ERROR_MESSAGE2 "OF" R "TO" R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Get MertechInc_SQL_ERROR_MESSAGE2 !2 to !4
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

Function MertechInc_SQL_ERROR_MESSAGE2 Global String sServer Returns String
    String sMessage

    Get MertechInc_Pre_Size_String 800 to sMessage
    Call_Driver 0 MertechInc_DriverName Function CALLDRV_SQL_ERROR_MESSAGE2 CALLBACK 0 PASSING sServer sMessage 0 RESULT MertechInc_iRet

    Function_Return sMessage
End_Function

//=============================================================================
/// @Name        MERTECH_WARNING_MESSAGE
/// @Description When restructuring a table, i.e. Structure_Start, a warning
/// message will appear to confirm the restructure before it is executed.
/// This command is used to disable or enable that warning message. All that
/// is passed is either the constant "Enabled" or "Disabled". By default,
/// this message is enabled.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
///
/// @Syntax MERTECH_WARNING_MESSAGE {Enabled|Disabled}
/// @Param Enabled			Enables the restructure warning
/// @Param Disabled			Disables the restructure warning
///
/// @Example
/// Move Customer.File_Number to hFile
/// MERTECH_WARNING_MESSAGE Disabled
///
/// Structure_Start hFile
///    	Set_Attribute DF_FILE_OEM_TRANSLATION of hFile to True
/// Structure_End hFile
#COMMAND MERTECH_WARNING_MESSAGE "ENABLED""DISABLED" .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        #IFSAME !1 DISABLED
            CALL_DRIVER 0 MertechInc_DriverName  FUNCTION 34 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 1 RESULT MertechInc_iRet
        #ELSE
            CALL_DRIVER 0 MertechInc_DriverName  FUNCTION 34 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
        #ENDIF
    End
#ENDCOMMAND

//=============================================================================
/// @Name        DISABLE_SELECT_COLUMNS_ERRORS
/// @Description When using SELECT_COLUMNS_FIND to limit the number of columns
/// to fetch, the framework might still ask for columns that you do not need.
/// As a result you'll end up getting runtime errors you do not want to see.
/// This command gives you the ability to stop reporting errors for querying
/// for data from columns that are not part of the query.
///
/// DISABLED_SELECT_COLUMNS_ERRORS DISABLED will disable the errors, use
/// ENABLED to turn the error messages back on.
///
/// By default triggering error messages on unknown columns is ENABLED
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2014-04-28 by Wil van Antwerpen
/// @See         SELECT_COLUMNS_FIND RESET_FETCH_FIELDS
///
/// @Example
/// Open Customer
/// RESET_FETCH_FIELDS  CUSTOMER DF_FETCH_FALSE
/// SELECT_COLUMNS_FIND CUSTOMER CUSTOMER_NUMBER NAME
/// DISABLE_SELECT_COLUMNS_ERRORS DISABLED
///
/// Clear Customer
/// Repeat
///    Find Gt Customer by Index.1
///    If (Found) Showln Customer.Customer_Number '-' Customer.Name
/// Until (Not(Found))
///
/// RESET_FETCH_FIELDS Customer DF_FETCH_TRUE
///
/// @Syntax DISABLE_SELECT_COLUMNS_ERRORS {ENABLED|DISABLED}
#COMMAND DISABLE_SELECT_COLUMNS_ERRORS "ENABLED""DISABLED" .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        #IFSAME !1 DISABLED
            CALL_DRIVER 0 MertechInc_DriverName  FUNCTION 35 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 1 RESULT MertechInc_iRet
        #ELSE
            CALL_DRIVER 0 MertechInc_DriverName  FUNCTION 35 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
        #ENDIF
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQLFlex_REVISION
/// @Description This command will put the current version (decimals included)
/// of the MSSQL driver associated with the current workspace into the
/// specified variable.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See 		 GET_DRIVER_REVISION
///
/// @Syntax SQLFlex_REVISION {variable}
/// @Param variable			String variable to hold the returned version
///
/// @Example
/// SQLFlex_REVISION sVersion
#COMMAND SQLFlex_REVISION #CRUG .
    INDICATE ERR False
    Move (Repeat(" ",255)) to !1
    Call_Driver 0 SQLFlex Function 0 CALLBACK 0 PASSING MertechInc_Blank !1 0 RESULT MertechInc_iRet
    If MertechInc_iRet EQ -1 INDICATE ERR True
#ENDCOMMAND

//=============================================================================
/// @Name        SQLFlex_MAJOR_REVISION
/// @Description This command will put the major version (no decimals) of
/// the the MSSQL driver associated with the current workspace into the
/// specified variable.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See 		 GET_DRIVER_MAJOR_REVISION
///
/// @Syntax SQLFlex_MAJOR_REVISION {variable}
/// @Param variable			String variable to hold the returned version
///
/// @Example
/// SQLFlex_MAJOR_REVISION sVersion
#COMMAND SQLFlex_MAJOR_REVISION #CRUG .
    INDICATE ERR False
    Move (Repeat(" ",10)) to MertechInc_sArg2
    Call_Driver 0 SQLFlex Function 0 CALLBACK 0 PASSING MertechInc_Blank MertechInc_sArg2 4 RESULT MertechInc_iRet
    If MertechInc_iRet EQ -1 INDICATE ERR True
    Else Move MertechInc_sArg2 to !1
#ENDCOMMAND

//=============================================================================
/// @Name        LOGGED_USERS
/// @Description This command returns the number of native users that are
/// using the driver currently. This number is stored in the variable that
/// is passed with the command.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See		 MAXIMUM_NUMBER_OF_USERS
///
/// @Syntax LOGGED_USERS {variable}
/// @Param variable			Variable to hold the number of users
///
/// @Example LOGGED_USERS sUsers
#COMMAND LOGGED_USERS #CRUG .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Call_Driver 0 MertechInc_DriverName Function 33 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
        MOVE MertechInc_iRet TO !1
    End
#ENDCOMMAND

//=============================================================================
/// @Name        MAXIMUM_NUMBER_OF_USERS
/// @Description This command returns the maximum number of user allowed by
/// the current license.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See 		 LOGGED_USERS
///
/// @Syntax MAXIMUM_NUMBER_OF_USERS {variable}
/// @Param variable			Variable to hold the maximum number of users
///
/// @Example
/// MAXIMUM_NUMBER_OF_USERS sMax
#COMMAND MAXIMUM_NUMBER_OF_USERS #CRUG .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        INDICATE ERR FALSE
        Move (Repeat(" ",10)) to MertechInc_sArg2
        CALL_DRIVER 0 MertechInc_DriverName FUNCTION 0 CALLBACK 0 PASSING MertechInc_Blank MertechInc_sArg2 3 RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
        Else Move MertechInc_sArg2 to !1
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SET_DATABASE_NAME
/// @Description This command overrides the database set in the INT file
/// under DATABASE_SPACE_NAME. Any opens or finds will use the database
/// specified here. This can be used when the database is not stated in
/// the INT file or if the database needs to be dynamically changed for
/// a certain query. If the database is not specified with this command
/// or in the INT file, then the default database for the server will be
/// used. To set the database to be used for embedded SQL statements,
/// use SQL_USE_DATABASE.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex, MySQLFlex and PGFlex
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See 		 GET_DATABASE_NAME SQL_USE_DATABASE
/// @INTOPT		 DATABASE_SPACE_NAME
///
/// @Syntax SET_DATABASE_NAME to {database}
/// @Param database			Name of the database
///
/// @Example
/// Login "localhost" "user" "pas123" "sql_drv"
/// SET_DATABASE_NAME to "TestDB"
/// Open Customer
#COMMAND SET_DATABASE_NAME "TO" R .
    DO_GETFILENUMBER_DRIVERNAME 0
    INDICATE ERR FALSE
    IF (MertechInc_DriverName EQ SQLFLEX OR MertechInc_DriverName EQ MDSMySQL OR MertechInc_DriverName EQ MDSPgSQL) BEGIN
        MOVE !2 TO MertechInc_sArg1
        CALL_DRIVER 0 MertechInc_DriverName FUNCTION 9 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    END
#ENDCOMMAND

//=============================================================================
/// @Name        GET_DATABASE_NAME
/// @Description This command is used to get the name of the database
/// currently being used. The name of the database is returned into the
/// specified string. Even though this command works either way, it is
/// typically used when the INT file does not contain the DATABASE_SPACE_NAME.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex, MySQLFlex and PgFlex
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See SET_DATABASE_NAME SQL_USE_DATABASE
///
/// @Syntax GET_DATABASE_NAME to {variable}
/// @Param variable			Variable to hold the database name
///
/// @Example
/// GET_DATABASE_NAME to sDbName
#COMMAND GET_DATABASE_NAME "TO" #CRUG .
    DO_GETFILENUMBER_DRIVERNAME 0
    INDICATE ERR FALSE
    IF (MertechInc_DriverName EQ SQLFLEX OR MertechInc_DriverName EQ MDSMySQL OR MertechInc_DriverName EQ MDSPgSQL) BEGIN
        MOVE (REPEAT(" ",255)) to MertechInc_sArg1
        CALL_DRIVER 0 MertechInc_DriverName FUNCTION 9 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 1 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
        [  ERR ] Move ""               to !2
        [ ~ERR ] Move MertechInc_sArg1 to !2
    END
#ENDCOMMAND

//=============================================================================
/// @Name        GET_NAME_SPACE
/// @Description This command returns the name space, or schema, being
/// used with the current application.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     PgFlex
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See 		 SET_NAME_SPACE
///
/// @Syntax GET_NAME_SPACE to {variable}
/// @Param variable			Variable to hold the returned name space.
///
/// @Example
/// GET_NAME_SPACE to sNameSpace
#COMMAND GET_NAME_SPACE "TO" #CRUG .
    DO_GETFILENUMBER_DRIVERNAME 0
    INDICATE ERR False
    MOVE (REPEAT(" ",255)) to MertechInc_sArg1
    If MertechInc_DriverName EQ PGFLEX Call_Driver 0 PGFLEX Function CALLDRV_PGSQL_NAME_SPACE CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
    IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    [  ERR ] MOVE ""     TO !2
    [ ~ERR ] MOVE MertechInc_sArg1 TO !2
#ENDCOMMAND

//=============================================================================
/// @Name        SET_NAME_SPACE
/// @Description This command sets the name space, or schema, to be used
/// for the application. In Postgres, schemas are objects where all the
/// tables,views and indexes are stored. Separate schemas are used to
/// specify relational data. Note that this command will override the
/// NAME_SPACE value in the INT file.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     PgFlex
/// @VersionNote Last Revised: 2009-08-14 By Ian Smith
/// @See		 GET_NAME_SPACE
/// @INTOPT		 NAME_SPACE
///
/// @Syntax SET_NAME_SPACE to {variable}
/// @Param variable			Name of the name space
///
/// @Example
/// SET_NAME_SPACE to "public"
#COMMAND SET_NAME_SPACE "TO" R .
    DO_GETFILENUMBER_DRIVERNAME 0
    INDICATE ERR False
    IF MertechInc_DriverName EQ PGFLEX BEGIN
        Move !2 to MertechInc_sArg1
        Call_Driver 0 PGFLEX Function CALLDRV_PGSQL_NAME_SPACE CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 1 RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    END
    ELSE INDICATE ERR TRUE
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_USE_DATABASE
/// @Description This command is used to specify which database is used
/// for SQL statements only. Any normal table queries or changes will
/// still use the default database, this only effects SQL statements.
/// If none is specified then the default database is used. This can
/// be useful if a certain SQL statement needs to query data from a
/// database not currently being used. Note that this only works if
/// the table name is not fully qualified in the SQl statement, i.e.
/// "TestDB.Customer".
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex MySQLFLex PgSQL
/// @VersionNote Last Revised: 2013-10-07 by Aaron Gulack
/// @See		 SET_DATABASE_NAME GET_DATABASE_NAME
///
/// @Syntax SQL_USE_DATABASE of {server} to {database}
/// @Param server			Name of the server (Postgre only)
/// @Param database			Name of the database
///
/// @Example
/// SQL_USE_DATABASE "testDB"
///
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active' "
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// SQL_FETCH_NEXT_ROW into sID sFirstName sLastName
/// If (Found) Begin
///     Showln sFirstName
///     Showln sLastName
/// End
/// SQL_CANCEL_QUERY_STMT
#COMMAND SQL_USE_DATABASE
    DO_GETFILENUMBER_DRIVERNAME 0

    #IFSAME !1 of
        #CHECK !3 "TO"
        Move !2 to MertechInc_sArg2
        Move !4 to MertechInc_sArg1
    #ELSE
        Move !1      to MertechInc_sArg1
        Move MertechInc_Blank to MertechInc_sArg2
    #ENDIF
    If (MertechInc_DriverName EQ SQLFLEX or MertechInc_DriverName EQ MDSMySQL or MertechInc_DriverName EQ MDSPgSQL) Begin
        Call_Driver 0 MertechInc_DriverName Function 18 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 0 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SET_CURRENT_SQL_SERVER
/// @Description This command is used to set the server to be used when
/// opening tables. It will override the SERVER_NAME token in the INT file.
/// If the server is not specified in the INT file or with this command,
/// then the server used during login will be used. This command is only
/// needed when connecting to multiple SQL servers. To set the server to
/// use for embedded SQL statements, use SET_CURRENT_SQL_SERVER_CONNECTION.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See 		 GET_CURRENT_SQL_SERVER  SET_CURRENT_SQL_SERVER_CONNECTION GET_CURRENT_SQL_SERVER_CONNECTION
/// @INTOPT		 SERVER_NAME
///
/// @Syntax SET_CURRENT_SQL_SERVER to {server}
/// @Param server			Name of the server
///
/// @Example
/// SET_CURRENT_SQL_SERVER to "localhost"
#COMMAND SET_CURRENT_SQL_SERVER "TO" R .
    INDICATE ERR FALSE
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        If MertechInc_DriverName EQ ORAFLEX Move CALLDRV_ORA_CURRENT_SQL_SERVER to MertechInc_iFunction
        Else                                Move CALLDRV_CURRENT_SQL_SERVER     to MertechInc_iFunction
        Move !2 to MertechInc_sArg1
        Call_Driver 0 MertechInc_DriverName Function MertechInc_iFunction CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//IGS - removed. CURRENT_SERVER is a property of Validation_List_Mixin so this
//               replace conflicts with the property SET message.
//#Replace SET_CURRENT_SERVER SET_CURRENT_SQL_SERVER

//=============================================================================
/// @Name        GET_CURRENT_SQL_SERVER
/// @Description This command returns the name of the server to be used
/// for opening and querying tables.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-07 by Aaron Gulack
/// @See SET_CURRENT_SQL_SERVER SET_CURRENT_SQL_SERVER_CONNECTION GET_CURRENT_SQL_SERVER_CONNECTION
///
/// @Syntax GET_CURRENT_SERVER to {variable}
/// @Param variable			Variable to hold the server name
///
/// @Example
/// GET_CURRENT_SQL_SERVER to sServer
#COMMAND GET_CURRENT_SQL_SERVER "TO" #CRUG .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Move (Repeat(" ",255)) to MertechInc_sArg1
        If MertechInc_DriverName EQ ORAFLEX Move CALLDRV_ORA_CURRENT_SQL_SERVER to MertechInc_iFunction
        Else                                Move CALLDRV_CURRENT_SQL_SERVER     to MertechInc_iFunction
        Call_Driver 0 MertechInc_DriverName Function MertechInc_iFunction CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 1 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
        [  ERR ] Move ""     to !2
        [ ~ERR ] Move MertechInc_sArg1 to !2
    End
#ENDCOMMAND

//IGS - removed. CURRENT_SERVER is a property of Validation_List_Mixin so this
//               replace conflicts with the property GET message.
//#Replace GET_CURRENT_SERVER GET_CURRENT_SQL_SERVER

//=============================================================================
/// @Name        SET_CURRENT_SQL_SERVER_CONNECTION
/// @Description This command is used to specify which server to use for
/// embedded SQL statements. By default, the last logged in server will
/// be used. Note that in addition to setting the server, this command
/// also sets the driver to be used. This command is only needed when
/// connecting to multiple servers. To set the server for opening tables,
/// use SET_CURRENT_SQL_SERVER.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See		 GET_CURRENT_SQL_SERVER_CONNECTION GET_CURRENT_SQL_SERVER SET_CURRENT_SQL_SERVER
///
/// @Syntax SET_CURRENT_SQL_SERVER_CONNECTION of {constant} to {server}
/// @Param constant			MYSQLFLEX, ORAFLEX, PGFLEX, or SQLFLEX
/// @Param server      		Name of the server
///
/// @Example
/// SET_CURRENT_SQL_SERVER_CONNECTION of SQLFLEX to "(localdb)\v11.0"
#COMMAND SET_CURRENT_SQL_SERVER_CONNECTION "OF" R "TO" R .
    INDICATE ERR FALSE

    #IFSAME !2 MYSQLFLEX
    #ELSE
      #IFSAME !2 ORAFLEX
      #ELSE
        #IFSAME !2 PGFLEX
        #ELSE
          #IFSAME !2 SQLFLEX
          #ELSE
            #ERROR 4099 "Invalid parameter"
          #ENDIF
        #ENDIF
      #ENDIF
    #ENDIF

    Move (Uppercase(Trim(!2))) to MertechInc_DriverName

    If (Trim(!4) > "") Move !2 to MertechInc_CurrentDriver
    Else               Move "" to MertechInc_CurrentDriver
    Move !4 to MertechInc_sArg1
    Call_Driver 0 MertechInc_DriverName Function CALLDRV_CURRENT_SQL_SERVER_CONNECTION CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
    If MertechInc_iRet EQ -1 INDICATE ERR True
#ENDCOMMAND

//=============================================================================
/// @Name        GET_CURRENT_SQL_SERVER_CONNECTION
/// @Description This command returns the server currently being used for
/// embedded SQL statements.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See		 SET_CURRENT_SQL_SERVER_CONNECTION GET_CURRENT_SQL_SERVER SET_CURRENT_SQL_SERVER
///
/// @Syntax GET_CURRENT_SQL_SERVER_CONNECTION of {constant} to {variable}
/// @Param constant			MYSQLFLEX, ORAFLEX, PGFLEX, or SQLFLEX
/// @Param variable       	Variable to hold the name of the server
///
/// @Example
/// GET_CURRENT_SQL_SERVER_CONNECTION of SQLFLEX to sServer
#COMMAND GET_CURRENT_SQL_SERVER_CONNECTION "OF" R "TO" #CRUG .
    INDICATE ERR FALSE

    #IFSAME !2 MYSQLFLEX
    #ELSE
      #IFSAME !2 ORAFLEX
      #ELSE
        #IFSAME !2 PGFLEX
        #ELSE
          #IFSAME !2 SQLFLEX
          #ELSE
            #ERROR 4099 "Invalid parameter"
          #ENDIF
        #ENDIF
      #ENDIF
    #ENDIF

    Move (Repeat(" ",255)) to MertechInc_sArg1
    Move !2 to MertechInc_sArg2
    Call_Driver 0 MertechInc_sArg2 Function CALLDRV_CURRENT_SQL_SERVER_CONNECTION CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 1 RESULT MertechInc_iRet
    If MertechInc_iRet EQ -1 INDICATE ERR True
    [  ERR ] Move ""               to !4
    [ ~ERR ] Move MertechInc_sArg1 to !4
#ENDCOMMAND

//=============================================================================
/// @Name        LOGIN_SQLFLEX
/// @Description This command allows the user to login with a specified
/// hostname. The default hostname that is passed is the path of the
/// executable. Passing a custom hostname can be very useful for tracking
/// a specific user for different situations. For example, if a company
/// is using a terminal server and a whole sales team logs in under the
/// same username and hostname, locating a specific user could otherwise
/// be difficult. With this command, each user can pass a custom hostname,
/// easily distinguishing themselves from other users.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See
///
/// @Syntax LOGIN_SQLFLEX {server} {username} {password} {hostname}
/// @Param server		Server to use for login
/// @Param username     Username to use for login
/// @Param password     Password to use for login
/// @Param hostname     Hostname to use for login
///
/// @Example
/// LOGIN_SQLFLEX "localhost" "guestUser" "pas123" "WIN-MM7PQS5CP6C"
#COMMAND LOGIN_SQLFLEX #ULGR$ #ULGR$ #ULGR$ #ULG$ .
  LOGIN (!1+"*"+!4) !2 !3 "SQL_DRV"
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_CANCEL_QUERY_STMT
/// @Description This command is used to close any open cursors related to
/// an SQL_EXECUTE_STMT. This should be used once the SQL statement has
/// been executed and all rows have been fetched.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-03 by Aaron Gulack
/// @See 		 SQL_SET_STMT SQL_EXECUTE_STMT SQL_FETCH_NEXT_ROW SQL_APPEND_STMT SQL_PREPARE_STMT
///
/// @Syntax SQL_CANCEL_QUERY_STMT [of {FileName}]
/// @Param FileName		Name of the file (optional)
///
/// @Example
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active' "
/// SQL_PREPARE_STMT
/// SQL_BINDCOLUMNS_STMT of Customer to DF_BIND_ALL_COLUMNS
/// SQL_EXECUTE_STMT of Customer
/// SQL_FETCH_NEXT_ROW of Customer
/// If (Found) Begin
///     Showln Customer.FirstName
///     Showln Customer.LastName
/// End
/// SQL_CANCEL_QUERY_STMT of Customer
#COMMAND SQL_CANCEL_QUERY_STMT """OF"
    #IF (!0>1)
        DO_GETFILENUMBER_DRIVERNAME !2
    #ELSE
        DO_GETFILENUMBER_DRIVERNAME 0
    #ENDIF
    If (MertechInc_FileNumber <> -1) Begin
        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 22 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 4 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        NATIVE_OPTIMIZATION
/// @Description Allows user to turn off the use of index hints on the native
/// server. Setting this command to DEFAULT will cause the server to use the
/// default settings for hints. Hints are off by default in Microsoft SQL
/// Server but are on in Oracle. Care should be taken with changing the
/// default, and should only be used if the diagnostics tool for your server
/// indicates performance problems with the type of queries that are being
/// generated. Note that this can be turned off or on for the whole server
/// or just for a specific table.
///
/// DEFAULT 		- The specified server's default settings
/// USE_INDEXHINT 	- All Index hints will be used
/// NO_INDEXHINT 	- No index hints will be used
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex, ORAFlex
/// @VersionNote Last Revised: 2013-10-08 by Aaron Gulack
/// @See
///
/// @Syntax NATIVE_OPTIMIZATION of {scopeLevel} {variable} to {constant}
/// @Param scopeLevel		TABLE or SERVER. Indicates the scope of the setting
/// @Param variable			Either the name of the server or of the table
/// @Param constant			DEFAULT, USE_INDEXHINT, or NO_INDEXHINT
///
/// @Example
/// NATIVE_OPTIMIZATION of SERVER "localhost" to USE_INDEXHINT
#COMMAND NATIVE_OPTIMIZATION "OF" "SERVER""TABLE" R "TO" "DEFAULT""NO_INDEXHINT""USE_INDEXHINT"
    #IFSAME !2 TABLE
        DO_GETFILENUMBER_DRIVERNAME !3
        Move "" to MertechInc_sArg1
    #ELSE
        DO_GETFILENUMBER_DRIVERNAME 0
        Move !3 to MertechInc_sArg1
    #ENDIF

    #IFSAME !5 DEFAULT
        Move 0 to MertechInc_iArg
    #ELSE
        #IFSAME !5 NO_INDEXHINT
            Move 1 to MertechInc_iArg
        #ELSE
            Move 2 to MertechInc_iArg
        #ENDIF
    #ENDIF

    If (MertechInc_DriverName = ORAFLEX or MertechInc_DriverName = SQLFLEX) Begin
        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function CALLDRV_NATIVE_OPTIMIZATION CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
    End
    If (MertechInc_iRet = -1) INDICATE ERR True
#ENDCOMMAND

//=============================================================================
/// @Name        SET_ISOLATION_LEVEL
/// @Description This command sets the locking and row versioning behavior
/// for SQL statements. See the options below for information on the various
/// effects they can have on transactions.
///
/// DEFAULT  - The default isolation level for the server (READ_COMMITTED
/// for MSSQL).
///
/// READ_COMMITTED - This option is used to prevent dirty reads. A dirty
/// read is when one transaction reads data from another transaction that
/// has yet to be committed. If one transaction fails, the other now is
/// dealing with invalid data. By setting the isolation level to
/// READ_COMMITTED, dirty reads will be avoided by not allowing transactions
/// to deal with any other data that has not been committed yet. However,
/// in between statements within the current transaction, data can be changed
/// by other transactions. This can result in phantom data or non-repeatable
/// reads. Note that this can slow down performance speeds but is usually
/// good practice.
///
/// READ_UNCOMMITTED - This option is the least restrictive isolation level.
/// With this option, dirty reads are allowed, thus no exclusive locks are
/// honored and modified data from one uncommitted transaction can be read
/// by other transactions.
///
/// REPEATABLE_READ - This option is similar to the READ_COMMITTED option
/// in that locks all placed on all transactions and uncommitted data from
///	other transactions cannot be read, preventing dirty reads. However, unlike
/// READ_COMMITTED, new rows that are added by other transactions can be read
/// by the current transaction if it is retried, possibly resulting in phantom
/// reads. This option should not be used unless there is a specific reason to
/// do so.
///
/// SERIALIZABLE - This option is the most restrictive isolation level. With
/// this option, no interaction is allowed between transactions until they
/// have been committed. Similar to READ_COMMITTED, no transaction can deal
/// with any uncommitted data. On top of that though, range locks are placed on
/// all rows being modified until the current transaction is complete. Because
/// concurrency is so low with this option, performance speeds can be much lower
/// and so this should only be used when there is a specific reason to do so.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-08 by Aaron Gulack
/// @See
///
/// @Syntax SET_ISOLATION_LEVEL of {server} to {constant}
/// @Param server			Name of the server
/// @Param constant			DEFAULT, READ_COMMITTED, READ_UNCOMMITTED, REPEATABLE_READ, or SERIALIZABLE
///
/// @Example
/// LOGIN "localhost" "user" "pass123" "SQL_DRV"
/// SET_ISOLATION_LEVEL of "localhost" to READ_COMMITTED
#COMMAND SET_ISOLATION_LEVEL "OF" R "TO" "DEFAULT""READ_COMMITTED""READ_UNCOMMITTED""REPEATABLE_READ""SERIALIZABLE""SNAPSHOT_LEVEL"
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_DriverName EQ SQLFLEX or MertechInc_DriverName EQ MYSQLFLEX) Begin
        Move !2 to MertechInc_sArg1

        #IFSAME !4 READ_COMMITTED
            Move 0 to MertechInc_iArg
        #ELSE
            #IFSAME !4 READ_UNCOMMITTED
                Move 1 to MertechInc_iArg
            #ELSE
                #IFSAME !4 REPEATABLE_READ
                    Move 2 to MertechInc_iArg
                #ELSE
                    #IFSAME !4 SERIALIZABLE
                        Move 3 to MertechInc_iArg
                    #ELSE
                        #IFSAME !4 SNAPSHOT_LEVEL
                            Move 4 to MertechInc_iArg
                        #ELSE
                            Move 5 to MertechInc_iArg
                        #ENDIF
                    #ENDIF
                #ENDIF
            #ENDIF
        #ENDIF

        Call_Driver 0 MertechInc_DriverName Function CALLDRV_SET_ISOLATION_LEVEL CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SET_SESSION_PARAMETER
/// @Description There are two sets of code pages used in windows, ANSI and
/// OEM. ANSI is what is commonly used now, but some data still uses the OEM
/// code pages. When migrating data, this command is used to determine whether
/// the OEM data will be translated to ANSI during the migration. For example,
/// migrating passwords with special characters may call for different code
/// pages. Sending true will convert the OEM data to ANSI, sending false will
/// not. Both OEM_TO_ANSI and OEM_TRANSLATION_STATE do essentially the same
/// thing, however since MSSQL has the functionality built in, OEM_TO_ANSI
/// will use MSSQL's built in translation and thus only works with SQLFlex.
/// OEM_TRANSLATION_STATE is internal and built into the driver so it works
/// for all drivers. Note that if using custom entries with
/// SET_CUSTOM_OEM_TO_ANSI then OEM_TRANSLATION_STATE must be used. Also, if
/// there are already custom entries set then turning OEM_TRANSLATION_STATE
/// on will automatically enable those custom translations.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-08 by Aaron Gulack
/// @See 		 SET_CUSTOM_OEM_TO_ANSI GET_CUSTOM_OEM_TO_ANSI
///
/// @Syntax SET_SESSION_PARAMETER {OEM_TO_ANSI/OEM_TRANSLATION_STATE} to {variable}
/// @Param variable			Boolean variable enabling or disabling translation
///
/// @Example
/// SET_SESSION_PARAMETER OEM_TO_ANSI to True
#COMMAND SET_SESSION_PARAMETER "OEM_TRANSLATION_STATE""OEM_TO_ANSI" "TO" R
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Move !3 to MertechInc_sArg1

        #IFSAME !1 OEM_TO_ANSI
            Move CALLDRV_OLEDB_OEM_TRANSLATION to MertechInc_iArg
        #ELSE
            Move CALLDRV_OEM_TRANSLATION_STATE to MertechInc_iArg
        #ENDIF

        Call_Driver 0 MertechInc_DriverName Function 0 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
    End
#ENDCOMMAND

Procedure MertechInc_SET_CUSTOM_OEM_TO_ANSI Global Integer iChar Integer iOem Integer iAnsi
    Move iChar to MertechInc_sArg1
    move (String(iOem) + "," + String(iAnsi)) to MertechInc_sArg2
    Call_Driver 0 MertechInc_DriverName Function CALLDRV_LICENSE_ENVIRONMENT_SET CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 CALLDRV_SET_CUSTOM_OEM_TO_ANSI RESULT MertechInc_iRet
    IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
End_Procedure

//=============================================================================
/// @Name        SET_CUSTOM_OEM_TO_ANSI
/// @Description In very rare situations, a custom OEM to ANSI translation
/// is needed. When that is the case, this command can be used to create
/// those custom entries. This is done by passing the character numbered
/// position, the OEM value and the ANSI value. Note that
/// OEM_TRANSLATION_STATE must be set to true for these custom entries to
/// work.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-08 by Aaron Gulack
/// @See		 GET_CUSTOM_OEM_TO_ANSI SET_SESSION_PARAMETER
///
/// @Syntax SET_CUSTOM_OEM_TO_ANSI {character} to OEM {value1} ANSI {value2}
/// @Param character		Numbered position (0-255) of the character
/// @Param value1			Character number for the OEM value
/// @Param value2			Character number for the ANSI value
#COMMAND SET_CUSTOM_OEM_TO_ANSI R "TO" "OEM" R "ANSI" R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Send MertechInc_SET_CUSTOM_OEM_TO_ANSI !1 !4 !6
    End
#ENDCOMMAND

Procedure MertechInc_GET_CUSTOM_OEM_TO_ANSI Global Integer iChar Integer iOem Integer iAnsi
    Move iChar to MertechInc_sArg1
    Move (Repeat(" ", 255)) to MertechInc_sArg2
    Call_Driver 0 MertechInc_DriverName Function CALLDRV_LICENSE_ENVIRONMENT_SET CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 CALLDRV_GET_CUSTOM_OEM_TO_ANSI RESULT MertechInc_iRet
    IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
End_Function

//=============================================================================
/// @Name        GET_CUSTOM_OEM_TO_ANSI
/// @Description This command returns the custom OEM and ANSI values
/// respectively for a given character. If there is no custom translation
/// for the specified character then no error will be raised, but nothing
/// will be returned.
///
/// @Assumptions There exists a custom translation for the specified character
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-08 by Aaron Gulack
/// @See
///
/// @Syntax SET_CUSTOM_OEM_TO_ANSI {character} to OEM {value1} ANSI {value2}
/// @Param character		Numbered position (0-255) of the character
/// @Param value1			Variable to hold the OEM value
/// @Param value2			Variable to hold the ANSI value
#COMMAND GET_CUSTOM_OEM_TO_ANSI R "TO" "OEM" R "ANSI" R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Send MertechInc_GET_CUSTOM_OEM_TO_ANSI !1 !4 !6
        [Not Err] Begin
            Move MertechInc_sArg1 to !4
            Move MertechInc_sArg2 to !6
        End
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SET_AUTOMATIC_NUMERIC_DATATYPE_REMAPPING
/// @Description This command toggles off and on the automatic numeric
/// data type remapping built into SQLFlex. When adding or creating
/// smaller numeric columns during a restructure, SQLFlex will change
/// the type to a more specific data type i.e. smallint or tinyint since
/// they are handled more efficiently by the server. Sending false to this
/// command will force SQl to keep the column as a numeric field, preserving
/// the length and precision. Passing true will leave the remapping up to the
/// driver.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-04 by Aaron Gulack
/// @See
///
/// @Syntax SET_AUTOMATIC_NUMERIC_DATATYPE_REMAPPING to {variable}
/// @Param variable			Boolean variable enabling or disabling remapping
///
/// @Example
/// Structure_Start hFile
///
///     Create_Field hFile
///
///     SET_AUTOMATIC_NUMERIC_DATATYPE_REMAPPING to False
///
///     Set_Attribute DF_FIELD_NAME   of hFile iColumn to "Transaction_Count"
///     Set_Attribute DF_FIELD_TYPE   of hFile iColumn to DF_BCD
///     Set_Attribute DF_FIELD_LENGTH of hFile iColumn to 1
///
/// Structure_End hFile
#COMMAND SET_AUTOMATIC_NUMERIC_DATATYPE_REMAPPING "TO" R
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Move !2 to MertechInc_sArg1
        Call_Driver 0 MertechInc_DriverName Function 0 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank CALLDRV_AUTO_NUMERIC_REMAPPING RESULT MertechInc_iRet
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SET_FORCE_DATE_FORMAT_INIT
/// @Description At times, a stored procedure, function or trigger may
/// alter the default format for dates. This could cause problems because,
/// for example, if a trigger on a table does this, then every time a save
/// takes place on that table, the format for dates will be changed. By
/// sending true to this command, the date formats will reset to their
/// default format. Note that this is essentially the same thing as running
/// the SQL statement: "ALTER SESSION SET NLS_DATE_FORMAT='MM/DD/YYYY'", so
/// in most situations, that should be used instead of this command.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     ORAFlex
/// @VersionNote Last Revised: 2013-10-08 by Aaron Gulack
/// @See
///
/// @Syntax SET_FORCE_DATE_FORMAT_INIT to {variable}
/// @Param variable		Boolean variable enabling or disabling format reset
#COMMAND SET_FORCE_DATE_FORMAT_INIT "TO" R
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Move !2 to MertechInc_sArg1
        Call_Driver 0 MertechInc_DriverName Function 0 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank CALLDRV_FORCE_DATE_FORMAT_INIT RESULT MertechInc_iRet
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SET_STATIC_TABLE_OPTIMIZATION
/// @Description At this time, this command no longer serves any function.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-08 by Aaron Gulack
/// @See
///
/// @Syntax SET_STATIC_TABLE_OPTIMIZATION to {ENABLED/DISABLED}
#COMMAND SET_STATIC_TABLE_OPTIMIZATION "TO" "ENABLED""DISABLED" .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        #IFSAME !1 DISABLED
            Move 0 to MertechInc_sArg1
        #ELSE
            Move 1 to MertechInc_sArg1
        #ENDIF
        Call_Driver 0 MertechInc_DriverName Function 0 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank CALLDRV_STATIC_TABLE_OPT RESULT MertechInc_iRet
    End
#ENDCOMMAND

//=============================================================================
/// @Name        GET_MAX_OBJECT_NAME_LENGTH
/// @Description This command returns the maximum length allowed for object
/// names in the SQl backend. This includes table names, column names,
/// database names etc. The maximum length in put into the specified variable.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-04 by Aaron Gulack
/// @See
///
/// @Syntax GET_MAX_OBJECT_NAME_LENGTH to {variable}
/// @Param variable			Variable to hold the maximum length
///
/// @Example
/// GET_MAX_OBJECT_NAME_LENGTH to iMaxLength
#COMMAND GET_MAX_OBJECT_NAME_LENGTH "TO" R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Move (Repeat(" ", 10)) to MertechInc_sArg1
        Call_Driver 0 MertechInc_DriverName Function 0 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank CALLDRV_MAX_OBJECT_NAME_LENGTH RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
        Move MertechInc_sArg1 to !2
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SET_SQL_LOCK_TIMEOUT
/// @Description This command is used to set the number of milliseconds
/// an SQL statement waits for a database lock to be released before timing
/// out. Locks are used with transactions to maintain atomicity. If a lock is
/// not released before the timeout, then the statement will fail and an error
/// will be raised. By default, the timeout is set to -1, indicating that
/// statements will wait indefinitely before timing out.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-07 by Aaron Gulack
/// @See 		 GET_SQL_LOCK_TIMEOUT
///
/// @Syntax SET_SQL_LOCAL_TIMEOUT of {server} to {variable}
/// @Param server			Name of the server
/// @Param variable			Number of milliseconds to wait until timeout
///
/// @Example
/// SET_SQL_LOCK_TIMEOUT of "localhost" to 6000
#COMMAND SET_SQL_LOCK_TIMEOUT "OF" R "TO" R
    DO_GETFILENUMBER_DRIVERNAME 0
    IF MertechInc_DriverName EQ SQLFLEX Begin
        MOVE !2 TO MertechInc_sArg1
        MOVE !4 TO MertechInc_iArg

        Call_Driver 0 MertechInc_DriverName FUNCTION CALLDRV_SET_SQL_LOCK_TIMEOUT CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    End
#ENDCOMMAND

//=============================================================================
/// @Name        GET_SQL_LOCK_TIMEOUT
/// @Description This command returns the number of milliseconds an SQL
/// statement will wait for a database lock to be released. If the lock
/// is not released before the timeout, then the statement will fail and
/// an error will be raised. Note that the default value is -1, indicating
/// that the statement will wait indefinitely.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-07 by Aaron Gulack
/// @See 	 	 SET_SQL_LOCK_TIMEOUT
///
/// @Syntax GET_SQL_LOCAL_TIMEOUT of {server} to {variable}
/// @Param server			Name of the server
/// @Param variable			Variable to hold the number of milliseconds
///
/// @Example
/// GET_SQL_LOCK_TIMEOUT of "localhost" to iTimeout
#COMMAND GET_SQL_LOCK_TIMEOUT "OF" R "TO" R
    DO_GETFILENUMBER_DRIVERNAME 0
    If MertechInc_DriverName EQ SQLFLEX Begin
        Move !2 to MertechInc_sArg1
        Move (Repeat(" ", 10)) to MertechInc_sArg2

        Call_Driver 0 MertechInc_DriverName Function CALLDRV_GET_SQL_LOCK_TIMEOUT CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 0 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
        Move MertechInc_sArg2 to !4
    End
#ENDCOMMAND

//=============================================================================
/// @Name        DO_GET_SQLSERVER_PARAMETERS
/// @Description Retrieves stored procedure parameter values.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     All
/// @VersionNote Last Revised: 2009-08-18 By Ian Smith
/// @See
#COMMAND DO_GET_SQLSERVER_PARAMETERS
    #IF (!0>1)
        INCREMENT MertechInc_iParamCount
        #IFSAME !2 SQLOUT
            IF (POS("|V",|CS'!1') NE 0 OR POS("|S",|CS'!1') NE 0 OR POS("|F",|CS'!1') NE 0) BEGIN
                Send MertechInc_Set_DecSep     //Check Decimal Seperator and change to '.' if required
                Get MertechInc_DO_GET_SQLSERVER_PARAMETERS MertechInc_iParamCount to !1
                Send MertechInc_Reset_DecSep   //Reset Decimal Seperator if required
            END
            #IF (!0>2)
                DO_GET_SQLSERVER_PARAMETERS !3 !4 !5 !6 !7 !8 !9
            #ENDIF
        #ELSE
            DO_GET_SQLSERVER_PARAMETERS !2 !3 !4 !5 !6 !7 !8 !9
        #ENDIF
    #ENDIF
#ENDCOMMAND // DO_GET_SQLSERVER_PARAMETERS

Function MertechInc_DO_GET_SQLSERVER_PARAMETERS Global Integer iParameter Returns String
    String sValue

    Get MertechInc_Pre_Size_String 0 to sValue //Need to check if Call_Driver needs pre sized strings. Until then assume it does
    Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 24 CALLBACK 0 PASSING sValue MertechInc_Blank iParameter RESULT MertechInc_iRet

    Function_Return sValue
End_Function

//=============================================================================
/// @Name        DO_BIND_SQLSERVER_PARAMETERS
/// @Description Binds parameters for stored procedure call.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     All
/// @VersionNote Last Revised: 2009-08-18 By Ian Smith
/// @See
#COMMAND DO_BIND_SQLSERVER_PARAMETERS
    #IFSAME !1 BINDING
    #ELSE
        #IFSAME !2 SQLOUT
            Move "OUTPUT" to MertechInc_sWork
        #ELSE
            Move "INPUT" to MertechInc_sWork
        #ENDIF

        If (POS("|V",|CS'!1') NE 0 or POS("|S",|CS'!1') NE 0 or POS("|F",|CS'!1') NE 0) Begin
            If (POS("|VI",|CS'!1') NE 0 or POS("|SI",|CS'!1') NE 0) Move 6 to MertechInc_iWork
            Else If (POS("|VN",|CS'!1') NE 0 or POS("|SN",|CS'!1') NE 0 or POS("|FN",|CS'!1') NE 0) Move 25 to MertechInc_iWork
                Else If (POS("|VD",|CS'!1') NE 0 or POS("|SD",|CS'!1') NE 0 or POS("|FD",|CS'!1') NE 0) Move 10 to MertechInc_iWork
                    Else If (POS("|VS",|CS'!1') NE 0) Move 255 to MertechInc_iWork
                        Else If (POS("|SS",|CS'!1') NE 0 or POS("|FS",|CS'!1') NE 0) Move 16384 to MertechInc_iWork
            Increment MertechInc_iParamCount
        End
        Else Begin
            Move (LENGTH(!1)) to MertechInc_iWork
        End

        Send MertechInc_DO_BIND_SQLSERVER_PARAMETERS MertechInc_sWork !1 MertechInc_iWork
        #IF (!0>1)
            #IFSAME !2 SQLOUT
                #IF (!0>2)
                    DO_BIND_SQLSERVER_PARAMETERS !3 !4 !5 !6 !7 !8 !9
                #ENDIF
            #ELSE
                DO_BIND_SQLSERVER_PARAMETERS !2 !3 !4 !5 !6 !7 !8 !9
            #ENDIF
        #ENDIF
    #ENDIF
#ENDCOMMAND // DO_BIND_SQLSERVER_PARAMETERS

Procedure MertechInc_DO_BIND_SQLSERVER_PARAMETERS Global String sDirection String sParameter Integer iSize
    Call_Driver 0 SQLFLEX Function CALLDRV_BIND_PARAMETER CALLBACK 0 PASSING sDirection sParameter iSize RESULT MertechInc_iRet
End_Procedure

//=============================================================================
/// @Name        DO_CHECK_BINDING
/// @Description Sets MertechInc_bThereIsBinding True if any of the
/// parameters is the keyword BINDING.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     All
/// @VersionNote Last Revised: 2009-08-18 By Ian Smith
/// @See
#COMMAND DO_CHECK_BINDING
    #IFSAME !1 BINDING
        INDICATE MertechInc_bThereIsBinding True
    #ELSE
        #IF (!0>1)
            DO_CHECK_BINDING !2 !3 !4 !5 !6 !7 !8 !9
        #ENDIF
    #ENDIF
#ENDCOMMAND

//=============================================================================
/// @Name        DO_FETCH_FIRST_ROW
/// @Description Recursive - drops first parameter until the first parameter
/// is BINDING and then calls SQL_FETCH_NEXT_ROW passing remaining parameters.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2009-08-18 By Ian Smith
/// @See
#COMMAND DO_FETCH_FIRST_ROW
    #IFSAME !1 BINDING
        SQL_FETCH_NEXT_ROW INTO !2 !3 !4 !5 !6 !7 !8 !9
    #ELSE
        #IF (!0>1)
            DO_FETCH_FIRST_ROW !2 !3 !4 !5 !6 !7 !8 !9
        #ENDIF
    #ENDIF
#ENDCOMMAND

#COMMAND RECURSE_SET_SQL_PROCEDURE_PARAMS
	#IF (!0>1)
		#IF (!0>2)
			#IFSAME !2 SQLOUT
			  SQL_SET_PROCEDURE_PARAMETER MertechInc_iWork2 to !1 IN_OUT
			  move (MertechInc_iWork2+1) to MertechInc_iWork2
				RECURSE_SET_SQL_PROCEDURE_PARAMS !3 !4 !5 !6 !7 !8 !9
			#ELSE
			  SQL_SET_PROCEDURE_PARAMETER MertechInc_iWork2 to !1
			  move (MertechInc_iWork2+1) to MertechInc_iWork2
				RECURSE_SET_SQL_PROCEDURE_PARAMS !2 !3 !4 !5 !6 !7 !8 !9
			#ENDIF
	    #ENDIF
	    #IF (!0=2)
			#IFSAME !2 SQLOUT
			  SQL_SET_PROCEDURE_PARAMETER MertechInc_iWork2 to !1 IN_OUT
			  move (MertechInc_iWork2+1) to MertechInc_iWork2
				RECURSE_SET_SQL_PROCEDURE_PARAMS !3 !4 !5 !6 !7 !8 !9
			#ELSE
			  SQL_SET_PROCEDURE_PARAMETER MertechInc_iWork2 to !1
			  move (MertechInc_iWork2+1) to MertechInc_iWork2
				RECURSE_SET_SQL_PROCEDURE_PARAMS !2 !3 !4 !5 !6 !7 !8 !9
			#ENDIF
        #ENDIF
	#ENDIF
    #IF (!0=1)
		SQL_SET_PROCEDURE_PARAMETER MertechInc_iWork2 to !1
    #ENDIF
#ENDCOMMAND

#COMMAND GET_ACTUAL_PARAM_COUNT
  #IF !0>=1
    #IFSAME !1 SQLOUT
      decrement MertechInc_iWork2
    #ENDIF
    GET_ACTUAL_PARAM_COUNT !2 !3 !4 !5 !6 !7 !8 !9
  #ENDIF
#ENDCOMMAND

#COMMAND RECURSE_GET_SQL_PROCEDURE_PARAMS
	#IF (!0>1)
		#IFSAME !2 SQLOUT
		  SQL_GET_PROCEDURE_PARAMETER MertechInc_iWork2 to !1
		  move (MertechInc_iWork2+1) to MertechInc_iWork2
			RECURSE_GET_SQL_PROCEDURE_PARAMS !3 !4 !5 !6 !7 !8 !9
		#ELSE
            move (MertechInc_iWork2+1) to MertechInc_iWork2
			RECURSE_GET_SQL_PROCEDURE_PARAMS !2 !3 !4 !5 !6 !7 !8 !9
		#ENDIF
	#ENDIF
#ENDCOMMAND

//=============================================================================
/// @Name        CALL_STORED_PROCEDURE
/// @Description This command is used to call a stored procedure on the SQL
/// backend. To successfully call a procedure with this command, a string
/// must be passed containing a valid procedure name. In addition, if the
/// procedure takes any arguments, they must also be passed using the constant
/// "passing" along with all of the needed arguments. If the procedure has a
/// return value, then SQL_GET_FUNCTION_RETURN or SQL_FETCH_NEXT_ROW can be
/// used to get the value(s). If an error is found then the indicator "Err"
/// is set to true.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-09-25 by Aaron Gulack
/// @See
///
/// @Syntax CALL_STORED_PROCEDURE {procedure} Passing {variable}
/// @Param procedure		Full name of the procedure
/// @Param variable			Argument being passed (can be multiple)
///
/// @Example
/// CALL_STORED_PROCEDURE "sys.sp_addmessage" passing 50003 15 "Please enter a valid date"
#COMMAND CALL_STORED_PROCEDURE R "PASSING""BINDING"""
    #IF (!0 = 1)
      SQL_SET_PROCEDURE_NAME !1 NUMPAR 0
    #ELSE
      move (!0 - 2) to MertechInc_iWork2
      GET_ACTUAL_PARAM_COUNT !3 !4 !5 !6 !7 !8 !9

      SQL_SET_PROCEDURE_NAME !1 NUMPAR MertechInc_iWork2

      move 1 to MertechInc_iWork2
      RECURSE_SET_SQL_PROCEDURE_PARAMS !3 !4 !5 !6 !7 !8 !9
    #ENDIF

    SQL_PROCEDURE_EXECUTE
    #IF (!0 > 1)
      move 1 to MertechInc_iWork2
      RECURSE_GET_SQL_PROCEDURE_PARAMS !3 !4 !5 !6 !7 !8 !9
    #ENDIF
#ENDCOMMAND

//=============================================================================
/// @Name        CALL_SQLSERVER_PROCEDURE
/// @Description This command is used to call a stored procedure on the SQL
/// backend. To successfully call a procedure with this command, a string
/// must be passed containing a valid procedure name. In addition, if the
/// procedure takes any arguments, they must also be passed using the constant
/// "passing" along with all of the needed arguments. If the procedure has a
/// return value, then SQL_GET_FUNCTION_RETURN, SQL_FETCH_NEXT_ROW or
/// GET_PROCEDURE_RETURN can be used to get the value(s). If an error is found
/// then the indicator "Err" is set to true.
///
/// @Status      Deprecated
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See 		 CALL_STORED_PROCEDURE
///
/// @Syntax CALL_SQLSERVER_PROCEDURE {procedure} Passing {variable}
/// @Param procedure		Full name of the procedure
/// @Param variable			Argument to be passed (can be multiple)
///
/// @Example
/// CALL_SQLSERVER_PROCEDURE "sys.sp_addmessage" passing 50003 15 "Please enter a valid date"
#Replace CALL_SQLSERVER_STORED_PROCEDURE CALL_STORED_PROCEDURE
#Replace CALL_SQLSERVER_PROCEDURE CALL_STORED_PROCEDURE

//=============================================================================
/// @Name        END_CALL_PROCEDURE
/// @Description This command is used to close any open cursors created
/// by the respective stored procedure. Cursors are used in MSSQL to make
/// the results from one procedure temporarily available to other procedures
/// or triggers. To avoid causing unwanted results, it is good practice to
/// use this command once a procedure call is completed.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See 		 CALL_STORED_PROCEDURE
///
/// @Syntax END_CALL_PROCEDURE
///
/// @Example
/// CALL_STORED_PROCEDURE "sys.sp_spaceused" Passing "Customer"
/// GET_PROCEDURE_RETURN to sValue
/// END_CALL_PROCEDURE
/// Showln sValue
#COMMAND END_CALL_PROCEDURE .
    CALL_DRIVER 0 SQLFLEX FUNCTION 26 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
#ENDCOMMAND

//=============================================================================
/// @Name        GET_PROCEDURE_RETURN
/// @Description This command is used to get a returned value from a stored
/// procedure using MSSQL. Note that this command can only handle one
/// returned value and must be used after the procedure has already been
/// built and executed.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See
///
/// @Syntax GET_PROCEDURE_RETURN to {variable}
/// @Param variable 		Variable to hold the returned value
///
/// @Example
/// SQL_SET_PROCEDURE_NAME "sys.sp_spaceused" NUMPAR 1
/// SQL_SET_PROCEDURE_PARAMETER 1 to "Customer" IN
/// SQL_PROCEDURE_EXECUTE
/// GET_PROCEDURE_RETURN to sSpaceUsed
/// Showln sSpaceUsed
#COMMAND GET_PROCEDURE_RETURN "TO" R .
	SQL_GET_PROCEDURE_PARAMETER 0 to !2
#ENDCOMMAND

//=============================================================================
/// @Name        SET_MIRROR_SERVER
/// @Description This command is used to programmatically set the mirror
/// server for the database. This is to be used along with SQl server
/// failover mirroring. Note that this simply sets the server and database
/// to be used for mirroring. All set up for the servers must already be
/// working properly through SQL Server.
///
/// @Assumptions A compatible version of SQL Server is being used
/// @Status      Public
/// @Drivers     SQLFlex v9.2 and above
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See		 GET_MIRROR_SERVER
///
/// @Syntax SET_MIRROR_SERVER to {server} {database}
/// @Param server			The name of the mirror server
/// @Param database			The database acting as a mirror
///
/// @Example
/// SET_MIRROR_SERVER to "(localdb)\v11.0" "MirrorDB"
#COMMAND SET_MIRROR_SERVER "TO" R R .
    DO_GETFILENUMBER_DRIVERNAME 0

    IF (MertechInc_DriverName EQ SQLFlex) Begin
        MOVE !2 TO MertechInc_sArg1
        Move !3 to MertechInc_sArg2
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_MIRROR_SERVER CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 0 RESULT MertechInc_iRet
    End
    IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
#ENDCOMMAND

//=============================================================================
/// @Name        GET_MIRROR_SERVER
/// @Description This command is used to get the name of the server
/// and database being used for failover mirroring. Mirroring must
/// be properly set up in SQL Server for this command to return the
/// correct values.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex v9.2 and above
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See 		 SET_MIRROR_SERVER
///
/// @Syntax GET_MIRROR_SERVER to {server} {database}
/// @Param server			Variable to hold the name of the mirrored server
/// @Param database			Variable to hold the name of the mirrored database
///
/// @Example
/// GET_MIRROR_SERVER to sServer sDatabase
#COMMAND GET_MIRROR_SERVER "TO" R R .
    DO_GETFILENUMBER_DRIVERNAME 0

    IF (MertechInc_DriverName EQ SQLFlex) Begin
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_MIRROR_SERVER CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 1 RESULT MertechInc_iRet
        MOVE MertechInc_sArg1 TO !2
        Move MertechInc_sArg2 to !3
    End
    IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
#ENDCOMMAND

//=============================================================================
/// @Name        COPY_DATA
/// @Description This command is used to copy data from a DAT file to an
/// SQL table. Both the source and the destination files are opened, the
/// data is copied and then the files are closed. This is usually used
/// along with CREATE_TABLE_FROM_DAT_FILE, which creates the structure
/// and then this command will insert the data. If needed, this command
/// can also work backwards, copying data from an SQL table to a DAT file.
/// This is an alternative to using the Flex2SQL Migration Tool and can
/// improve performance when used in the right situations. Note that in
/// order for this process to work properly the table being copied can not
/// be opened. Because of this, a manual login must take place, using
/// something like LOGIN_SQLFLEX or LOGIN. Since this only copies the data,
/// CREATE_TABLE_FROM_DAT_FILE can be used to create the table structure.
///
/// Because COPY_DATA requires no user interaction, an optional callback
/// function can be passed for tracing purposes. By passing the constant
/// "CALLBACK" followed by the object name, a function can be used to set
/// up messages for tracking and error handling. Below is more information
/// regarding this callback object.
///
/// This function should follow this pattern:
///
/// Function Callback String sText Integer iStatusID Returns Integer
///
/// sText - Message corresponding to the current status ID
///
/// iStatusID - Integer value mapping to the current status constant:
///			DF_MESSAGE_PROGRESS_TITLE    Sent when SQLFlex starts the
///										 process
///
///  		DF_MESSAGE_HEADING_1         Sent when SQLFlex is about to
///										 copy the source data
///
/// 		DF_MESSAGE_ERROR             Sent when an error occurs
///
/// 		DF_MESSAGE_PROGRESS_STATUS   Sent each time an additional
///										 10% of the data is copied
///
/// NOTE: Returning false each time the function is called will continue
/// copying process. Returning true will end it.
///
/// Another optional parameter that can be used is a constrain on the data
/// being copied. This is done by passing the constant "CONSTRAIN" followed
/// by an SQL constrain statement. When passing a constrain but not a callback
/// object, pass 0 for the callback before passsing the constrain.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-08 by Aaron Gulack
/// @See 		 CREATE_TABLE_FROM_DAT_FILE CONVERT_DAT_FILE
///
/// @Syntax COPY_DATA {from} to {destination} [CALLBACK {function}] [CONSTRAIN {variable}]
/// @Param from				Table to copy from.
/// @Param destination		Table to copy to.
/// @Param function     	Object with callback function (optional)
/// @Param variable			SQL contraint to use when copying (optional)
///
/// @Example
/// Object CallBackObj is a Array
/// 	Function Callback String sText Integer iLogicalID Returns Integer
/// 	    If (iLogicalID = DF_MESSAGE_ERROR) Begin
/// 	        Showln "Error"
///				Showln sText
///				Function_Return True
/// 	    End
///
/// 	    Else Showln sText
///
///			Function_Return False
///
/// 	End_Function
/// End_Object
///
/// Login "localhost" "user" "pass123" "sql_drv"
/// CREATE_TABLE_FROM_DAT_FILE Customer.File_Number "Customer"
/// COPY_DATA "Customer" to "sql_drv:Customer" CALLBACK (Callback(Self)) CONSTRAIN "STATUS = 'Active'"
#COMMAND COPY_DATA R "TO" R
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Move (!1 + "||" + !3) to MertechInc_sArg1
        #IF !0>3
            #CHECK !4 "CALLBACK"
            Move !5 to MertechInc_iCallBack
            #IF !0>5
                #CHECK !6 "CONSTRAIN"
                Move !7 to MertechInc_sArg2
            #ELSE
                Move "" to MertechInc_sArg2
            #ENDIF
        #ELSE
            Move 0 to MertechInc_iCallBack
        #ENDIF
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_COPY_DATA CALLBACK MertechInc_iCallBack PASSING MertechInc_sArg1 MertechInc_sArg2 0 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        ORAFlex_REVISION
/// @Description This command will put the current version (decimals included)
/// of the Oracle driver associated with the current workspace into the specified
/// variable.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     ORAFlex
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See 		 GET_DRIVER_REVISION
///
/// @Syntax ORAFlex_REVISION {variable}
/// @Param variable			String variable to hold the returned version
///
/// @Example
/// ORAFlex_REVISION sVersion
#COMMAND ORAFlex_REVISION #CRUG .
    Move (Repeat(" ",255)) to !1
    Call_Driver 0 ORAFlex Function 0 CALLBACK 0 PASSING MertechInc_Blank !1 0 RESULT MertechInc_iRet
    If MertechInc_iRet EQ -1 INDICATE ERR True
#ENDCOMMAND

//=============================================================================
/// @Name        KEEP_FILES_OPEN
/// @Description Keep the files, currently in use, open after the server is
/// logged out. Sometimes an application needs to login to the same server
/// with a different user id. When logging out, however, the drivers
/// automatically close all opened files. The overhead of opening these files
/// should be avoided if the user will work with the same files that were
/// closed. KEEP_FILES_OPEN keeps all files opened after a user logs out
/// from the server.
///
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
///
/// @Syntax KEEP_FILES_OPEN of {server}
/// @Param server		Name of the server
#COMMAND KEEP_FILES_OPEN "OF" R .
    #IFDEF MertechInc_Obsolete_Code
        DO_GETFILENUMBER_DRIVERNAME 0
        If (MertechInc_FileNumber <> -1) Begin
            Move !2 to MertechInc_sArg1
            If (MertechInc_DriverName EQ ORAFlex);
                Call_Driver 0 MertechInc_DriverName Function 25 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
            Else ;
                Call_Driver 0 MertechInc_DriverName Function 28 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
            If MertechInc_iRet EQ -1 INDICATE ERR True
        End
    #ELSE
        MertechInc_Error_Obsolete_Code
    #ENDIF
#ENDCOMMAND

#REPLACE DONT_CLOSE_FILES KEEP_FILES_OPEN

//=============================================================================
/// @Name        SET_MAX_OPEN_CURSORS
/// @Description Set the maximum number of cursors you want the driver to use.
///
/// The driver will recycle the least used cursors if this limit is hit.
/// The trade off is between increased resources on the server and
/// re-preparing of cursors.
///
/// For a program that keeps 40+ files opened at the same time, 255 is a good
/// number for the open cursors parameter. For programs that open less than
/// 40 files, any number between 100-255 is sufficient. These numbers can be
/// changed based on available server resources.
///
/// On Oracle this value should not exceed the value of open_cursors in
/// init.ora
///
/// Note: Only change this setting if you are having performance issues
/// and the server is indicating you are using up too many cursors or too
/// much memory. GET_OPENED_CURSORS can be used to check the number of
/// cursors the server has opened. If this number is hitting the limit,
/// it is worth increasing the number, as long as the server has enough
/// resources.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-04 by Aaron Gulack
/// @See         GET_MAX_OPEN_CURSORS GET_OPENED_CURSORS
///
/// @Syntax SET_MAX_OPEN_CURSORS of {server} to {variable}
/// @Param server			The name of the server
/// @Param variable			Maximum number of cursors
#COMMAND SET_MAX_OPEN_CURSORS "OF" R "TO" R .
    DO_GETFILENUMBER_DRIVERNAME 0

    MOVE !2 TO MertechInc_sArg1
    Move "0"  to MertechInc_sArg2
    If (MertechInc_DriverName EQ ORAFlex or MertechInc_DriverName EQ MySQLFlex or MertechInc_DriverName EQ PgFlex)Begin
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_SQL_MAX_CURSORS CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 !4 RESULT MertechInc_iRet
    End
    Else If MertechInc_DriverName EQ SQLFlex Begin
        Call_Driver 0 SQLFlex Function CALLDRV_SQLFLEX_MAX_CURSORS CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 !4 RESULT MertechInc_iRet
    End
    IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
#ENDCOMMAND

//=============================================================================
/// @Name        GET_MAX_OPEN_CURSORS
/// @Description This command will return the maximum number of open
/// cursors allowed by the server.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-04 by Aaron Gulack
/// @See         SET_MAX_OPEN_CURSORS GET_OPENED_CURSORS
///
/// @Syntax GET_MAX_OPEN_CURSORS of {server} to {variable}
/// @Param server			Name of the server
/// @Param variable			Variable to hold the maximum number of open cursors
#COMMAND GET_MAX_OPEN_CURSORS "OF" R "TO" RC .
    DO_GETFILENUMBER_DRIVERNAME 0

    MOVE !2 TO MertechInc_sArg1
    Move "1" to MertechInc_sArg2
    If (MertechInc_DriverName EQ ORAFlex or MertechInc_DriverName EQ MySQLFlex or MertechInc_DriverName EQ PgFlex) Begin
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_SQL_MAX_CURSORS CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 0 RESULT MertechInc_iRet
    End
    Else If MertechInc_DriverName EQ SQLFlex Begin
        Call_Driver 0 SQLFlex Function CALLDRV_SQLFLEX_MAX_CURSORS CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 0 RESULT MertechInc_iRet
    End
    If MertechInc_iRet EQ -1 INDICATE ERR True
    ELSE MOVE MertechInc_iRet TO !4
#ENDCOMMAND

//=============================================================================
/// @Name        GET_OPENED_CURSORS
/// @Description This command returns the number of cursors currently
/// open on the server.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-04 by Aaron Gulack
/// @See         SET_MAX_OPEN_CURSORS GET_MAX_OPEN_CURSORS
///
/// @Syntax GET_MAX_OPEN_CURSORS of {server} to {variable}
/// @Param server			Name of the server
/// @Param variable			Variable to hold the number of cursors currently open
///
#COMMAND GET_OPENED_CURSORS "OF" R "TO" RC .
    DO_GETFILENUMBER_DRIVERNAME 0

    MOVE !2 TO MertechInc_sArg1
    Move "2" to MertechInc_sArg2
    If (MertechInc_DriverName EQ ORAFlex or MertechInc_DriverName EQ MySQLFlex or MertechInc_DriverName EQ PgFlex) Begin
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_SQL_MAX_CURSORS CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 0 RESULT MertechInc_iRet
    End
    Else If MertechInc_DriverName EQ SQLFlex Begin
        Call_Driver 0 SQLFlex Function CALLDRV_SQLFLEX_MAX_CURSORS CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 0 RESULT MertechInc_iRet
    End
    If MertechInc_iRet EQ -1 INDICATE ERR True
    ELSE MOVE MertechInc_iRet TO !4
#ENDCOMMAND

//=============================================================================
/// @Name        ACTIVATE_TIME_STAMP
/// @Description This command will specify whether or not to show the time
/// portion of a date field. When set to ON, the time portion will be
/// included, OFF will just show the date. This is the same as changing
/// the date format with "ALTER SESSION SET nls_timestamp_format". Note that
/// this will only take effect if the date is put into a string variable.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     OraFlex
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See
///
/// @Syntax ACTIVATE_TIME_STAMP of {server} to {ON/OFF}
/// @Param server			Name of the server
///
/// @Example
/// ACTIVATE_TIME_STAMP of "localhost/orcl.localdomain" to OFF
///
/// SQL_SET_STMT to 'SELECT * from USER."Customer" '
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// SQL_FETCH_NEXT_ROW into sID sFirstName sLastName sDOB
/// If (Found) Begin
///     Showln sDOB
/// End
#COMMAND ACTIVATE_TIME_STAMP "OF" R "TO" "ON""OFF"  .
    DO_GETFILENUMBER_DRIVERNAME 0
    If MertechInc_DriverName EQ ORAFlex Begin
        #IFSAME !4 ON
            Move 1 to MertechInc_iArg
        #ELSE
            Move 0 to MertechInc_iArg
        #ENDIF
        Move !2 to MertechInc_sArg1
        Call_Driver 0 MertechInc_DriverName Function 27 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        CALL_ORACLE_STORED_FUNCTION
/// @Description This command is used to execute a function stored in Oracle.
/// This is an alternative to building a function with the SQL_SET_FUNCTION_NAME,
/// SQL_SET_FUNCTION_PARAMETER and SQL_FUNCTION_EXECUTE commands. This command
/// builds and executes the function by setting the full function name, the
/// parameter(s) to pass and the variable to hold the returned value. Note that
/// this command can only return a single value so SQL_SET_FUNCTION_PARAMETER
/// and SQL_SET_FUNCTION_NAME must be used when dealing with multiple return
/// values.
///
/// @Status      Deprecated
/// @Drivers     ORAFLex
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See		 CALL_STORED_FUNCTION
///
/// @Syntax CALL_ORACLE_STORED_FUNCTION {function} Returns {variable} Passing {argument}
/// @Param function			Full name of the function
/// @Param variable			Variable to hold the returned value
/// @Param argument			Argument to pass (can be multiple)
///
/// @Example
/// CALL_ORACLE_STORED_FUNCTION "user.getCustomerStatus" Returns sStatus passing sCustomerID
/// Showln sStatus
#COMMAND CALL_ORACLE_STORED_FUNCTION R "RETURNS" R "PASSING"""
    MOVE 0 TO MertechInc_iParamCount
    INDICATE ERR FALSE
    SQL_SET_STMT TO "BEGIN "
    SQL_APPEND_STMT TO ":PAR_RET := "
    SQL_APPEND_STMT TO !1
    SQL_APPEND_STMT TO "( "
    #IF (!0>4)
        DO_PASS_ARGUMENTS !5 !6 !7 !8 !9
    #ENDIF
    SQL_APPEND_STMT TO  " ); END;"
    SQL_PREPARE_STMT
    DO_BIND_PAR_RET !3
    #IF (!0>4)
        [ NOT ERR ] BEGIN
            IF MertechInc_iParamCount GT 0 BEGIN
                MOVE 0 TO MertechInc_iParamCount
                DO_BIND_PARAMETERS !5 !6 !7 !8 !9 // Bind the other arguments
            END
        END
    #ENDIF
    SQL_EXECUTE_STMT
    [ NOT ERR ] BEGIN
        MOVE 0 TO MertechInc_iParamCount // Getting returned value
        DO_GET_BIND_PARAMETERS !3
        #IF (!0>4)
            DO_GET_BIND_PARAMETERS !5 !6 !7 !8 !9 // Bind the other arguments
        #ENDIF
    END
#ENDCOMMAND

//=============================================================================
/// @Name        CALL_PGSQL_STORED_FUNCTION
/// @Description This command is used to execute a function stored in Oracle.
/// This is an alternative to building a function with the SQL_SET_FUNCTION_NAME,
/// SQL_SET_FUNCTION_PARAMETER and SQL_FUNCTION_EXECUTE commands. This command
/// builds and executes the function by setting the full function name, the
/// parameter(s) to pass and the variable to hold the returned value. Note that
/// this command can only return a single value so SQL_SET_FUNCTION_PARAMETER
/// and SQL_SET_FUNCTION_NAME must be used when dealing with multiple return
/// values.
///
/// @Status      Deprecated
/// @Drivers     PGFlex
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See		 CALL_STORED_FUNCTION
///
/// @Syntax CALL_PGSQL_STORED_FUNCTION {function} Returns {variable} Passing {argument}
/// @Param function			Full name of the function
/// @Param variable			Variable to hold the returned value
/// @Param argument			Argument to pass (can be multiple)
///
/// @Example
/// CALL_PGSQL_STORED_FUNCTION "user.getCustomerStatus" Returns sStatus passing sCustomerID
/// Showln sStatus
#COMMAND CALL_PGSQL_STORED_FUNCTION R "RETURNS" R "PASSING"""
    MOVE 0 TO MertechInc_iParamCount
    INDICATE ERR FALSE
    SQL_SET_STMT TO !1
    SQL_APPEND_STMT TO "("
    #IF (!0>4)
        DO_PASS_ARGUMENTS !5 !6 !7 !8 !9
    #ENDIF
    SQL_APPEND_STMT TO  ")"
    SQL_PREPARE_STMT

    // Indicate that a stored function will be executed - Query = 0, Procedure = 1, Function = 2
    Call_Driver 0 MertechInc_DriverName Function CALLDRV_EMBEDDED_SQL_TYPE CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 2 RESULT MertechInc_iRet
    #IF (!0>4)
        [ NOT ERR ] BEGIN
            IF MertechInc_iParamCount GT 0 BEGIN
                MOVE 0 TO MertechInc_iParamCount
                DO_BIND_PARAMETERS !5 !6 !7 !8 !9 // Bind the other arguments
            END
        END
    #ENDIF
    SQL_EXECUTE_STMT
    [ NOT ERR ] BEGIN
        MOVE 0 TO MertechInc_iParamCount // Getting returned value
        DO_GET_BIND_PARAMETERS !3
        #IF (!0>4)
            DO_GET_BIND_PARAMETERS !5 !6 !7 !8 !9 // Bind the other arguments
        #ENDIF
    END
#ENDCOMMAND

//=============================================================================
/// @Name        MERTECH_LANGUAGE_SUPPORT
/// @Description Sets the support language for the driver.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     ORAFLex
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See
///
/// @Syntax MERTECH_LANGUAGE_SUPPORT of {server} to {language}
/// @Param server		The name of the server being used
/// @Param language	  	The language to set support to
#COMMAND MERTECH_LANGUAGE_SUPPORT "OF" R "TO" R .
    MOVE !2 TO MertechInc_sArg1
    Move !4 to MertechInc_sArg2
    Call_Driver 0 ORAFlex Function 28 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 0 RESULT MertechInc_iRet
    IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_SAVE_BUFFER_BEGIN
/// @Description This command is used to initialize a SAVE_BUFFER
/// statement. Doing this will allow a specified set of records to be
/// stored in the buffer before a save takes place. Once the buffer is
/// filled, it will be saved automatically. This set of commands can be
/// used to efficiently save a large number of records. Once the buffer
/// is full, the save occurs automatically and the buffer will be emptied
/// out. It is good practice to use this method inside of a transaction to
/// maintain atomicity. Note that these commands should not be used in
/// conjuction with finds.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-04 by Aaron Gulack
/// @See         SQL_SAVE_BUFFER_END SQL_SAVE_BUFFER
///
/// @Syntax SQL_SAVE_BUFFER_BEGIN of {FileName} to {variable}
/// @Param FileName			Name of the file
/// @Param variable			Number of records to store in the buffer
///
/// @Example
/// Open Customer
///
/// SQL_SAVE_BUFFER_BEGIN of Transactions to 10
///
/// For i from 0 to 1000
///     Move i to Transactions.ID
///     SQL_SAVE_BUFFER of Transactions
/// Loop
///
/// SQL_SAVE_BUFFER_END of Customer
#COMMAND SQL_SAVE_BUFFER_BEGIN "OF" R "TO" R .
    DO_GETFILENUMBER_DRIVERNAME !2
    If (MertechInc_DriverName EQ ORAFLEX or MertechInc_DriverName EQ SQLFLEX or MertechInc_DriverName EQ MDSDB2 or MertechInc_DriverName EQ MDSPgSQL) Begin
        MOVE !4 TO MertechInc_sArg1
        IF (MertechInc_DriverName EQ ORAFLEX OR MertechInc_DriverName EQ MDSDB2) Call_Driver MertechInc_FileNumber MertechInc_DriverName FUNCTION 20 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
        Else                                                                     Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 8  CALLBACK 0 PASSING MertechInc_Blank MertechInc_sArg1 1 RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    END
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_SAVE_BUFFER
/// @Description This command is used to send a record to the "Save
/// Record" buffer. It must be used along with SQL_SAVE_BUFFER_BEGIN
/// and SQL_SAVE_BUFFER_END. SQL_SAVE_BUFFER_BEGIN sets the number of
/// records to store in the buffer before a save is done on all the records
/// at once. Each time a record is created, this command should be called
/// to insert it into the buffer. Using this set of commands can be useful
/// to efficiently save a large number of records. Once the buffer is full,
/// the save occurs automatically and the buffer will be emptied out. It is
/// good practice to use this method inside of a transaction to maintain
/// atomicity.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-04 by Aaron Gulack
/// @See 		 SQL_SAVE_BUFFER_BEGIN SQL_SAVE_BUFFER_END
///
/// @Syntax SQL_SAVE_BUFFER of {FileName}
/// @Param FileName			Name of the file
///
/// @Example
/// Open Customer
///
/// SQL_SAVE_BUFFER_BEGIN of Transactions to 10
///
/// For i from 0 to 1000
///     Move i to Transactions.ID
///     SQL_SAVE_BUFFER of Transactions
/// Loop
///
/// SQL_SAVE_BUFFER_END of Customer
#COMMAND SQL_SAVE_BUFFER "OF" R .
    DO_GETFILENUMBER_DRIVERNAME !2
    If (MertechInc_DriverName EQ ORAFLEX or MertechInc_DriverName EQ SQLFLEX or MertechInc_DriverName EQ MDSDB2 or MertechInc_DriverName EQ MDSPgSQL) Begin
        If (MertechInc_DriverName EQ ORAFLEX or MertechInc_DriverName EQ MDSDB2) Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 20 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 1 RESULT MertechInc_iRet
        Else                                                                     Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 8  CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 2 RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    END
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_SAVE_BUFFER_END
/// @Description This command indicates the end of the extended record
/// buffer and forces a save of any data currently in the buffer.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-04 by Aaron Gulack
/// @See         SQL_SAVE_BUFFER_BEGIN SQL_SAVE_BUFFER
///
/// @Syntax SQL_SAVE_BUFFER_END of {FileName}
/// @Param FileName			Name of the file
///
/// @Example
/// Open Customer
///
/// SQL_SAVE_BUFFER_BEGIN of Transactions to 10
///
/// For i from 0 to 1000
///     Move i to Transactions.ID
///     SQL_SAVE_BUFFER of Transactions
/// Loop
///
/// SQL_SAVE_BUFFER_END of Customer
#COMMAND SQL_SAVE_BUFFER_END "OF" R .
    DO_GETFILENUMBER_DRIVERNAME !2
    If (MertechInc_DriverName EQ ORAFLEX or MertechInc_DriverName EQ SQLFLEX or MertechInc_DriverName EQ MDSDB2 or MertechInc_DriverName EQ MDSPgSQL) Begin
        If (MertechInc_DriverName EQ ORAFLEX or MertechInc_DriverName EQ MDSDB2) Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 20 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 2 RESULT MertechInc_iRet
        Else                                                                     Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 8  CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 4 RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    END
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_SAVE_SET_ATTRIBUTES
/// @Description Unknown - Not in help - Not call by any other macros
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2009-08-18 By Ian Smith
/// @See
#COMMAND SQL_SAVE_SET_ATTRIBUTES "OF" R "DISABLED""KBYTES""ROWS" #L "TABLOCK"""
    DO_GETFILENUMBER_DRIVERNAME !2
    If (MertechInc_DriverName EQ SQLFLEX) Begin
        #IFSAME !3 DISABLED
        #ELSE
            #CHECK !4 _FG#L
            #IFSAME !3 KBYTES
                Move ("KILOBYTES_PER_BATCH = " + String(!4)) to MertechInc_sArg1
            #ELSE
                Move ("ROWS_PER_BATCH = " + String(!4)) to MertechInc_sArg1
            #ENDIF

            #IF !0 > 4
                Move (MertechInc_sArg1 + ", TABLOCK") to MertechInc_sArg1
            #ENDIF
        #ENDIF
        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function 8 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 7 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        ENABLE_TRACE_ON
/// @Description This command enables driver level tracing to the
/// specified file. Enabling trace on an application and using it
/// in conjunction with SQL_TEXT_MESSAGE is a good way to study
/// particular problems you encounter in the driver. SQL_TEXT_MESSAGE
/// allows you to insert sections of your code into the trace file.
/// This command can also set the trace to three different levels,
/// allowing different amounts of information to be logged. Note that
/// trace files can become very large so it is good practice to only
/// turn them on when specifically needed.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See		 DISABLE_TRACE_ON SQL_TEXT_MESSAGE
///
/// @Syntax ENABLE_TRACE_ON to {fileName} Debug_Level [{constant}]
/// @Param fileName			The path of the file to send the trace to
/// @Param constant  		DETAIL_LEVEL1, DETAIL_LEVEL2, DETAIL_LEVEL3 (optional)
///
/// @Example ENABLE_TRACE_ON TO "C:\Temp\trace_file.txt" Debug_Level DETAIL_LEVEL3
#COMMAND ENABLE_TRACE_ON TO R "ERROR_LEVEL""DEBUG_LEVEL""DETAIL_LEVEL1""DETAIL_LEVEL2""DETAIL_LEVEL3"""
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Move !2 to MertechInc_sArg1
        #IF (!0=3)
            #IFSAME !3 ERROR_LEVEL
                Move -1 to MertechInc_sArg2
            #ELSE
                #IFSAME !3 DEBUG_LEVEL
                    Move 0 to MertechInc_sArg2
                #ELSE
                    #IFSAME !3 DETAIL_LEVEL1
                        Move 1 to MertechInc_sArg2
                    #ELSE
                        #IFSAME !3 DETAIL_LEVEL2
                            Move 2 to MertechInc_sArg2
                        #ELSE
                            Move 3 to MertechInc_sArg2
                        #ENDIF
                    #ENDIF
                #ENDIF
            #ENDIF
        #ELSE
            Move 0 to MertechInc_sArg2
        #ENDIF

        Call_Driver 0 MertechInc_DriverName Function 15 CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 0 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND // ENABLE_TRACE_ON

//=============================================================================
/// @Name        DISABLE_TRACE_ON
/// @Description This command disables the current trace taking
/// place on a driver.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See ENABLE_TRACE_ON SQL_TEXT_MESSAGE
///
/// @Syntax DISABLE_TRACE_ON
#COMMAND DISABLE_TRACE_ON .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Call_Driver 0 MertechInc_DriverName Function 15 CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 1 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        CREATE_TABLE_FROM_DAT_FILE
/// @Description This command is used to create a SQL table from a .DAT
/// file. The table being copied must be not be opened in order for this
/// command to work properly. This is the programmatic equivalent to
/// using the Flex2SQL Migration Tool. Optional restructuring options
/// can be specified here (see below) as well as an alternative table
/// name than the physical name of the .DAT file. Note that this only
/// creates the  table structure, no data will be copied here. To copy
/// the data, use COPY_DATA after the table has been created.
///
/// DF_STRUCTEND_OPT_FORCE_INVK		- Deprecated
///
/// DF_STRUCTEND_OPT_OLD_INVK_NAME	- Deprecated
///
/// DF_STRUCTEND_OPT_FORCE_NOT_NULL - forces all fields to be created as NOT NULL.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See		 COPY_DATA CONVERT_DAT_FILE
///
/// @Syntax CREATE_TABLE_FROM_DAT_FILE {FileNumber} [{options} {table}]
/// @Param FileNumber		Number of the file
/// @Param options			DF_STRUCTEND_OPT_FORCE_INVK
///							DF_STRUCTEND_OPT_OLD_INVK_NAME
///							DF_STRUCTEND_OPT_FORCE_NOT_NULL (optional)
/// @Param table            name of table to use instead of physical name (optional)
///
/// @Example
/// Login "localhost" "user" "pass123" "sql_drv"
/// CREATE_TABLE_FROM_DAT_FILE Customer.File_Number "Customer"
/// COPY_DATA "Customer" to "sql_drv:Customer" CALLBACK (Callback(Self)) CONSTRAIN "STATUS = 'Active'"
#COMMAND CREATE_TABLE_FROM_DAT_FILE R
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        #IF (!0 > 1)
            Move !2 to MertechInc_iArg
            #IF (!0 > 2)
                Move !3 to MertechInc_sArg1
            #ELSE
                Move MertechInc_Blank to MertechInc_sArg1
            #ENDIF
        #ELSE
            Move 0 to MertechInc_iArg
            Move MertechInc_Blank to MertechInc_sArg1
        #ENDIF

        If (MertechInc_DriverName = ORAFlex) Call_Driver !1 MertechInc_DriverName Function CALLDRV_ORA_CREATE_TABLE_FROM_DAT CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
        Else                                 Call_Driver !1 MertechInc_DriverName Function CALLDRV_CREATE_TABLE_FROM_DAT     CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        CONVERT_DAT_FILE
/// @Description This command is the programmatic equivalent to the
/// Flex2SQL Migration Tool. With this command, a SQL table can be
/// created from a .DAT table. This combines the COPY_DATA and
/// CREATE_TABLE_FROM_DAT_FILE, creating the table structure and
/// copying all the data into the new table with one command. The
/// table being converted cannot be opened and so a manual login is
/// needed. Note that to specify the database to copy the table to,
/// use SET_DATABASE_NAME. Below is a list of the optional restructure
/// options to use when creating the table.
///
/// DF_STRUCTEND_OPT_FORCE_INVK		- Deprecated
///
/// DF_STRUCTEND_OPT_OLD_INVK_NAME	- Deprecated
///
/// DF_STRUCTEND_OPT_FORCE_NOT_NULL - forces all fields to be created as NOT NULL.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See		 CREATE_TABLE_FROM_DAT_FILE COPY_DATA
///
/// @Syntax CONVERT_DAT_FILE {FileNumber} [{options} {table}]
/// @Param FileNumber		Number of the file
/// @Param options			DF_STRUCTEND_OPT_FORCE_INVK
///							DF_STRUCTEND_OPT_OLD_INVK_NAME
///							DF_STRUCTEND_OPT_FORCE_NOT_NULL (optional)
/// @Param table            Name of table to use instead of physical name (optional)
///
/// @Example
/// Login "localhost" "user" "pass123" "sql_drv"
/// CONVERT_DAT_FILE Customer.File_Number DF_STRUCTEND_OPT_FORCE_NOT_NULL "Customer"
#COMMAND CONVERT_DAT_FILE R
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        #IF (!0 > 1)
            Move !2 to MertechInc_iArg
            #IF (!0 > 2)
                Move !3 to MertechInc_sArg1
            #ELSE
                Move MertechInc_Blank to MertechInc_sArg1
            #ENDIF
        #ELSE
            Move 0 to MertechInc_iArg
            Move MertechInc_Blank to MertechInc_sArg1
        #ENDIF

        Call_Driver !1 MertechInc_DriverName Function CALLDRV_CONVERT_DAT_FILE CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SET_DEFAULT_FILE_CASING
/// @Description This command is used to set the file casing standard when
/// creating or restructuring tables. By default, all table and column names
/// are created using the specified casing. Passing FILE_CASING_UPPER or
/// FILE_CASING_LOWER will allow the names to be saved in uppercase or
/// lowercase respectively. This can be useful for backwards compatibility
/// where casing was important. Note that the casing standard for a file can
/// also be changed through mertech.ini. Below is a description of the constants
/// that can be passed to this command.
///
/// FILE_CASING_UPPER : All created or edited object names will be converted to uppercase.
/// FILE_CASING_LOWER : All created or edited object names will be converted to lowercase.
/// FILE_CASING_KEEP (default) : All created or edited object names will maintain their inputed casing.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-07 by Aaron Gulack
/// @See 		 GET_DEFAULT_FILE_CASING
///
/// @Syntax SET_DEFAULT_FILE_CASING to {constant}
/// @Param constant			FILE_CASING_UPPER, FILE_CASING_LOWER, FILE_CASING_KEEP
///
/// @Example
/// SET_DEFAULT_FILE_CASING to FILE_CASING_UPPER
#COMMAND SET_DEFAULT_FILE_CASING TO R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Move !2 to MertechInc_sArg1
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_DEFAULT_FILE_CASING CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank CALLDRV_VALUE_SET RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        GET_DEFAULT_FILE_CASING
/// @Description This command returns the file casing standard used
/// when creating or restructuring tables. Note that an integer is returned,
/// mapping to a casing method. Below are the meanings of the possible
/// returned integers.
///
/// 0 - FILE_CASING_UPPER : All created or edited object names will be converted to uppercase.
/// 1 - FILE_CASING_LOWER : All created or edited object names will be converted to lowercase.
/// 2 -	FILE_CASING_KEEP : All created or edited object names will maintain their inputed casing.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-07 by Aaron Gulack
/// @See 		 SET_DEFAULT_FILE_CASING
///
/// @Syntax GET_DEFAULT_FILE_CASING to {variable}
/// @Param variable			Variable to hold the returned casing
///
/// @Example
/// GET_DEFAULT_FILE_CASING TO iCasing
#COMMAND GET_DEFAULT_FILE_CASING TO R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_DEFAULT_FILE_CASING CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank CALLDRV_VALUE_GET RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
        Move MertechInc_iRet to !2
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SET_DEFAULT_TABLESPACE
/// @Description This command sets the default table space to use when
/// creating tables through Dataflex. A tablespace is a container of
/// segments (objects that have an allotted amount of space), i.e. tables
/// and indexes.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     ORAFlex, PgFlex
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See 		 GET_DEFAULT_TABLESPACE SET_DEFAULT_INDEX_TABLESPACE GET_DEFAULT_INDEX_TABLESPACE
///
/// @Syntax SET_DEFAULT_TABLESPACE to {variable}
/// @Param variable			Name of the default table space
///
/// @Example
/// SET_DEFAULT_TABLESPACE to "Users"
#COMMAND SET_DEFAULT_TABLESPACE TO R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Move !2 to MertechInc_sArg1
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_GLOBAL_SETTING CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank GLOBAL_SETTING_TABLESPACE_SET RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        GET_DEFAULT_TABLESPACE
/// @Description This command returns the default table space name for
/// the current database.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     ORAFlex, PgFlex
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See 		 SET_DEFAULT_TABLESPACE SET_DEFAULT_INDEX_TABLESPACE GET_DEFAULT_INDEX_TABLESPACE
///
/// @Syntax GET_DEFAULT_TABLESPACE to {variable}
/// @Param variable			Variable to hold the default table space name.
///
/// @Example
/// GET_DEFAULT_TABLESPACE to sTableSpace
#COMMAND GET_DEFAULT_TABLESPACE TO R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        MOVE (REPEAT(" ",255)) to MertechInc_sArg1
        CALL_DRIVER 0 MertechInc_DriverName FUNCTION CALLDRV_GLOBAL_SETTING CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank GLOBAL_SETTING_TABLESPACE_GET RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
        [  ERR ] Move ""               to !2
        [ ~ERR ] Move MertechInc_sArg1 to !2
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SET_DEFAULT_INDEX_TABLESPACE
/// @Description This command sets the default table space for indexes
/// when creating tables through the DataFlex API. A tablespace is a
/// container of segments (objects that have an allotted amount of space),
/// i.e. tables and indexes.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     ORAFlex, PgFlex
/// @VersionNote Last Revised: 2013-10-09-2013 by Aaron Gulack
/// @See 		 SET_DEFAULT_TABLESPACE GET_DEFAULT_TABLESPACE GET_DEFAULT_INDEX_TABLESPACE
///
/// @Syntax SET_DEFAULT_INDEX_TABLESPACE to {variable}
/// @Param variable			Variable to hold the default index table space name.
///
/// @Example
/// SET_DEFAULT_INDEX_TABLESPACE to "Users"
#COMMAND SET_DEFAULT_INDEX_TABLESPACE TO R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Move !2 to MertechInc_sArg1
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_GLOBAL_SETTING CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank GLOBAL_SETTING_INDEX_TABLESPACE_SET RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        GET_DEFAULT_INDEX_TABLESPACE
/// @Description This command returns the default table space name for
/// indexes in the current database.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     ORAFlex, PgFlex
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See 		 SET_DEFAULT_TABLESPACE GET_DEFAULT_TABLESPACE SET_DEFAULT_INDEX_TABLESPACE
///
/// @Syntax GET_DEFAULT_INDEX_TABLESPACE to {variable}
/// @Param variable			Variable to hold the default index table space name.
///
/// @Example
/// GET_DEFAULT_INDEX_TABLESPACE to sTableSpace
#COMMAND GET_DEFAULT_INDEX_TABLESPACE TO R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        MOVE (REPEAT(" ",255)) to MertechInc_sArg1
        CALL_DRIVER 0 MertechInc_DriverName FUNCTION CALLDRV_GLOBAL_SETTING CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank GLOBAL_SETTING_INDEX_TABLESPACE_GET RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
        [  ERR ] Move ""               to !2
        [ ~ERR ] Move MertechInc_sArg1 to !2
    End
#ENDCOMMAND

//=============================================================================
/// @Name        ENABLE_SCRIPTING
/// @Description Scripting is used for testing and preparation. This
/// command allows structural changes to be compiled and tested without
/// actually making any of the changes. Any table restructuring done
/// between this command and DISABLE_SCRIPTING will not actually be
/// committed but will instead create a mock INT file. The script and
/// INT file can then be retrieved and examined for testing purposes.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See 		 DISABLE_SCRIPTING GET_SQL_SCRIPT_CHUNK GET_INT_CHUNK
///
/// @Syntax ENABLE_SCRIPTING
///
/// @Example
/// ENABLE_SCRIPTING
/// 	//Table restructuring would go here
/// DISABLE_SCRIPTING
///
/// GET_SQL_SCRIPT_CHUNK OFFSET 0 to sChunk sLength
/// Showln sChunk
#COMMAND ENABLE_SCRIPTING
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin

        Call_Driver 0 MertechInc_DriverName Function CALLDRV_RESTRUCTURE_SCRIPT CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank CALLDRV_RESTRUCTURE_SCRIPT_ENABLE RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        DISABLE_SCRIPTING
/// @Description This command ends any scripting started by ENABLE_SCRIPTING.
/// The mock INT file and script can then be retrieved and examined.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2010-12-13 By Marcelo Nachbar
/// @See 		 ENABLE_SCRIPTING  GET_SQL_SCRIPT_CHUNK GET_INT_CHUNK
///
/// @Syntax DISABLE_SCRIPTING
///
/// @Example
/// ENABLE_SCRIPTING
/// 	//Table restructuring would go here
/// DISABLE_SCRIPTING
///
/// GET_SQL_SCRIPT_CHUNK OFFSET 0 to sChunk sLength
/// Showln sChunk
#COMMAND DISABLE_SCRIPTING
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin

        Call_Driver 0 MertechInc_DriverName Function CALLDRV_RESTRUCTURE_SCRIPT CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank CALLDRV_RESTRUCTURE_SCRIPT_DISABLE RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

Function MertechInc_GET_RESTRUCTURE_SCRIPT Global Integer iLong Integer iOffset Returns String
    Integer iChuck_Size
    String sChunk

    //Get current Chuck size and pre size string
    Call_Driver 0 MertechInc_DriverName Function CALLDRV_CHUNK_SIZE CALLBACK 0 PASSING iChuck_Size MertechInc_Blank 1 RESULT MertechInc_iRet
    Get MertechInc_Pre_Size_String iChuck_Size to sChunk

    //Get data
    Call_Driver 0 MertechInc_DriverName Function CALLDRV_RESTRUCTURE_SCRIPT CALLBACK 0 PASSING sChunk iOffset iLong RESULT MertechInc_iRet

    // Replace insert a CR before any LF character
    Move (Replaces(Character(10), sChunk, Character(13)+Character(10))) to sChunk

    Function_Return sChunk
End_Function


//=============================================================================
/// @Name        GET_SQL_SCRIPT_CHUNK
/// @Description This command returns a chunk of the script generated
/// from the restructuring done inside of ENABLE_SCRIPTING and
/// DISABLE_SCRIPTING. Since some scripts can be very large, the script
/// can be looped through, grabbing chunks at a time.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See 		 ENABLE_SCRIPTING DISABLE_SCRIPTING GET_INT_CHUNK
///
/// @Syntax GET_SQL_SCRIPT_CHUNK OFFSET {offset} to {variable} [{length}]
/// @Param offset			Specifies the offset to start at for the chunk
/// @Param variable			Variable to hold the chunk
/// @Param length			Length of chunk returned (optional)
///
/// @Example
/// ENABLE_SCRIPTING
/// 	//Table restructuring would go here
/// DISABLE_SCRIPTING
///
/// GET_SQL_SCRIPT_CHUNK OFFSET 0 to sChunk sLength
/// Showln sChunk
#COMMAND GET_SQL_SCRIPT_CHUNK "OFFSET" R "TO" R R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Get MertechInc_GET_RESTRUCTURE_SCRIPT CALLDRV_RESTRUCTURE_SCRIPT_GET_CHUNK_SQL !2 To !4
        If MertechInc_iRet EQ -1 Begin
            INDICATE ERR True
            Move 0 to !5
        End
        Else Move MertechInc_iRet to !5
    End
#ENDCOMMAND

//=============================================================================
/// @Name        GET_INT_CHUNK
/// @Description This command returns a chunk of the INT file generated
/// from the restructuring done inside of ENABLE_SCRIPTING and
/// DISABLE_SCRIPTING. Since some INT files can be very large, the file
/// can be looped through, grabbing chunks at a time.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See 		 ENABLE_SCRIPTING DISABLE_SCRIPTING GET_SQL_SCRIPT_CHUNK
///
/// @Syntax GET_INT_CHUNK OFFSET {offset} to {variable} [{length}]
/// @Param offset			Specifies the offset to start at for the chunk
/// @Param variable			Variable to hold the chunk
/// @Param length			Length of chunk returned (optional)
///
/// @Example
/// ENABLE_SCRIPTING
/// 	//Table restructuring would go here
/// DISABLE_SCRIPTING
///
/// GET_INT_CHUNK OFFSET 0 to sChunk sLength
/// Showln sChunk
#COMMAND GET_INT_CHUNK OFFSET R to R R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Get MertechInc_GET_RESTRUCTURE_SCRIPT CALLDRV_RESTRUCTURE_SCRIPT_GET_CHUNK_INT !2 To !4
        If MertechInc_iRet EQ -1 Begin
            INDICATE ERR True
            Move 0 to !5
        End
        Else Move MertechInc_iRet to !5
    End
#ENDCOMMAND

//=============================================================================
/// @Name        REPORT_STMT
/// @Description This command is an alternative to DataFlex's "Report"
/// command. This allows embedded SQL to be used to fetch data instead of
/// standard table queries.. All of the finds, for example, normally found
/// in "Report" are replaced by SQL_FETCH_NEXT_ROW.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     n/a
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See
///
/// @Syntax See DataFlex / Visual DataFlex documentation
///
/// @Example
/// /Header
/// __/__/____                                                        Page ___.
///                 MERTECH DATA SYSTEMS, INC. - NOT FOR RESALE
///
/// ID   NAME
///
/// /Body
/// ____ _________________________
/// /Total
/// Records printed = _______.
/// /*
///
///
/// OPEN SALESP
/// direct_output "con:"
/// // Write the complete SELECT statement to retrieve the expected records from your REPORT
/// // Must include the expression to qualify the required records and specify the order by as well
///
/// sql_set_stmt of salesp to "select recnum, id, name from SALESP where recnum > 5 order by id"
/// sql_prepare_stmt of salesp
/// sql_bindcolumns_stmt of salesp to salesp.recnum salesp.id salesp.name
/// sql_execute_stmt of salesp
///
/// Report_stmt SALESP By Index.1
///
/// Section Header
///     Sysdate Header.1
///     Move PageCount to Header.2
///     output header
///
/// Section Body
///     Print Salesp.id   to Body.1
///     Print Salesp.name to Body.2
///     output body
/// Section Total
///
/// Return
/// ReportEnd
#COMMAND REPORT_STMT T "BY""DOWN" VFW%LGR "BREAK"""
    #CHECK !1.RECNUM _UVCWGL
    Integer RECCOUNT
    #SET P$ 0
    !A [] $82 |CI20000 |VI10                //MOVEINT 20000 TO LINECOUNT    - start with a full page
    !A [] $82 |CI0 RECCOUNT                 //MOVE 0 TO RECCOUNT
    !A [] $207                              //BREAKINIT                     - init breakpoints
    #IFDEF FIRSTREC
    #ELSE
        #Replace FIRSTREC |!C
    #ENDIF
    !A [] $4028 |CI0 |CI0 FIRSTREC~         //INDICATE FIRSTREC TRUE        - used for subtotals

    SQL_FETCH_NEXT_ROW of !1.FILE_NUMBER    //Retrieve the First Row
    //#IFSAME !2 BY                         // FIND first record
    //    FIND GE !1 BY !3
    //#ELSE
    //    FIND LE !1 BY !3
    //#ENDIF
    [~Found] Goto END$OF$REPORT
    !A [] $144                              //CLEARSCREEN                   - start with a clear screen
    RPT.Loop:                               //INDICATE SELECT TRUE      // default for SELECT
    #IFDEF SELECT
    #ELSE
        #Replace SELECT |!C
    #ENDIF
    !A [] $4028 |CI0 |CI0 SELECT~
    !A [] $42 |CL0                          //GOSUB RPT.SELECTION     // go to user selection
    #FREF RPT.SELECTION !a
    !A [~ SELECT] $41 |CL0                  //[NOT SELECT] GOTO RPT.CONT        // test SELECT
    #FREF RPT.CONT !a
    BREAK$ !5 !6 !7 !8 !9                   //set breakpoints
    #SET X$ !p                              //set up to break down
    [not FIRSTREC] BREAK$DOWN RPT.SUBTOTAL  //break down for SUBTOTAL
    #SET X$ 0                               //set up to break up
    !A [] $C4 !1.RECNUM                     //RELATE !1           // get related records
    BREAK$UP RPT.SUBHEADER                  //break up for SUBHEADER
    !A [] $083 RECCOUNT |CI0                //INCREMENT RECCOUNT
    !A [] $42 |CL0                          //GOSUB RPT.BODY          // print body
    #FREF RPT.BODY !a
    !A [] $4028 |CI0 |CI0 FIRSTREC          //INDICATE FIRSTREC FALSE     // not first any more
    RPT.CONT:
    SQL_FETCH_NEXT_ROW of !1.FILE_NUMBER    //Retrieve the next Row from current query
    //#IFSAME !2 BY                         // FIND next record
    //    FIND GT !1 BY !3
    //#ELSE
    //    FIND LT !1 BY !3
    //#ENDIF
    !A [] $46                               //KEYCHECK            // check keyboard
    !A [Found ~ KEYPRESS] $41 RPT.Loop      //[FOUND NOT KEYPRESS] GOTO RPT.LOOP    // if ok, loop
    !A [Found KEYPRESS]   $42 |CL0          //[KEYPRESS]  GOSUB RPT.KEYPRESS    // user can disable KEYPRESS
    #FREF RPT.KEYPRESS !a
    !A [Found ~ KEYPRESS] $41 RPT.Loop
    #SET X$ !p                              //set up for break down
    End.of.REPORT:
    [~ FIRSTREC]  BREAK$DOWN RPT.SUBTOTAL $X    // break down for last subtotals
    !A [~ FIRSTREC] $42 |CL0                //[FIRSTREC]  GOSUB RPT.TOTAL       // print TOTAL
    #FREF RPT.TOTAL !a
    !A [] $41 |CL0                          //GOTO END$OF$REPORT      // GOTO end
    #FREF END$OF$REPORT !a
    NEWPAGE:                                //GOSUB RPT.HEADER      // new page, print HEADER
    !A [] $42 |CL0
    #FREF RPT.HEADER !a
    #SET X$ 0                               //this will reprint the page headers if included //
    [not FIRSTREC] BREAK$PRT SUBHEADER      //reprint pages
    !A [] $43 |CI0                          //RETURN              // end of NEWPAGE
    RPT.SELECTION:                          //selection starts after REPORT
#ENDCOMMAND

//=============================================================================
/// @Name        GET_SERVER_CFG
/// @Description This command, when passed a valid server name, returns
/// the a value for the specified attribute. See the list below for an
/// explanation of each attribute.
///
/// SERVER_REVISION    Returns the major version, to the left of the decimal, of the server
/// SUPPORT_DESC       Returns 1 if Server supports descending index segments
/// SUPPORT_CASE       Returns 1 if Server supports case insensitive index segments
/// SERVER_VERSION     Returns the full version of the server
/// SERVER_ENCODING    Returns the Server Encoding
/// CONNECTION_ACTIVE  Returns 1 if the connection to the server is active
/// CITEXT_SUPPORT     Returns 1 if Server supports citext, a PostgreSQL data type
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See
///
/// @Syntax GET_SERVER_CFG {constant} of {server} to {variable}
/// @Param constant			SERVER_REVISION,SERVER_MIN_REVISION,SUPPORT_DESC,SUPPORT_CASE,SERVER_VERSION,SERVER_ENCODING,CONNECTION_ACTIVE
/// @Param server			Name of the server being checked
/// @Param variable			Variable to hold the returned value
///
/// @Example
/// GET_SERVER_CFG SERVER_VERSION of "localhost" to sVersion
#COMMAND GET_SERVER_CFG "SERVER_REVISION""SERVER_MIN_REVISION""SUPPORT_DESC""SUPPORT_CASE""SERVER_VERSION""SERVER_ENCODING""CONNECTION_ACTIVE""CITEXT_SUPPORT" "OF" R
    DO_GETFILENUMBER_DRIVERNAME 0

    //workout server name
    #IFSAME !1 CONNECTION_ACTIVE
        #IFSAME !4 to
            Move !3 to MertechInc_sArg1
        #ELSE
            #CHECK !5 "TO"
            Move (!3+"*"+!4) to MertechInc_sArg1
        #ENDIF
    #ELSE
        #CHECK !4 "TO"
        Move !3 to MertechInc_sArg1
    #ENDIF

    //Workout attribute to get
    #IFSAME !1 SERVER_REVISION
        Move 0 to MertechInc_iArg
    #ELSE
        #IFSAME !1 SUPPORT_DESC
            Move 1 to MertechInc_iArg
        #ELSE
            #IFSAME !1 SUPPORT_CASE
                Move 2 to MertechInc_iArg
            #ELSE
                #IFSAME !1 SERVER_MIN_REVISION
                    Move 3 to MertechInc_iArg
                #ELSE
                    #IFSAME !1 SERVER_VERSION
                        Move 4 to MertechInc_iArg
                    #ELSE
                        #IFSAME !1 SERVER_ENCODING
                           Move 5 to MertechInc_iArg
                        #ELSE
                            #IFSAME !1 CONNECTION_ACTIVE
                               Move 6 to MertechInc_iArg
                            #ELSE
                               Move 7 to MertechInc_iArg
                            #ENDIF
                        #ENDIF
                    #ENDIF
                #ENDIF
            #ENDIF
        #ENDIF
    #ENDIF

    #IFSAME !4 to
        Get MertechInc_GET_SERVER_CFG MertechInc_sArg1 MertechInc_iArg to !5
    #ELSE
        Get MertechInc_GET_SERVER_CFG MertechInc_sArg1 MertechInc_iArg to !6
    #ENDIF

    If MertechInc_iRet EQ -1 INDICATE ERR True
#ENDCOMMAND

Function MertechInc_GET_SERVER_CFG Global String sServer Integer iAttribute Returns String
    String sReturnValue

    Get MertechInc_Pre_Size_String 512 to sReturnValue

    Call_Driver 0 MertechInc_DriverName Function CALLDRV_GET_SERVER_CFG CALLBACK 0 PASSING sServer sReturnValue iAttribute RESULT MertechInc_iRet

    //If iAttribute = SERVER_VERSION or SERVER_ENCODING then return sReturnValue
    //else we need to return MertechInc_iRet
    If ((iAttribute = 4) or (iAttribute = 5)) Function_Return sReturnValue
    Else                                      Function_Return MertechInc_iRet
End_Function

//=============================================================================
/// @Name        GET_CONNECTION_STATUS
/// @Description Retrieve the connection status for the specified server.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     All
/// @VersionNote Last Revised: 2009-09-25 By Ian Smith
/// @See
///
/// @Syntax GET_CONNECTION_STATUS of <serverName> [<databaseName>] to <variable>
/// @Param serverName    Server Name
/// @Param databaseName  Database Name
/// @Param variable      DFTRUE means connection is active
#COMMAND GET_CONNECTION_STATUS "OF" R
    #IFSAME !3 TO
        GET_SERVER_CFG CONNECTION_ACTIVE OF !2 TO !4
    #ELSE
        #CHECK !4 "TO"
        GET_SERVER_CFG CONNECTION_ACTIVE OF !2 !3 TO !5
    #ENDIF
#ENDCOMMAND

//=============================================================================
/// @Name        GET_CLIENT_CFG
/// @Description Returns the client character encoding (or encoding ID) information.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     MySQLFlex and PgFlex
/// @VersionNote Last Revised: 2009-09-25 By Ian Smith
/// @See
///
/// @Syntax GET_CLIENT_CFG [ENCODING | ENCODING_ID] of <Server> [<MySQL_Database>] to <Var>
/// @Param Server           Server name to get encoding of
/// @Param MySQL_Database   Database if   is the File Name
/// @Param Var              Variable to hold returned value
#COMMAND GET_CLIENT_CFG "ENCODING""ENCODING_ID" "OF" R
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_DriverName EQ MySQLFLEX  or MertechInc_DriverName EQ MDSPgSQL) Begin
        Get MertechInc_Pre_Size_String 255 to MertechInc_sArg2

        #IFSAME !5 to
            Move (!3+"*"+!4) to MertechInc_sArg1
        #ELSE
            #CHECK !4 "TO"
            Move !3 to MertechInc_sArg1
        #ENDIF

        #IFSAME !1 ENCODING
            Move 0 to MertechInc_iArg
        #ELSE
            Move 3 to MertechInc_iArg
        #ENDIF

        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function CALLDRV_CLIENT_CFG CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 MertechInc_iArg RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
        Else Begin
            #IFSAME !5 to
                Move MertechInc_sArg2 to !6
            #ELSE
                Move MertechInc_sArg2 to !5
            #ENDIF
        End
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SET_CLIENT_CFG
/// @Description Returns the client character encoding (or encoding ID) information.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     MySQLFlex and PgFlex
/// @VersionNote Last Revised: 2009-09-25 By Ian Smith
/// @See
///
/// @Syntax SET_CLIENT_CFG [ENCODING | UNIQUE_CHECKS] of <Server> [<MySQL_Database>] to <Value>
/// @Param Server           Server name to get encoding of
/// @Param MySQL_Database   Database if   is the File Name
/// @Param Value            Value to set
///
/// @Comment ENCODING - Set the Client Encoding
/// @Comment UNIQUE_CHECKS {DFTRUE/DFFALSE} - enable/disable uniqueness checks for secondary indexes in InnoDB tables
#COMMAND SET_CLIENT_CFG "ENCODING""UNIQUE_CHECKS" "OF" R
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_DriverName EQ MySQLFLEX  or MertechInc_DriverName EQ MDSPgSQL) Begin
        #IFSAME !1 ENCODING
            Move 1 to MertechInc_iArg
            #IFSAME !4 to
                Move !3 to MertechInc_sArg1
                Move !5 to MertechInc_sArg2
            #ELSE
                Move (!3+"*"+!4) to MertechInc_sArg1
                Move !6 to MertechInc_sArg2
            #ENDIF
        #ELSE
            #CHECK !4 "TO"
            Move !3 to MertechInc_sArg1
            Move 2 to MertechInc_iArg
            Move !5 to MertechInc_sArg2
        #ENDIF

        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function CALLDRV_CLIENT_CFG CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 MertechInc_iArg RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        CALL_DB2_PROCEDURE
/// @Description Executes a DB2 Server stored procedure.
/// @Status      Public
/// @Drivers     DB2Flex
/// @VersionNote Last Revised: 2009-08-19 By Ian Smith
///
/// @Syntax CALL_DB2_PROCEDURE <OWNER> <STORED_PROC> {PASSING <ARG1> {. <ARGn>}}
/// @Param Owner        Name of the Procedure's Owner.
/// @Param Stored_Proc  Full name of the stored procedure being called.
/// @Param Arg1..Argn   Arguments passed to the procedure.
///
#COMMAND CALL_DB2_PROCEDURE R R "PASSING""BINDING"""
    LOAD_DRIVER "MertechInc_DB2"

    INDICATE MertechInc_bThereIsBinding False

    #IF (!0>3)
        DO_CHECK_BINDING !4 !5 !6 !7 !8 !9
    #ENDIF

    MOVE 0 TO MertechInc_iParamCount
    INDICATE ERR FALSE
    SQL_SET_STMT TO "CALL "
    SQL_APPEND_STMT TO !1
    SQL_APPEND_STMT TO "."
    SQL_APPEND_STMT TO !2
    SQL_APPEND_STMT TO " "
    #IF (!0>2)
        DDO_PASS_ARGUMENTS  !3 !4 !5 !6 !7 !8 !9
        IF (MertechInc_iParamCount > 0) SQL_APPEND_STMT TO ")"
    #ENDIF

    MOVE (UPPERCASE(!1)) TO MertechInc_sArg1
    Move (UPPERCASE(!2)) to MertechInc_sArg2

    Call_Driver 0 MDSDB2 Function CALLDRV_BIND_PARAMETER CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 0 RESULT MertechInc_iRet
    IF MertechInc_iRet NE -1 BEGIN
        MOVE 0 TO MertechInc_iParamCount

        SQL_PREPARE_STMT
        #IF (!0>2)
        DDO_BIND_PARAMETERS  !3 !4 !5 !6 !7 !8 !9
        #ENDIF

        SQL_EXECUTE_STMT
        [ NOT ERR ] BEGIN
            If ( MertechInc_iParamCount GT 0 ) BEGIN
                MOVE 0 TO MertechInc_iParamCount
                [not MertechInc_bThereIsBinding] Begin
                    #IF (!0>3)
                        DDO_GET_BIND_PARAMETERS  !4 !5 !6 !7 !8 !9
                    #ENDIF
                END
            END
        END
    END
    ELSE INDICATE ERR TRUE
#ENDCOMMAND // CALL_DB2_PROCEDURE

//=============================================================================
/// @Name        GET_RESULTS
/// @Description Returns the initial result set.
/// @Status      Public
/// @Drivers     DB2Flex
/// @VersionNote Last Revised: 2009-08-19 By Ian Smith
///
/// @Syntax GET_RESULTS
#COMMAND GET_RESULTS .
    CALL_DRIVER 0 MDSDB2 FUNCTION CALLDRV_GET_RESULTS CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
    IF MertechInc_iRet EQ -1 INDICATE FINDERR TRUE
    ELSE INDICATE FOUND TRUE
#ENDCOMMAND

//=============================================================================
/// @Name        GET_MORE_RESULTS
/// @Description Returns remaining values not retrieved with GET_RESULT.
/// @Status      Public
/// @Drivers     DB2Flex
/// @VersionNote Last Revised: 2009-08-19 By Ian Smith
///
/// @Syntax GET_MORE_RESULTS
#COMMAND GET_MORE_RESULTS .
    CALL_DRIVER 0 MDSDB2 FUNCTION CALLDRV_GET_MORE_RESULTS CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
    IF MertechInc_iRet EQ -1 INDICATE FINDERR TRUE
    ELSE BEGIN
        INDICATE FOUND TRUE
        GET_RESULTS
    END
#ENDCOMMAND

//=============================================================================
/// @Name        GET_CURRENT_USER_NAME
/// @Description This command is used to get the name of the user currently
/// logged into the server.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See 		 GET_CURRENT_USER_PASSWORD
///
/// @Syntax GET_CURRENT_USER_NAME of {server} to {variable}
/// @Param server		The name of the server the user is in
/// @Param variable		Variable to hold the username
///
/// @Example
/// GET_CURRENT_USER_NAME of "localhost" to sUserName
#COMMAND GET_CURRENT_USER_NAME "OF" R "TO" R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Move !2 to MertechInc_sArg1
        Get MertechInc_Pre_Size_String 255 to MertechInc_sArg2
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_GET_CURRENT_USER_NAME CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 0 RESULT MertechInc_iRet
        Move MertechInc_sArg2 to !4
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        GET_CURRENT_USER_PASSWORD
/// @Description This command is used to get the password associated with
/// the user currently logged into the server.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See 		 GET_CURRENT_USER_NAME
///
/// @Syntax GET_CURRENT_USER_PASSWORD of {server} to {variable}
/// @Param server		The name of the server the user is in
/// @Param variable		Variable to hold the password
///
/// @Example
/// GET_CURRENT_USER_PASSWORD of "localhost" to sPassword
#COMMAND GET_CURRENT_USER_PASSWORD "OF" R "TO" R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Move !2 to MertechInc_sArg1
        Get MertechInc_Pre_Size_String 255 to MertechInc_sArg2

        Call_Driver 0 MertechInc_DriverName Function CALLDRV_GET_CURRENT_USER_PASSWORD CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 0 RESULT MertechInc_iRet
        Move MertechInc_sArg2 to !4
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        CREATE_DB2_DATABASE
/// @Description Creates a DB2 database with the same DataFlex collating sequence.
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2009-08-12 By Ian Smith
///
/// @Syntax CREATE_DB2_DATABASE <DB Name> <DB Alias> <Code Set> <Territory> [<Path> <Node Name> <User ID><Password>]
/// @Param DB Name     Name of the database being created
/// @Param DB Alias    Alias Name applied to the database being created
/// @Param Code Set    Code Set used by the database being created
/// @Param Territory   Territory associated to the database being created
/// @Param Path        Location of the database                                    - Optional
/// @Param Node Name   Name of the machine (node) where the database is to reside  - Optional
/// @Param User ID     User ID owning the database                                 - Optional
/// @Param Password    Password of the User owning the database                    - Optional
///
#COMMAND CREATE_DB2_DATABASE R R R R
    Move !1 to MertechInc_sArg1 // Set DB Name
    Call_Driver 0 MDSDB2 Function CALLDRV_CREATE_DB CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
    Move !2 to MertechInc_sArg1 // Set DB Alias
    Call_Driver 0 MDSDB2 Function CALLDRV_CREATE_DB CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 1 RESULT MertechInc_iRet
    Move !3 to MertechInc_sArg1 // Set Code Set
    Call_Driver 0 MDSDB2 Function CALLDRV_CREATE_DB CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 2 RESULT MertechInc_iRet
    Move !4 to MertechInc_sArg1 // Set Territory
    Call_Driver 0 MDSDB2 Function CALLDRV_CREATE_DB CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 3 RESULT MertechInc_iRet

    #IF (!0 > 4)
        Move !5 to MertechInc_sArg1 // Set Path
        Call_Driver 0 MDSDB2 Function CALLDRV_CREATE_DB CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 4 RESULT MertechInc_iRet
        #IF (!0 = 8)
            Move !6 to MertechInc_sArg1 // Set NodeName
            Call_Driver 0 MDSDB2 Function CALLDRV_CREATE_DB CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 5 RESULT MertechInc_iRet
            Move !7 to MertechInc_sArg1 // Set UserId
            Call_Driver 0 MDSDB2 Function CALLDRV_CREATE_DB CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 6 RESULT MertechInc_iRet
            Move !8 to MertechInc_sArg1 // Set UserId
            Call_Driver 0 MDSDB2 Function CALLDRV_CREATE_DB CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 7 RESULT MertechInc_iRet
        #ENDIF
    #ENDIF

    CALL_DRIVER 0 MDSDB2 FUNCTION CALLDRV_CREATE_DB CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 8 RESULT MertechInc_iRet
    IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_OPEN_CURSOR_STMT
/// @Description This command is used to create a new SQl Cursor. Once
/// created, SQL_SET_CURRENT_CURSOR_STMT can be called to specify which
/// cursor is to be used for a given SQL statement. Creating multiple
/// cursors using this command allows multiple SQL statements to be
/// opened at once. Optionally a different server can be specified for each
/// cursor by passing the server name to this command as well. If no
/// server is specified, the current server will be used. Note that it
/// is important to close all cursors at the end using SQL_CLOSE_CURSOR_STMT.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-07 by Aaron Gulack
/// @See		 SQL_CLOSE_CURSOR_STMT SQL_SET_CURRENT_CURSOR_STMT SQL_GET_CURRENT_CURSOR_STMT
///
/// @Syntax SQL_OPEN_CURSOR_STMT [of {server}] to {variable}
/// @Param server			Name of the server (optional)
/// @Param variable			Variable to hold the returned cursor handle
///
/// @Example
///
/// Integer iCursor1 iCursor2 iCustomer
/// String  sName
/// Number  nOrderTotal
///
/// SQL_OPEN_CURSOR_STMT to iCursor1
/// SQL_SET_STMT         to "SELECT CUSTOMER_NUMBER,NAME FROM CUSTOMER "
/// SQL_APPEND_STMT      to "ORDER BY NAME "
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
/// Repeat
///     SQL_SET_CURRENT_CURSOR_STMT TO iCursor1
///     SQL_FETCH_NEXT_ROW INTO iCustomer sName
///     If (Found) Begin
///        SQL_OPEN_CURSOR_STMT to iCursor2
///        SQL_SET_STMT         to "SELECT SUM(ORDER_TOTAL) FROM ORDERHEA "
///        SQL_APPEND_STMT      to ("WHERE CUSTOMER_NUMBER = " + Trim(iCustomer))
///        SQL_PREPARE_STMT
///        SQL_EXECUTE_STMT
///        SQL_FETCH_NEXT_ROW INTO nOrderTotal
///        If (Found and nOrderTotal > 0) Begin
///            Showln "Customer : " iCustomer "-" sName " - Total: " nOrderTotal
///        End
///        SQL_CLOSE_CURSOR_STMT to Cursor2
///
///        Indicate Found True
///     End
/// Until (Not(Found))
///
/// SQL_CLOSE_CURSOR_STMT to Cursor1
#COMMAND SQL_OPEN_CURSOR_STMT "OF""TO""" R
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        #IFSAME !1 of
            Move !2 to MertechInc_sArg1
            #CHECK !3 "TO"
        #ELSE
            Move "" to MertechInc_sArg1
            #CHECK !1 "TO"
        #ENDIF

        Call_Driver 0 MertechInc_DriverName Function CALLDRV_OPEN_EMBEDDED_CURSOR CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
        #IFSAME !1 of
            Move MertechInc_iRet to !4
        #ELSE
            Move MertechInc_iRet to !2
        #ENDIF
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_CLOSE_CURSOR_STMT
/// @Description This command closes the specified cursor that was created
/// from SQL_OPEN_CURSOR_STMT. It is good practice to close all cursors
/// once the statements associated with them are complete.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-07 by Aaron Gulack
/// @See 		 SQL_OPEN_CURSOR_STMT SQL_SET_CURRENT_CURSOR_STMT SQL_GET_CURRENT_CURSOR_STMT
///
/// @Syntax SQL_CLOSE_CURSOR_STMT [of {server}] to {variable}
/// @Param server			Name of the server (optional)
/// @Param variable			Cursor handle to close
///
/// @Example
///
/// SQL_OPEN_CURSOR_STMT to hCursor1
///
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active' "
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
///
/// SQL_OPEN_CURSOR_STMT to hCursor2
///
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Inactive' "
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
///
/// Repeat
///     SQL_SET_CURRENT_CURSOR_STMT to hCursor1
///     SQL_FETCH_NEXT_ROW INTO  sID sFirstName sLastName
///     If (Found) Begin
///        Showln "Active : " sID "- " sFirstName sLastName
///     End
///
///     SQL_SET_CURRENT_CURSOR_STMT to hCursor2
///     SQL_FETCH_NEXT_ROW into sId sFirstName sLastName
///     If (Found) Begin
///         Showln "Inactive : " sID "- " sFirstName sLastName
///     End
/// Until (FindErr)
///
/// SQL_CLOSE_CURSOR_STMT to hCursor1
/// SQL_CLOSE_CURSOR_STMT to hCursor2
#COMMAND SQL_CLOSE_CURSOR_STMT "OF""TO""" R
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        #IFSAME !1 of
            Move !2 to MertechInc_sArg1
            #CHECK !3 "TO"
            Move !4 to MertechInc_iArg
        #ELSE
            Move "" to MertechInc_sArg1
            #CHECK !1 "TO"
            Move !2 to MertechInc_iArg
        #ENDIF

        Call_Driver 0 MertechInc_DriverName Function CALLDRV_CLOSE_EMBEDDED_CURSOR CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_SET_CURRENT_CURSOR_STMT
/// @Description This command is used to open a cursor to be used for an
/// SQl statement. The cursor must be created using the SQL_OPEN_CURSOR_STMT,
/// but once it has been created, this command can easily switch between
/// cursors as desired. Optionally a different server can be specified for each
/// cursor by passing the server name to this command as well. If no
/// server is specified, the current server will be used. Note that it
/// is important to close all cursors at the end using SQL_CLOSE_CURSOR_STMT.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-07 by Aaron Gulack
/// @See		 SQL_OPEN_CURSOR_STMT SQL_CLOSE_CURSOR_STMT SQL_GET_CURRENT_CURSOR_STMT
///
/// @Syntax SQL_SET_CURRENT_CURSOR_STMT [of {server}] to {variable}
/// @Param server			Name of the server (optional)
/// @Param variable			Cursor handle to use
///
/// @Example
///
/// SQL_OPEN_CURSOR_STMT to hCursor1
///
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Active' "
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
///
/// SQL_OPEN_CURSOR_STMT to hCursor2
///
/// SQL_SET_STMT to "SELECT * FROM CUSTOMER WHERE STATUS = 'Inactive' "
/// SQL_PREPARE_STMT
/// SQL_EXECUTE_STMT
///
/// Repeat
///     SQL_SET_CURRENT_CURSOR_STMT to hCursor1
///     SQL_FETCH_NEXT_ROW INTO  sID sFirstName sLastName
///     If (Found) Begin
///        Showln "Active : " sID "- " sFirstName sLastName
///     End
///
///     SQL_SET_CURRENT_CURSOR_STMT to hCursor2
///     SQL_FETCH_NEXT_ROW into sId sFirstName sLastName
///     If (Found) Begin
///         Showln "Inactive : " sID "- " sFirstName sLastName
///     End
/// Until (FindErr)
///
/// SQL_CLOSE_CURSOR_STMT to hCursor1
/// SQL_CLOSE_CURSOR_STMT to hCursor2
#COMMAND SQL_SET_CURRENT_CURSOR_STMT "OF""TO""" R
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        #IFSAME !1 of
            Move !2 to MertechInc_sArg1
            #CHECK !3 "TO"
            Move !4 to MertechInc_iArg
        #ELSE
            Move "" to MertechInc_sArg1
            #CHECK !1 "TO"
            Move !2 to MertechInc_iArg
        #ENDIF

        Call_Driver 0 MertechInc_DriverName Function CALLDRV_SET_CURRENT_EMBEDDED_CURSOR CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_GET_CURRENT_CURSOR_STMT
/// @Description This command returns the current active cursor being
/// used. The cursor is returned to the specified variable.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-07 by Aaron Gulack
/// @See SQL_OPEN_CURSOR_STMT SQL_CLOSE_CURSOR_STMT SQL_SET_CURRENT_CURSOR_STMT
///
/// @Syntax SQL_GET_CURRENT_CURSOR_STMT [of {server}] to {variable}
/// @Param server			Name of the server (optional)
/// @Param variable 	    Variable to hold the current cursor handle
///
/// @Example
/// SQL_GET_CURRENT_CURSOR_STMT to hCursor
#COMMAND SQL_GET_CURRENT_CURSOR_STMT "OF""TO""" R
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        #IFSAME !1 of
            Move !2 to MertechInc_sArg1
            #CHECK !3 "TO"
        #ELSE
            Move "" to MertechInc_sArg1
            #CHECK !1 "TO"
        #ENDIF

        Call_Driver 0 MertechInc_DriverName Function CALLDRV_GET_CURRENT_EMBEDDED_CURSOR CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
        #IFSAME !1 of
            Move MertechInc_iRet to !4
        #ELSE
            Move MertechInc_iRet to !2
        #ENDIF
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_SET_MAX_CURSORS_STMT
/// @Description Sets the maximum number of simultaneous cursors allowed.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-07 by Aaron Gulack
/// @See
///
/// @Syntax SQL_SET_MAX_CURSORS_STMT [of {server}] to {variable}
/// @Param server			Name of the server (optional)
/// @Param variable			Maximum number of cursors allowed
///
/// @Example
/// SQL_SET_MAX_CURSORS_STMT to 50
#COMMAND SQL_SET_MAX_CURSORS_STMT "OF""TO""" R
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        #IFSAME !1 of
            Move !2 to MertechInc_sArg1
            #CHECK !3 "TO"
            Move !4 to MertechInc_iArg
        #ELSE
            Move "" to MertechInc_sArg1
            #CHECK !1 "TO"
            Move !2 to MertechInc_iArg
        #ENDIF

        Call_Driver 0 MertechInc_DriverName Function CALLDRV_SET_MAX_EMBEDDED_CURSOR CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_GET_MAX_CURSORS_STMT
/// @Description Retrieves the maximum number of cursors allowed.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-07 by Aaron Gulack
/// @See
///
/// @Syntax SQL_GET_MAX_CURSORS_STMT [of {server}] to {variable}
/// @Param server			Name of the server (optional)
/// @Param variable			Maximum number of cursors allowed
///
/// @Example
/// SQL_GET_MAX_CURSORS_STMT to iCursors
#COMMAND SQL_GET_MAX_CURSORS_STMT "OF""TO""" R
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        #IFSAME !1 of
            Move !2 to MertechInc_sArg1
            #CHECK !3 "TO"
        #ELSE
            Move "" to MertechInc_sArg1
            #CHECK !1 "TO"
        #ENDIF

        Call_Driver 0 MertechInc_DriverName Function CALLDRV_GET_MAX_EMBEDDED_CURSOR CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
        #IFSAME !1 OF
            MOVE MertechInc_iRet TO !4
        #ELSE
            MOVE MertechInc_iRet TO !2
        #ENDIF
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_SET_LOCAL_TD_PATH
/// @Description Sets the directory where the driver will find the LOCAL TD files.
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2009-08-19 By Ian Smith
///
/// @Syntax SQL_SET_LOCAL_TD_PATH TO <DirectoryPath|Variable>
/// @Param DirectoryPath   Directory path were the TD files are to be located.
#COMMAND SQL_SET_LOCAL_TD_PATH "TO" R
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Move !2 to MertechInc_sArg1

        Call_Driver 0 MertechInc_DriverName Function CALLDRV_LOCAL_TD_PATH CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 0 RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_GET_LOCAL_TD_PATH
/// @Description Gets the directory where the driver is looking for the LOCAL TD files.
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2009-08-19 By Ian Smith
///
/// @Syntax SQL_SET_LOCAL_TD_PATH TO <DirectoryPath|Variable>
/// @Param DirectoryPath   Directory path were the driver is looking
#COMMAND SQL_GET_LOCAL_TD_PATH "TO" R
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_LOCAL_TD_PATH CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank 1 RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
        ELSE MOVE MertechInc_sArg1 TO !2
    End
#ENDCOMMAND

//=============================================================================
/// @Name        GET_DRIVER_REVISION
/// @Description This command will put the current version (decimals included)
/// of the driver associated with the current workspace into the specified
/// variable.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See 		 GET_DRIVER_MAJOR_REVISION
///
/// @Syntax GET_DRIVER_REVISION to {variable}
/// @Param variable			String variable to hold the returned version
///
/// @Example
/// GET_DRIVER_REVISION to sVersion
#COMMAND GET_DRIVER_REVISION "TO" R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Get MertechInc_Pre_Size_String 255 to !2
        Call_Driver 0 MertechInc_DriverName Function 0 CALLBACK 0 PASSING MertechInc_Blank !2 0 RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        GET_DRIVER_MAJOR_REVISION
/// @Description This command will put the current version (no decimals)
/// of the driver associated with the current workspace into the specified
/// variable.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See 		 GET_DRIVER_REVISION
///
/// @Syntax GET_DRIVER_MAJOR_REVISION to {variable}
/// @Param variable			String variable to hold the returned version
///
/// @Example
/// GET_DRIVER_MAJOR_REVISION to sVersion
#COMMAND GET_DRIVER_MAJOR_REVISION "TO" R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Get MertechInc_Pre_Size_String 255 to !2
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_LICENSE_ENVIRONMENT_SET CALLBACK 0 PASSING MertechInc_Blank !2 CALLDRV_MAJOR_REVISION RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        GET_DRIVER_LICENSE_EXPIRATION_TIME
/// @Description This command is used to find out how long until a
/// specific temporary license for a driver expires. If 0 is returned,
/// then the license is not a temporary license. If -1 is returned, then
/// the license has already expired. Otherwise, the number returned
/// is the number of days until the license will expire.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-02 Aaron Gulack
/// @See 		 GET_DRIVER_LICENSE_PATH SET_DRIVER_LICENSE_EXPIRATION_WARNING
///
/// @Syntax GET_DRIVER_LICENSE_EXPIRATION_TIME to {variable}
/// @Param variable			Variable to hold the days until expiration
///
/// @Example
/// GET_DRIVER_LICENSE_EXPIRATION_TIME to iExpire
/// Showln iExpire
#COMMAND GET_DRIVER_LICENSE_EXPIRATION_TIME "TO" R .
    DO_GETFILENUMBER_DRIVERNAME 0

    If (MertechInc_FileNumber <> -1) Begin
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_LICENSE_ENVIRONMENT_SET CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank CALLDRV_TIME_TO_LIC_EXPIRATION RESULT MertechInc_iRet
        Move MertechInc_iRet to !2
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SET_DRIVER_LICENSE_EXPIRATION_WARNING
/// @Description This command is used to set a custom warning message to
/// be displayed when a temporary license for a driver is close to expiring.
/// Note that since the license evaluation is done during Login and before
/// any open calls, this command should be called before either of those.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See 		 GET_DRIVER_LICENSE_PATH GET_DRIVER_LICENSE_EXPIRATION_TIME
///
/// @Syntax SET_DRIVER_LICENSE_EXPIRATION_WARNING to {variable}
/// @Param variable			New warning message for expiring license
///
/// @Example
/// SET_DRIVER_LICENSE_EXPIRATION_WARNING to "Your license is about to expire."
/// Login "localhost" "" "" "sql_drv"
#COMMAND SET_DRIVER_LICENSE_EXPIRATION_WARNING "TO" R .
    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Move !2 to MertechInc_sArg1
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_LICENSE_ENVIRONMENT_SET CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank CALLDRV_LICENSE_EXPIRATION_WARN RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

//=============================================================================
/// @Name        GET_DRIVER_LICENSE_PATH
/// @Description This command will return the current path of the license
/// associated with the driver.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-01 by Aaron Gulack
/// @See 	  	 SET_DRIVER_LICENSE_EXPIRATION_WARNING GET_DRIVER_LICENSE_EXPIRATION_TIME
///
/// @Syntax GET_DRIVER_LICENSE_PATH to {variable}
/// @Param variable			Variable to hold the path of the license
#COMMAND GET_DRIVER_LICENSE_PATH "TO" R .
    Get MertechInc_GET_DRIVER_LICENSE_PATH to !2
#ENDCOMMAND

Function MertechInc_GET_DRIVER_LICENSE_PATH Global Returns String
    String sReturnValue

    DO_GETFILENUMBER_DRIVERNAME 0
    If (MertechInc_FileNumber <> -1) Begin
        Get MertechInc_Pre_Size_String 4096 to sReturnValue
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_LICENSE_ENVIRONMENT_SET CALLBACK 0 PASSING sReturnValue MertechInc_Blank CALLDRV_LICENSE_PATH RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End

    Function_Return sReturnValue
End_Function

//=============================================================================
/// @Name        SET_DATABASE_PORT
/// @Description This command is used to dynamically change the port
/// number to use for all TCP/IP connections to the server. Note that
/// the port is used for the current session only.
///
/// @Assumptions The port is valid and available
/// @Status      Public
/// @Drivers     MySQLFlex PgFlex
/// @VersionNote Last Revised: 2013-10-08 by Aaron Gulack
/// @See 		 GET_DATABASE_PORT
///
/// @Syntax SET_DATABASE_PORT of {constant} to {variable}
/// @Param constant			MYSQL or PGSQL
/// @Param variable			Port number to use to connect to server
///
/// @Example
/// GET_DATABASE_PORT of MYSQL to 1433
#COMMAND SET_DATABASE_PORT "OF" "MYSQL""PGSQL" "TO" R .
    #IFSAME !2 TO MYSQL
        MOVE MDSMySQL TO MertechInc_DriverName
    #ELSE
        MOVE MDSPGSQL TO MertechInc_DriverName
    #ENDIF

    MOVE !4 TO MertechInc_sArg1
    CALL_DRIVER 0 MertechInc_DriverName FUNCTION CALLDRV_LICENSE_ENVIRONMENT_SET CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank CALLDRV_SET_DB_PORT RESULT MertechInc_iRet
    If MertechInc_iRet EQ -1 INDICATE ERR True
#ENDCOMMAND

//=============================================================================
/// @Name        GET_DATABASE_PORT
/// @Description This command returns the TCP/IP port used to connect
/// to the server.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     MySQLFlex PgFlex
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See		 SET_DATABASE_PORT
///
/// @Syntax GET_DATABASE_PORT of {MYSQL/PGSQL} to {variable}
/// @Param variable			Variable to hold the TCP/IP port number
///
/// @Example
/// GET_DATABASE_PORT of MYSQL to iPort
#COMMAND GET_DATABASE_PORT "OF" "MYSQL""PGSQL" "TO" R .
    #IFSAME !2 TO MYSQL
        MOVE MDSMySQL TO MertechInc_DriverName
    #ELSE
        MOVE MDSPGSQL TO MertechInc_DriverName
    #ENDIF

    MOVE (REPEAT(" ",255)) to !4
    CALL_DRIVER 0 MertechInc_DriverName FUNCTION CALLDRV_LICENSE_ENVIRONMENT_SET CALLBACK 0 PASSING !4 MertechInc_Blank CALLDRV_GET_DB_PORT RESULT MertechInc_iRet
    If MertechInc_iRet EQ -1 INDICATE ERR True
#ENDCOMMAND

//=============================================================================
/// @Name        GET_SERIAL_NUMBER
/// @Description This command returns the serial number associated with
/// the current driver's license.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-07 by Aaron Gulack
/// @See
///
/// @Syntax GET_SERIAL_NUMBER to {variable}
/// @Param variable			Variable to hold the driver's serial number
///
/// @Example
/// GET_SERIAL_NUMBER to iSerial
#COMMAND GET_SERIAL_NUMBER "TO" R .
    DO_GETFILENUMBER_DRIVERNAME 0

    MOVE (REPEAT(" ",255)) to !2
    CALL_DRIVER 0 MertechInc_DriverName FUNCTION CALLDRV_LICENSE_ENVIRONMENT_SET CALLBACK 0 PASSING MertechInc_Blank !2 CALLDRV_SERIAL_NUMBER RESULT MertechInc_iRet
    IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
#ENDCOMMAND

//=============================================================================
/// @Name        SET_DATABASE_SOCKET
/// @Description This command is used to set the socket used to connect
/// to the server when running an application under Linux/Unix.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     MySQLFlex
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See  		 GET_DATABASE_SOCKET
///
/// @Syntax SET_DATABASE_SOCKET of MYSQL to {variable}
/// @Param variable			Full name of the socket
#COMMAND SET_DATABASE_SOCKET "OF" "MYSQL" "TO" R .
    MOVE MDSMySQL TO MertechInc_DriverName

    MOVE !4 TO MertechInc_sArg1
    CALL_DRIVER 0 MertechInc_DriverName FUNCTION CALLDRV_LICENSE_ENVIRONMENT_SET CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank CALLDRV_SET_DB_SOCKET RESULT MertechInc_iRet
    If MertechInc_iRet EQ -1 INDICATE ERR True
#ENDCOMMAND

//=============================================================================
/// @Name        GET_DATABASE_SOCKET
/// @Description This command returns the name of the socket used to
/// connect to the server when running an application under Linux/Unix.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     MySQLFlex
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See		 SET_DATABASE_SOCKET
///
/// @Syntax SET_DATABASE_SOCKET of MYSQL to {variable}
/// @Param variable			Variable to hold the full socket name
#COMMAND GET_DATABASE_SOCKET "OF" "MYSQL" "TO" R .
    MOVE MDSMySQL TO MertechInc_DriverName

    MOVE (REPEAT(" ",255)) to !4
    CALL_DRIVER 0 MertechInc_DriverName FUNCTION CALLDRV_LICENSE_ENVIRONMENT_SET CALLBACK 0 PASSING !4 MertechInc_Blank CALLDRV_GET_DB_SOCKET RESULT MertechInc_iRet
    If MertechInc_iRet EQ -1 INDICATE ERR True
#ENDCOMMAND

//=============================================================================
/// @Name        SET_AUTHENTICATION_MODE
/// @Description This command is used to control what mode the user logs
/// in as. When DEFAULT is passed, the user will be logged in with the
/// default privileges given to it. When SYSDBA is passed, the user will
/// be logged in with the roles assigned to the sysdba user, most likely
/// full control over the database.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     OraFlex
/// @VersionNote Last Revised: 2013-10-07 by Aaron Gulack
/// @See
///
/// @Syntax SET_AUTHENTICATION_MODE of Oracle to {SYSDBA/DEFAULT}
///
/// @Example
/// SET_AUTHENTICATION_MODE of Oracle to DEFAULT
#COMMAND SET_AUTHENTICATION_MODE "OF" "ORACLE" "TO" "SYSDBA""DEFAULT" .
    MOVE ORAFlex TO MertechInc_DriverName

    #IFSAME !4 SYSDBA
        MOVE 1 to MertechInc_sArg1
    #ELSE
        MOVE 0 to MertechInc_sArg1
    #ENDIF
    CALL_DRIVER 0 MertechInc_DriverName FUNCTION CALLDRV_LICENSE_ENVIRONMENT_SET CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank CALLDRV_SET_AS_SYSDBA RESULT MertechInc_iRet
    IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_ESCAPE_STRING
/// @Description This command is used to properly escape strings before
/// they are used in embedded SQL statements. This can be extremely
/// important when you do not have full control of the strings being passed
/// to the SQL statement as this will ensure that the strings are properly
/// quoted.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See
///
/// @Syntax SQL_ESCAPE_STRING of {string} to {variable}
/// @Param string		The string to be escaped.
/// @Param variable  	Variable to hold the newly escaped string
///
/// @Example
/// SQL_ESCAPE_STRING of "They said to me, 'hello'." to sEscaped
#COMMAND SQL_ESCAPE_STRING "OF" R "TO" R
    Get SQLESCAPESTRING !2 to !4
#ENDCOMMAND

Function SQLESCAPESTRING Global String sData Returns String
    String sReturnData

    DO_GETFILENUMBER_DRIVERNAME 0

    If (MertechInc_FileNumber <> -1) Begin
        Get MertechInc_Pre_Size_String 0 to sReturnData
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_ESCAPE_STRING CALLBACK 0 PASSING sData sReturnData 0 RESULT MertechInc_iRet
    End

    Function_Return sReturnData
End_Function

//=============================================================================
/// @Name        DIRECT_PATH_LOAD
/// @Description
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     OraFlex
/// @VersionNote Last Revised: 2009-09-21 By Ian Smith
/// @See
#COMMAND DIRECT_PATH_LOAD "OF" R "FROM" R
    DO_GETFILENUMBER_DRIVERNAME 0

    If (MertechInc_DriverName EQ ORAFlex) Begin
        [~Err] Move !4.File_Number to MertechInc_iArg
        Call_Driver !2.File_Number ORAFlex Function CALLDRV_DIRECT_PATH_LOAD CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
        #IF (!0=5)
            #CHECK !5 RLGU#
            [~Err] Move MertechInc_iRet to !5
            [ Err] Move 0        to !5
        #ENDIF
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_INITIALIZE_SEQUENCE
/// @Description This command is used to initialize all auto increment
/// columns, or sequences in Oracle, of the specified table to be the
/// highest number plus one. This is useful when inserting a large amount
/// of records in the table and the sequence is not being updated because
/// the auto incremented column is being manually filled.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     OraFlex PgFlex
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See
///
/// SQL_INITIALIZE_SEQUENCE of {FileNumber}
/// @Param FileNumber			The file number
#COMMAND SQL_INITIALIZE_SEQUENCE "OF" R .
    DO_GETFILENUMBER_DRIVERNAME !2

    IF (MertechInc_DriverName EQ ORAFlex OR MertechInc_DriverName EQ PgFlex) BEGIN
        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function CALLDRV_INITIALIZE_SEQUENCE CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    End
#ENDCOMMAND

//=============================================================================
/// @Name        LOB_APPEND
/// @Description This command is used to append data to an existing LOB
/// column in the database. When called, the data corresponding field
/// in the buffer is appended to the respective column in the database.
/// This can be very useful when saving data that exceeds VDF size limits
/// but falls within the limits of the SQL database. Note that this command
/// must write to a file that is active and locked. Also the save is handled
/// within the command so no extra calls are needed to save the changes made.
///
/// @Assumptions The field being used is a LOB field
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See 		 SQL_LOB_ADD_CHUNK
///
/// @Syntax LOB_APPEND of {FileName} {FieldNumber}
/// @Param FileName			Name of the file containing the LOB column
/// @Param FieldNumber		Number of the field being appended to
///
/// @Example
/// Clear Customer
/// Find Gt Customer By Index.1
///
/// Direct_Input 'C:\Mertech.xml'
/// Lock
///    Find Eq Customer by Recnum
///
///    Read_Block Customer.Comments 16384
///    SQL_LOB_WRITE of Customer 13 // Customer.Comments
///    Repeat
///        Read_Block Customer.Comments 16384
///        SQL_LOB_APPEND of Customer 13 // Customer.Comments
///    Until (SeqEOF)
/// Unlock
///
/// Close_Input
/// Find Eq Customer By Recnum
/// SQL_LOB_LENGTH of Customer 13 to iLength
/// Showln 'Length: ' iLength
#COMMAND LOB_APPEND "OF" R R .
    DO_GETFILENUMBER_DRIVERNAME !2

    If (MertechInc_DriverName EQ SQLFLEX or MertechInc_DriverName EQ ORAFLEX  or MertechInc_DriverName EQ MDSMySQL or MertechInc_DriverName EQ MDSPgSQL ) Begin
        Move !3 To MertechInc_iArg

        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function CALLDRV_APPEND_LOB CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    End
#ENDCOMMAND

#REPLACE SQL_LOB_APPEND LOB_APPEND

//=============================================================================
/// @Name        LOB_LENGTH
/// @Description This command returns the length of the data in the
/// specified column. This command must be used after a proper FIND to
/// ensure that a valid record is in the buffer. This can be a useful
/// command for checking if uploaded data exceeds size limits.
///
/// @Assumptions The field being used is a LOB field
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See 		 SQL_GET_LOB_LENGTH
///
/// @Syntax LOB_LENGTH of {FileName} {FieldNumber} to {variable}
/// @Param FileName			Name of the file
/// @Param FieldNumber		Number of the LOB field
/// @Param variable			Variable to hold the length
///
/// @Example
/// Clear Customer
/// Find Gt Customer By Index.1
/// SQL_LOB_LENGTH of Customer 13 to iLength
/// Showln 'Length: ' iLength
#COMMAND LOB_LENGTH "OF" R R "TO" R .
    DO_GETFILENUMBER_DRIVERNAME !2

    If (MertechInc_DriverName EQ SQLFLEX or MertechInc_DriverName EQ ORAFLEX  or MertechInc_DriverName EQ MDSMySQL or MertechInc_DriverName EQ MDSPgSQL ) Begin
        Move !3 to MertechInc_iArg

        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function CALLDRV_LENGTH_LOB CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
        MOVE MertechInc_iRet to !5
    End
#ENDCOMMAND

#Replace SQL_LOB_LENGTH LOB_LENGTH

//=============================================================================
/// @Name        LOB_READ
/// @Description This command reads a chunk of data from a specified LOB
/// column, moving it into its corresponding field buffer. Because the
/// chunk will be moved into the field buffer, it can only be as large as
/// the buffer allows. To account for this, the constants FIRST or NEXT
/// are passed as well indicating whether to grab the first chunk for
/// the buffer or the next. Each chunk grabbed will be as large as allowed.
/// All these things considered, when reading data larger than the field
/// buffer, it is good practice to perform the read in a loop, adding the
/// length each time. Another optional parameter that can be passed is a
/// variable that will store the length of the chunk. Note that a LOB read
/// must be done after a successful find on the record.
///
/// @Assumptions The field being used is a LOB field
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See 		 SQL_GET_LOB SQL_GET_LOB_CHUNK
///
/// @Syntax LOB_READ of {FileName} {FieldNumber} {FIRST/NEXT} [{length}]
/// @Param FileName			Name of the file containing the LOB field
/// @Param FieldNumber		Number of the field being read from
/// @Param FIRST			Reads the first chunk of data
/// @Param NEXT				Reads the next chuck of data (if larger than buffer limit)
/// @Param length			Variable to hold the chunk length (optional)
///
/// @Example
/// Direct_Output ('binary:Mertech.pdf')
///
/// Clear customer
/// Find Gt customer by Index.1
/// SQL_LOB_LENGTH of customer 13 to liLength
///
/// While (liLength > 0)
///     Write customer.comments
///     SQL_LOB_READ of customer 13 Next liLength
/// Loop
///
/// Close_Output
#COMMAND LOB_READ "OF" R R "FIRST""NEXT"
    DO_GETFILENUMBER_DRIVERNAME !2

    If (MertechInc_DriverName EQ SQLFLEX or MertechInc_DriverName EQ ORAFLEX  or MertechInc_DriverName EQ MDSMySQL or MertechInc_DriverName EQ MDSPgSQL ) Begin
        Move !3 to MertechInc_iArg

        #IFSAME !4 FIRST
            MOVE "0" TO MertechInc_sArg1
        #ELSE
            MOVE "1" TO MertechInc_sArg1
        #ENDIF

        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function CALLDRV_READ_LOB CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
        #IF (!0=5)
            #CHECK !5 RLGU#
            IF MertechInc_iRet EQ -1 MOVE 0 TO !5
            ELSE MOVE MertechInc_iRet TO !5
        #ENDIF
    END
#ENDCOMMAND

#Replace SQL_LOB_READ LOB_READ

//=============================================================================
/// @Name        LOB_WRITE
/// @Description This command is used to write data to a LOB column.
/// By passing the file name and field number of the LOB column, this
/// command will take the current value of the respective field in
/// the field buffer, write it to the database and save it. Any data
/// currently in that field will be overridden by the data from the
/// buffer. Note that this command must write to a file that is active
/// and locked. Also this command handles the save so no extra calls
/// are needed to save the changes.
///
/// @Assumptions The field being used is a LOB field
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See 		 SQL_SET_LOB SQL_ADD_LOB_CHUNK
///
/// @Syntax LOB_WRITE of {FileName} {FieldNumber}
/// @Param FileName			Name of the file containing the LOB field
/// @Param FieldNumber		Number of the field being written to
///
/// @Example
/// Clear Customer
/// Find Gt Customer By Index.1
///
/// Direct_Input 'C:\Mertech.xml'
/// Lock
///    Find Eq Customer by Recnum
///
///    Read_Block Customer.Comments 16384
///    SQL_LOB_WRITE of Customer 13 // Customer.Comments
///    Repeat
///        Read_Block Customer.Comments 16384
///        SQL_LOB_APPEND of Customer 13 // Customer.Comments
///    Until (SeqEOF)
/// Unlock
/// Close_Input
///
/// Find Eq Customer By Recnum
/// SQL_LOB_LENGTH of Customer 13 to iLength
/// Showln 'Length: ' iLength
#COMMAND LOB_WRITE "OF" R R .
    DO_GETFILENUMBER_DRIVERNAME !2

    If (MertechInc_DriverName EQ SQLFLEX or MertechInc_DriverName EQ ORAFLEX  or MertechInc_DriverName EQ MDSMySQL or MertechInc_DriverName EQ MDSPgSQL ) Begin
        Move !3 to MertechInc_iArg
        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function CALLDRV_WRITE_LOB CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    End
#ENDCOMMAND

#Replace SQL_LOB_WRITE LOB_WRITE

//=============================================================================
/// @Name        LOB_LOADFROMFILE
/// @Description This command loads an external file into a specified LOB
/// column. After specifying the file name and field number, the path and
/// file must then be passed respectively. When using Oracle, instead of
/// passing the directory, a directory alias must be passed. This alias
/// can be created using a "CREATE DIRECTORY" statement in SQL. For more
/// information on setting this directory alias, see the Oracle help.
/// For other servers, the file must be a local file available to the
/// application that is calling the command. Note that this command must
/// write to a file that is active and locked. Also this command handles
/// the save so no extra calls are needed to save the changes.
///
/// @Assumptions The field being used is a LOB field
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See 		 LOB_APPEND LOB_LENGTH LOB_WRITE LOB_READ LOB_ERASE LOB_TRUNCATE FLUSH_LOB_BUFFER
///
/// @Syntax LOB_LOADFROMFILE of {FileName} {FieldNumber} From {path} {file}
/// @Param FileName			Name of the file containing the LOB column
/// @Param FieldNumber		Number of the LOB column being used
/// @Param path			  	The path of the file, excluding the file name
/// @Param file				The name of the file, including the extension
///
/// @Example
/// Clear Customer
/// Find Gt Customer By Index.1
/// Lock
///    Find Eq Customer by Recnum
///    LOB_TRUNCATE OF customel 13 to 0 // Customer.Comments
///    Saverecord Customer
///    // Directory name is case sensitive.
///    // Make sure the name case matches
///    LOB_LOADFROMFILE OF customel 13 FROM "C:\Mertech\FilesToLoad" "Mertech.XML"
/// Unlock
#COMMAND LOB_LOADFROMFILE "OF" R R "FROM" R R .
    DO_GETFILENUMBER_DRIVERNAME !2

    If (MertechInc_DriverName EQ SQLFLEX or MertechInc_DriverName EQ ORAFLEX  or MertechInc_DriverName EQ MDSMySQL or MertechInc_DriverName EQ MDSPgSQL ) Begin
        Move !3 to MertechInc_iArg
        MOVE !5 TO MertechInc_sArg1
        Move !6 to MertechInc_sArg2

        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function CALLDRV_LOADFROMFILE_LOB CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 MertechInc_iArg RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    End
#ENDCOMMAND

#Replace SQL_LOB_LOADFROMFILE LOB_LOADFROMFILE

//=============================================================================
/// @Name        LOB_ERASE
/// @Description This command is used to erase a portion of data from a
/// LOB column. For text fields, the portion of data to be erased is
/// replaced with white space, and in binary fields, with 0X0. To erase
/// a portion of the data, pass the length to erase as well as the number
/// to offset from. For this command to work properly, it must be done
/// after a valid find. Note that the save is handled inside this command
/// so no extra commands are needed to save the changes.
///
/// @Assumptions The field being used is a LOB field
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See LOB_APPEND LOB_LENGTH LOB_WRITE LOB_READ LOB_LOADFROMFILE LOB_ERASE LOB_TRUNCATE FLUSH_LOB_BUFFER
///
/// @Syntax LOB_ERASE OF {FileName} {FieldNumber} {length} {offset}
/// @Param FileName			Name of the file containing the LOB column
/// @Param FieldNumber		Number of the LOB column being erased
/// @Param Length			Length of chunk to erase from column
/// @Param offset			Starting position for erase
///
/// @Example
/// Clear customer
/// Find Gt customer by Recnum
/// Lock
/// Find Eq customer by Recnum
/// LOB_LENGTH OF customer 13 to liTotalLength
/// LOB_ERASE  OF customer 13    liTotalLength 1
/// Unlock
#COMMAND LOB_ERASE "OF" R R R R .
    DO_GETFILENUMBER_DRIVERNAME !2

    If (MertechInc_DriverName EQ SQLFLEX or MertechInc_DriverName EQ ORAFLEX  or MertechInc_DriverName EQ MDSMySQL or MertechInc_DriverName EQ MDSPgSQL ) Begin
        Move !3 to MertechInc_iArg
        MOVE !4 TO MertechInc_sArg1
        Move !5 to MertechInc_sArg2

        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function CALLDRV_ERASE_LOB CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 MertechInc_iArg RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    End
#ENDCOMMAND

#Replace SQL_LOB_ERASE LOB_ERASE

//=============================================================================
/// @Name        LOB_TRUNCATE
/// @Description This command is used to trim a LOB column down to a
/// specified length. By passing the table name and column number, the
/// value in the column can then be trimmed down the specified length.
/// This can be a useful command for clearing out a column before entering
/// new data into it. Note that this command must write to a file that is active
/// and locked. Also this command handles the save so no extra calls
/// are needed to save the changes. This command can be used to clear out a field before adding new data
///
/// @Assumptions The field being used is a LOB field
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See 		 LOB_APPEND LOB_LENGTH LOB_WRITE LOB_READ LOB_LOADFROMFILE LOB_ERASE FLUSH_LOB_BUFFER
///
/// @Syntax LOB_TRUNCATE of {FileName} {FieldNumber} to {variable}
/// @Param FileName			Name of the file
/// @Param FieldNumber		The field number
/// @Param length			New length to truncate to
///
/// @Example
/// Clear Customer
/// Find Gt Customer By Index.1
/// Lock
///    Find Eq Customer by Recnum
///    SQL_LOB_TRUNCATE of Customer 13 to 0 // Customer.Comments
///    Saverecord Customer
/// Unlock
#COMMAND LOB_TRUNCATE "OF" R R "TO" R .
    DO_GETFILENUMBER_DRIVERNAME !2

    If (MertechInc_DriverName EQ SQLFLEX or MertechInc_DriverName EQ ORAFLEX  or MertechInc_DriverName EQ MDSMySQL or MertechInc_DriverName EQ MDSPgSQL ) Begin
        Move !3 to MertechInc_iArg
        MOVE !5 TO MertechInc_sArg1

        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function CALLDRV_TRUNCATE_LOB CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

#Replace SQL_LOB_TRUNCATE LOB_TRUNCATE

//=============================================================================
/// @Name        FLUSH_LOB_BUFFER
/// @Description This command currently serves no function.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     MySQLFlex
/// @VersionNote Last Revised: 2013-10-08 by Aaron Gulack
/// @See
///
/// @Syntax FLUSH_LOB_BUFFER of {FileName}
/// @Param FileName			Name of the file
#COMMAND FLUSH_LOB_BUFFER "OF" R
    DO_GETFILENUMBER_DRIVERNAME !2

    IF (MertechInc_DriverName EQ MySQLFlex) BEGIN
        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function CALLDRV_END_SAVERECORD CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    End
#ENDCOMMAND

#Replace SQL_END_SAVERECORD FLUSH_LOB_BUFFER

//=============================================================================
/// @Name        SQL_ENABLE_RECONNECT
/// @Description Allow MySql Driver to auto reconnect after a time-out.
///
/// Driver auto-reconnect feature handles the issue where MySQL
/// will kick off a user after inactivity.
///
/// @Status      Deprecated
/// @Drivers     MySQL
/// @VersionNote Last Revised: 2009-09-11 By Ian Smith
///
/// @Syntax SQL_ENABLE_RECONNECT of <ServerName> to dftrue/dffalse
/// @Param ServerName  Server Name.
///
/// @Usage SQL_ENABLE_RECONNECT Of sServerID To dftrue
#COMMAND SQL_ENABLE_RECONNECT "OF" R "TO" R .
    DO_GETFILENUMBER_DRIVERNAME 0

    MOVE !2 TO MertechInc_sArg1
    IF (MertechInc_DriverName EQ MySQLFlex);
        CALL_DRIVER 0 MertechInc_DriverName FUNCTION CALLDRV_ENABLE_RECONNECT CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank !4 RESULT MertechInc_iRet
    IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
#ENDCOMMAND

//=============================================================================
/// @Name        CALL_MYSQL_STORED_PROCEDURE
/// @Description This command is used to call a stored procedure on the SQL
/// backend. To successfully call a procedure with this command, a string
/// must be passed containing a valid procedure name. In addition, if the
/// procedure takes any arguments, they must also be passed using the constant
/// "passing" along with all of the needed arguments. If the procedure has a
/// return value, then SQL_GET_FUNCTION_RETURN or SQL_FETCH_NEXT_ROW can be
/// used to get the value(s). If an error is found then the indicator "Err"
/// is set to true.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     MySQLFlex
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See		 CALL_STORED_PROCEDURE
///
/// @Syntax CALL_MYSQL_STORED_PROCEDURE {procedure} Passing {argument}
/// @Param procedure		Full name of the procedure
/// @Param argument			Argument to pass (can be multiple)
///
/// @Example
/// CALL_MYSQL_STORED_PROCEDURE "getCustomerStatus" passing sCustomerID sStatus
/// SQL_GET_PROCEDURE_PARAMETER 2 to sStatus
/// Showln sStatus
#REPLACE CALL_MYSQL_STORED_PROCEDURE CALL_STORED_PROCEDURE

//=============================================================================
/// @Name        CALL_MYSQL_STORED_FUNCTION
/// @Description This command is used to execute a function stored in MySQL.
/// This is an alternative to building a function with the SQL_SET_FUNCTION_NAME,
/// SQL_SET_FUNCTION_PARAMETER and SQL_FUNCTION_EXECUTE commands. This command
/// builds and executes the function by setting the full function name, the
/// parameter(s) to pass and the variable to hold the returned value. Note that
/// this command can only return a single value so SQL_SET_FUNCTION_PARAMETER
/// and SQL_SET_FUNCTION_NAME must be used when dealing with multiple return
/// values.
///
/// @Status      Deprecated
/// @Drivers     MySQLFlex
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See		 CALL_STORED_FUNCTION
///
/// @Syntax CALL_MYSQL_STORED_FUNCTION {function} Returns {variable} Passing {argument}
/// @Param function			Full name of the function
/// @Param variable			Variable to hold the returned value
/// @Param argument			Argument to pass (can be multiple)
///
/// @Example
/// CALL_MYSQL_STORED_FUNCTION "getCustomerStatus" Returns sStatus passing sCustomerID
/// Showln sStatus
#COMMAND CALL_MYSQL_STORED_FUNCTION R "RETURNS" R "PASSING"""
    Move 0 to Mertech_iMySQLParam

    #IF (!0>4)
        SQL_SET_FUNCTION_NAME !1 NUMPAR (!0-4)
        DO_SET_ALL_FUNCTION_PARAMETERS !5 !6 !7 !8 !9
    #ELSE
        SQL_SET_FUNCTION_NAME !1 NUMPAR 0
    #ENDIF

    SQL_PROCEDURE_EXECUTE

    SQL_GET_FUNCTION_RETURN to !3
#ENDCOMMAND

//=============================================================================
/// @Name        DO_SET_ALL_FUNCTION_PARAMETERS
/// @Description Sets the parameters for a MySQL stored function call.
///
/// @Assumptions
/// @Status      Internal
/// @Drivers     MySQLFlex
/// @VersionNote Last Revised: 2009-09-21 By Ian Smith
/// @See
///
/// @Syntax DO_SET_ALL_FUNCTION_PARAMETERS [sParam1 [sParam2 . sParamn]]
/// @Param sParam1.n    Parameters for the stored function
#COMMAND DO_SET_ALL_FUNCTION_PARAMETERS
    Increment Mertech_iMySQLParam
    SQL_SET_FUNCTION_PARAMETER Mertech_iMySQLParam to !1 IN
    #IF !0>1
        DO_SET_ALL_FUNCTION_PARAMETERS !2 !3 !4 !5 !6 !7 !8 !9
    #ENDIF
#ENDCOMMAND

//=============================================================================
/// @Name        GET_NO_AVAILABLE_SQLSERVERS
/// @Description This command is used to get the number of available MSSQL
/// servers detected in the network. When used with GET_SQLSERVER_NAME,
/// all the available server names can be easily retrieved.
///
/// @Assumptions SQL Server Browser Service is started and firewall is configured properly
/// @Status      Public
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See 		 GET_SQLSERVER_NAME
///
/// @Syntax GET_NO_AVAILABLE_SQLSERVERS to {variable}
/// @Param variable			Variable to hold number of servers
///
/// @Example
/// GET_NO_AVAILABLE_SQLSERVERS to iServers
///
/// While (i <= iServers)
///     GET_SQLSERVER_NAME i to sServer
///     Showln sServer
///     Increment i
/// Loop
#COMMAND GET_NO_AVAILABLE_SQLSERVERS "TO" R .
    Get SQL_AVAILABLE_SQL_SERVERS to !2
#ENDCOMMAND

Function SQL_AVAILABLE_SQL_SERVERS Global Returns Integer
    Call_Driver 0 SQLFLEX Function CALLDRV_ENUMERATE_SERVER CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank CALLDRV_ENUMERATE_SERVER_COUNT RESULT MertechInc_iRet

    Function_Return MertechInc_iRet
End_Function

#Replace AvailableSQLServers SQL_AVAILABLE_SQL_SERVERS

//=============================================================================
/// @Name        GET_SQLSERVER_NAME
/// @Description This command returns the name of the server based on the
/// specified index number. The number of servers can be retrieved from
/// GET_NO_AVAILABLE_SQLSERVERS and the names can be indexed from that
/// number.
///
/// @Assumptions SQL Server Browser Service is started and firewall is configured properly
/// @Status      Public
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See 		 GET_NO_AVAILABLE_SQLSERVERS
///
/// @Syntax SQL_AVAILABLE_SQL_SERVER_NAME {index} to {variable}
/// @Param index		The numbered index name to retrieve
/// @Param variable		Variable to hold the server name
///
/// @Example
/// GET_NO_AVAILABLE_SQLSERVERS to iServers
///
/// While (i <= iServers)
///     GET_SQLSERVER_NAME i to sServer
///     Showln sServer
///     Increment i
/// Loop
#COMMAND GET_SQLSERVER_NAME R "TO" R .
    Get SQL_AVAILABLE_SQL_SERVER_NAME !1 to !3
#ENDCOMMAND

Function SQL_AVAILABLE_SQL_SERVER_NAME Global Integer iIndex Returns String
    String sName

    Get MertechInc_Pre_Size_String 80 to sName
    Call_Driver 0 SQLFLEX Function CALLDRV_ENUMERATE_SERVER CALLBACK 0 PASSING sName iIndex CALLDRV_ENUMERATE_SERVER_SERVER RESULT MertechInc_iRet

    Function_Return sName
End_Function

#Replace AvailableSQLServerName SQL_AVAILABLE_SQL_SERVER_NAME

//=============================================================================
/// @Name        SET_USE_ROWCOUNT_IN_TRANSACTION
/// @Description Turn on / off Row_Count for specified server.
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2009-09-21 By Ian Smith
///
/// @Syntax SET_USE_ROWCOUNT_IN_TRANSACTION OF <Server> To <State>
/// @Param Server      Name of server to turn On / Off Row_Count
/// @Param State       TRUE = turn on Row_Count  FALSE = turn off Row_Count
///
/// @Comment This SHOULD ALWAYS BE TURNED ON
#COMMAND SET_USE_ROWCOUNT_IN_TRANSACTION "OF" R "TO" R .
    Set SQL_USE_ROWCOUNT_IN_TRANSACTIONS to !2 !4
#ENDCOMMAND

Procedure Set SQL_USE_ROWCOUNT_IN_TRANSACTIONS Global String sServer Integer iState
    DO_GETFILENUMBER_DRIVERNAME 0

    Call_Driver 0 MertechInc_DriverName Function CALLDRV_USE_ROWCOUNT_IN_TRANSACTIONS CALLBACK 0 PASSING sServer iState CALLDRV_VALUE_SET RESULT MertechInc_iRet
    If MertechInc_iRet EQ -1 INDICATE ERR True
End_Procedure

//IGS - commented out by a.n. Other
//#REPLACE UseRowCountInTransactions SQL_USE_ROWCOUNT_IN_TRANSACTIONS

//=============================================================================
/// @Name        GET_USE_ROWCOUNT_IN_TRANSACTION
/// @Description Gets the Row_Count setting for specified server.
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2009-09-21 By Ian Smith
///
/// @Syntax GET_USE_ROWCOUNT_IN_TRANSACTION OF <Server> To <State>
/// @Param Server      Name of server to get Row_Count state of
/// @Param State       Variable to hold returned value
#COMMAND GET_USE_ROWCOUNT_IN_TRANSACTION "OF" R "TO" R .
    Get SQL_USE_ROWCOUNT_IN_TRANSACTIONS !2 to !4
#ENDCOMMAND

Function SQL_USE_ROWCOUNT_IN_TRANSACTIONS Global String sServer Returns Integer
    DO_GETFILENUMBER_DRIVERNAME 0

    Call_Driver 0 MertechInc_DriverName Function CALLDRV_USE_ROWCOUNT_IN_TRANSACTIONS CALLBACK 0 PASSING sServer MertechInc_Blank CALLDRV_VALUE_GET RESULT MertechInc_iRet

    Function_Return MertechInc_iRet
End_Function

#REPLACE UseRowCountInTransactions SQL_USE_ROWCOUNT_IN_TRANSACTIONS

//=============================================================================
/// @Name        SQL_SET_DATE_FORMAT
/// @Description This command controls the date format of data returned
/// through embedded SQL. If set to DATAFLEX, then the dates will be
/// returned in whatever format is set in DF_DATE_FORMAT. When set to
/// NATIVE, this command will force dates to return dates in the format
/// specified on the SQL server. Note that in order for the variables to
/// be in the right form, they need to be string variables.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-02 by Aaron Gulack
/// @See
///
/// @Syntax SQL_SET_DATE_FORMAT to {DATAFLEX/NATIVE}
///
/// @Example
/// SQL_SET_DATE_FORMAT to NATIVE
#COMMAND SQL_SET_DATE_FORMAT TO "DATAFLEX""NATIVE"
    #IFSAME !2 DATAFLEX
        Set SQL_USE_DATAFLEX_DATEFORMAT to DFTRUE
    #ELSE
        Set SQL_USE_DATAFLEX_DATEFORMAT to DFFALSE
    #ENDIF
#ENDCOMMAND

Procedure Set SQL_USE_DATAFLEX_DATEFORMAT Global Integer iState
    DO_GETFILENUMBER_DRIVERNAME 0

    If MertechInc_DriverName eq SQLFlex Begin
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_USE_DFLEX_DATE_FORMAT CALLBACK 0 PASSING iState MertechInc_Blank CALLDRV_VALUE_SET RESULT MertechInc_iRet
        IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
    End
End_Procedure

Function SQL_USE_DATAFLEX_DATEFORMAT Global Returns Integer
    DO_GETFILENUMBER_DRIVERNAME 0

    If MertechInc_DriverName eq SQLFlex Begin
        CALL_DRIVER 0 MertechInc_DriverName FUNCTION CALLDRV_USE_DFLEX_DATE_FORMAT CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank CALLDRV_VALUE_GET RESULT MertechInc_iRet
    End
    Else Move DFFALSE to MertechInc_iRet

    function_return MertechInc_iRet
End_Function

#Replace SqlUseDataflexDateFormat SQL_USE_DATAFLEX_DATEFORMAT

//=============================================================================
/// @Name        SET_FIELDS_NOT_NULL
/// @Description This command is used to specify how to handle blank
/// and zero values on the SQL backend. Since blank or zero values can
/// often be stored as null in the server database, this command allows
/// that to be altered if needed. When set to true, a value will be
/// inserted into blank records to keep them from being null. See the
/// list below for what value will be stored instead of null. If set to
/// false, values will be stored normally in the database. Note that this
/// command effects all data types.
///
/// DF_ASCII and DF_TEXT - 		' ' (one blank space)
///
/// DF_BCD - 					0 (zero)
///
/// DF_DATe and DF_DATETIME -   00/00/0000 for MYSQL
///								01/01/0001 for Oracle MSSQL, and Postgre
///								01/01/1753 for MSSQL Datetimes
///
/// DF_BINARY - 				0X0
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-08 by Aaron Gulack
/// @See		 SET_FIELDS_NULL GET_FIELDS_NULL
///
/// @Syntax SET_FIELDS_NOT_NULL to {variable}
/// @Param variable 		Boolean variable to indicate how to handle null values
///
#COMMAND SET_FIELDS_NOT_NULL "TO" R .
   Set SQL_FORCE_FIELDS_NOT_NULL to !2
#ENDCOMMAND

Procedure Set SQL_FORCE_FIELDS_NOT_NULL Global Integer iState
    DO_GETFILENUMBER_DRIVERNAME 0

    If (MertechInc_FileNumber <> -1) Begin
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_FORCE_FIELDS_NOT_NULL CALLBACK 0 PASSING iState MertechInc_Blank CALLDRV_VALUE_SET RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
End_Procedure

#Replace SET_FORCE_FIELDS_NOT_NULL SET_FIELDS_NOT_NULL

#COMMAND GET_FIELDS_NOT_NULL "TO" R .
    Get SQL_FORCE_FIELDS_NOT_NULL to !2
#ENDCOMMAND

#Replace GET_FORCE_FIELDS_NOT_NULL GET_FIELDS_NOT_NULL

Function SQL_FORCE_FIELDS_NOT_NULL Global Returns Integer
    DO_GETFILENUMBER_DRIVERNAME 0

    If (MertechInc_FileNumber <> -1) Begin
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_FORCE_FIELDS_NOT_NULL CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank CALLDRV_VALUE_GET RESULT MertechInc_iRet
    End
    Else Move DFFALSE to MertechInc_iRet

    Function_Return MertechInc_iRet
End_Function

#Replace SqlForceFieldsNotNull SQL_FORCE_FIELDS_NOT_NULL

//=============================================================================
/// @Name        SET_FIELDS_NULL
/// @Description This command is used to specify how to store blank or zero
/// values in the database. Since database can sometimes store these value,
/// i.e. '' or 0, as null, using this command can be useful in managing that.
/// When set to true, any value in a column of the given type considered blank
/// or 0 will be stored as null in the database. Setting it to false will cause
/// the server to save as it normally would. Note that this command is used to
/// set specific data types only, it can not effect all types at once. Below is
/// a list of value that would be considered blank/zero values.
///
/// DF_ASCII and DF_TEXT - 		' ' (one blank space)
///
/// DF_BCD - 					0 (zero)
///
/// DF_DATe and DF_DATETIME -   00/00/0000 for MYSQL
///								01/01/0001 for Oracle MSSQL, and Postgre
///								01/01/1753 for MSSQL Datetimes
///
/// DF_BINARY - 				0X0
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-08 by Aaron Gulack
/// @See		 GET_FIELDS_NULL SET_FIELDS_NOT_NULL
///
/// @Syntax SET_FIELDS_NULL {datatype} to {variable}
/// @Param datatype			DF_ASCII, DF_BCD, or DF_DATE
/// @Param variable 		Boolean to indicate how to handle blank data
#COMMAND SET_FIELDS_NULL "OF" R "TO" R .
    DO_GETFILENUMBER_DRIVERNAME 0

    If (MertechInc_FileNumber <> -1) Begin
        Move !2 to MertechInc_sArg1
        Move !4 to MertechInc_sArg2
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_FORCE_FIELDS_NULL CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_sArg2 CALLDRV_VALUE_SET RESULT MertechInc_iRet
        If MertechInc_iRet EQ -1 INDICATE ERR True
    End
#ENDCOMMAND

#Replace SET_FORCE_FIELDS_NULL SET_FIELDS_NULL

//=============================================================================
/// @Name        GET_FIELDS_NULL
/// @Description This command will return the value of SET_FIELDS_NULL for
/// the specified data type.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-08 by Aaron Gulack
/// @See 		 SET_FIELDS_NULL SET_FIELDS_NOT_NULL
///
/// @Syntax GET_FIELDS_NULL {datatype} to {variable}
/// @Param datatype			DF_ASCII, DF_BCD, or DF_DATE
/// @Param variable 		Variable to hold the value of SET_FIELDS_NULL
#COMMAND GET_FIELDS_NULL "OF" R "TO" R .
    DO_GETFILENUMBER_DRIVERNAME 0

    If (MertechInc_FileNumber <> -1) Begin
        Move !2 to MertechInc_sArg1
        Call_Driver 0 MertechInc_DriverName Function CALLDRV_FORCE_FIELDS_NULL CALLBACK 0 PASSING MertechInc_sArg1 MertechInc_Blank CALLDRV_VALUE_GET RESULT MertechInc_iRet
        Move MertechInc_iRet to !4
    End
    Else Move DFFALSE to !4

#ENDCOMMAND

#Replace GET_FORCE_FIELDS_NULL GET_FIELDS_NULL

//=============================================================================
/// @Name        STRUCTURE_START_DYNAMIC
/// @Description This command is used when scripting structural changes.
/// It is the same as using ENABLE_SCRIPTING and Structure_Start separately.
/// It allows structural changes to be compiled and tested without
/// actually making any of the changes. Any table restructuring done
/// between this command and STRUCTURE_END_DYNAMIC will not actually be
/// committed but will instead create a mock INT file. The script and
/// INT file can then be retrieved and examined for testing purposes.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See 		 ENABLE_SCRIPTING DISABLE_SCRIPTING
///
/// @Syntax STRUCTURE_START_DYNAMIC of {FileNumber}
/// @Param FileNumber			The number of the file
#COMMAND STRUCTURE_START_DYNAMIC "OF" R .
    DO_GETFILENUMBER_DRIVERNAME !2

    If (MertechInc_FileNumber <> -1) Begin
        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function CALLDRV_FILE_STRUCT_DYNAMIC_ONLINE CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
    End

#ENDCOMMAND

//=============================================================================
/// @Name        STRUCTURE_END_DYNAMIC
/// @Description This command ends the scripting started by
/// STRUCTURE_START_DYNAMIC. It is the same as calling Structure_End
/// and DISABLE_SCRIPTING separately.
///
/// @Assumptions
/// @Status      Deprecated
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See 		 ENABLE_SCRIPTING DISABLE_SCRIPTING
///
/// @Syntax STRUCTURE_START_DYNAMIC of {FileNumber}
/// @Param FileNumber			The number of the file
#COMMAND STRUCTURE_END_DYNAMIC "OF" R .
    DO_GETFILENUMBER_DRIVERNAME !2

    If (MertechInc_FileNumber <> -1) Begin
        Call_Driver MertechInc_FileNumber MertechInc_DriverName Function CALLDRV_FILE_STRUCT_DYNAMIC_ONLINE CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 1 RESULT MertechInc_iRet
    End

#ENDCOMMAND

//=============================================================================
/// @Name        SQLSERVER_ATTACH_DB
/// @Description Attachs an MS SQL mdf to the current server instance. If
/// the passed database is already attached, no error is generated.
///
/// The SQLSERVER_ATTACH_DB command is intended for use with our new support
/// of Microsoft LocalDB's.  When using LocalDB's a common use case might be
/// to attach to a customer DB, do some work on it, and then detach this DB
/// and attach to a different DB.  This was possible using stored procedures,
/// but the code had some complexities that a developer need not worry about.
/// When you attach a database, you must pass the database name, along with
/// the path to an MDF file which contains the database.  Any associated LDF's
/// (log files) and NDF's (secondary data files) must be in the same folder.
///
/// If you call SQLSERVER_ATTACH_DB on a database that is already attached,
/// no error will be generated.  After you call SQLSERVER_ATTACH_DB, you
/// should call SET_DATABASE_NAME if you wish to make the attached database
/// the currently selected database.
///
/// SQLSERVER_ATTACH_DB will work on all supported version of SQL server.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-09 Aaron Gulack
/// @See
///
/// @Syntax SQLSERVER_ATTACH_DB {database} on {filePath}
/// @Param database			Name of the database
/// @Param filePath			Path of the MDF file
///
/// @Example
/// SQLSERVER_ATTACH_DB "MTSample" ON "C:\Mertech\Data\SampleDb.mdf"
#COMMAND SQLSERVER_ATTACH_DB R "ON" R
    CALL_SQLSERVER_PROCEDURE "sp_databases"
    While (not(finderr))
        SQL_FETCH_NEXT_ROW into MertechInc_sWork
        If (Found and MertechInc_sWork = !1) Break
    Loop

    If (MertechInc_sWork <> !1) Begin
        SQL_SET_STMT to ("Create Database " + !1 + " on (filename='" + !3 + "') for attach")
        SQL_PREPARE_STMT
        SQL_EXECUTE_STMT
    End
#ENDCOMMAND

//=============================================================================
/// @Name        SQLSERVER_DETACH_DB
/// @Description The SQLSERVER_DETACH_DB command is intended for use with our
/// new support of Microsoft LocalDB's.  When using LocalDB's a common use
/// case might be to attach to a customer DB, do some work on it, and then
/// detach this DB and attach to a different DB.  This was possible using
/// stored procedures, but the code had some complexities that a developer
/// need not worry about.  A detach can only be done if the database passed
/// has no open connections.  As part of the detach process, the command
/// closes ALL open files (even those not associated with this database or
/// driver).
///
/// NOTE: SQLSERVER_DETACH_DB will often fail to execute if you are testing
/// your application from the studio.  This is because the studio itself
/// normally has open connections to the database.  If you test your
/// application outside of the studio and the studio is closed (and any
/// other application or tools that access this database are closed) you
/// can successfully detach the database.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     SQLFlex
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See
///
/// @Syntax SQLSERVER_DETACH_DB {database}
/// @Param database			Name of the database
///
/// @Example
/// SQLSERVER_DETACH_DB "TestDB"
#COMMAND SQLSERVER_DETACH_DB R
    Close DF_ALL
    SQL_SET_STMT to "use master"
    SQL_PREPARE_STMT
    SQL_EXECUTE_STMT
    CALL_SQLSERVER_PROCEDURE "sp_detach_db" passing !1
#ENDCOMMAND

//=============================================================================
/// @Name        SET_FIXED_FILE_RECORDS_USED
/// @Description This command is used to set DF_FILE_RECORDS_USED to a
/// fixed value. This can be useful because doing a SELECT COUNT(*) is
/// a very expensive process to the server. Many applications do counts
/// often and using this command can help cut down the server traffic.
/// Sometimes when counts are used, an exact number is not necessary so
/// a fixed value, updated occasionally can be used. By setting this
/// command to 0 or greater, the value of DF_FILE_RECORDS_USED will be
/// set to that specified value and the internal SELECT COUNT(*) will be
/// suppressed. If this command is set to something less that zero,
/// DF_FILE_RECORDS_USED will be dynamically calculated whenever it is
/// called.
///
/// The default value for this command is -1
///
/// @Assumptions
/// @Status		 Public
/// @Drivers	 All
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See		 GET_FIXED_FILE_RECORDS_USED SUPPRESS_SELECT_COUNT UNSUPPRESS_SELECT_COUNT
///
/// @Syntax SET_FIXED_FILE_RECORDS_USED to {variable}
/// @Param variable			Fixed value for DF_FILE_RECORDS_USED
///
/// @Example
/// SET_FIXED_FILE_RECORDS_USED to 10000
#COMMAND SET_FIXED_FILE_RECORDS_USED "TO" R .
    MOVE !2 TO MertechInc_iArg
    DO_GETFILENUMBER_DRIVERNAME 0
    Call_Driver 0 MertechInc_DriverName FUNCTION CALLDRV_SET_FIXED_FILE_RECORDS_USED CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank MertechInc_iArg RESULT MertechInc_iRet
    IF MertechInc_iRet EQ -1 INDICATE ERR TRUE
#ENDCOMMAND

//=============================================================================
/// @Name        GET_FIXED_FILE_RECORDS_USED
/// @Description This command returns the value of DF_FILE_RECORDS_USED
/// if it has been set to a fixed value by SET_FIXED_FILE_RECORDS_USED.
/// If anything greater than or equal to 0 is returned then that is the
/// fixed value returned by any SELECT COUNT(*) statements, internal or
/// not. If something less than zero is returned, then DF_FILE_RECORDS_USED
/// returns a dynamic count whenever it is called.
///
/// By default the value of this is -1
///
/// @Assumptions
/// @Status		 Public
/// @Drivers	 All
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See 		 SET_FIXED_FILE_RECORDS_USED SUPPRESS_SELECT_COUNT UNSUPPRESS_SELECT_COUNT
///
/// @Syntax GET_FILE_RECORDS_USED to {variable}
/// @Param variable			Variable to hold the fixed value
///
/// @Example
/// GET_FIXED_FILE_RECORDS_USED to iRecords
#COMMAND GET_FIXED_FILE_RECORDS_USED "TO" R .
    MOVE !2 TO MertechInc_iArg
    DO_GETFILENUMBER_DRIVERNAME 0
    Call_Driver 0 MertechInc_DriverName FUNCTION CALLDRV_GET_FIXED_FILE_RECORDS_USED CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank 0 RESULT MertechInc_iRet
    Move MertechInc_iRet to !2
#ENDCOMMAND

//=============================================================================
/// @Name        SUPPRESS_SELECT_COUNT
/// @Description This command sets the value of DF_FILE_RECORDS_USED to
/// a fixed value of zero. That way anytime a SELECT COUNT(*) is done,
/// zero is returned, cutting down on server traffic. This is the same
/// as setting SET_FIXED_FILE_RECORDS_USED to 0.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See		 UNSUPPRESS_SELECT_COUNT SET_FIXED_FILE_RECORDS_USED GET_FIXED_FILE_RECORDS_USED
///
/// @Syntax SUPPRESS_SELECT_COUNT
#COMMAND SUPPRESS_SELECT_COUNT .
    SET_FIXED_FILE_RECORDS_USED TO 0
#ENDCOMMAND

//=============================================================================
/// @Name        UNSUPPRESS_SELECT_COUNT
/// @Description This command resets the value of DF_FILE_RECORDS_USED to
/// -1. That way anytime a SELECT COUNT(*) is done, it returns the actual
/// count of records. This is the same as setting SET_FIXED_FILE_RECORDS_USED
/// to -1.
///
/// @Assumptions
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2013-10-09 by Aaron Gulack
/// @See		 SUPPRESS_SELECT_COUNT SET_FIXED_FILE_RECORDS_USED GET_FIXED_FILE_RECORDS_USED
///
/// @Syntax UNSUPPRESS_SELECT_COUNT
#COMMAND UNSUPPRESS_SELECT_COUNT .
    SET_FIXED_FILE_RECORDS_USED TO (-1)
#ENDCOMMAND


///
// Private:
// Get the filenumber of a file.field parameter
//
#COMMAND MERTECH_GET_FILENUMBER R "TO" R .
    #PUSH !g
    #SET G$ !1   // get filenumber
    Move |CI!g  To !3
    #POP G$
#ENDCOMMAND

///
// Private:
// Get the fieldnumber of a file.field parameter
//
#COMMAND MERTECH_GET_FIELDNUMBER R "TO" R .
    #PUSH !g
    #SET G$ %!1   // get fieldnumber
    Move |CI!g  To !3
    #POP G$
#ENDCOMMAND



#IFDEF DFERR_COMP_MERTECH_UNDEFINED_SYMBOL
#ELSE
  #REPLACE DFERR_COMP_MERTECH_UNDEFINED_SYMBOL    |CI14328
#ENDIF

//
// Minimum required DataFlex version for new LOB support below is VDF 4
//
#IF (!@>32) // Do not change comparison operator into >= as it won't work in old DF versions

TYPE tMertechLOB_Args
    FIELD tMertechLOB_Args.cbSize       AS WORD          // always the size of the structure (verification + versioning)
    FIELD tMertechLOB_Args.nField       AS DWORD         // always the field number
    FIELD tMertechLOB_Args.pszData      AS POINTER
    FIELD tMertechLOB_Args.nSize        AS DWORD
    FIELD tMertechLOB_Args.nOffset      AS POINTER
END_TYPE

//=============================================================================
/// @Name        SQL_SET_LOB
/// @Description This command replaces whatever is currently in a LOB Field
/// with the data passed. It writes to a client side buffer. It can be used
/// to Write an arbitrary amount of data into a LOB.
/// If passed an empty String, it will remove all the contents of the LOB.
/// If you wish to Set a LOB back to NULL, please use the SQL_SET_LOB_NULL
/// command.
/// NOTE: Unlike the previous call LOB_WRITE, this call does not
/// perform the Save. This must be done separately.
///
/// @Assumptions The field being used is a LOB field
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2014-07-10 by Aaron Gulack
/// @See 		 SQL_ADD_LOB_CHUNK SQL_GET_LOB SQL_GET_LOB_CHUNK SQL_GET_LOB_LENGTH SQL_LOB_TRUNCATE
///
/// @Syntax		SQL_SET_LOB {FileName.FieldName} to {variable}
/// @Param		FileName		The name of the file containing the LOB field
/// @Param		FieldName		The name of the LOB field being set
/// @Param		variable		The variable to use to set the field's value
///
/// @Example
/// Set_Argument_Size 262144
/// String sLine
///
/// Clear Customer
///    Move iID to Customer.ID
/// Find Eq Customer by Index.1
/// If (Found) Begin
///    Direct_Input "C:\bigFile.xml"
///    Reread Customer
///       SQL_SET_LOB Customer.Comments to ""
///       Read_Block sLine 262144
///       SQL_SET_LOB Customer.Comments to sLine
///       While (not(SeqEof))
///          Read_Block sLine 262144
///          SQL_ADD_LOB_CHUNK Customer.Comments to sLine
///       Loop
///    Saverecord Customer
///    Unlock
///    Close_Input
/// End
#COMMAND SQL_SET_LOB R "TO" R .
    #IF (!0=3)
      #CHECK !2 "TO"
    #ELSE
      #ERROR DFERR_COMP_MERTECH_UNDEFINED_SYMBOL SQL_SET_LOB INCORRECT NUMBER OF PARAMETERS
    #ENDIF
    #IFCLASS !1 F         // test for file element
      MERTECH_GET_FILENUMBER  !1 To MertechInc_FileNumber
      MERTECH_GET_FIELDNUMBER !1 To MertechInc_iWork
      Send MertechInc_Get_Driver_name
      Send MertechInc_SQL_SET_LOB MertechInc_DriverName MertechInc_FileNumber MertechInc_iWork !3
    #ELSE
      #ERROR DFERR_COMP_MERTECH_UNDEFINED_SYMBOL SQL_SET_LOB MUST USE FILE.FIELD AS FIRST PARAMETER: !1
    #ENDIF
#ENDCOMMAND

Procedure MertechInc_SQL_SET_LOB String sDriver Integer iFile Integer iField String sData
    String sLOB_Args       // can drop local command if minimum vdf version is 6

    ZeroType tMertechLOB_Args to sLOB_Args
    // First move the size of the structure to the Structure
    Put tMertechLOB_Args_size to sLOB_Args at tMertechLOB_Args.cbSize
    Put iField                to sLOB_Args at tMertechLOB_Args.nField
    Put (AddressOf(sData))    to sLOB_Args at tMertechLOB_Args.pszData
    Put (length(sData))       to sLOB_Args at tMertechLOB_Args.nSize

    Call_Driver iFile sDriver Function CALLDRV_LOB_EX_WRITE CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank (addressof(sLOB_Args)) RESULT MertechInc_iRet
End_Procedure // MertechInc_SQL_SET_LOB

//=============================================================================
/// @Name        SQL_ADD_LOB_CHUNK
/// @Description This command is used to add additional chunks to the buffer
/// before saving the record. After SQL_SET_LOB has been called
/// SQL_ADD_LOB_CHUNK can be called as many times as needed to add additional
/// chunks of data before a save. It can also be called independent of
/// SQL_SET_LOB to append data to an existing LOB column.
/// NOTE: Unlike the previous call LOB_APPEND, this call does not perform
/// the save. This must be done separately.
///
/// @Assumptions The field being used is a LOB field
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2014-07-10 by Aaron Gulack
/// @See 		 SQL_SET_LOB SQL_GET_LOB SQL_GET_LOB_CHUNK SQL_GET_LOB_LENGTH SQL_LOB_TRUNCATE
///
/// @Syntax		SQL_ADD_LOB_CHUNK {FileName.FieldName} to {variable}
/// @Param		FileName		The name of the file containing the LOB field
/// @Param		FieldName		The name of the LOB field being set
/// @Param		variable		The variable to add as the LOB chunk
///
/// @Example
/// Set_Argument_Size 262144
/// String sLine
///
/// Clear Customer
///    Move iID to Customer.ID
/// Find Eq Customer by Index.1
/// If (Found) Begin
///    Direct_Input "C:\bigFile.xml"
///    Reread Customer
///       SQL_SET_LOB Customer.Comments to ""
///       Read_Block sLine 262144
///       SQL_SET_LOB Customer.Comments to sLine
///       While (not(SeqEof))
///          Read_Block sLine 262144
///          SQL_ADD_LOB_CHUNK Customer.Comments to sLine
///       Loop
///    Saverecord Customer
///    Unlock
///    Close_Input
/// End
#COMMAND SQL_ADD_LOB_CHUNK R "TO" R .
    #IF (!0=3)
      #CHECK !2 "TO"
    #ELSE
      #ERROR DFERR_COMP_MERTECH_UNDEFINED_SYMBOL SQL_ADD_LOB_CHUNK INCORRECT NUMBER OF PARAMETERS
    #ENDIF
    #IFCLASS !1 F
      MERTECH_GET_FILENUMBER  !1 To MertechInc_FileNumber
      MERTECH_GET_FIELDNUMBER !1 To MertechInc_iWork
      Send MertechInc_Get_Driver_name
      Send MertechInc_SQL_ADD_LOB_CHUNK MertechInc_DriverName MertechInc_FileNumber MertechInc_iWork !3
    #ELSE
      #ERROR DFERR_COMP_MERTECH_UNDEFINED_SYMBOL SQL_ADD_LOB_CHUNK MUST USE FILE.FIELD AS FIRST PARAMETER: !1
    #ENDIF
#ENDCOMMAND

Procedure MertechInc_SQL_ADD_LOB_CHUNK String sDriver Integer iFile Integer iField String sData
    String sLOB_Args

    ZeroType tMertechLOB_Args to sLOB_Args
    // First move the size of the structure to the Structure
    Put tMertechLOB_Args_size to sLOB_Args at tMertechLOB_Args.cbSize
    Put iField                to sLOB_Args at tMertechLOB_Args.nField
    Put (AddressOf(sData))    to sLOB_Args at tMertechLOB_Args.pszData
    Put (length(sData))       to sLOB_Args at tMertechLOB_Args.nSize

    Call_Driver iFile sDriver Function CALLDRV_LOB_EX_APPEND CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank (addressof(sLOB_Args)) RESULT MertechInc_iRet
end_procedure // MertechInc_SQL_ADD_LOB_CHUNK

//=============================================================================
/// @Name        SQL_GET_LOB
/// @Description This command is used for getting the value of a specified LOB
/// field. Two optional parameters can be passed specifying the offset and
/// length of the chunk to get. Passing these parameters essentially makes this
/// call the same as SQL_GET_LOB_CHUNK.
/// Depending on the situation, the two calls can be interchanged for improved
/// code readability. Excluding these additional parameters will get the whole
/// field value within DataFlex variable size limits.
///
/// @Assumptions The field being used is a LOB field
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2014-07-10 by Aaron Gulack
/// @See 		 SQL_SET_LOB SQL_ADD_LOB_CHUNK SQL_GET_LOB_CHUNK SQL_GET_LOB_LENGTH SQL_LOB_TRUNCATE
///
/// @Syntax 	SQL_GET_LOB {FileName.FieldName} TO {variable} [ OFFSET {offset} LENGTH {length} ]
/// @Param		FileName			The name of the file that contains the specified LOB field
/// @Param		FieldName			The name of the LOB field
/// @Param		variable			The variable to hold the LOB value
/// @Param		offset				Integer amount to offset when getting the LOB value (optional)
/// @Param		length				Length of value to get from the LOB field (optional)
///
/// @Example
/// Set_Argument_Size 262144
/// String sResult
///
/// Move 262144 to iChunkSize
/// Move 0      to iChunk
///
/// Clear Customer
///    Move iID to Customer.ID
/// Find Eq Customer by Index.1
/// If (Found) Begin
///    Direct_Output ('Binary:' + sDestFileName)
///    SQL_GET_LOB_LENGTH Customer.Comments to iLength
///    While (iChunk*iChunkSize < iLength)
///       SQL_GET_LOB Customer.Comments to sResult OFFSET (iChunk*iChunkSize) LENGTH iChunkSize
///       Write sResult
///       Increment iChunk
///    Loop
///    Close_Output
/// End
#COMMAND SQL_GET_LOB R "TO" R "OFFSET""" ULG "LENGTH""" ULG .
    #IF (!0=3)
      #CHECK !2 "TO"
    #ELSE
      #IF (!0=7)
        #CHECK !2 "TO"
        #CHECK !4 "OFFSET"
        #CHECK !6 "LENGTH"
      #ELSE
        #ERROR DFERR_COMP_MERTECH_UNDEFINED_SYMBOL SQL_GET_LOB INCORRECT NUMBER OF PARAMETERS
      #ENDIF
    #ENDIF
    #IFCLASS !1 F
      MERTECH_GET_FILENUMBER  !1 To MertechInc_FileNumber
      MERTECH_GET_FIELDNUMBER !1 To MertechInc_iWork
      Send MertechInc_Get_Driver_name
      #IF (!0=3)
        Get MertechInc_SQL_GET_LOB MertechInc_DriverName MertechInc_FileNumber MertechInc_iWork 0 0 To !3
      #ELSE
        #IF (!0=7)
          Get MertechInc_SQL_GET_LOB MertechInc_DriverName MertechInc_FileNumber MertechInc_iWork !5 !7 To !3
        #ENDIF
      #ENDIF
    #ELSE
      #ERROR DFERR_COMP_MERTECH_UNDEFINED_SYMBOL SQL_GET_LOB MUST USE FILE.FIELD AS FIRST PARAMETER: !1
    #ENDIF
#ENDCOMMAND


Function MertechInc_SQL_GET_LOB String sDriver Integer iFile Integer iField Integer iOffset Integer iLength Returns String
    String sLOB_Args
    String sData
    DWord  nSize

    Move "" To sData
    ZeroType tMertechLOB_Args to sLOB_Args
    // First move the size of the structure to the Structure
    Put tMertechLOB_Args_size to sLOB_Args at tMertechLOB_Args.cbSize
    Put iField                to sLOB_Args at tMertechLOB_Args.nField

    Call_Driver iFile sDriver Function CALLDRV_LOB_EX_GET_LENGTH CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank (addressof(sLOB_Args)) RESULT MertechInc_iRet

    GetBuff from sLOB_Args at tMertechLOB_Args.nSize to nSize
    If nSize GT 0 Begin
      If (iOffset=0 and iLength=0) Begin
        ZeroString nSize to sData
	    //Send Assert (AddressOf(sData) <> 0) ("AddressOf(sData) is NULL") DFTrue
        Put (AddressOf(sData)) to sLOB_Args at tMertechLOB_Args.pszData
      End
      Else Begin
        ZeroString iLength to sData
        Put (AddressOf(sData)) to sLOB_Args at tMertechLOB_Args.pszData
        Put iLength            to sLOB_Args at tMertechLOB_Args.nSize
        Put iOffset            to sLOB_Args at tMertechLOB_Args.nOffset
      End
      Call_Driver iFile sDriver Function CALLDRV_LOB_EX_READ CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank (addressof(sLOB_Args)) RESULT MertechInc_iRet
    End
    Else Begin
        Move "" to sData
    End
    Function_Return sData
End_Function // MertechInc_SQL_GET_LOB

//=============================================================================
/// @Name        SQL_GET_LOB_CHUNK
/// @Description This command is used for getting a chunk of data from a specified
/// LOB field. The difference between this command and SQL_GET_LOB is only that
/// the parameters OFFSET and LENGTH are not optional when using this command.
/// You may consider using this command to retrieve small portions of a very
/// large BLOB so as to reduce memory usage.
///
/// @Assumptions The field being used is a LOB field
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2014-07-10 by Aaron Gulack
/// @See 		 SQL_SET_LOB SQL_ADD_LOB_CHUNK SQL_GET_LOB SQL_GET_LOB_LENGTH SQL_LOB_TRUNCATE
///
/// @Syntax 	SQL_GET_LOB_CHUNK {FileName.FieldName} TO {variable} OFFSET {offset} LENGTH {length}
/// @Param		FileName			The name of the file that contains the specified LOB field
/// @Param		FieldName			The name of the LOB field
/// @Param		variable			The variable to hold the LOB chunk
/// @Param		offset				Integer amount to offset when getting the LOB chunk
/// @Param		length				Length of chunk to get from the LOB field
///
/// @Example
/// Set_Argument_Size 262144
/// String sResult
///
/// Move 262144 to iChunkSize
/// Move 0      to iChunk
///
/// Clear Customer
///    Move iID to Customer.ID
/// Find Eq Customer by Index.1
/// If (Found) Begin
///    SQL_GET_LOB_LENGTH Customer.Comments to iLength
///    While (iChunk*iChunkSize < iLength)
///       SQL_GET_LOB_CHUNK Customer.Comments to sResult OFFSET (iChunk*iChunkSize) LENGTH iChunkSize
///       // Do something with the LOB data
///       Increment iChunk
///    Loop
/// End
#COMMAND SQL_GET_LOB_CHUNK R "TO" R "OFFSET""" R "LENGTH""" R .
    #IF (!0=7)
      #CHECK !2 "TO"
      #CHECK !4 "OFFSET"
      #CHECK !6 "LENGTH"
    #ELSE
      #ERROR DFERR_COMP_MERTECH_UNDEFINED_SYMBOL SQL_GET_LOB_CHUNK INCORRECT NUMBER OF PARAMETERS
    #ENDIF
    #IFCLASS !1 F
      MERTECH_GET_FILENUMBER  !1 To MertechInc_FileNumber
      MERTECH_GET_FIELDNUMBER !1 To MertechInc_iWork
      Send MertechInc_Get_Driver_name
      Get MertechInc_SQL_GET_LOB MertechInc_DriverName MertechInc_FileNumber MertechInc_iWork !5 !7 To !3
    #ELSE
      #ERROR DFERR_COMP_MERTECH_UNDEFINED_SYMBOL SQL_GET_LOB_CHUNK MUST USE FILE.FIELD AS FIRST PARAMETER: !1
    #ENDIF
#ENDCOMMAND

//=============================================================================
/// @Name        SQL_GET_LOB_LENGTH
/// @Description This command is used to get the length of a specified LOB field.
/// It is useful, for example, in determining the number of iterations to
/// perform while reading from a LOB field using chunking.
///
/// @Assumptions The field being used is a LOB field
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2014-07-10 by Aaron Gulack
/// @See 		 SQL_SET_LOB SQL_ADD_LOB_CHUNK SQL_GET_LOB SQL_GET_LOB_CHUNK SQL_LOB_TRUNCATE
///
/// @Syntax		SQL_GET_LOB_LENGTH {FileName.FieldName} to {variable}
/// @Param		FileName			The name of the file containing the LOB field
/// @Param		FieldName			The name of the specified LOB field
/// @Param		variable			The variable to hold the length of the field
///
/// @Example
/// Set_Argument_Size 262144
/// String sResult
///
/// Move 16384 to iChunkSize
/// Move 0     to iChunk
///
/// Clear Customer
///    Move iID to Customer.ID
/// Find Eq Customer by Index.1
/// If (Found) Begin
///    SQL_GET_LOB_LENGTH Customer.Comments to iLength
///    While (iChunk*iChunkSize < iLength)
///       SQL_GET_LOB Customer.Comments to sResult OFFSET (iChunk*iChunkSize) LENGTH iChunkSize
///       // Do something with the LOB data
///       Increment iChunk
///    Loop
/// End
#COMMAND SQL_GET_LOB_LENGTH R "TO" R
    #IF (!0=3)
      #CHECK !2 "TO"
    #ELSE
      #ERROR DFERR_COMP_MERTECH_UNDEFINED_SYMBOL SQL_GET_LOB_LENGTH INCORRECT NUMBER OF PARAMETERS
    #ENDIF
    #IFCLASS !1 F
      MERTECH_GET_FILENUMBER  !1 To MertechInc_FileNumber
      MERTECH_GET_FIELDNUMBER !1 To MertechInc_iWork
      Send MertechInc_Get_Driver_name
      Get MertechInc_SQL_GET_LOB_LENGTH MertechInc_DriverName MertechInc_FileNumber MertechInc_iWork To !3
    #ELSE
      #ERROR DFERR_COMP_MERTECH_UNDEFINED_SYMBOL SQL_GET_LOB_LENGTH MUST USE FILE.FIELD AS FIRST PARAMETER: !1
    #ENDIF
#ENDCOMMAND


Function MertechInc_SQL_GET_LOB_LENGTH String sDriver Integer iFile Integer iField Returns Integer
    String sLOB_Args
    DWord  nSize

    ZeroType tMertechLOB_Args to sLOB_Args
    // First move the size of the structure to the Structure
    Put tMertechLOB_Args_size to sLOB_Args at tMertechLOB_Args.cbSize
    Put iField                to sLOB_Args at tMertechLOB_Args.nField

    Call_Driver iFile sDriver Function CALLDRV_LOB_EX_GET_LENGTH CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank (addressof(sLOB_Args)) RESULT MertechInc_iRet

    GetBuff from sLOB_Args at tMertechLOB_Args.nSize to nSize
    Function_Return nSize
End_Function // MertechInc_SQL_GET_LOB_LENGTH

//=============================================================================
/// @Name        SQL_SET_LOB_NULL
/// @Description This command is used to set a LOB column to null. Often
/// LOB columns should either contain data or be null. A "blank" LOB column
/// often doesn't appear empty in other environments, so settings it back to
/// null is best.
///
/// @Assumptions The field being used is a LOB field
/// @Status      Public
/// @Drivers     All
/// @VersionNote Last Revised: 2014-07-10 by Aaron Gulack
/// @See 		 SQL_SET_LOB SQL_ADD_LOB_CHUNK SQL_GET_LOB SQL_GET_LOB_CHUNK SQL_LOB_TRUNCATE
///
/// @Syntax		SQL_SET_LOB_NULL    {FileName.FieldName}
/// @Param		FileName			The name of the file containing the LOB field
/// @Param		FieldName			The name of the specified LOB field
///
/// @Example
////
/// Clear Customer
/// Move iID to Customer.ID
/// Find Eq Customer by Index.1
/// If (Found) Begin
///    Reread Customer
///        SQL_SET_LOB_NULL Customer.Comments
///        Saverecord Customer
///    Unlock
/// End

#COMMAND SQL_SET_LOB_NULL R
    #IFCLASS !1 F
      MERTECH_GET_FILENUMBER  !1 To MertechInc_FileNumber
      MERTECH_GET_FIELDNUMBER !1 To MertechInc_iWork
      Send MertechInc_Get_Driver_name
      Send MertechInc_SQL_SET_LOB_NULL MertechInc_DriverName MertechInc_FileNumber MertechInc_iWork
    #ELSE
      #ERROR DFERR_COMP_MERTECH_UNDEFINED_SYMBOL SQL_GET_LOB_LENGTH MUST USE FILE.FIELD AS FIRST PARAMETER: !1
    #ENDIF
#ENDCOMMAND

Procedure MertechInc_SQL_SET_LOB_NULL String sDriver Integer iFile Integer iField
    String sLOB_Args

    ZeroType tMertechLOB_Args to sLOB_Args
    // First move the size of the structure to the Structure
    Put tMertechLOB_Args_size to sLOB_Args at tMertechLOB_Args.cbSize
    Put iField                to sLOB_Args at tMertechLOB_Args.nField

    Call_Driver iFile sDriver Function CALLDRV_LOB_EX_SET_NULL CALLBACK 0 PASSING MertechInc_Blank MertechInc_Blank (addressof(sLOB_Args)) RESULT MertechInc_iRet
End_Procedure // MertechInc_SQL_SET_LOB_NULL

#ELSE
//
// Console mode does not understand Type/Put/Get/AddressOf
// Tell the developer why his compile failed.
//
#COMMAND SQL_SET_LOB R "TO" R .
    #ERROR DFERR_COMP_MERTECH_UNDEFINED_SYMBOL SQL_SET_LOB COMMAND UNSUPPORTED IN CONSOLE MODE DATAFLEX
#ENDCOMMAND

#COMMAND SQL_ADD_LOB_CHUNK R "TO" R .
    #ERROR DFERR_COMP_MERTECH_UNDEFINED_SYMBOL SQL_ADD_LOB_CHUNK COMMAND UNSUPPORTED IN CONSOLE MODE DATAFLEX
#ENDCOMMAND

#COMMAND SQL_GET_LOB R "TO" R "OFFSET""" ULG "LENGTH""" ULG .
    #ERROR DFERR_COMP_MERTECH_UNDEFINED_SYMBOL SQL_GET_LOB COMMAND UNSUPPORTED IN CONSOLE MODE DATAFLEX
#ENDCOMMAND

#COMMAND SQL_GET_LOB_LENGTH R "TO" R
    #ERROR DFERR_COMP_MERTECH_UNDEFINED_SYMBOL SQL_GET_LOB_LENGTH COMMAND UNSUPPORTED IN CONSOLE MODE DATAFLEX
#ENDCOMMAND

#COMMAND SQL_GET_LOB_CHUNK R "TO" R "OFFSET" ULGR "LENGTH" ULGR .
    #ERROR DFERR_COMP_MERTECH_UNDEFINED_SYMBOL SQL_GET_LOB_CHUNK COMMAND UNSUPPORTED IN CONSOLE MODE DATAFLEX
#ENDCOMMAND

#COMMAND SQL_LOB_TRUNCATE R "TO" R .
    #ERROR DFERR_COMP_MERTECH_UNDEFINED_SYMBOL SQL_LOB_TRUNCATE COMMAND UNSUPPORTED IN CONSOLE MODE DATAFLEX
#ENDCOMMAND


#ENDIF


//=============================================================================
// End of Mertech.inc
//=============================================================================
