Use DUFLanguageConstants.inc

Register_Function paSQLQueryMessages Returns String[]
Register_Procedure Set paSQLQueryMessages String[] aSQLQueryMessages

#IFNDEF DATAFLEX_ID
    Define DATAFLEX_ID for "DATAFLEX"
#ENDIF

#IFNDEF CS_OEM_Txt
    Define CS_OEM_Txt for "OEM"
#ENDIF

#IFNDEF CS_ANSI_Txt
    Define CS_ANSI_Txt for "ANSI"
#ENDIF

#IFNDEF CS_DFCONNID
    Define CS_DFCONNID for "DFCONNID"
#ENDIF  

#IFNDEF CS_SERVER
    Define CS_SERVER for "SERVER"
#ENDIF 

#IFNDEF CS_SERVER_NAME
    Define CS_SERVER_NAME for "SERVER_NAME"
#ENDIF 

#IFNDEF CS_DRIVER_NAME
    Define CS_DRIVER_NAME for "DRIVER_NAME"
#ENDIF

#IFNDEF CS_DATABASE_NAME
    Define CS_DATABASE_NAME for "DATABASE_NAME"
#ENDIF 

#IFNDEF CS_SCHEMA_NAME
    Define CS_SCHEMA_NAME for "SCHEMA_NAME"
#ENDIF

#IFNDEF CS_TABLE_CHARACTER_FORMAT
    Define CS_TABLE_CHARACTER_FORMAT for "TABLE_CHARACTER_FORMAT"
#ENDIF

#IFNDEF CS_USE_DUMMY_ZERO_DATE 
    Define CS_USE_DUMMY_ZERO_DATE for "USE_DUMMY_ZERO_DATE"
#ENDIF

#IFNDEF CS_SYSTEM_FILE 
    Define CS_SYSTEM_FILE for "SYSTEM_FILE"
#ENDIF  

#IFNDEF CS_RECNUM_TABLE
    Define CS_RECNUM_TABLE for "RECNUM_TABLE"
#ENDIF    

#IFNDEF CS_PRIMARY_INDEX
    Define CS_PRIMARY_INDEX for "PRIMARY_INDEX"
#ENDIF

#IFNDEF CS_INDEX_NUMBER
    Define CS_INDEX_NUMBER for "INDEX_NUMBER"
#ENDIF

#IFNDEF CS_INDEX_NAME
    Define CS_INDEX_NAME for "INDEX_NAME"
#ENDIF

#IFNDEF ghoDbUpdateHandler
    Global_Variable Handle ghoDbUpdateHandler
#ENDIF     

#IFNDEF ghoDbUpdateFunctionLibrary
    Global_Variable Handle ghoDbUpdateFunctionLibrary
#ENDIF                                

#IFNDEF _struct_tSQLScriptArray
Struct tSQLScriptArray
    Boolean bError   
    Boolean bArgumentSizeChanged
    Integer iOrgArgumentSize
    String[] sSQLScriptArray  
End_Struct 
#ENDIF
       
#IFNDEF _struct_tSqlErrorArray
Struct tSqlErrorArray    
    String[]  sSqlErrorArray
    String[]  sSqlStatementArray
    Integer[] iSqlErrorArray
End_Struct
#ENDIF    
    
#IFNDEF _struct_tSqlColumnNew
Struct tSqlColumnNew
    String  sBaseColumnName
    String  sBaseTableName
    String  sLabel
    Integer iSqlType
    Integer iSize
    Integer iPrecision
    Integer iDFType
    Integer iDFNativeType
End_Struct
#ENDIF

#IFNDEF struct_tColumnType
Struct tColumnType
    String  sType
    Integer iType  
    String  sDataFlexType
    Integer iDataFlexType 
    String  sPrecision  
    Boolean bFixedSize
End_Struct  
#ENDIF

// Used to store/retreive SQL keywords in a struct array.
// Various SQL back-ends can have slightly different
// keywords.
#IFNDEF struct_tSQLKeyWords
Struct tSQLKeyWords
    Integer iSQLWord
    Integer iSQLDbType
    String  sSQLPhrase // Can be more than one word.
End_Struct  
#ENDIF

#IFNDEF struct_tSQLRelation
Struct tSQLRelation
    Integer iFileNumber
    Integer iFieldNumber
    String  sFileName
    String  sFieldName
End_Struct  
#ENDIF 

#IFNDEF struct_tSQLLoggedInUser
Struct tSQLLoggedInUser
    String sUser
    String sProgram
End_Struct
#ENDIF

// Used as a start for error handing. Used by Error_Report_Mode property
#IFNDEF DUF_ERROR_REPORT
Enumeration_List
    Define DUF_ERROR_REPORT    // Report Error on screen
    Define DUF_ERROR_NO_REPORT // Show no Error..
End_Enumeration_List
#ENDIF

// SQL Back-ends (iSQLDbType in the tSQLKeywords struct).
// They can have slightly different SQL keywords. 
// Note: If a new type is added to the list,
//       the struct array xxx must be adjusted
//       so that it is filled with all SQL
//       keywords for that new type.
Enum_List
    Define EN_DbTypeMSSQL
    Define EN_DbTypeMySQL
    Define EN_DbTypeOracle
    Define EN_DbTypeDB2 
    Define EN_DbTypePostgre 
    Define EN_DbTypeDataFlex // Embedded database.
End_Enum_List 

// We need to have our "own" constants for the standard DataFlex data types.
// These can be used with SQL functions such as e.g. SQLColumnAdd, instead
// of using one of the driver specific integer constants such as e.g. "SQL_VARCHAR".
// We need to re-define the standard constants because several driver constants
// have the same value and we need to be able to distinguish which data type to use when
// e.g. creating a column with embedded SQL (ESQL).
Enum_List 
    Define DF_ASCII_DUF     for 1500
    Define DF_BCD_DUF       for 1499
    Define DF_BINARY_DUF    for 1494
    Define DF_DATE_DUF      for 1498
    Define DF_DATETIME_DUF  for 1493
    Define DF_TEXT_DUF      for 1495
End_Enum_List

Define CS_DbTypeMSSQL       for "Microsoft SQL Server"
Define CS_DbTypeMySQL       for "MySQL"
Define CS_DbTypeOracle      for "Oracle"
Define CS_DbTypeDB2         for "IBM DB2"
Define CS_DbTypePostgre     for "PostgreSQL"
Define CS_DbTypeDataFlex    for "DataFlex Embedded"

#IFNDEF SQL_TEXT
    Define SQL_TEXT for (DF_TEXT + 1024)
#ENDIF 

Define SQL_CHARBIT          for (DF_BINARY + 1024)
Define SQL_LONGVARCHARBIT   for (DF_BINARY + 1025)
Define SQL_VARCHARBIT       for (DF_BINARY + 1026)

Struct tSQLIntTableInfo
    String sDriverName
    String sServerName
    String sDatabaseName
    String sSchemaName             
    Boolean bRecnumTable
    Integer iPrimaryIndex          
    Integer iGenerateRecordIdMethod  // RIM_NONE, RIM_IDENTITY_COLUMN,  RIM_DISPENSER_TABLE, RIM_EXTERNAL
    String sTableCharacterFormat
    Boolean bUseDummyZeroDate   
    Integer iFileDummyUpdateColumn // Init value to -1 if not exists (value can be in range 1 - number of columns)  
    Integer iFileBlockSize         // Init value to -1 if not exists  
    Integer iFileMaxRowsFetched    // Init value to -1 if not exists  
    Integer iFileGetRidAfterCreate // Init value to -1. But is boolean! 
    Integer iFileJitBinding        // Init value to -1. But is boolean!  
    String sRefindAfterSave        // Yes or No (how to handle?) 
    String sSystemFile             // Yes or No (how to handle?) 
    String sFileIndexTablespace  
    String sFileLongTablespace
    String sTableTablespace
End_Struct           

Struct tSQLIntColumnInfo
    Integer iFieldNumber
    Integer iFieldIndex
    Integer iFieldRelatedFile
    Integer iFieldRelatedField
    Integer iIndexNumber 
    Integer iIndexNumberSegments      // Men d� finns det inte n�got index namn?
    Integer iIndexSegmentField1
    Integer iIndexSegmentField2
    Integer iIndexSegmentFieldn
    String sIndexName
End_Struct


// SQL Key-Word Constants: 
// Used by the _FindKeyWord function to return a proper keyword depending on the backend SQL,
// i.e. one of the EN_DbTypeXXX members from the Enum_list above. 
// E.g. the CI_SQLAlterTable is only defined once, but the _FindKeyWord function can return
// different wording content depending on the EN_xxx value also passed to the function.
Enum_List
    Define CI_SQLAlterTable            //for "ALTER TABLE"
    Define CI_SQLAlterColumn           //for "ALTER COLUMN" 
    Define CI_SQLRenameColumn          //for "RENAME COLUMN" 
    Define CI_SQLColumn                //for "COLUMN" 
    Define CI_SQLSelect                //for "SELECT"
    Define CI_SQLWhere                 //for "WHERE"
    Define CI_SQLInfoSchema            //for "INFORMATION_SCHEMA.COLUMNS"
    Define CI_SQLTable_Name            //for "TABLE_NAME"
    Define CI_SQLTable                 //for "TABLE"
    Define CI_SQLSys                   //for "SYS" 
    Define CI_SQLSp_Help               //for "SP_HELP"
    Define CI_SQLFrom                  //for "FROM" 
    Define CI_SQLAdd                   //for "ADD" 
    Define CI_SQLDropColumn            //for "DROP"       
    Define CI_SQLCreateDatabase        //for "CREATE DATABASE"
    Define CI_SQLCreateTable           //for "CREATE TABLE"
    Define CI_SQLDropTable             //for "DROP TABLE"
    Define CI_SQLCreateView            //for "CREATE VIEW"
//    Define CI_SQLSelectFromWhereName   //for "SELECT name from [master].[dbo].[sysdatabases] where name"
    Define CI_SQLDropView              //for "DROP VIEW"
    Define CI_SQLSetNoCountOn          //for "SET NOCOUNT ON" 
    Define CI_SQLTo                    //for "TO" 
    Define CI_SQLGO                    //for "GO" 
    Define CI_SQLUse                   //for "USE"  
    Define CI_SQLDBO                   //for "DBO"
    
    Define CI_SQLName                  //for "NAME"                               
    Define CI_SQLMaster                //for "MASTER"                                    
    Define CI_SQLDatabases             //for "DATABASES"
    Define CI_SQLSysIndexes            //for "SYS.INDEXES"
    Define CI_SQLObjectID              //for "OBJECT_ID"
    Define CI_SQLID                    //for "ID"
    Define CI_SQLAND                   //for "AND"
    Define CI_SQLUpdate                //for "UPDATE" 
    Define CI_SQLSet                   //for "SET"  
    Define CI_SQLNotNull               //for "NOT NULL"
End_Enum_List

#COMMAND SQLIncludeScriptFile _TR "AS" _R
    #Set Q$ DF_RESOURCE_TYPE_LINE     // default to binary.
    #Replace !3.RSC |CI!ZR            // create unique resource id.
    #Resource !1 !Zr !q !3            // register new resource.
#ENDCOMMAND
