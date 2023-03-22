Use Dfclient.pkg
Use Cursor.pkg
Use Batchdd.pkg
Use cButton.pkg
Use cDbUpdateFunctionLibrary.pkg
Use DUFStatusPanel.pkg
Use seq_chnl.pkg
Use vWin32fh.pkg

Define CS_ReportFileName           for "DUFCompareReport"
Define CS_ReportFileNameExtenstion for ".txt"
Define CS_ReportDifferenceNote     for "(*)"
Define CS_ReportFieldNotFound      for "Field doesn't exist!"
Define CS_ReportHeaderUnderWrite   for "===================================================================================="

Define CI_ReportColumn1            for 15
Define CI_ReportColumn2            for 50
Define CI_ReportColunn3            for 65
Define CI_ReportColunn4            for 80

Activate_View Activate_oCompareDatabases_vw for oCompareDatabases_vw
Object oCompareDatabases_vw is a dbView
    Set Size to 216 521
    Set Label to "Compare Databases"
    Set piMinSize to 89 211
    Set Location to 2 2
    Set Border_Style To Border_Thick
    Set pbAutoActivate to True
    Set Icon to "DbCompare.ico"
    
    Property String psOrgOpenPath
    
    // Set psOrgOpenPath at startup
    Procedure StartUp
        String sOrgOpenPath sDataPath
        Get_Attribute DF_OPEN_PATH to sOrgOpenPath
        // First remove the current Data folder path
        Get PathAtIndex of (phoWorkspace(ghoApplication)) sOrgOpenPath 1 to sDataPath
        Move (Replace(sDataPath, sOrgOpenPath, "")) to sOrgOpenPath
        If (Left(sOrgOpenPath, 2) = "\;") Begin
            Move (Replace("\;", sOrgOpenPath, "")) to sOrgOpenPath
        End
        Set psOrgOpenPath to sOrgOpenPath
    End_Procedure                        

    Object oInfo_tb is a TextBox
        Set Auto_Size_State to False
        Set Size to 25 424
        Set Location to 12 19
        Set Label to "This will compare two Filelist.cfg files and write the differences as a text report. It will try to find a DUF SQLConnections.ini in the Programs folder - or if not found a DAW DFConnId.ini file in the Data folder, to be able to open SQL tables. After the compare has been run, click the 'Tag Filelist Diff' button to tag all tables with differences on the 'Code Generator' view."
        Set Justification_Mode to JMode_Left
        Set peAnchors to anTopLeftRight
    End_Object
    Send StartUp
    
    Object oFilelistPathFrom_fm is a Form
        Set Size to 13 486
        Set Location to 55 19
        Set Label to "Please select the FROM database Filelist.cfg (F4)"
        Set Label_Col_Offset to 0
        Set Label_Row_Offset to 1
        Set Label_Justification_Mode to JMode_Top
        Set Prompt_Button_Mode to PB_PromptOn
        Set peAnchors to anTopLeftRight 
        Set Prompt_Object to Self
        
        Procedure Prompt
            String sFileName sPath sFileMask sRetval

            Get Value to sFileName
            Get ParseFolderName sFileName to sPath
            Move "Filelist.cfg files (*.cfg)|*.cfg" to sFileMask
            Get vSelect_File sFileMask "Please select a Filelist.cfg file" sPath to sRetval
            If (sRetval <> "") Begin
                Set Value to sRetval
            End
        End_Procedure 
        
        Procedure OnChange
            String sValue
            Get Value to sValue
            Set psFilelistFrom of ghoApplication to sValue
        End_Procedure

        On_Key Key_Ctrl+Key_W Send None
        On_Key Key_Ctrl+Key_Q Send None
    End_Object

    Object oFilelistPathTo_fm is a Form
        Set Size to 13 486
        Set Location to 83 19
        Set Label to "Please select the TO database Filelist.cfg (F4)"
        Set Label_Col_Offset to 0
        Set Label_Row_Offset to 1
        Set Label_Justification_Mode to JMode_Top
        Set Prompt_Button_Mode to PB_PromptOn
        Set peAnchors to anTopLeftRight 
        Set Prompt_Object to Self
        
        Procedure Prompt
            String sFileName sPath sFileMask sRetval

            Get Value to sFileName
            Get ParseFolderName sFileName to sPath
            Move "Filelist.cfg files (*.cfg)|*.cfg" to sFileMask
            Get vSelect_File sFileMask "Please select a Filelist.cfg file" sPath to sRetval
            If (sRetval <> "") Begin
                Set Value to sRetval
            End
        End_Procedure  
        
        Procedure OnChange
            String sPath sReportName sToday
            Date dToday
            
            Sysdate dToday
            Move (Replaces("/", dToday, "-")) to sToday
            Get Value to sPath
            Get ParseFolderName sPath to sPath
            Get vFolderFormat   sPath to sPath
            Move (sPath + CS_ReportFileName + String(sToday) + CS_ReportFileNameExtenstion) to sReportName
            Set Value of oReportFileName_fm to sReportName
        End_Procedure

        On_Key Key_Ctrl+Key_W Send None
        On_Key Key_Ctrl+Key_Q Send None
    End_Object

//    Object oCompareType_rg is a RadioGroup
//        Set Location to 75 19
//        Set Size to 33 486
//        Set Label to "Compare Type"
//        Set peAnchors to anTopLeftRight
//    
//        Object oRadio1 is a Radio
//            Set Auto_Size_State to False
//            Set Label to "Write Comparison Report"
//            Set Size to 10 100
//            Set Location to 14 10
//        End_Object
//    
//        Object oRadio2 is a Radio
//            Set Auto_Size_State to False
//            Set Label to "Tag Tables in Filelist.cfg containing differences (for Code Generation)"
//            Set Size to 10 260
//            Set Location to 14 136
//        End_Object
//    
//        Procedure Notify_Select_State Integer iToItem Integer iFromItem
//            Forward Send Notify_Select_State iToItem iFromItem
//            Set Enabled_State of oReportFileName_fm     to (iToItem = 0) 
//            Set Enabled_State of oCompareProperties_grp to (iToItem = 0) 
//            Set pbTagFileNames of ghoApplication to (iToItem = 1) 
//            Set Enabled_State of oOK_Btn to (iToItem = 0)
//        End_Procedure
//
//    End_Object

    Object oCompareProperties_grp is a Group
        Set Size to 45 486
        Set Location to 112 19
        Set Label to "Compare Properties"

        Object oCompareDate_DataTime_cb is a CheckBox
            Set Auto_Size_State to False
            Set Size to 9 123
            Set Location to 14 10
            Set Label to "Check Date/DataTime difference"
            Set Checked_State to False
            Set psToolTip to "Check Date to DateTime column differences"
        End_Object

        Object oCompareIndexAscending_cb is a CheckBox
            Set Auto_Size_State to False
            Set Size to 9 134
            Set Location to 14 137
            Set Label to "Check Index Ascending/Descending"
            Set Checked_State to False
            Set psToolTip to "Compare if Index is Ascending/Descending. (In SQL this setting is set for the whole database by selecting a 'Collation', so then checking this per table doesn't make sense)"
        End_Object

        Object oCompareIndexUppercase_cb is a CheckBox
            Set Auto_Size_State to False
            Set Size to 9 117
            Set Location to 14 276
            Set Label to "Check Index Lower/Uppercase"
            Set Checked_State to False
            Set psToolTip to "Compare if Index is Uppercase/Lowercase. (In SQL this setting is set for the whole database by selecting a 'Collation', so then checking this per table doesn't make sense)"
        End_Object

        Object oIgnoreFilelistUppercase_cb is a CheckBox
            Set Auto_Size_State to False
            Set Size to 9 210
            Set Location to 27 10
            Set Label to "Ignore Filelist Entries Uppercase/Lowercase"
            Set Checked_State to True
            Set psToolTip to "Check Filelist.cfg RootName, LogicalName and DisplayName uppercase/lowercase differences"
        End_Object

    End_Object

    Object oReportFileName_fm is a Form
        Set Size to 13 486
        Set Location to 176 19
        Set Label to "Report File Name"
        Set Label_Col_Offset to 0
        Set Label_Row_Offset to 1
        Set Label_Justification_Mode to JMode_Top
        Set Prompt_Button_Mode to PB_PromptOn
        Set peAnchors to anTopLeftRight 
        Set Prompt_Object to Self
        
        Procedure Prompt
            String sFileName sPath sFileMask sRetval

            Get Value to sFileName
            Get ParseFolderName sFileName to sPath
            Move "Text files (*.txt)|*.txt" to sFileMask
            Get vSelect_File sFileMask "Please select a text file for the report" sPath to sRetval
            If (sRetval <> "") Begin
                Set Value to sRetval
            End
        End_Procedure

        On_Key Key_Ctrl+Key_W Send None
        On_Key Key_Ctrl+Key_Q Send None
    End_Object

    Function ChangeFilelistPathing String sFileList Returns Boolean
        String sPath sSQLConnectionsIniName sDataPath sDriverID sServer sOrgOpenPath
        Boolean bExists 
        Handle hoDbUpdateHandler hoSQLConnectionHandler hoSQLConnectionIniFile hTable
        tSQLConnection SQLConnection 
        Number nVersionNumber                
        Integer iRetval
        
        Move False to Err
        Get vFilePathExists sFileList to bExists
        If (bExists = False) Begin
            Function_Return False
        End  
        
        Get psDriverID of ghoDbUpdateFunctionLibrary to sDriverID      
        Get psServer   of ghoDbUpdateFunctionLibrary to sServer
        Close DF_ALL
        Logout sDriverID sServer
        
        Set psFileList of (phoWorkspace(ghoApplication))   to sFileList
        Set_Attribute DF_FILELIST_NAME                     to sFileList 
        Get ParseFolderName sFileList                      to sDataPath
        If (Right(sDataPath, 1) = "\") Begin
            Move (Left(sDataPath, (Length(sDataPath) -1))) to sDataPath
        End
        Set psDataPath of (phoWorkspace(ghoApplication))   to sDataPath 
        
        // Temporarily "redirect" the Open path to the current Data folder
        Get psOrgOpenPath to sOrgOpenPath
        Set_Attribute DF_OPEN_PATH to (sDataPath + ";" + sOrgOpenPath)

        Get vFolderFormat sDataPath to sPath            
        // Note: We delete all cache files (*.cch) before
        // attempting to open any tables as a precausion, in case the table has been changed at the SQL end:
        Get vDeleteFile (sPath + "*.cch") to iRetval

        Get vParentPath sDataPath to sPath  
        Get vFolderFormat sPath   to sPath                           
        Move (sPath + "Programs") to sPath
        Get vFolderFormat sPath   to sPath                           
        Move CS_SQLIniFileName to sSQLConnectionsIniName
        Get vFilePathExists (sPath + sSQLConnectionsIniName) to bExists
        If (bExists = False) Begin
            Get YesNo_Box ("Couldn't find the Programs\SQLConnections.ini file. If this is an SQL database this program won't be able to open any table. Continue?") to iRetval
            If (iRetval <> MBR_Yes) Begin
                Function_Return False
            End
        End
        Else Begin
            Get phoDbUpdateHandler of ghoApplication to hoDbUpdateHandler
            Get phoSQLConnectionHandler of hoDbUpdateHandler to hoSQLConnectionHandler
            Get phoSQLConnectionIniFile of hoSQLConnectionHandler to hoSQLConnectionIniFile
            Set psIniFilePath of hoSQLConnectionIniFile to sPath
            Set psIniFileName of hoSQLConnectionIniFile to sSQLConnectionsIniName

            Get SetupSQLConnection of hoSQLConnectionHandler True to SQLConnection
            Set pSQLConnection     of hoSQLConnectionHandler to SQLConnection 
        End                      
        Function_Return (Err = False)
    End_Function  
    
    Procedure Reset_DF_OPEN_PATH
        String sOrgOpenpath
        Get psOrgOpenPath to sOrgOpenpath
        Set_Attribute DF_OPEN_PATH to sOrgOpenPath
    End_Procedure

    Procedure StartComparing
        String sFilelistFrom sFilelistTo 
        Integer[] iaDifferences    
        Integer iSize iRetval
        Boolean bFromExists bToExists 
        tAPITableBooleans CompareTableBooleans
        
        Get Value of oFilelistPathFrom_fm to sFilelistFrom
        Get vFilePathExists sFilelistFrom to bFromExists
        Get Value of oFilelistPathTo_fm   to sFilelistTo
        Get vFilePathExists sFilelistTo   to bToExists  
        
        If (bFromExists = False or bToExists = False) Begin
            Send Info_Box "You first need to select a 'From' and a 'To' Filelist.cfg."
            Procedure_Return
        End

//        Get pbTagFileNames of ghoApplication to bTagFileNames
        Get Checked_State of oCompareDate_DataTime_cb    to CompareTableBooleans.bCompareDate_DateTime
        Get Checked_State of oCompareIndexAscending_cb   to CompareTableBooleans.bCompareIndexAscending
        Get Checked_State of oCompareIndexUppercase_cb   to CompareTableBooleans.bCompareIndexUppercase
        Get Checked_State of oIgnoreFilelistUppercase_cb to CompareTableBooleans.bCompareFilelistUppercase
        
        Get CompareDatabases sFilelistFrom sFilelistTo CompareTableBooleans to iaDifferences
        Set piaDifferences of ghoApplication to iaDifferences

//        If (bTagFileNames = False) Begin        
        Send Stop_StatusPanel of ghoStatusPanel
        Move (SizeOfArray(iaDifferences)) to iSize
        If (iSize > 0) Begin
            Get YesNo_Box ("Ready!" * String(iSize) * "Differences found. View the report now?") to iRetval
            If (iRetval = MBR_Yes) Begin
                Send KeyAction of oViewReport_Btn
            End
        End 
        Else If (iaDifferences[0] <> -1) Begin
            Send Info_Box "No differences found. The two databases are identical."
        End
        Else If (iaDifferences[0] = -1) Begin
            Send Info_Box "Process interrupted."
        End
//        End
//        Else Begin
//            Send Close_Panel
//        End
    End_Procedure

    Function CompareDatabases String sFilelistFrom String sFilelistTo tAPITableBooleans CompareTableBooleans Returns Integer[]
        Integer iSize iSizeFrom iSizeTo iCount iItemFrom iItemTo iNoOfTables
        Boolean bIsSame bFilelistError bIsAlias bUserCancel bOK
        Handle hTable hTableFrom hTableTo
        String sLogicalName 
        tAPITable[] aFromStructure    aToStructure
        Integer[] iaDifferences iaDifferencesEmpty
        
        Set Message_Text of ghoStatusPanel to ""
        // Set up the pathing correctly for the 'FROM' Filelist.cfg so we can open tables:
        Get ChangeFilelistPathing sFilelistFrom to bOK
        If (bOK = False) Begin 
            Move -1 to iaDifferences[0]
            Function_Return iaDifferencesEmpty
        End
        Set pbVisible of ghoProgressBar to True
        Set pbVisible of ghoProgressBarOverall to True
        Get UtilFilelistNoOfTables of ghoDbUpdateFunctionLibrary to iNoOfTables
        Set piMaximum of ghoProgressBarOverall to iNoOfTables
        
        // Fill the 'From' structure with data:
        Get UtilTableStructFill of ghoDbUpdateFunctionLibrary True True to aFromStructure
        
        // Set up the pathing correctly for the 'To' Filelist.cfg so we can open tables:
        Get ChangeFilelistPathing sFilelistTo to bOK
        If (bOK = False) Begin
            Move -1 to iaDifferences[0]
            Function_Return iaDifferencesEmpty
        End
        
        // Fill the 'To' structure with data:
        Get UtilTableStructFill of ghoDbUpdateFunctionLibrary True False to aToStructure

        // Make the comparison:
        Set Message_Text of ghoStatusPanel to "Comparing Tables:"
        Move 0 to hTable
        Move 0 to iCount
        Move (SizeOfArray(aFromStructure)) to iSizeFrom  
        Move (SizeOfArray(aToStructure))   to iSizeTo
        Move (iSizeFrom max iSizeTo)       to iSize 
        Set piMaximum of ghoProgressBarOverall to iSize  
        Decrement iSize 
        
        For iCount from 0 to iSize                 
            Move True to bIsSame                   
            Set piPosition of ghoProgressBarOverall to iCount
            Get FindArrayItem aFromStructure aToStructure iCount (&hTable) (&iItemFrom) (&iItemTo) to sLogicalName
            Set Action_Text of ghoStatusPanel to ("Name:" * sLogicalName * "Number:" * String(hTable))  
            If (iItemFrom > -1 and iItemTo > -1) Begin
                Get UtilTableCompare_Ex of ghoDbUpdateFunctionLibrary aFromStructure[iItemFrom] aToStructure[iItemTo] CompareTableBooleans False (&bFilelistError) to bIsSame
            End 
            Else Begin
                Move True to bFilelistError
            End
            If (bFilelistError = True or bIsSame = False) Begin
                Move hTable to iaDifferences[SizeOfArray(iaDifferences)]
            End
                    
            Get Check_StatusPanel of ghoStatusPanel to bUserCancel
            If (bUserCancel = True) Begin
                Send Stop_StatusPanel of ghoStatusPanel
                Send Info_Box "Process interrupted..."
                Function_Return iaDifferencesEmpty
            End
        Until (hTable = 0)    
        
//        If (bTagFileNames = False) Begin        
//            Move (SizeOfArray(iaDifferences)) to iSize
//            If (iSize > 0) Begin
        Send WriteDifferenceReport (&aFromStructure) (&aToStructure) (&iaDifferences) (&CompareTableBooleans)
//            End 
//        End

        Function_Return iaDifferences
    End_Function  
    
    Function FindArrayItem tAPITable[] aFromStructure tAPITable[] aToStructure Integer iCount Handle ByRef hTable Integer ByRef iItemFrom Integer ByRef iItemTo Returns String
        Integer iSizeFrom iSizeTo   
        Handle hTableFrom hTableTo
        String sLogicalName
        
        Move (SizeOfArray(aFromStructure)) to iSizeFrom
        Move (SizeOfArray(aToStructure))   to iSizeTo

        Move -1 to hTableFrom
        Move -1 to hTableTo
        Move iCount to iItemFrom
        Move iCount to iItemTo
        
        // The two struct arrays may be different in size (contain different number of items/tables). 
        //
        // To avoid "Referenced Array Index Out of Bounds" error.
        If (iCount < iSizeFrom) Begin
            Move aFromStructure[iCount].ApiTableInfo.iTableNumber to hTableFrom
        End
        If (iCount < iSizeTo) Begin
            Move aToStructure[iCount].ApiTableInfo.iTableNumber   to hTableTo
        End
        If (hTableFrom <> -1 and hTableTo <> -1) Begin
            Move (hTableFrom min hTableTo)                to hTable
        End
        Else Begin
            Move (hTableFrom max hTableTo)                to hTable
        End
                
        If (iCount < iSizeFrom and hTableFrom <= hTableTo) Begin
            Move aFromStructure[iCount].ApiTableInfo.sLogicalName to sLogicalName                                                       
            Get FindTableNumber aToStructure hTable to iItemTo
        End 
        
        // If the 'To' table number is lower than 'From'
        Else If (iCount < iSizeTo) Begin
            Move aToStructure[iCount].ApiTableInfo.sLogicalName to sLogicalName                                                       
            Get FindTableNumber aFromStructure hTable to iItemFrom
        End              
        Else If (iCount = iSizeTo) Begin
            Get FindTableNumber aToStructure hTable to iItemTo
        End              
        
        Function_Return sLogicalName
    End_Function
    
    Function FindTableNumber tAPITable[] ByRef aTableStructure Handle hTable Returns Integer
        Integer iSize iCount iTable iItem
        tAPITableNameInfo ApiTableNameInfo
        
        Move -1 to iItem
        Move (SizeOfArray(aTableStructure)) to iSize
        Decrement iSize
        For iCount from 0 to iSize
            Move aTableStructure[iCount].ApiTableInfo to ApiTableNameInfo
            If (ApiTableNameInfo.iTableNumber = hTable) Begin
                Move iCount to iItem
                Move iSize  to iCount // We're done.
            End
        Loop
        
        Function_Return iItem
    End_Function
    
    Procedure WriteDifferenceReport tAPITable[] ByRef aFromStructure tAPITable[] ByRef aToStructure Integer[] ByRef iaDifferences tAPITableBooleans ByRef CompareTableBooleans
        Integer iCh iSize iCount iItem iErrors iItemFrom iItemTo iItems
        String sFilelistFrom sFilelistTo sReportName sDriverID sLogicalName sFrom sTo sRootName sTableName
        Handle hTable
        Boolean bCompareDate_DateTime bCompareIndexUppercase bCompareIndexAscending bCompareFilelistUppercase
        Boolean bIsSame bExistsFrom bExistsTo bUserCancel bIsSQLFrom bIsSQLTo
        DateTime dtCreationTime
        tAPITableNameInfo APITableNameInfoFrom APITableNameInfoTo
        tAPIColumn[]   APIColumnsFrom   APIColumnsTo
        tAPIIndex[]    APIIndexesFrom   APIIndexesTo
        tAPIRelation[] APIRelationsFrom APIRelationsTo
        
        Get Value of oReportFileName_fm   to sReportName
        Get Seq_Open_Output_Channel sReportName to iCh
        If (iCh = DF_SEQ_CHANNEL_ERROR) Begin
            Send Stop_Box "Sorry, couldn't retrieve a free channel number."
            Procedure_Return
        End
        
        Move 0 to iItems
        Get Value of oFilelistPathFrom_fm to sFilelistFrom
        Get Value of oFilelistPathTo_fm   to sFilelistTo
        Move CompareTableBooleans.bCompareDate_DateTime     to bCompareDate_DateTime
        Move CompareTableBooleans.bCompareIndexAscending    to bCompareIndexAscending
        Move CompareTableBooleans.bCompareIndexUppercase    to bCompareIndexUppercase
        Move CompareTableBooleans.bCompareFilelistUppercase to bCompareFilelistUppercase
        Move (CurrentDateTime()) to dtCreationTime
        Set Action_Text of ghoStatusPanel to "Writing difference report..."
               
        Writeln channel iCh ("/" + "/ *** The Database Update Framework (DUF)    ***")
        Writeln channel iCh ("/" + "/ *** Compare Report: Database Differences   ***")
        Writeln channel iCh ("/" + "/ *** Created at:" * String(dtCreationTime) + "    ***")
        Writeln channel iCh ("/" + "/")
        Writeln channel iCh ("/" + "/ FROM: Database Filelist.cfg -" * String(sFilelistFrom))
        Writeln channel iCh ("/" + "/ TO  : Database Filelist.cfg -" * String(sFilelistTo))
        Writeln channel iCh ("/" + "/")  
        Writeln channel iCh ("/" + "/ Note: An asterisk in paranthesis (*) denotes that there is a difference!")
        Writeln channel iCh 
        
        Move 0 to iErrors
        Move (SizeOfArray(iaDifferences)) to iSize
        Set piMaximum of ghoProgressBarOverall to iSize  
        Decrement iSize
        
        For iCount from 0 to iSize
            Set piPosition of ghoProgressBarOverall to iCount
            Move iaDifferences[iCount] to hTable  
            Get FindTableNumber aFromStructure hTable               to iItemFrom
            Get FindTableNumber aToStructure hTable                 to iItemTo
            Move aFromStructure[iItemFrom].ApiTableInfo.bIsSQL      to bIsSQLFrom
            Move aFromStructure[iItemTo].ApiTableInfo.bIsSQL        to bIsSQLTo
            Move aFromStructure[iItemFrom].ApiTableInfo.sDriverID   to sDriverID
            
            If (iItemFrom <> -1) Begin
                Move aFromStructure[iItemFrom].ApiTableInfo to APITableNameInfoFrom
                Move APITableNameInfoFrom.sLogicalName      to sLogicalName
            End
            If (iItemTo <> -1) Begin
                Move aToStructure[iItemTo].ApiTableInfo to APITableNameInfoTo
                Move APITableNameInfoTo.sLogicalName    to sLogicalName
            End
                    
            Set Message_Text of ghoStatusPanel to "Writing difference(s) for table:"
            Set Action_Text of ghoStatusPanel  to (String(hTable) * String(APITableNameInfoFrom.sLogicalName))
                
            // Table Names:
            Get UtilTableInfoCompare of ghoDbUpdateFunctionLibrary bCompareFilelistUppercase APITableNameInfoFrom APITableNameInfoTo to bIsSame
            If (bIsSame = False) Begin
                Send WriteTableInfoDiff APITableNameInfoFrom APITableNameInfoTo iCh 
                Increment iItems
            End
            
            // Check if both tables exists: (Else the header text will say so and there is no point in showing columns.)
            Move (iItemFrom > 0) to bExistsFrom
            Move (iItemTo > 0)   to bExistsTo
                
            // Column Check:
            If (bExistsFrom = True and bExistsTo = True) Begin
                Move aFromStructure[iItemFrom].aApiColumns         to APIColumnsFrom
                Move aToStructure[iItemTo].aApiColumns             to APIColumnsTo  
                Move aFromStructure[iItemFrom].ApiTableInfo.bIsSQL to bIsSQLFrom
                Move aToStructure[iItemTo].ApiTableInfo.bIsSQL     to bIsSQLTo
                Get UtilColumnsCompare of ghoDbUpdateFunctionLibrary sDriverID bIsSQLFrom bIsSQLTo APIColumnsFrom APIColumnsTo bCompareDate_DateTime to bIsSame
                If (bIsSame = False) Begin  
                    // If array size = 0 the table doesn't exist.
                    If (SizeOfArray(APIColumnsFrom) <> 0 and SizeOfArray(APIColumnsTo) <> 0) Begin
                        Send WriteColumnInfoDiff sDriverID hTable APITableNameInfoFrom.sLogicalName bIsSQLFrom bIsSQLTo APIColumnsFrom APIColumnsTo bCompareDate_DateTime iCh
                        Increment iItems
                    End
                End
                
                // Index Check:
                Move aFromStructure[iItemFrom].aApiIndexes to APIIndexesFrom
                Move aToStructure[iItemTo].aApiIndexes     to APIIndexesTo
                Get UtilIndexesCompare of ghoDbUpdateFunctionLibrary hTable APIIndexesFrom APIIndexesTo bCompareIndexUppercase bCompareIndexAscending to bIsSame
                If (bIsSame = False) Begin
                    Send WriteIndexInfoDiff hTable APITableNameInfoFrom.sLogicalName APIIndexesFrom APIIndexesTo bCompareIndexUppercase bCompareIndexAscending iCh
                End
                
                // Relations Check:
                Move aFromStructure[iItemFrom].aApiRelations to APIRelationsFrom
                Move aToStructure[iItemTo].aApiRelations     to APIRelationsTo
                Get UtilRelationsCompare of ghoDbUpdateFunctionLibrary hTable APIRelationsFrom APIRelationsTo to bIsSame
                If (bIsSame = False) Begin
                    Send WriteRelationInfoDiff hTable APIRelationsFrom APIRelationsTo iCh
                End
            End

            Get Check_StatusPanel of ghoStatusPanel to bUserCancel
            If (bUserCancel = True) Begin
                Move iSize to iCount
            End
        Loop 
        
        If (bUserCancel = False) Begin
            Writeln channel iCh
            Writeln channel iCh "SUMMARY:"                                                   
            Writeln channel iCh CS_ReportHeaderUnderWrite
            Writeln channel iCh "Number of Tables with differences: " (String(iSize + 1))
        End
        
        Send Seq_Close_Channel iCh  
        Send Stop_StatusPanel of ghoStatusPanel
    End_Procedure                                                                
    
    Function MakeStringLength String sValue Integer iReportColumnPos Returns String
        Move (Pad(sValue, (Length(sValue) + (iReportColumnPos - Length(sValue))))) to sValue
        
        Function_Return sValue
    End_Function
    
    // Note: The rootname will be first be stripped if it contains any driver id prefix.
    Procedure WriteTableInfoDiff tAPITableNameInfo APITableNameInfoFrom tAPITableNameInfo APITableNameInfoTo Integer iCh
        String sRootNameFrom sRootNameTo  
        Boolean bExistsFrom bExistsTo 
        Handle hTableFrom hTableTo hTable
        
        Move APITableNameInfoFrom.iTableNumber to hTableFrom
        Move (hTableFrom > 0)                  to bExistsFrom
        Move APITableNameInfoFrom.sRootName    to sRootNameFrom
        Move APITableNameInfoTo.iTableNumber   to hTableTo
        Move (hTableTo > 0)                    to bExistsTo
        Move APITableNameInfoTo.sRootName      to sRootNameTo 
        Move (If(hTableFrom > 0, hTableFrom, hTableTo)) to hTable
        
        Writeln channel iCh
        Writeln channel iCh "Table Name Difference(s) Table Number: " hTable
        Writeln channel iCh CS_ReportHeaderUnderWrite
        If (bExistsFrom = False) Begin
            Writeln channel iCh "*** This table does not exist in the 'FROM' database! ***"
        End
        If (bExistsTo = False) Begin
            Writeln channel iCh "*** This table does not exist in the 'TO' database! ***"
        End
        Writeln channel iCh "Logical Name From/To: " APITableNameInfoFrom.sLogicalName "     " APITableNameInfoTo.sLogicalName
        Writeln channel iCh "Root Name From/To:    " sRootNameFrom                 "     " sRootNameTo
        Writeln channel iCh "Display Name From/To: " APITableNameInfoFrom.sDisplayName "     " APITableNameInfoTo.sDisplayName
        Writeln channel iCh
    End_Procedure

    Procedure WriteColumnInfoDiff String sDriverID Handle hTable String sLogicalTableName Boolean bIsSQLFrom Boolean bIsSQLTo tAPIColumn[] APIColumnsFrom tAPIColumn[] APIColumnsTo Boolean bCompareDate_DateTime Integer iCh 
        Integer iSize iSizeFrom iSizeTo iCount iDbType iFromType iToType
        Boolean bIsSame   
        String sFrom sTo sTypeFrom sTypeTo 
        
        Get piDbType of ghoDbUpdateFunctionLibrary to iDbType
        
        Writeln channel iCh "Field Difference(s) for Table Number: " (String(hTable)) " - " sLogicalTableName
        Writeln channel iCh CS_ReportHeaderUnderWrite
        // Logical Name:
//                        Move ("Logical Name: " * String(APITableNameInfoFrom.sLogicalName))     to sFrom
//                        Move (Pad(sFrom, (Length(sFrom) + (CI_ReportColumn2 - Length(sFrom))))) to sFrom
//                        Move (String(APITableNameInfoTo.sLogicalName))                          to sTo
//                        Writeln channel iCh sFrom sTo

        // Root Name:
//                        Move ("Root Name   : " * String(APITableNameInfoFrom.sRootName))            to sFrom
//                        Move (String(APITableNameInfoTo.sRootName))                                 to sTo
//                        Move (Pad(sFrom, (Length(sFrom) + (CI_ReportColumn2 - Length(sFrom))))) to sFrom
//                        Writeln channel iCh sFrom sTo
        
//                        Move ("Display Name: " * String(APITableNameInfoFrom.sDisplayName))         to sFrom
//                        Move (String(APITableNameInfoTo.sDisplayName))                              to sTo
//                        Move (Pad(sFrom, (Length(sFrom) + (CI_ReportColumn2 - Length(sFrom))))) to sFrom
//                        Writeln channel iCh sFrom sTo

//        Writeln channel iCh
        Move "FROM Database:" to sFrom 
        Get MakeStringLength sFrom CI_ReportColumn2 to sFrom
        Move (sFrom + "TO Database:") to sFrom
        Writeln channel iCh sFrom
        Move (Repeat("-", Length(sFrom))) to sFrom
        Writeln channel iCh sFrom

        // Any of the 'From' or 'To' table may have more fields then the other...
        Move (SizeOfArray(APIColumnsFrom)) to iSizeFrom
        Move (SizeOfArray(APIColumnsTo))   to iSizeTo
        Move (iSizeFrom max iSizeTo)       to iSize
        Decrement iSize
        For iCount from 0 to iSize                                                            
            // Field exists in 'From' but not in 'To'
            If (iCount >= iSizeTo) Begin
                // Field Number:
                Get MakeStringLength "Number:" CI_ReportColumn1                 to sFrom
                Move (sFrom + String(APIColumnsFrom[iCount].iFieldNumber))      to sFrom
                Get MakeStringLength sFrom CI_ReportColumn2                     to sFrom
                Writeln channel iCh sFrom
                
                // Field Name:
                Get MakeStringLength "Name:" CI_ReportColumn1                   to sFrom
                Move (sFrom + String(APIColumnsFrom[iCount].sFieldName))        to sFrom
                Get MakeStringLength sFrom CI_ReportColumn2                     to sFrom
                Move (String(CS_ReportFieldNotFound * CS_ReportDifferenceNote)) to sTo
                Writeln channel iCh sFrom sTo
                
                Get MakeStringLength "Type:" CI_ReportColumn1                   to sFrom
                Move (sFrom + String(APIColumnsFrom[iCount].sType))             to sFrom
                Get MakeStringLength sFrom CI_ReportColumn2                     to sFrom
                Writeln channel iCh sFrom 
                
                // Field Length:    
                Get MakeStringLength "Length:" CI_ReportColumn1                 to sFrom
                Move (sFrom + String(APIColumnsFrom[iCount].iLength))           to sFrom
                Get MakeStringLength sFrom CI_ReportColumn2                     to sFrom
                Writeln channel iCh sFrom 
                
                // Field Precision: 
                Get MakeStringLength "Precision:" CI_ReportColumn1              to sFrom
                Move (sFrom + String(APIColumnsFrom[iCount].iPrecision))        to sFrom
                Get MakeStringLength sFrom CI_ReportColumn2                     to sFrom
                Writeln channel iCh sFrom
            End 

            // Field exists in 'To' but not in 'From'
            Else If (iCount >= iSizeFrom) Begin
                // Field Number:
                Get MakeStringLength "Number:" CI_ReportColumn1                         to sFrom
                Move (sFrom + String(APIColumnsTo[iCount].iFieldNumber))                to sTo
                Writeln channel iCh sFrom sTo
                
                // Field Name:
                Get MakeStringLength "Name:" CI_ReportColumn1                           to sFrom
                Move (sFrom + String(CS_ReportFieldNotFound * CS_ReportDifferenceNote)) to sFrom
                Get MakeStringLength sFrom CI_ReportColumn2                             to sFrom
                Move (String(APIColumnsTo[iCount].sFieldName))                          to sTo
                Writeln channel iCh sFrom sTo
                
                Get MakeStringLength "Type:"                                            to sFrom
                Move (String(APIColumnsTo[iCount].sType))                               to sTo
                Writeln channel iCh sFrom sTo
                
                // Field Length:    
                Get MakeStringLength "Length:"                                          to sFrom
                Move (String(APIColumnsTo[iCount].iLength))                             to sTo
                Writeln channel iCh sFrom sTo
                
                // Field Precision: 
                Get MakeStringLength "Precision:"                                       to sTo
                Move (String(APIColumnsTo[iCount].iPrecision))                          to sTo
                Writeln channel iCh sFrom sTo
            End                                                                             
            
            If (iCount < iSizeFrom and iCount < iSizeTo) Begin
                Get UtilColumnCompare of ghoDbUpdateFunctionLibrary sDriverID bIsSQLFrom bIsSQLTo APIColumnsFrom[iCount] APIColumnsTo[iCount] bCompareDate_DateTime to bIsSame

                If (bIsSame = False) Begin
                    // Field Number:
                    Get MakeStringLength "Number:" CI_ReportColumn1                     to sFrom
                    Move (sFrom + String(APIColumnsFrom[iCount].iFieldNumber))          to sFrom
                    Get MakeStringLength sFrom CI_ReportColumn2                         to sFrom
                    Move (String(APIColumnsTo[iCount].iFieldNumber))                    to sTo
                    If (APIColumnsFrom[iCount].iFieldNumber <> APIColumnsTo[iCount].iFieldNumber) Begin
                        Move (sTo * String(CS_ReportDifferenceNote))                    to sTo
                    End
                    Writeln channel iCh sFrom sTo
                    
                    // Field Name:
                    Get MakeStringLength "Name:" CI_ReportColumn1                       to sFrom
                    Move (sFrom + String(APIColumnsFrom[iCount].sFieldName))            to sFrom
                    Get MakeStringLength sFrom CI_ReportColumn2                         to sFrom
                    Move (String(APIColumnsTo[iCount].sFieldName))                      to sTo
                    If (APIColumnsFrom[iCount].sFieldName <> APIColumnsTo[iCount].sFieldName) Begin
                        Move (sTo * String(CS_ReportDifferenceNote))                    to sTo
                    End
                    Writeln channel iCh sFrom sTo
                    
                    // Field Type:                         
                    Move APIColumnsFrom[iCount].sType to sTypeFrom
                    Move APIColumnsTo[iCount].sType   to sTypeTo
                    Move APIColumnsFrom[iCount].iType to iFromType
                    Move APIColumnsTo[iCount].iType   to iToType

                    // If one of the two tables is SQL and the other Embedded we need to "translate"
                    // data types between Embedded and SQL, to be able to check if they are different or not.
                    If (bIsSQLFrom = True and bIsSQLTo = False) Begin
                        Get UtilSqlColumnTypeToDataFlexType of ghoDbUpdateFunctionLibrary sDriverID iDbType iFromType APIColumnsFrom[iCount].iLength to iFromType
                    End
                    Else If (bIsSQLFrom = False and bIsSQLTo = True) Begin
                        Get UtilSqlColumnTypeToDataFlexType of ghoDbUpdateFunctionLibrary sDriverID iDbType iToType   APIColumnsTo[iCount].iLength   to iToType
                    End
                    Move (iFromType = iToType) to bIsSame

                    Get MakeStringLength "Type:" CI_ReportColumn1                           to sFrom
                    Move (sFrom + sTypeFrom)                                                to sFrom
                    Get MakeStringLength sFrom CI_ReportColumn2                             to sFrom
                    Move (String(sTypeTo))                                                  to sTo
                    If (bIsSame = False) Begin
                        Move (sTo * String(CS_ReportDifferenceNote))                        to sTo
                    End
                    Writeln channel iCh sFrom sTo
                    
                    // Field Length:    
                    Get MakeStringLength "Length:" CI_ReportColumn1                         to sFrom
                    Move (sFrom + String(APIColumnsFrom[iCount].iLength))                   to sFrom
                    Get MakeStringLength sFrom CI_ReportColumn2                             to sFrom
                    Move (String(APIColumnsTo[iCount].iLength))                             to sTo
                    If (APIColumnsFrom[iCount].iLength <> APIColumnsTo[iCount].iLength) Begin
                        Move (sTo * String(CS_ReportDifferenceNote))                        to sTo
                    End
                    Writeln channel iCh sFrom sTo
                    
                    // Field Precision: 
                    Get MakeStringLength "Precision:" CI_ReportColumn1                      to sFrom
                    Move (sFrom + String(APIColumnsFrom[iCount].iPrecision))                to sFrom
                    Get MakeStringLength sFrom CI_ReportColumn2                             to sFrom
                    Move (String(APIColumnsTo[iCount].iPrecision))                          to sTo
                    If (APIColumnsFrom[iCount].iPrecision <> APIColumnsTo[iCount].iPrecision) Begin
                        Move (sTo * String(CS_ReportDifferenceNote))                        to sTo
                    End
                    Writeln channel iCh sFrom sTo
                End
            End
        Loop
    End_Procedure  
    
    Procedure WriteIndexInfoDiff Handle hTable String sLogicalTableName tAPIIndex[] APIIndexFrom tAPIIndex[] APIIndexTo Boolean bCompareIndexUppercase Boolean bCompareIndexAscending Integer iCh 
        Integer iSize iCount iSegmentSizeFrom iSegmentSizeTo iCount2 iSize2
        tAPIIndexSegment[] aApiIndexSegmentsFrom aApiIndexSegmentsTo
        String sFrom sTo
        
        Writeln channel iCh "Index Difference(s) for Table Number: " (String(hTable)) " - " sLogicalTableName
        Writeln channel iCh CS_ReportHeaderUnderWrite
        Move (SizeOfArray(APIIndexFrom)) to iSize
        Decrement iSize
        For iCount from 0 to iSize  
            Get MakeStringLength "Index Number:" CI_ReportColumn1 to sFrom
            Writeln channel iCh (sFrom + String(APIIndexFrom[iCount].iIndexNumber))
            If (APIIndexFrom[iCount].sSQLIndexName <> "") Begin
                Get MakeStringLength "SQL FROM Index Name:" CI_ReportColumn1 to sFrom
                Writeln channel iCh (sFrom + String(APIIndexFrom[iCount].sSQLIndexName) * "SQL TO Index Name:" * String(APIIndexTo[iCount].sSQLIndexName))
                Get MakeStringLength "SQL FROM Index Type:" CI_ReportColumn1 to sFrom
                Writeln channel iCh (sFrom + String(APIIndexFrom[iCount].iSQLIndexType) * "SQL TO Index Type:" * String(APIIndexTo[iCount].iSQLIndexType))
            End                             
            Move APIIndexFrom[iCount].IndexSegmentArray to aApiIndexSegmentsFrom
            Move APIIndexTo[iCount].IndexSegmentArray   to aApiIndexSegmentsTo
            Move (SizeOfArray(aApiIndexSegmentsFrom))   to iSegmentSizeFrom
            If (iSegmentSizeFrom <> 0) Begin
                Move (SizeOfArray(aApiIndexSegmentsTo))     to iSegmentSizeTo  
                Move (iSegmentSizeFrom max iSegmentSizeTo)  to iSize2
                Decrement iSize2   

                Get MakeStringLength "Field Number:" CI_ReportColumn1 to sFrom
                Move (sFrom + "Field Name:") to sFrom
                Get MakeStringLength sFrom           CI_ReportColumn2 to sFrom
                Move (sFrom + "Uppercase:")                           to sFrom
                Get MakeStringLength sFrom           CI_ReportColunn3 to sFrom
                Move (sFrom + "Ascending:")                           to sFrom
                Writeln channel iCh sFrom
                Move (Repeat("-", Length(sFrom))) to sFrom
                Writeln channel iCh sFrom
                
                For iCount2 from 0 to iSize2
                    Get MakeStringLength ("From: " + String(aApiIndexSegmentsFrom[iCount2].iFieldNumber)) CI_ReportColumn1 to sFrom // Field Number
                    Move (sFrom + String(aApiIndexSegmentsFrom[iCount2].sFieldName)) to sFrom                      // Field Name
                    Get MakeStringLength sFrom CI_ReportColumn2                      to sFrom   
                    If (bCompareIndexUppercase = True) Begin
                        Move (sFrom + String(If(aApiIndexSegmentsFrom[iCount2].bUppercase = 1, "Yes","No")))  to sFrom // Uppercase
                    End 
                    Else Begin
                        Move (sFrom + String("N/A")) to sFrom
                    End
                        
                    Get MakeStringLength sFrom CI_ReportColunn3     to sFrom
                    If (bCompareIndexAscending = True) Begin
                        Move (sFrom + String(If(aApiIndexSegmentsFrom[iCount2].bAscending = 1, "Yes", "No"))) to sFrom // Ascending
                    End 
                    Else Begin
                        Move (sFrom + String("N/A")) to sFrom
                    End
                        
                    Writeln channel iCh sFrom
                    
                    If (iCount2 < iSegmentSizeTo) Begin
                        Get MakeStringLength ("To  : " + String(aApiIndexSegmentsTo[iCount2].iFieldNumber))   CI_ReportColumn1 to sTo // Field Number
                        Move (sTo + String(aApiIndexSegmentsTo[iCount2].sFieldName))     to sTo                      // Field Name   
                        If (aApiIndexSegmentsFrom[iCount2].sFieldName <> aApiIndexSegmentsTo[iCount2].sFieldName) Begin
                            Move (sTo * String(CS_ReportDifferenceNote)) to sTo
                        End
                        Get MakeStringLength sTo CI_ReportColumn2                        to sTo
                        If (bCompareIndexUppercase = True) Begin
                            Move (sTo + String(If(aApiIndexSegmentsTo[iCount2].bUppercase = 1, "Yes", "No"))) to sTo // Uppercase
                        End
                        Else Begin
                            Move (sTo + String("N/A")) to sTo
                        End
                            
                        Get MakeStringLength sTo CI_ReportColunn3     to sTo
                        If (bCompareIndexAscending = True) Begin
                            Move (sTo + String(If(aApiIndexSegmentsTo[iCount2].bAscending = 1, "Yes", "No"))) to sTo // Ascending
                        End 
                        Else Begin
                            Move (sTo + String("N/A")) to sTo
                        End
                            
                        Writeln channel iCh sTo                                                    
                    End
                Loop
                Writeln channel iCh
            End
        Loop
    End_Procedure                                                 
    
    Procedure WriteRelationInfoDiff Handle hTable tAPIRelation[] APIRelationFrom tAPIRelation[] APIRelationTo Integer iCh 
        Integer iSizeFrom iSizeTo iCount
        Boolean bExists bOK  
        String sFrom sTo sFromFields sToFields
        
        Writeln channel iCh ""
        Writeln channel iCh "Relation Difference(s) for Table Number: " (String(hTable)) " - " APIRelationFrom[0].sLogicalNameFrom
        Writeln channel iCh CS_ReportHeaderUnderWrite
        Move "FROM Database:" to sFrom
        Get MakeStringLength sFrom CI_ReportColumn2 to sFrom
        Move (sFrom + "TO Database:") to sFrom
        Writeln channel iCh sFrom
        Move (Repeat("-", Length(sFrom))) to sFrom
        Writeln channel iCh sFrom

        Move (SizeOfArray(APIRelationFrom)) to iSizeFrom
        Move (SizeOfArray(APIRelationTo))   to iSizeTo
        Decrement iSizeFrom
        For iCount from 0 to iSizeFrom
            Move ("Relation: " + String(iCount + 1)) to sFrom
            Get MakeStringLength sFrom CI_ReportColumn1 to sFrom
            Move (sFrom + "Table.Field:" * String(APIRelationFrom[iCount].hTableFrom) + "." + String(APIRelationFrom[iCount].iColumnFrom) * "->") to sFrom
            Move (sFrom * String(APIRelationFrom[iCount].hTableTo) + "." + String(APIRelationFrom[iCount].iColumnTo)) to sFrom
            Get MakeStringLength sFrom CI_ReportColumn2 to sFrom
            Move (String(APIRelationFrom[iCount].sLogicalNameFrom) + "." + String(APIRelationFrom[iCount].sFieldNameFrom) * "->") to sFromFields
            Move (sFromFields * String(APIRelationFrom[iCount].sLogicalNameTo)   + "." + String(APIRelationFrom[iCount].sFieldNameTo)) to sFromFields

            Move (iCount < iSizeTo) to bExists  
            If (bExists = True) Begin
                Move ("Table.Field:" * String(APIRelationTo[iCount].hTableFrom) + "." + String(APIRelationTo[iCount].iColumnFrom) * "->") to sTo
                Move (sTo * String(APIRelationTo[iCount].hTableTo) + "." + String(APIRelationTo[iCount].iColumnTo)) to sTo
                Move (APIRelationFrom[iCount].hTableFrom = APIRelationTo[iCount].hTableFrom and APIRelationFrom[iCount].hTableTo = APIRelationTo[iCount].hTableTo) to bOK
                If (bOK = True) Begin
                    Move (APIRelationFrom[iCount].iColumnFrom = APIRelationTo[iCount].iColumnFrom and APIRelationFrom[iCount].iColumnTo = APIRelationTo[iCount].iColumnTo) to bOK
                End
                If (bOK = False) Begin
                    Move (sTo * String(CS_ReportDifferenceNote)) to sTo
                End
                Move (" 'TO:'" * String(APIRelationTo[iCount].sLogicalNameFrom) + "." + String(APIRelationTo[iCount].sFieldNameFrom) * "->") to sToFields
                Move (sToFields * String(APIRelationTo[iCount].sLogicalNameTo) + "." + String(APIRelationTo[iCount].sFieldNameTo)) to sToFields 
                Get MakeStringLength sToFields CI_ReportColumn2 to sToFields
//                Move (Pad(sToFields, (Length(sToFields) + (CI_ReportColumn2 - Length(sToFields))))) to sToFields
            End
            If (bExists = False) Begin
                Move ("Relationship doesn't exist!" * String(CS_ReportDifferenceNote)) to sTo  
                Move "" to sToFields
            End
            
            Writeln channel iCh sFrom sTo 
            Writeln channel iCh sFromFields sToFields  
            If (iCount < iSizeFrom) Begin
                Writeln channel iCh
            End
        Loop
    
    End_Procedure                                                 
    
    Object oBusinessProcess is a BusinessProcess  
        Set Status_Panel_Id to ghoStatusPanel
        Set Allow_Cancel_State to True
        Set Process_Caption to "The Database Update Framework"
        Set Process_Title to "Comparing Database Structures..."
//        Set Process_Message to "...for table:"
//        Set Display_Error_State to True // Temp!
    
        Procedure OnProcess
            Send StartComparing
        End_Procedure                           
        
        Procedure Ignore_Error Integer iError
        End_Procedure                        
        Procedure Trap_Error Integer iError
        End_Procedure 
        
    End_Object

    Object oOK_Btn is a Button
        Set Size to 14 47
        Set Label to "Compare!"
        Set Location to 195 334
        Set peAnchors to anBottomRight
        Set FontWeight to fw_Bold
        Set Default_State to True

        Procedure OnClick
            String sFilelistFrom sFilelistTo 
            Integer[] iaDifferences                         
            Boolean bFromExists bToExists 
            
            Get Value of oFilelistPathFrom_fm to sFilelistFrom
            Get vFilePathExists sFilelistFrom to bFromExists
            Get Value of oFilelistPathTo_fm   to sFilelistTo
            Get vFilePathExists sFilelistTo   to bToExists
            If (bFromExists = False or bToExists = False) Begin
                Send Info_Box "You need to both select a FROM and a TO database Filelist.cfg. Please adjust and try again."
                Procedure_Return
            End
            
            Send DoProcess of oBusinessProcess
            Send Reset_DF_OPEN_PATH
        End_Procedure   
        
    End_Object

    Object oViewReport_Btn is a cButton
        Set Label    to "View Report"
        Set Location to 195 392
        Set peAnchors to anBottomRight

        Procedure OnClick
            String sReportName                            
            Get Value of oReportFileName_fm to sReportName
            Send vShellExecute "open" sReportName "" "" 
        End_Procedure

        Procedure DoEnable
            String sReportName
            Boolean bExists

            Get Value of oReportFileName_fm to sReportName
            Get vFilePathExists sReportName to bExists
            Set Enabled_State to (bExists = True)
        End_Procedure

    End_Object

    Object oTagFilelist_Btn is a Button
        Set Size to 14 58
        Set Label     to "&Tag Filelist Diff"
        Set psToolTip to "Tag Tables in Filelist.cfg containing differences (for Code Generation) on the 'Code Generator' view page."
        Set Location to 195 448
        Set peAnchors to anBottomRight

        Procedure OnClick 
            Send TagFileNamesForCodeGeneration
        End_Procedure

    End_Object  
    
    // TEMP!
    Set Value of oFilelistPathFrom_fm to "C:\DataFlex 19.0 Examples\Order Entry - Embedded Test 1\Data\Filelist.cfg"
    Set Value of oFilelistPathTo_fm   to "C:\DataFlex 19.0 Examples\Order Entry - Embedded Test 2\Data\Filelist.cfg"
    
    On_Key Key_Alt+Key_O Send KeyAction of oOK_Btn
    On_Key Key_Alt+Key_T Send KeyAction of oCancel_Btn
End_Object

//Procedure Activate_CompareDatabases String sFileListFrom
//    Handle ho hoFilelistFrom hoTableDUFCodeGenerator_vw
//    Boolean bTagFileNames                                                  
//    Integer[] iaDifferences    
//    
//    Move (oCompareDatabases_vw(Self)) to ho
//    Move (oFilelistPathFrom_fm(ho)) to hoFilelistFrom
//    If (sFileListFrom <> "") Begin
//        Set Value of hoFilelistFrom to sFileListFrom
//    End
//    
//    Send Popup of ho               
//    Send Activate_oCompareDatabases_vw
//    
//    Get pbTagFileNames of ho to bTagFileNames
//    If (bTagFileNames = False) Begin
//        Procedure_Return
//    End                 
//    
//    Get Value of hoFilelistFrom to sFileListFrom
//    Get piaDifferences    of ho to iaDifferences
//    Get phoTableDUFCodeGenerator_vw of ghoApplication to hoTableDUFCodeGenerator_vw
//    Send TagChangedTables of hoTableDUFCodeGenerator_vw sFileListFrom iaDifferences
//End_Procedure
