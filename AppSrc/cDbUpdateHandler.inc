// Constant declarations, structs etc. for the cDbUdpateHandler class.
//
Use VdfBase.pkg   
Use DUFLanguageConstants.inc

#IFNDEF _struct_tDbUpdateError
Struct tDbUpdateError
    Number nUpdateVersion
    Integer iError
    String  sErrorText
    Integer iErrorLine
    Boolean bError
End_Struct
#ENDIF    

//  DF_FILE_ALIAS_DEFAULT if no master or alias
//  DF_FILE_IS_MASTER if master
//  DF_FILE_IS_ALIAS if alias
#IFNDEF _struct_tDbUpdateHandlerMasterAlias
Struct tDbUpdateHandlerMasterAlias
    Handle hTable
    Integer iMode
End_Struct
#ENDIF

// Used as a start for error handing. Used by Error_Report_Mode property
#IFNDEF DUF_ERROR_REPORT
Enumeration_List
    Define DUF_ERROR_REPORT    // Report Error on screen
    Define DUF_ERROR_NO_REPORT // Show no Error..
End_Enumeration_List
#ENDIF

#IFNDEF DATAFLEX_ID
    Define DATAFLEX_ID for "DATAFLEX"
#ENDIF

// Global handle to a cDatabaseUpdateHandler object that can be used to
// communicate with the object from anywhere in a program.
#IFNDEF ghoDbUpdateHandler
    Global_Variable Handle ghoDbUpdateHandler
#ENDIF     

// NOTE: If the DbVersion table should _not_ be used and you
// instead sets the "Set Data_File_Field to (RefTable(MyTable)) (RefTable(MyTable.DbUpdateVersion))"
// in the cDbUpdateHandler object; Add a "Define DUF_Use_DbVersion" to your code
#IFNDEF DUF_Use_Custom_DbVersion   
    Declare_Datafile DbVersion
#ENDIF
