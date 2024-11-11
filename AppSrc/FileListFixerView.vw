Use Windows.pkg
Use Dfclient.pkg
Use MSSqldrv.pkg 
Use db2_drv.pkg
Use odbc_drv.pkg
Use seq_chnl.pkg
Use File_dlg.pkg
Use cRichEdit.pkg
Use cRDCForm.pkg
Use cRDCButton.pkg
Use cDbUpdateFunctionLibrary.pkg
Use cRDCComboForm.pkg
Use cRDCCheckbox.pkg
Use cNumForm.pkg
Use cMyRichEdit.pkg
Use vWin32fh.pkg
Use DriverIntFileSettings.dg

// Just to get a shorter handle name
Global_Variable Handle ghoDUF 
Move ghoDbUpdateFunctionLibrary to ghoDUF

Define CS_ReportFileName for "FileListFixes.txt"
Define CS_BackupFolder   for "Backup"

Struct tBlock
    Integer iFieldNumber
    String[] asLines    
End_Struct

Activate_View Acivate_oFileListFixerView for oFileListFixerView
Object oFilelistFixerView is a dbView 
    Set Location to 2 1
    Set Size to 456 691
    Set piMinSize to 425 691
    Set Maximize_Icon to True
    Set Border_Style to Border_Thick
    Set pbAutoActivate to True

    Set phoFilelistFixerView of ghoApplication to Self
    
    Property String psFileList ""
    Property String psConnId   ""
    Property String psConnIdFile ""
    Property Boolean pbOpenLogFile False
    Property Integer piChannel -1  
    
    Object oFilelist_fm is a cRDCForm
        Set Size to 12 387
        Set Location to 14 77
        Set Label to "Filelist.cfg:" 
        Set Prompt_Object to Self
        
        Property Boolean pbFirst True
        
        Procedure Prompt
            String sFileName sPath sFileMask sRetval
            Get Value to sFileName
            Get ParseFolderName sFileName to sPath
            Move "Filelist.cfg files (*.cfg)|*.cfg" to sFileMask
            Get vSelect_File sFileMask "Please select a Filelist.cfg file" sPath to sRetval
            If (sRetval <> "") Begin
                Send ClearData
                Set Value to sRetval
            End
        End_Procedure
        
        Procedure Set Value Integer iItem String sValue
            Forward Set Value iItem to sValue
            Set psFileList to sValue
        End_Procedure

        Procedure OnChange
            String sFileList sPath
            Boolean bExists bCfgFile bOK

            Get Value to sFileList
            Get vFilePathExists sFileList to bExists
            Move (Lowercase(sFileList) contains ".cfg") to bCfgFile
            If (bExists = True and bCfgFile = True) Begin
                // A little trick to show the filelist.cfg in the form before we start filling the control.
                Send PumpMsgQueue of Desktop
                Get ChangeFilelistPathing of ghoApplication sFileList to bOK
                If (bOK = True) Begin
                    Set psFilelistFrom of ghoApplication to sFileList
                    Send UpdateConnIdData of oConnidInfo_edt
                    Get ChangeFilelistPathing of ghoApplication sFileList to bOK
                    Send UpdateDriverIniFile of oDriver_fm
                    Get ParseFolderName sFileList to sPath
                    Get vFolderFormat sPath to sPath
                    Set Value of oLogFile_fm to (sPath + CS_ReportFileName)
                    // We can't do this when the program starts, because it will make 
                    // the runtime go bananas with the status_panel(!) 
                    If (Value(oDriver_fm) <> "" and pbFirst(Self) = False) Begin
                        Send ShowSQLTablesCount
                    End
                End
            End   
        End_Procedure

        Procedure Page Integer iPageObject
            String sFileName
            
            Forward Send Page iPageObject
            Get psFilelistFrom of ghoApplication to sFileName
            If (sFileName = "") Begin
                Get psFileList of (phoWorkspace(ghoApplication)) to sFileName
            End
            Set Value to sFileName
            Set pbFirst to False
        End_Procedure
        
    End_Object

    Object oSelectFilelist_btn is a cRDCButton
        Set Size to 12 50
        Set Location to 14 470
        Set Label to "Select"
        Set peAnchors to anNone
        Set psImage to "ActionOpen.ico"
    
        Procedure OnClick
            Send Prompt of oFilelist_fm
        End_Procedure
    
    End_Object

    Object oRefresh_btn is a cRDCButton
        Set Size to 30 61
        Set Location to 3 530
        Set Label to "Refresh Data!"
        Set Default_State to True
        Set Form_FontWeight to fw_Bold
        Set psToolTip to "Refreshes all data by reading the Filelist.cfg and SQL database tables (F5)" 
        Set psImage to "ActionRefresh.ico"
        Set piImageSize to 32
        Set MultiLineState to True
        Set peAnchors to anNone
        
        Procedure OnClick
            Send RefreshData
        End_Procedure
    
    End_Object

    Object oSQL_grp is a Group
        Set Size to 142 673
        Set Location to 35 12
        Set Label to "SQL Settings:"
        Set peAnchors to anTopLeftRight

        Object oConnidInfo_edt is a cMyRichEdit
            Set Size to 75 449
            Set Location to 23 5
            Set peAnchors to anNone
            Set Skip_State to True
            
            Procedure Page Integer iPageObject
                Forward Send Page iPageObject
                Send UpdateConnIdData
            End_Procedure
            
            Procedure UpdateConnIdData
                String sDFConnidFile sText sDatapath sDatabase
                Boolean bExists
                tConnection[] Connections
                
                If (ghoConnection = 0) Begin
                    Procedure_Return
                End
                
                Send Delete_Data
                Set Label to ""
                Get psDataPath of (phoWorkspace(ghoApplication)) to sDatapath
                File_Exist (sDatapath + "\" + String(C_ConnectionIniFileName)) bExists
                If (bExists = True) Begin
                    Move (sDatapath + "\" + String(C_ConnectionIniFileName)) to sDFConnidFile
                End
                Else Begin
                    Procedure_Return
                End
                
                Get ConnectionIDs of ghoConnection to Connections
                If (SizeOfArray(Connections) <> 0) Begin
                    Set psConnId to Connections[0].sId
                    Set psConnIdFile to sDFConnidFile
//                    Send AppendTextLn ("DFConnId File=" + String(sDFConnidFile))  
                    Set Label to ("DFConnId File=" + String(sDFConnidFile))  
                    Send AppendTextLn ""
                    Send AppendTextLn ("id=" + String(Connections[0].sId))
                    Send AppendTextLn ("driver=" + String(Connections[0].sDriver))
                    Send AppendTextLn ("connection=" + String(Connections[0].sString))
                    Send AppendTextLn ("trusted_connection=" + String(Connections[0].bTrustedConnection))
                    Send AppendTextLn ("disabled=" + String(Connections[0].bDisabled)) 
                    Send Beginning_of_Data  
                    Get psDatabase of ghoDUF to sDatabase
                    Set Value of oDatabase_fm to sDatabase
                End   
                Else Begin
                    Send AppendTextLn "No DFConnid.ini file found, or no active connection."
                End
            End_Procedure
    
        End_Object
        
        Object oEditDFConnIt_btn is a cRDCButton
            Set Size to 12 50
            Set Location to 23 458
            Set Label to "Edit"
            Set peAnchors to anNone
            Set psImage to "ActionEdit.ico"
        
            Procedure OnClick
                String sFileName
                Get psConnIdFile to sFileName
                Runprogram Shell Background sFileName
            End_Procedure
        
            Function IsEnabled Returns Boolean
                Boolean bExists
                String sFileName
                Get psConnIdFile to sFileName
                File_Exist sFileName bExists
                Function_Return bExists
            End_Function
    
        End_Object
        
        Object oDriver_fm is a cRDCForm
            Set Size to 12 387
            Set Location to 103 66
            Set Label to "Driver .int file:"
            Set peAnchors to anNone
            
            Procedure Page Integer iPageObject
                Forward Send Page iPageObject 
                Send UpdateDriverIniFile
            End_Procedure
            
            Procedure UpdateDriverIniFile
                String sFileName sPath sDriver sExt
                Boolean bExists
                Integer iPos
                
                Get psDataPath of (phoWorkspace(ghoApplication)) to sPath
                Get vFolderFormat sPath to sPath
                Get psDriverID of ghoDUF to sDriver
                Set Enabled_State to (sDriver <> DATAFLEX_ID) 
                Set Enabled_State of oViewDriverProperties_btn to (sDriver <> DATAFLEX_ID) 
                If (sDriver = DATAFLEX_ID) Begin
                    Procedure_Return    
                End 
                Move (Pos(".", sDriver)) to iPos
                Move (Left(sDriver, iPos -1)) to sFileName
                Move (sFileName + ".int") to sFileName
//                Set Label to sFileName
                
                File_Exist (sPath + sFileName) bExists
                If (bExists = False) Begin
                    Get_File_Path sFileName to sFileName   
                End
                Else Begin
                    Move (sPath + sFileName) to sFileName
                End
                Set Value to sFileName
            End_Procedure
            
        End_Object    
        
        Object oViewDriverProperties_btn is a cRDCButton
            Set Size to 12 50
            Set Location to 103 458
            Set Label to "View"
            Set peAnchors to anNone
            Set psImage to "View.ico"
        
            Procedure OnClick
                String sFileName
                Get Value of oDriver_fm to sFileName
                Send ActivateDriverIntSettingsDialog sFileName     
            End_Procedure
        
        End_Object
        
        Object oDatabase_fm is a cRDCForm
            Set Label to "Database Name:"
            Set Size to 12 387
            Set Location to 119 66
            Set Label_Col_Offset to 0
            Set peAnchors to anNone
            Set Label_Row_Offset to 1
//            Set Label_FontWeight to fw_Bold
    //        Set FontWeight to fw_Bold
        End_Object
        
        Object oConnIDErrors_edt is a cMyRichEdit
            Set Size to 74 77
            Set Location to 23 517
            Set Label to "DFCONNID Changes:"
            Set peAnchors to anTopLeftRight
            Set Label_Col_Offset to -5
        End_Object
        
        Object oConnIDErrors_btn is a cRDCButton
            Set Size to 32 61
            Set Location to 23 600
            Set Label to "Change .int files to use DFConnid"
            Set psToolTip to "Changes or updates all .int files in the Data folder - except for DAW driver .int files (MSSQL_DRV.int, DB2_DRV.int & ODBC_DRV.int) - to use 'SERVER_NAME DFCONNID=xxx', where xxx is the 'id=' of the DFConnid.ini file displayed to the left."
            Set peAnchors to anTopRight
            Set MultiLineState to True
    
            Procedure OnClick
                String sDataPath sConnectionID sText
                String[] asFileChanges
                Boolean bExists bActive bOK
                Integer iRetval iSize iCount 
                Handle ho
    
                Get psDataPath of (phoWorkspace(ghoApplication)) to sDataPath
                Get psConnId to sConnectionID
                Get YesNo_Box ("Do you want to change all .int files in folder:\n" + sDataPath + "\n\nTo use 'DFCONNID=" + sConnectionID +"' ?") to iRetval
                If (iRetval <> MBR_Yes) Begin
                    Procedure_Return
                End
                
                Move 0 to iCount
                Set Value of oConnIDErrors_fm to 0
                Move oConnIDErrors_edt to ho     
                Send Delete_Data of ho
                Send StartStatusPanel "Changing to Connection ID's in .int files" "" -1
    
                Get SqlUtilChangeIntFilesToConnectionIDs of ghoDUF sDataPath sConnectionID True to asFileChanges
    
                Send UpdateStatusPanel ""
                Get Active_State of ghoStatusPanel to bActive
                If (bActive = False) Begin
                    Send StopStatusPanel
                    Send Info_Box "Process interupted..."
                    Procedure_Return
                End
    
                Move (SizeOfArray(asFileChanges)) to iSize
                Set Value of oConnIDErrors_fm to (iSize max 0)
                Send StopStatusPanel
                If (SizeOfArray(asFileChanges) <> 0) Begin
                    Decrement iSize
                    For iCount from 0 to iSize
                        Send AppendTextLn of ho asFileChanges[iCount]
                    Loop       
                    Send Beginning_of_Data of ho
                    // Note: Remove all cache-files:
                    EraseFile (sDataPath + "\*.cch")
                    Send RefreshData
                    Send Info_Box ("Ready!" * String(iSize + 1) * ".int files contained errors and were changed to be using DFConnID's.")
                End
                Else Begin
                    Send Info_Box "Ready! No problems found."    
                End
                Send StopStatusPanel
            End_Procedure
    
        End_Object
        
        Object oConnIDErrors_fm is a cNumForm
            Set Size to 12 34
            Set Location to 103 560
            Set Label to "Counter:"
            Set peAnchors to anTopRight
        End_Object
        
        Object oNumberOfSQLTables_fm is a cNumForm
            Set Label to "Number of SQL Tables:"
            Set Size to 12 34
            Set Location to 119 560
            Set peAnchors to anTopRight
        End_Object
        
//        Object oCurrentCollatingSequence_fm is a cRDCForm
//            Set Size to 13 387
//            Set Location to 135 66
//            Set pbAutoEnable to True 
//            Set Label to "Current Collating"
//            
//            Procedure Page Integer iPageObject
//                String sDatabase
//    
//                Forward Send Page iPageObject
//                Get psDatabase of ghoDUF to sDatabase
//            End_Procedure 
//            
//            Procedure UpdateCollatingSequence String sDatabase
//                String sCollatingSequence
//                If (sDatabase = "") Begin
//                    Procedure_Return
//                End
//                Get SqlDatabaseCollationQuery of ghoDUF sDatabase True to sCollatingSequence
//                Set Value to sCollatingSequence
//            End_Procedure
//            
//            Function IsEnabled Returns Boolean
//                Boolean bEnabled
//                String sDatabase
//                Get psDatabase of ghoDUF to sDatabase
//                If (sDatabase <> "") Begin
//                    Send UpdateCollatingSequence sDatabase
//                End
//                Function_Return False
//            End_Function
//    
//        End_Object
//        
//        Object oCollatingSequenceHelp_btn is a cRDCButton
//            Set Size to 12 50
//            Set Location to 135 458
//            Set Label to "Help"
//            Set psImage to "ActionHelp.ico"
//        
//            Procedure OnClick
//                Runprogram Shell Background "https://learn.microsoft.com/en-us/sql/relational-databases/databases/contained-database-collations?view=sql-server-ver16"
//            End_Procedure
//        
//        End_Object
//       
//        Object oCollatingSequence_fm is a cRDCComboForm
//            Set Size to 13 387
//            Set Location to 152 66
//            Set Label to "Change Collating:"
//            Set pbAutoEnable to True            
//            Set Entry_State to True
//    
//            Procedure Combo_Fill_List
//                String sCollatingSequence
//                Send Combo_Add_Item "Latin1_General_CI_AI"
//                Send Combo_Add_Item "Latin1_General_100_CI_AI"
//                Send Combo_Add_Item "SQL_Latin1_General_CP1_CI_AI"
//                Send Combo_Add_Item "Latin1_General_CI_AS"
//                Send Combo_Add_Item "Latin1_General_100_CI_AS"
//                Send Combo_Add_Item "SQL_Latin1_General_CP1_CI_AS"  
//                Send Combo_Add_Item " Latin1_General_100_CI_AS_SC_UTF8"
//                Get Value of oCurrentCollatingSequence_fm to sCollatingSequence
//                If (sCollatingSequence <> "") Begin
//                    Send Combo_Add_Item sCollatingSequence
//                    Set Value to oCurrentCollatingSequence_fm
//                End
//                Else Begin
//                    Set Value to "Latin1_General_CI_AI"
//                End
//            End_Procedure
//    
//            Function IsEnabled Returns Boolean
//                Boolean bEnabled
//                String sDatabase
//                Get psDatabase of ghoDUF to sDatabase
//                Function_Return (sDatabase <> "")
//            End_Function
//    
//        End_Object
//        
//        Object oCollatingSequence_btn is a cRDCButton
//            Set Size to 12 50
//            Set Location to 152 458
//            Set Label to "Change"
//            Set psImage to "ActionSort.ico"
//            
//            Procedure OnClick
//                String sDatabase sCurrentCollatingSequence sCollatingSequence
//                Integer iRetval
//                Boolean bOK
//                
//                Get psDatabase of ghoDUF to sDatabase   
//                Get Value of oCurrentCollatingSequence_fm to sCurrentCollatingSequence
//                Get Value of oCollatingSequence_fm to sCollatingSequence              
//                If (sCurrentCollatingSequence = sCollatingSequence) Begin
//                    Send Info_Box "Nope that won't work. The database is already using this collating sequence."
//                    Procedure_Return
//                End
//                Get YesNo_Box ("Are you sure you want to change the collating sequence for database:" * sDatabase * "\nto use this collating sequence:\n'" + sCollatingSequence + "'?\n\nMake the change now?") to iRetval
//                If (iRetval <> MBR_Yes) Begin
//                    Procedure_Return
//                End
//                Send StartStatusPanel "Checking that nobody is using the database..." "" -1
//                
//                Get IsDatabaseInUse of ghoDUF to bOK
//                If (bOK = False) Begin
//                    Send Info_Box "Not all tables could be opened exclusivly, which indicates that somebody else is using the database. It is therefor not advised to try to change the collating sequence at current."
//                    Procedure_Return
//                End
//                Get SqlDatabaseCollationChange of ghoDUF sDatabase sCollatingSequence to bOK
//                Send StopStatusPanel
//                If (bOK = True) Begin
//                    Send Info_Box ("Success! The collating sequence was changed for database:" * sDatabase)
//                End
//                Else Begin
//                    Send Info_Box "The change of collating sequence failed, and was *not* changed."
//                End
//            End_Procedure
//        
//            Function IsEnabled Returns Boolean
//                Boolean bEnabled
//                String sDatabase
//                Get psDatabase of ghoDUF to sDatabase
//                Function_Return (sDatabase <> "")
//            End_Function
//    
//        End_Object
    
    End_Object

    Object oCount_gp is a Group
        Set Size to 166 673
        Set Location to 184 12
        Set Label to "Filelist.cfg:"
        Set peAnchors to anTopLeftRight

        Object oDatTables_edt is a cMyRichEdit
            Set Size to 110 104
            Set Location to 29 6
            Set Label to "RootName *.dat"
            Set psExtension to ".dat"
        End_Object

        Object oDatTables_fm is a cNumForm
            Set Size to 12 34
            Set Location to 144 76
            Set Label to "Counter:"
            Set peAnchors to anBottomLeft 
            Procedure OnChange
                String sVal
                Get Value to sVal
                Set Value of oNoOfDatTables2_fm to sVal
            End_Procedure
        End_Object

        Object oAliasErrors_edt is a cMyRichEdit
            Set Size to 110 104
            Set Location to 29 113
            Set Label to "Alias Table Errors"
            Set psExtension to ".int"
        End_Object

        Object oAliasErrors_fm is a cNumForm
            Set Size to 12 34
            Set Location to 144 183
            Set Label to "Counter:"
        End_Object

        Object oRootNameIntTables_edt is a cMyRichEdit
            Set Size to 110 104
            Set Location to 29 220
            Set Label to "RootName *.int"
            Set psExtension to ".int"
        End_Object

        Object oRootNameIntTables_fm is a cNumForm
            Set Size to 12 34
            Set Location to 144 290
            Set Label to "Counter:"
            Set peAnchors to anBottomLeft
        End_Object

        Object oOpenErrorTables_edt is a cMyRichEdit
            Set Size to 110 125
            Set Location to 29 327
            Set Label to "Open Table Errors"
            Set peAnchors to anTopLeftRight            
            Set psExtension to ".int"
        End_Object

        Object oOpenErrorTables_fm is a cNumForm
            Set Size to 12 34
            Set Location to 144 418
            Set Label to "Counter:"
            Set peAnchors to anBottomRight
        End_Object

        Object oFileList_grp is a Group
            Set Size to 137 209
            Set Location to 25 459
            Set Label to "FileList.cfg Counters:"
            Set peAnchors to anTopRight 

            Object oNoOfSystemTables_fm is a cNumForm
                Set Size to 12 34
                Set Location to 50 102
                Set Label to "System Tables"
            End_Object

            Object oNumberOfMasterFileListSQLTables_fm is a cNumForm
                Set Size to 12 34
                Set Location to 72 102
                Set Label to "Master Tables with SQL prefix:"
            End_Object
            
            Object oNoOfAliasSQLTables_fm is a cNumForm
                Set Size to 12 34
                Set Location to 87 102
                Set Label to "Alias Tables:"
            End_Object

            Object oNoOfDatTables2_fm is a cNumForm
                Set Size to 12 34
                Set Location to 102 102
                Set Label to "RootName *.dat Tables:"
            End_Object
            
            Object oNumberOfFileListTables_fm is a cNumForm
                Set Size to 12 34
                Set Location to 117 102
                Set Label to "Total Filelist Tables:"
                Set Label_FontWeight to fw_Bold
            End_Object

        End_Object
        
    End_Object

    Object oFixProblemsPreUpdate_grp is a Group
        Set Size to 60 448
        Set Location to 357 12
        Set Label to "Pre-Update Database Actions:"
        Set peAnchors to anNone

        // Will remove non Alias Filelist entries that:
        //   - Does not have a corresponding .Dat file, 
        Object oFixFileListErrors_btn is a cRDCButton
            Set Size to 32 61
            Set Location to 14 113
            Set Label to "1. Fix 'RootName .dat Errors'"
            Set peAnchors to anTopRight
            Set MultiLineState to True
            Set psToolTip to "The fix will spin through the Filelist and \n1. Removes non Alias entries that does not have a corresponding .Dat file.\nNote:This only applies to non Alias tables."
        
            Procedure OnClick
                Integer iRetval iCounter
                Get YesNo_Box "The fix will spin through the Filelist and \n1. Removes non Alias entries that does not have a corresponding .Dat file.\nNote:This only applies to non Alias tables.\n\nPlease take a copy of the Filelist.cfg file first!\n\nContinue?" to iRetval
                If (iRetval <> MBR_Yes) Begin
                    Procedure_Return    
                End
                
                Get FixFileListErrors to iCounter
                If (iCounter <> 0) Begin
                    Send Info_Box ("Ready! Removed" * String(iCounter) * "Filelist.cfg entries that pointed to a .dat file but the .dat file was missing, and the table was not an Alias. See: Log file!")
                End
                Else Begin
                    Send Info_Box "Ready! No problems found."
                End
            End_Procedure
                          
        End_Object

        Object oFixAliasProblems_btn is a cRDCButton
            Set Size to 32 61
            Set Location to 14 179
            Set Label to "2. Fix 'Alias Table Errors'"
            Set peAnchors to anTopRight
            Set MultiLineState to True
            Set psToolTip to "The fix will spin through Filelist.cfg and \n1. either add or remove driver prefixes for ALIAS rootnames, depending on the Master RootName\n2. Change all ALIAS table Descriptions to the ROOTNAME + 'ALIAS'"
        
            Procedure OnClick
                Integer iRetval iCounter
                Get YesNo_Box "The fix will spin through Filelist.cfg and \n1. either add or remove driver prefixes for ALIAS rootnames, depending on the Master RootName\n2. Change all ALIAS table Descriptions to the ROOTNAME + 'ALIAS'\n\nPlease take a copy of the Filelist.cfg file first!\n\nContinue?" to iRetval
                If (iRetval <> MBR_Yes) Begin
                    Procedure_Return    
                End
                
                Get FixFileListAliasProblems to iCounter
                
                If (iCounter <> 0) Begin 
                    Send RefreshData
                    Send Info_Box ("Ready!" * String(iCounter) * "Alias problems fixed in Filelist.cfg. See Also: Logfile")
                End
                Else Begin
                    Send Info_Box "Ready! NO Alias problems found in Filelist.cfg."
                End
            End_Procedure
                          
        End_Object

        Object oFixFileListSQLMissingTables_btn is a cRDCButton
            Set Size to 32 61
            Set Location to 14 244
            Set Label to "3. Make Filelist RootNames equal to SQL Database"
            Set peAnchors to anTopRight
            Set MultiLineState to True
            Set psToolTip to "The fix will spin through Filelist.cfg and \n1. Remove all driver prefixes for Master tables that does NOT exist in the SQL Database\n2. OR Add driver prefix for Master filelist entries that are missing a driver prefix."
        
            Procedure OnClick
                Integer iRetval iCounter
                Get YesNo_Box "The fix will spin through Filelist.cfg and \n1. Remove all driver prefixes for tables that does NOT exist in the SQL Database\n2. OR Add driver prefix for Master filelist entries that are missing a driver prefix.\n\nPlease take a copy of the Filelist.cfg file first!\n\nContinue?" to iRetval
                If (iRetval <> MBR_Yes) Begin
                    Procedure_Return    
                End
                Get FixFileListSQLMissingTables to iCounter               
                If (iCounter <> 0) Begin
                    Send Info_Box ("Ready!" * String(iCounter) * "RootName entries in Filelist.cfg that pointed to SQL tables that doesn't exist in the SQL database, were adjusted.\n\nTop tip: If tables were added to the ''Open Table Errors', check the list 'Int table Errors' (top right) for a match. The odds are high that there is something wrong with the .int file.")
                End
                Else Begin
                    Send Info_Box "Ready! No problems found."    
                End
            End_Procedure
                          
        End_Object

        Object oFixFileListOpenErrors_btn is a cRDCButton
            Set Size to 32 61
            Set Location to 14 311
            Set Label to "4. Fix Filelist: 'Open Table Errors'"
            Set peAnchors to anTopRight
            Set MultiLineState to True
            Set psToolTip to "The fix will spin through the Filelist and \n1. Try to fix or removes Non SQL entries for tables that cannot be opened."
        
            Procedure OnClick
                Integer iRetval iCounter iOpenErrors
                
                Get YesNo_Box "The fix will spin through the Filelist and: \n- Try to fix or remove Non SQL Filelist entries for tables that cannot be opened.\n\nPlease take a copy of the Filelist.cfg file first!\n\nContinue?" to iRetval
                If (iRetval <> MBR_Yes) Begin
                    Procedure_Return    
                End

                Get FixFileListOpenErrors to iCounter
                Get _CountFileListOpenErrors of ghoDUF to iOpenErrors
                
                If (iOpenErrors <> 0 and iCounter = 0) Begin 
                    Send RefreshData
                    Send Info_Box ("Ready! No Errors were fixed. NOTE:" * String(iOpenErrors) * "Open errors still exists and needs your attention. Please use the button 'Recreate Open table Errors *.int files'!)")
                End
                Else If (iOpenErrors <> 0 and iCounter <> 0) Begin
                    Send RefreshData
                    Send Info_Box ("Ready!" * String(iCounter) * "RootName entries were changed. See: Log file!")
                End
                Else Begin
                    Send Info_Box "Ready! No problems found"
                End
            End_Procedure
                          
        End_Object

        Object oFixIntFileError_btn is a cRDCButton
            Set Size to 32 61
            Set Location to 14 377
            Set Label to "5. Recreate 'Open Table Errors' *.int files"
            Set peAnchors to anTopRight
            Set MultiLineState to True
            Set psToolTip to "This will try recreate the .int files listed in the 'Open Table Errors' list."
            
            Procedure OnClick
                Integer iRetval iCounter
                
                Get YesNo_Box "This will recreate the .int files listed in the 'Open Table Errors' list.\n\nContinue?" to iRetval
                If (iRetval <> MBR_Yes) Begin
                    Procedure_Return    
                End
                
                Get FixAllIntFileErrors to iCounter
                If (iCounter > 0) Begin
                    Send Info_Box ("Ready! Update to:" * String(iCounter) * ".int files done.")
                End
                Else If (iCounter = 0) Begin
                    Send Info_Box "Ready! No problems found."
                End
                Else Begin
                    Send Info_Box "No 'Open Table Errors' found."
                End
            End_Procedure
            
        End_Object

    End_Object

    Object oFixExtraProblems_grp is a Group
        Set Size to 60 210
        Set Location to 357 470
        Set Label to "More Database Actions:"
        Set peAnchors to anTopRight

        Object oRefreshAllIntFiles_btn is a cRDCButton
            Set Size to 32 61
            Set Location to 14 9
            Set Label to "Refresh ALL *.int files"
            Set peAnchors to anTopRight
            Set MultiLineState to True
            Set psToolTip to "This will refresh all .int files."
            
            Procedure OnClick
                Integer iRetval iCounter
                
                Get YesNo_Box "This will refresh all .int files.\n\nContinue?" to iRetval
                If (iRetval <> MBR_Yes) Begin
                    Procedure_Return    
                End  
                
                Get RefreshAllIntFiles to iCounter
                If (iCounter <> 0) Begin
                    Send Info_Box ("Ready! Refresh of:" * String(iCounter) * ".int files done.")
                End
                Else Begin
                    Send Info_Box "Ready! No .int files to refresh."
                End
            End_Procedure
            
        End_Object

        Object oRecreateAllIntFiles_btn is a cRDCButton
            Set Size to 32 61
            Set Location to 14 75
            Set Label to "Recreate All *.int files"
            Set MultiLineState to True
            Set psToolTip to "This will recreate all .int files."
            
            Procedure OnClick
                Integer iRetval iCounter
                Boolean bUseUcase
                String sDataPath sBackup
                
                Get psDataPath of (phoWorkspace(ghoApplication)) to sDataPath
                Get vFolderFormat sDataPath to sDataPath
                Move (sDataPath + CS_BackupFolder) to sBackup
                Get YesNo_Box ("This will recreate all .int files. Relations from the current .int file will be preserved, if exists. A backup of .int files will be created here:\n" + String(sBackup) * "folder.\n\nContinue?") to iRetval
                If (iRetval <> MBR_Yes) Begin
                    Procedure_Return    
                End
                Move True to bUseUcase
                
                Get RecreateAllIntFiles bUseUcase to iCounter
                If (iCounter > 0) Begin
                    Send Info_Box ("Ready!" * String(iCounter) * ".int files recreated.")
                End
                Else If (iCounter = 0) Begin
                    Send Info_Box "Ready! No .int files found to recreate."
                End
            End_Procedure
            
        End_Object

        Object oMoveUnusedDatFiles_btn is a cRDCButton
            Set Size to 32 61
            Set Location to 14 142
            Set Label to "Move Unused .dat files to Backup folder"
            Set MultiLineState to True
            Set psToolTip to "This will move all *.dat related files, that does not exist in the Filelist, to the workspace's '.\Data\Backup' folder."
            
            Procedure OnClick
                Integer iRetval iCounter 
                
                Get YesNo_Box "Move all *.dat related files that is not in the 'Rootname *.dat' list, to the workspace's '.\Data\Backup' folder.\n\nContinue?" to iRetval
                If (iRetval <> MBR_Yes) Begin
                    Procedure_Return    
                End
                
                Get MoveUnusedDatFileToBackupFolder CS_BackupFolder to iCounter
                
                If (iCounter = -1) Begin
                    Send Info_Box ("The backup folder:\n" + CS_BackupFolder + "\nCould not be created! No *.dat related files were moved.")
                End
                Else If (iCounter > 0) Begin
                    Send Info_Box ("Ready! Moved:" * String(iCounter) * ".dat related files to backup folder: '.\Data\Backkup'.")
                End
                Else Begin
                    Send Info_Box "Ready! No files moved."
                End
            End_Procedure  
            
        End_Object
        
    End_Object
    
    Object oLogFile_grp is a Group
        Set Size to 30 669
        Set Location to 423 12
        Set Label to "Logged Changes:"
        Set peAnchors to anTopLeftRight

        Object oLogFile_fm is a cRDCForm
            Set Size to 12 387
            Set Location to 14 66
            Set Enabled_State to False
            Set Label to "Log File:"
            Set peAnchors to anNone
    
            Procedure Page Integer iPageObject
                String sFileName sHomePath
                Forward Send Page iPageObject
                Get psHome of (phoWorkspace(ghoApplication)) to sHomePath
                Move CS_ReportFileName to sFileName
                Set Value to (sHomePath + sFileName)
            End_Procedure
            
        End_Object

        Object oOpenLogFile_btn is a cRDCButton
            Set Size to 12 50
            Set Location to 14 458
            Set Label to "View"
            Set peAnchors to anNone
            Set psImage to "View.ico"
        
            Procedure OnClick
                String sFileName
                Boolean bExists
                Get Value of oLogFile_fm to sFileName
                File_Exist sFileName bExists
                If (bExists = False) Begin
                    Send Info_Box ("The log file hasn't been created yet:\n" + sFileName)
                    Procedure_Return
                End
                Runprogram Shell Background sFileName
            End_Procedure
        
        End_Object  

    End_Object

    Object oLocalError_Info_Object is a cObject
        Property Handle phoOrgError_Object_Id
        Property Boolean pbErrorProcessingState
        Property Integer piErrNum
        Property Integer piErrLine
        Property String  psErrText
        
        Procedure OnCreate
            Set phoOrgError_Object_Id to Error_Object_Id
            Move Self to Error_Object_Id
            Move Self to ghoErrorHandler
        End_Procedure
        Send OnCreate

        Procedure Error_Report Integer iErrNum Integer iErrLine String sTxt
            String sErrText
            If (pbErrorProcessingState(Self)) ; 
                Procedure_Return 
            Set pbErrorProcessingState to True 
            If (num_arguments = 2 or sTxt = "") Begin
                Move (Trim(Error_Text(DESKTOP, iErrNum))) to sErrText
            End
            Else Begin
                Move sTxt to sErrText
            End
                
            Move Self to ghoErrorSource 
            Set piErrNum  to iErrNum
            Set piErrLine to iErrLine
            Set psErrText to sErrText
            Send WriteError of (Parent(Self)) ("Error:" * String(iErrNum) * "at line:" * String(iErrLine) * "Text:" * String(sErrText))
            Set pbErrorProcessingState to False 
        End_Procedure

        Function Extended_Error_Message Returns String
            Integer iErrNum iErrLine
            String sErrText
        
            Get piErrNum  to iErrNum
            Get piErrLine to iErrLine
            Get psErrText to sErrText
            Send WriteError ("Error:" * String(iErrNum) * "at line:" * String(iErrLine) * "Text:" * String(sErrText))
        
            Function_Return sErrText
        End_Function
        
        Procedure Ignore_Error Integer iError
        End_Procedure
        
        Procedure Trap_Error Integer iError
        End_Procedure
        
        Procedure Ignore_All
        End_Procedure
        
        Procedure Trap_All
        End_Procedure   
        
    End_Object
    
    // Dummy message that shows as delimiter in the Studio's Code Explorer:
    Procedure COMMON_MESSAGES
    End_Procedure

    Procedure ShowSQLTablesCount
        String[] asSQLTables
        Send StartStatusPanel "Enumerating SQL Tables" "" -1 
        Send UtilFillSQLTables of ghoDUF
        Get pasSQLDataTables   of ghoDUF to asSQLTables
        Set Value of oNumberOfSQLTables_fm to (String(SizeOfArray(asSQLTables))) 
        Send StopStatusPanel
    End_Procedure

    Procedure ShowFileListData
        Integer iCount
        String sDataPath
        tFilelist[] FileListArray
        
        Get _UtilNumberOfFileListTables of ghoDUF to iCount
        Send StartStatusPanel "Filling Filelist Struct Array" "" iCount

        // Note: Removes all cached files, else we don't open what we think we are.
        Get psDataPath of (phoWorkspace(ghoApplication)) to sDataPath
        EraseFile (sDataPath + "\*.cch") 

        Send UtilFillFileListStruct of ghoDUF
        Get pFileListArray of ghoDUF to FileListArray
        Set Value of oNumberOfFileListTables_fm to (SizeOfArray(FileListArray))
        Send ListRootDatFiles
        Send ListRootIntFiles
        Send ListOpenErrorFiles
        
        Get _CountFileListMasterTables of ghoDUF to iCount
        Set Value of oNumberOfMasterFileListSQLTables_fm to iCount
        Get _CountFileListAliasTables of ghoDUF to iCount
        Set Value of oNoOfAliasSQLTables_fm to iCount
        Get _CountFilelistSystemTables of ghoDUF to iCount
        Set Value of oNoOfSystemTables_fm to iCount
        Get _CountFileListOpenErrors of ghoDUF to iCount
        Set Value of oOpenErrorTables_fm to iCount
        Send ListAliasErrorFiles
        
        Send StopStatusPanel
    End_Procedure

    // Fills list of "RootName *.dat Files" with tables that are not Alias and does
    // not have a driver prefix or contains ".int".
    Procedure ListRootDatFiles
        Handle ho
        String[] asFiles
        Boolean bIsIntTable
        Integer iSize iCount iCounter
        
        Move 0 to iCounter
        Move oDatTables_edt to ho
        Send Delete_Data of ho
        Get InUseDatFiles to asFiles
        If (SizeOfArray(asFiles) <> 0) Begin
            Move (SortArray(asFiles, Desktop, (RefFunc(DFSTRICMP)))) to asFiles
            Move (SizeOfArray(asFiles)) to iSize
            Decrement iSize
            For iCount from 0 to iSize
                Send AppendTextLn of ho asFiles[iCount]
                Increment iCounter
            Loop
        End
        Set Value of oDatTables_fm to iCounter
        Send Beginning_of_Data of ho
    End_Procedure

    Procedure ListAliasErrorFiles
        tFilelist[] FileListArray
        Integer iSize iCount
        Handle ho
        
        Move (oAliasErrors_edt(Self)) to ho
        Send Delete_Data of ho
        Set Value of oAliasErrors_fm to 0
        Get _CountFileListAliasErrors of ghoDUF to FileListArray
        Move (SizeOfArray(FileListArray)) to iSize
        If (iSize = 0) Begin
            Procedure_Return
        End
        Decrement iSize
        For iCount from 0 to iSize
            Send AppendTextLn of ho (FileListArray[iCount].sRootName * "(" + String(FileListArray[iCount].hTable) + ")")
        Loop
        Set Value of oAliasErrors_fm to (iSize + 1)
        Send Beginning_of_Data of ho
    End_Procedure

    Procedure ListRootIntFiles
        Handle ho
        tFilelist[] FilelistTables
        Boolean bIsIntTable
        Integer iSize iCount iCounter
        
        Move 0 to iCounter
        Get pFileListArray of ghoDUF to FileListTables
        Move oRootNameIntTables_edt to ho
        Send Delete_Data of ho
        Move (SizeOfArray(FilelistTables)) to iSize
        Decrement iSize
        For iCount from 0 to iSize
            Get _IsIntEntry of ghoDUF FilelistTables[iCount].hTable to bIsIntTable
            If (bIsIntTable = True) Begin
                Send AppendTextLn of ho FilelistTables[iCount].sRootName
                Increment iCounter
            End
        Loop
        Set Value of oRootNameIntTables_fm to iCounter
        Send Beginning_of_Data of ho
    End_Procedure

    Procedure ListOpenErrorFiles
        Handle ho hTable
        tFilelist[] FilelistTables
        tFilelist[] ErrorFilesArray
        Boolean bDatTable
        Integer iSize iCount
        String sVal
        
        Get pFileListArray of ghoDUF to FileListTables
        Move oOpenErrorTables_edt to ho
        Send Delete_Data of ho
        Move (SizeOfArray(FilelistTables)) to iSize
        Decrement iSize
        For iCount from 0 to iSize
            If (FilelistTables[iCount].bErrorOpening = True) Begin
                Move (FilelistTables[iCount].sRootName * ("(" + String(FilelistTables[iCount].hTable) + ")")) to sVal
                Send AppendTextLn of ho sVal
                Move FilelistTables[iCount] to ErrorFilesArray[SizeOfArray(ErrorFilesArray)]
            End
        Loop
        Set Value of oOpenErrorTables_fm to (SizeOfArray(ErrorFilesArray))
        Set pErrorTables of ghoDUF to ErrorFilesArray
        Send Beginning_of_Data of ho
    End_Procedure

    Function FixFileListErrors Returns Integer
        Integer iRetval hTable iSize iCount iItem iCh iCounter iAliases
        tFilelist[] FileListArray
        String sNoDriverRootname sDriver sRootName sRootNameNew sDatabase sLogicalName sDisplayName sDataPath
        Boolean bIsAlias bIsDatEntry bExists
        
        Move 0 to iCounter 
        Move 0 to hTable

        Get pFileListArray of ghoDUF to FileListArray
        If (SizeOfArray(FileListArray) = 0) Begin
            Send RefreshData
            Get pFileListArray of ghoDUF to FileListArray
        End    
        Send OpenLogFile
        Get piChannel to iCh
        Move (SizeOfArray(FileListArray)) to iSize
        Send StartStatusPanel "Fixing Filelist RootName .dat Errors" "" iSize
        Decrement iSize
        
        For iCount from 0 to iSize
            Move FileListArray[iCount].hTable to hTable 
            Send UpdateStatusPanel FileListArray[iCount].sLogicalName
            // 50 is FlexErrs.
            If (FileListArray[iCount].bIsAlias = False and hTable <> 50) Begin
                Get _IsDatEntry of ghoDUF hTable to bIsDatEntry
                If (bIsDatEntry = True) Begin 
                    Get _DatFileExists of ghoDUF hTable to bExists
                    If (bExists = False) Begin
                        Set_Attribute DF_FILE_ROOT_NAME    of hTable to ""
                        Set_Attribute DF_FILE_LOGICAL_NAME of hTable to ""
                        Set_Attribute DF_FILE_DISPLAY_NAME of hTable to ""
                        Writeln channel iCh "File Number     = " hTable
                        Writeln channel iCh "RootName        = " FileListArray[iCount].sRootName
                        Writeln channel iCh "LogicalName     = " FileListArray[iCount].sLogicalName
                        Writeln channel iCh "DisplayName     = " FileListArray[iCount].sDisplayName
                        Writeln channel iCh "Removed Filelist.cfg entry that was not an Alias file, pointed to a .dat file but the .Dat file was missing."
                        Writeln channel iCh ""
                        Increment iCounter
                    End
                End
            End
        Loop
        
        Send CloseLogFile
        Send StopStatusPanel
        If (iCounter <> 0) Begin
            Send RefreshData
        End     
        Function_Return iCounter
    End_Function

    Function FixFileListAliasProblems Returns Integer
        Integer iCounter iIntError iSize
        Handle hTable hMasterTable
        String sLogicalNameOrg sRootNameOrg sDisplayNameOrg 
        String sDriver sNoDriverRootname sRootNameNew sLogicalNameNew sDisplayNameNew
        Boolean bIsAlias bIsIntTable bIsAliasSQL bIsMasterSQL
        tFilelist[] FilelistArray
        
        Get _CountFileListAliasErrors of ghoDUF to FileListArray
        Move (SizeOfArray(FileListArray)) to iSize
        If (iSize = 0) Begin
            Function_Return 0
        End
                
        Send StartStatusPanel "Fixing Alias Filelist Errors" "" iSize
        Move 0 to iCounter 
        Move 0 to hTable

        Repeat
            Get_Attribute DF_FILE_NEXT_USED of hTable to hTable
            // Table 50 is FlexErrs
            If (hTable <> 0 and hTable <> 50) Begin
                Get_Attribute DF_FILE_ROOT_NAME    of hTable to sRootNameOrg
                Get_Attribute DF_FILE_LOGICAL_NAME of hTable to sLogicalNameOrg
                Send UpdateStatusPanel sLogicalNameOrg
                Get_Attribute DF_FILE_DISPLAY_NAME of hTable to sDisplayNameOrg 
                Get _TableNameOnly of ghoDUF sRootNameOrg to sNoDriverRootname 
                Get _IsAliasTable of ghoDUF hTable to bIsAlias  
                If (bIsAlias = True) Begin
                    Get _IsIntEntry of ghoDUF hTable to bIsIntTable
                    Get UtilAliasToMasterTableHandle of ghoDUF hTable to hMasterTable
                    If (hMasterTable <> 0) Begin
                        Get _IsSQLEntry of ghoDUF hTable       to bIsAliasSQL
                        Get _IsSQLEntry of ghoDUF hMasterTable to bIsMasterSQL
                        Get _FindAliasEntryError of ghoDUF hTable to iIntError
                        If (iIntError = 1) Begin
                            If ((bIsAliasSQL = False and bIsIntTable = False) and bIsMasterSQL = True) Begin
                                Move (MSSQLDRV_ID + ":" + sRootNameOrg) to sRootNameNew
                                Set_Attribute DF_FILE_ROOT_NAME of hTable to sRootNameNew
                            End
                            Else If ((bIsAliasSQL = True or bIsIntTable = True) and bIsMasterSQL = False) Begin
                                Set_Attribute DF_FILE_ROOT_NAME of hTable to sNoDriverRootname
                            End 
                            Else If ((bIsAliasSQL = True or bIsIntTable = True) and bIsMasterSQL = True) Begin
                                Move (MSSQLDRV_ID + ":" + sRootNameOrg) to sRootNameNew
                                Set_Attribute DF_FILE_ROOT_NAME of hTable to sRootNameNew                                
                            End
                            Move (sNoDriverRootname * "ALIAS") to sDisplayNameNew
                            Set_Attribute DF_FILE_DISPLAY_NAME of hTable to sDisplayNameNew
                            Send WriteToLogFile True hTable sLogicalNameOrg sRootNameOrg sRootNameNew sNoDriverRootname sDisplayNameOrg sDisplayNameNew
                            Increment iCounter
                        End
                    End
                    
                    Else If (hMasterTable = 0) Begin
                        Set_Attribute DF_FILE_ROOT_NAME    of hTable to ""
                        Set_Attribute DF_FILE_LOGICAL_NAME of hTable to ""
                        Set_Attribute DF_FILE_DISPLAY_NAME of hTable to ""
                        Send WriteToLogFile True hTable sLogicalNameOrg sRootNameOrg "" sDisplayNameOrg "Alias Filelist entry SHOULD BE REMOVED!"
                        Increment iCounter
                    End
                    Get_Attribute DF_FILE_DISPLAY_NAME of hTable to sDisplayNameNew
                    Get_Attribute DF_FILE_LOGICAL_NAME of hTable to sLogicalNameNew
                    If (not(Lowercase(sDisplayNameNew) contains "alias")) Begin
                        Move (sLogicalNameNew * "(" + sNoDriverRootname * "ALIAS)") to sDisplayNameNew
                        Set_Attribute DF_FILE_DISPLAY_NAME of hTable to sDisplayNameNew
                        Send WriteToLogFile True hTable sLogicalNameOrg sRootNameOrg sRootNameNew sDisplayNameOrg sDisplayNameNew
                        Increment iCounter
                    End
                End
                // Adjust DisplayName?
                If (bIsAlias = False and Lowercase(sDisplayNameOrg) contains "alias") Begin
                    Get RemoveDisplayNameAlias hTable sDisplayNameOrg to sDisplayNameNew
                    Send WriteToLogFile False hTable sLogicalNameOrg sRootNameOrg sRootNameNew sDisplayNameOrg sDisplayNameNew
                    Increment iCounter
                End
            End
        Until (hTable = 0)
        Send StopStatusPanel
        Function_Return iCounter
    End_Function

    Function FixFileListSQLMissingTables Returns Integer
        Integer iRetval hTable iSize iCount iItem iCh iCounter iAliases iPos
        String[] asSQLTables
        tFilelist[] FileListArray
        String sNoDriverRootname sDriver sRootName sRootNameNew sDatabase sLogicalName sDisplayName
        Boolean bIsAlias bIsIntTable bExists
        
        Move 0 to iCounter 
        Move 0 to hTable
        Get pasSQLDataTables of ghoDUF to asSQLTables
        If (SizeOfArray(asSQLTables) = 0) Begin
            Send UtilFillSQLTables of ghoDUF
            Get pasSQLDataTables of ghoDUF to asSQLTables
        End
        Get pFileListArray of ghoDUF to FileListArray
        If (SizeOfArray(FileListArray) = 0) Begin
            Send RefreshData
            Get pFileListArray of ghoDUF to FileListArray
        End    
        
        Send OpenLogFile
        Get piChannel to iCh
        Get psDatabase of ghoDUF to sDatabase
        Writeln channel iCh ("Adjustment of RootNames for tables that exists in the SQL database:" * String(sDatabase))
        
        Move (SizeOfArray(FileListArray)) to iSize
        Send StartStatusPanel "Enumerating SQL Tables" "" iSize
        Decrement iSize
        
        For iCount from 0 to iSize
            Move FileListArray[iCount].hTable to hTable
            Move FileListArray[iCount].sRootName to sRootName
            Get _RemoveDriverFromRootName of ghoDUF sRootName (&sDriver) to sNoDriverRootname
            Send UpdateStatusPanel sNoDriverRootname
            Get _IsIntEntry of ghoDUF hTable to bIsIntTable
            // 50 is FlexErrs.
            If (hTable <> 50) Begin
                Move (SearchArray(sNoDriverRootname, asSQLTables, Desktop , (RefFunc(DFSTRICMP)))) to iItem
                // If the Table name in Filelist.cfg points to an SQL table, but that table doesn't
                // exist in the SQL database, remove the driver prefix from Filelist.cfg.
                If (iItem = -1) Begin
                    Move sNoDriverRootname to sRootNameNew
                End
                Else Begin
                    Get _IntFileExists of ghoDUF hTable to bExists
                    If (bExists = True) Begin
                        Move (MSSQLDRV_ID + ":" + sNoDriverRootname) to sRootNameNew
                    End
                    Else Begin
                        // If the .int file wasn't found, we will not make a filelist change.
                        Move sNoDriverRootname to sRootNameNew
                    End
                End
                If (sRootName <> sRootNameNew) Begin
                    Set_Attribute DF_FILE_ROOT_NAME of hTable to sRootNameNew
                    Writeln channel iCh "File Number     = " hTable
                    Writeln channel iCh "RootName        = " FileListArray[iCount].sRootName
                    Writeln channel iCh "NEW RootName    = " sRootNameNew
                    Writeln channel iCh "LogicalName     = " FileListArray[iCount].sLogicalName
                    Writeln channel iCh "DisplayName     = " FileListArray[iCount].sDisplayName
                    Writeln channel iCh "RootName Error fixed!"
                    Writeln channel iCh ""
                    Increment iCounter
                End
            End
        Loop

        Send CloseLogFile
        Send StopStatusPanel
        If (iCounter <> 0) Begin
            Send RefreshData
        End
        Function_Return iCounter
    End_Function

    Function FixFileListOpenErrors Returns Integer        
        Integer iRetval hTable iSize iCount iItem iCh iCounter iAliases iOpenErrors
        tFilelist[] FileListArray
        String sNoDriverRootname sDriver sRootName sRootNameNew sDatabase sLogicalName sDisplayName sDataPath
        Boolean bIsAlias bExists bChange bFirst bIsSQLTable bIsIntTable
        
        Move False to bFirst
        Move 0 to iCounter 
        Move 0 to hTable
        Get pFileListArray of ghoDUF to FileListArray
        If (SizeOfArray(FileListArray) = 0) Begin
            Send RefreshData
            Get pFileListArray of ghoDUF to FileListArray
        End    
        
        Send StartStatusPanel "Fixing Filelist Open Errors" "" iSize
        Get psDataPath of (phoWorkspace(ghoApplication)) to sDataPath
        Send OpenLogFile
        Get piChannel to iCh
        Get psDatabase of ghoDUF to sDatabase
        Move (SizeOfArray(FileListArray)) to iSize
        Decrement iSize
        
        For iCount from 0 to iSize
            Move False to bChange
            Move FileListArray[iCount].hTable to hTable 
            Send UpdateStatusPanel FileListArray[iCount].sLogicalName
            // Table 50 is FlexErrs
            If (FileListArray[iCount].bErrorOpening = True and hTable <> 50) Begin
                Get _IsSQLEntry of ghoDUF hTable to bIsSQLTable
                Get _IsIntEntry of ghoDUF hTable to bIsIntTable
                If (bIsSQLTable = True and bIsIntTable = True) Begin
                    Move FileListArray[iCount].sRootName to sRootName 
                    Get _RemoveDriverFromRootName of ghoDUF sRootName (&sDriver) to sNoDriverRootname
                    If (sRootName <> (sDriver + ":" + sNoDriverRootname) or (sRootName contains ":" and Lowercase(sRootName) contains ".int")) Begin
                        Set_Attribute DF_FILE_ROOT_NAME of hTable to (sDriver + ":" + sNoDriverRootname)
                        Writeln channel iCh "File Number     = " hTable
                        Writeln channel iCh "RootName        = " FileListArray[iCount].sRootName
                        Writeln channel iCh "NEW RootName    = " (sDriver + ":" + sNoDriverRootname)
                        Increment iCounter
                    End
                End
                Else If (bIsSQLTable = False) Begin
                    Set_Attribute DF_FILE_ROOT_NAME    of hTable to ""
                    Set_Attribute DF_FILE_LOGICAL_NAME of hTable to ""
                    Set_Attribute DF_FILE_DISPLAY_NAME of hTable to ""
                    If (bFirst = False) Begin
                        Writeln channel iCh "Removed Filelist.cfg entries for tables that could not be opened."
                        Move True to bFirst
                    End
                    Writeln channel iCh "File Number     = " hTable
                    Writeln channel iCh "RootName        = " FileListArray[iCount].sRootName
                    Writeln channel iCh "LogicalName     = " FileListArray[iCount].sLogicalName
                    Writeln channel iCh "DisplayName     = " FileListArray[iCount].sDisplayName
                    Writeln channel iCh "FileList entry was removed because the Table could not be opened"
                    Writeln channel iCh ""
                    Increment iCounter
                End
            End
        Loop

        Send CloseLogFile
        Send StopStatusPanel
        If (iCounter <> 0) Begin
            Send RefreshData
        End     
        Function_Return iCounter
    End_Function

    Function FixAllIntFileErrors Returns Integer
        Integer iRetval iSize iCount iCounter iDriver
        tFilelist[] ErrorFilesArray FileListArray
        String sDriver sRootName sIntFileName sConnectionID sErrorText sText sDataPath
        Boolean bOK bIsSystem bUseUcase bCurrentUcaseMode
        Handle hTable hoCurrentErrorObject

        Get pFileListArray of ghoDUF to FileListArray
        If (SizeOfArray(FileListArray) = 0) Begin
            Send RefreshData
            Get pFileListArray of ghoDUF to FileListArray
        End    

        Get pErrorTables of ghoDUF to ErrorFilesArray
        If (SizeOfArray(ErrorFilesArray) = 0) Begin
            Function_Return -1
        End
        
        Send OpenLogFile
        Get psDriverID of ghoDUF to sDriver
        Get DriverIndex of ghoDUF sDriver to iDriver
        // Note: If Ignore_Ucase_Support is set to false, the Connectivity Kit will 
        //       behave the same as earlier driver versions.
        //       This means that "U_" columns will be kept during a restructure.
        Get_Attribute DF_DRIVER_IGNORE_UCASE_SUPPORT of iDriver to bCurrentUcaseMode
        Set_Attribute DF_DRIVER_IGNORE_UCASE_SUPPORT of iDriver to bUseUcase
        Move (SizeOfArray(ErrorFilesArray)) to iSize
        Send StartStatusPanel "Fixing Int File Errors" "" iSize
    
        Get psDataPath of (phoWorkspace(ghoApplication)) to sDataPath
        Get psConnId to sConnectionID
    
        For iCount from 0 to (iSize - 1)
            Move ErrorFilesArray[iCount].sDriver to sDriver
            If (sDriver = "") Begin
                Get _RemoveDriverFromRootName of ghoDUF ErrorFilesArray[iCount].sRootName (&sDriver) to sRootName
                If (sDriver = "") Begin
                    Get psDriverID of ghoDUF to sDriver
                End
            End

            Send UpdateStatusPanel ("Fixing .int file problems for table:" * String(sRootName))
            Move (ErrorFilesArray[iCount].sNoDriverRootname + ".int") to sIntFileName
            
            If (sDriver <> DATAFLEX_ID) Begin
                Move ErrorFilesArray[iCount].hTable to hTable
                Get _IsSystemFile of ghoDUF hTable to bIsSystem
    
                Get RecreateSingleIntFile hTable sDataPath sDriver sConnectionID bIsSystem sIntFileName to bOK
                If (bOK) Begin
                    Increment iCounter
                    Set_Attribute DF_FILE_ROOT_NAME of hTable to (sDriver + ":" + ErrorFilesArray[iCount].sNoDriverRootname)
                End
                Else Begin
                    Send WriteError ("The recreation of the.int file:" * String(sIntFileName) * "failed.") 
                End
            End
        Loop
    
        Set_Attribute DF_DRIVER_IGNORE_UCASE_SUPPORT of iDriver to bCurrentUcaseMode
        Send CloseLogFile
        Send StopStatusPanel
        If (iCounter <> 0) Begin
            Send RefreshData
        End
    
        Function_Return iCounter
    End_Function

    Function RefreshAllIntFiles Returns Integer
        Integer iRetval iSize iCount iCounter
        tFilelist[] FileListArray
        String sDriver sRootName sIntFileName sConnectionID sErrorText sText sDataPath
        Boolean bOK bIsSystem bAnsi bIsAlias
        Handle hTable
    
        Get pFileListArray of ghoDUF to FileListArray
        If (SizeOfArray(FileListArray) = 0) Begin
            Send RefreshData
            Get pFileListArray of ghoDUF to FilelistArray
        End
    
        Move 0 to iCounter
        Move (SizeOfArray(FileListArray)) to iSize     
        // Each Start_Restructure/End_Restructure calls the "Callback" message 3 times,
        // and it does a "Send DoAdvance" to the ghoProgressBar...
        Send StartStatusPanel "Refreshing Int Files" "" (iSize * 3)
        Decrement iSize
        
        Get psDataPath of (phoWorkspace(ghoApplication)) to sDataPath
        Get psConnId to sConnectionID 
        Get pbToANSI of ghoDUF to bAnsi 
        Send OpenLogFile
    
        For iCount from 0 to iSize
            Move FileListArray[iCount].sDriver to sDriver
            Move FileListArray[iCount].hTable to hTable
            Get _RemoveDriverFromRootName of ghoDUF FileListArray[iCount].sRootName (&sDriver) to sRootName
            Set Message_Text of ghoStatusPanel to ("Table number:" * String(hTable))
            If (sDriver = "") Begin
                Get psDriverID of ghoDUF to sDriver
            End
            Move FileListArray[iCount].bIsAlias to bIsAlias
            If (bIsAlias = False) Begin
                Move (FileListArray[iCount].sNoDriverRootname + ".int") to sIntFileName
                If (sDriver <> DATAFLEX_ID) Begin
                    Get _IsSystemFile of ghoDUF hTable to bIsSystem
                    Send UpdateStatusPanel ("Refreshing .int file:" * String(sRootName))
                    
                    // Refresh!
                    Get _SqlUtilRefreshIntFile of ghoDUF hTable sDriver sConnectionID bansi bIsSystem to bOK
    
                    If (bOK) Begin
                        Increment iCounter
                        Set_Attribute DF_FILE_ROOT_NAME of hTable to (sDriver + ":" + FileListArray[iCount].sNoDriverRootname)
                    End 
                    Else Begin
                        Send WriteError ("Could not refresh the .int file:" * FileListArray[iCount].sNoDriverRootname + ".int")
                    End
                End
            End
        Loop
    
        Send StopStatusPanel
        Send CloseLogFile
        If (iCounter <> 0) Begin
            Send RefreshData
        End
    
        Function_Return iCounter
    End_Function

    Procedure GENERATE_ALL_INT_FILES_CODE_STARTS_HERE
    End_Procedure

    Function RecreateAllIntFiles Boolean bUseUcase Returns Integer
        Integer iRetval iSize iCount iCounter iDriver iLastErr iErrLine
        tFilelist[] FileListArray
        String[] asIntFileData
        String sDriver sIntFileName sConnectionID sErrorText sText sDataPath
        Boolean bExists bOK bIsSystem bAnsi bIsAlias bIsSQL bCurrentUcaseMode bErr
        Handle hTable
    
        Get pFileListArray of ghoDUF to FileListArray
        If (SizeOfArray(FileListArray) = 0) Begin
            Send RefreshData
            Get pFileListArray of ghoDUF to FilelistArray
        End
    
        Move 0 to iCounter
        Move Err to bErr
        Move LastErr to iLastErr
        Move ErrLine to iErrLine
        Move False to Err
        Move 0 to LastErr
        Move 0 to ErrLine
        
        Send OpenLogFile
        Get psDriverID of ghoDUF to sDriver
        Get DriverIndex of ghoDUF sDriver to iDriver
        // Note: If Ignore_Ucase_Support is set to false, the Connectivity Kit will 
        //       behave the same as earlier driver versions.
        //       This means that "U_" columns will be kept during a restructure.
        Get_Attribute DF_DRIVER_IGNORE_UCASE_SUPPORT of iDriver to bCurrentUcaseMode
        Set_Attribute DF_DRIVER_IGNORE_UCASE_SUPPORT of iDriver to bUseUcase
        Get psDataPath of (phoWorkspace(ghoApplication)) to sDataPath
        Get psConnId to sConnectionID 
        Get pbToANSI of ghoDUF to bAnsi 
        Move (SizeOfArray(FileListArray)) to iSize     
        Decrement iSize 
        // Each Start_Restructure/End_Restructure calls the "Callback" message 3 times,
        // and each one does a "Send DoAdvance" to the ghoProgressBar...
        Send StartStatusPanel "Recreating Int Files" "" (iSize * 3)
    
        For iCount from 0 to iSize
            Move FileListArray[iCount].sDriver  to sDriver
            Move FileListArray[iCount].hTable   to hTable
            Get _IsSQLEntry of ghoDUF hTable    to bIsSQL
            Move FileListArray[iCount].bIsAlias to bIsAlias                   
            Set Message_Text of ghoStatusPanel to ("Table number:" * String(hTable))
            If (bIsSQL = True and bIsAlias = False) Begin
                Move (FileListArray[iCount].sNoDriverRootname + ".int") to sIntFileName
                File_Exist (sDataPath + "\" + sIntFileName) bExists
                If (bExists and sDriver <> DATAFLEX_ID) Begin
                    Open hTable
                    Get _IsSystemFile of ghoDUF hTable to bIsSystem
                    Send UpdateStatusPanel ("Recreating file:" * String(FileListArray[iCount].sNoDriverRootname) + ".int")
                    
                    Get RecreateSingleIntFile hTable sDataPath sDriver sConnectionID bIsSystem sIntFileName to bOK
                    
                    Close hTable
                    If (bOK) Begin
                        Increment iCounter
                        Set_Attribute DF_FILE_ROOT_NAME of hTable to (sDriver + ":" + FileListArray[iCount].sNoDriverRootname)
                    End
                    Else Begin
                        Send WriteError ("The recreation of the.int file:" * String(sIntFileName) * "failed.") 
                    End
                End
            End
            Send DoAdvance of ghoStatusPanel 
        Loop
    
        Set_Attribute DF_DRIVER_IGNORE_UCASE_SUPPORT of iDriver to bCurrentUcaseMode
        Send CloseLogFile
        Send StopStatusPanel
        Move bErr to Err
        Move iLastErr to LastErr
        Move iErrLine to ErrLine
        If (iCounter > 0) Begin
            Send RefreshData
        End
    
        Function_Return iCounter
    End_Function

    // Helper function to recreate a single .int file
    Function RecreateSingleIntFile Handle hTable String sDataPath String sDriver String sConnectionID Boolean bIsSystem String sIntFileName Returns Boolean
        Boolean bOK bAnsi
        String sErrorText sText
        Integer iRetval iDbType
        String[] asIntFileData
    
        Get pbToANSI of ghoDUF to bAnsi 
        // 1. Backup the .int file
        Get BackupIntFile sDataPath sIntFileName CS_BackupFolder to bOK
        // 2. Collect relation and index info from old .ini file:
        Get CollectIntFileRelations sIntFileName to asIntFileData
        // 3. Add more data from the current data table
        Get CollectMoreFieldAttributes hTable sDriver asIntFileData to asIntFileData
        // 4. Tell driver to create a new .int file.
        Get CreateNewIntFile hTable sDriver sConnectionID bAnsi bIsSystem False to bOK
        If (bOK = False) Begin
            Function_Return False
        End
        // 5. Merge data from the old .int file, with the new .int file and "MoreFieldAttributes" data:
        Get MergeIntFileData hTable sIntFileName asIntFileData to bOK
        Function_Return bOK
    End_Function
    
    Function CreateNewIntFile Handle hTable String sDriver String sConnectionID Boolean bAnsi Boolean bIsSystem Boolean bBackup Returns Boolean
        Boolean bOK
        Get _SqlUtilCreateIntFile of ghoDUF hTable sDriver sConnectionID bAnsi bIsSystem False to bOK
        Function_Return bOK
    End_Function

    Function CollectIntFileRelations String sIntFile Returns String[]
        Integer iSize iCount
        String[] asIntFile asData
        String sLine sFieldTxt
        Boolean bFound
        
        Get FullDataPathFileName sIntFile to sIntFile
        Get ReadFileToArray sIntFile to asIntFile
        Move (SizeOfArray(asIntFile)) to iSize
        Decrement iSize
        
        For iCount from 0 to iSize
            Move (Trim(asIntFile[iCount])) to sLine  
            If (Uppercase(Left(sLine, 13)) = "FIELD_NUMBER ") Begin
                Move sLine to sFieldTxt
                Repeat
                    If (iCount < iSize) Begin
                        Increment iCount               
                        // Try to find both: FIELD_RELATED_FILE & FIELD_RELATED_FIELD
                        // Note that we can't be sure in whitch order they are in.
                        If (Uppercase(Left(asIntFile[iCount], 14)) = "FIELD_RELATED_") Begin
                            If (sFieldTxt <> "") Begin  
                                Move ""    to asData[-1]
                                Move sLine to asData[-1]
                                Move "" to sFieldTxt
                            End
                            Move asIntFile[iCount] to asData[-1]
                        End
                    End
                Until (Trim(asIntFile[iCount] = "") or iCount >= iSize)
            End
            
        Loop
        Function_Return asData
    End_Function
    
    Function SanitizeColumnNames String[] asColumns Returns String[]
        Integer iSize iCount
        String sColName
        
        Move (SizeOfArray(asColumns)) to iSize
        If (iSize = 0) Begin
            Function_Return asColumns
        End
        Decrement iSize
        For iCount from 0 to iSize
            Move asColumns[iCount] to sColName
            If (Left(Uppercase(sColName), 2) = "U_" or Uppercase(sColName) = "RECNUM") Begin
                Move (RemoveFromArray(asColumns, iCount)) to asColumns
                Decrement iSize
            End
        Loop
        Function_Return asColumns    
    End_Function

    Function IsDuplicateAttributeInIntFile String[] asIntFileData String sFieldNoText String sAttribute Returns Boolean
        Integer iSize iIndex
        String sLine
        
        Move (SearchArray(sFieldNoText, asIntFileData, Desktop, (RefFunc(DFSTRICMP)))) to iIndex
        If (iIndex = -1) Begin
            Function_Return False
        End
        If (Trim(sAttribute) = "") Begin
            Function_Return
        End
        Move (SizeOfArray(asIntFileData)) to iSize
        Increment iIndex
        Repeat
            Move (Uppercase(Trim(asIntFileData[iIndex]))) to sLine
            If (sLine = Uppercase(Trim(sAttribute))) Begin
                Function_Return True
            End
            Increment iIndex
        Until (asIntFileData[iIndex] = "" or iIndex >= iSize)
        
        Function_Return False
    End_Function              
    
    // Note: The hTable needs to be open when this is called.
    //       It adds other FIELD_NUMBER settings that does not exist in the old passed .int file string array.
    Function CollectMoreFieldAttributes Handle hTable String sDriver String[] asIntFileData Returns String[]
        Integer iSize iCount iItem iField iDbType iFieldNumber
        String sFieldNoTxt sLine sHidden sFieldDateTxt sFieldHiddenTxt sFieldName
        Boolean bFound bOpen
        String[] asColumnsNamesOrg asColumnsNames asFieldTimeDates asFieldHidden

        Get piDbType of ghoDUF to iDbType
        Get _SqlUtilEnumerateColumnsByHandle of ghoDUF sDriver hTable to asColumnsNamesOrg
        Get SanitizeColumnNames asColumnsNamesOrg to asColumnsNames

        // 1. Find "DATETIME" fields:
        Move (SizeOfArray(asColumnsNames)) to iSize
        For iCount from 1 to iSize
            Move ("FIELD_NUMBER" * String(iCount)) to sFieldNoTxt 
            Get FieldNumberToDataTimeText hTable sFieldNoTxt sDriver iDbType to sFieldDateTxt   
            Get IsDuplicateAttributeInIntFile asIntFileData sFieldNoTxt sFieldDateTxt to bFound
            If (sFieldDateTxt <> "" and bFound = False) Begin
                Move ""            to asFieldTimeDates[-1]
                Move sFieldNoTxt   to asFieldTimeDates[-1] 
                Move sFieldDateTxt to asFieldTimeDates[-1]
            End
        Loop
        If (SizeOfArray(asFieldTimeDates) <> 0) Begin
            Get CombineArrays asIntFileData asFieldTimeDates to asIntFileData        
        End
        
        // 2. Find "HIDDEN" fields:
        Move (SizeOfArray(asColumnsNamesOrg)) to iSize
        Decrement iSize
        For iCount from 0 to iSize
            Move "" to sFieldHiddenTxt
            If (iCount < iSize) Begin
                Move (Trim(Uppercase(asColumnsNamesOrg[iCount]))) to sLine
                If (Left(sLine, 2) = "U_") Begin
                    Move (Replace("U_", sLine, "")) to sFieldName
                    Move (SearchArray(sFieldName, asColumnsNames, Desktop, (RefFunc(DFSTRICMP)))) to iField
                    Move ("FIELD_NUMBER" * String(iField +1)) to sFieldNoTxt
                    Move "NEXT_COLUMN_HIDDEN UPPERCASED"      to sFieldHiddenTxt
                    Get IsDuplicateAttributeInIntFile asIntFileData sFieldNoTxt sFieldHiddenTxt to bFound
                    If (iField <> -1 and bFound = False) Begin
                        Move ""              to asFieldHidden[-1]
                        Move sFieldNoTxt     to asFieldHidden[-1]
                        Move sFieldHiddenTxt to asFieldHidden[-1]
                    End
                End
            End
        Loop
        If (SizeOfArray(asFieldHidden) <> 0) Begin
            Get CombineArrays asIntFileData asFieldHidden to asIntFileData        
        End

        Function_Return asIntFileData
    End_Function

    // Parses data from an .int file as a string array, and
    // returns all "FIELD_NUMBER xx" data as a struct arrray.
    Function ParseBlocks String[] asData Returns tBlock[]
        tBlock[] Blocks 
        tBlock Block
        Integer iSize iCount iFieldNumber iBlock
        String sLine
        
        Move 0 to iBlock
        Move (SizeOfArray(asData)) to iSize
        Decrement iSize
        For iCount from 0 to iSize
            Move asData[iCount] to sLine
            Move (Trim(sLine)) to sLine
            If (Left(sLine, 12) = "FIELD_NUMBER") Begin
                If (Block.iFieldNumber > 0) Begin
                    Move Block to Blocks[iBlock]
                    Increment iBlock            
                End
                Get FieldTextToColumnNumber sLine to Block.iFieldNumber
                Move (ResizeArray(Block.asLines, 0)) to Block.asLines
                Move sLine to Block.asLines[0]
            End
            Else If (sLine = "") Begin
                If (Block.iFieldNumber > 0) Begin
                    Move Block to Blocks[iBlock]
                    Increment iBlock
                End
                Move 0 to Block.iFieldNumber
                Move (ResizeArray(Block.asLines, 0)) to Block.asLines
            End
            Else Begin
                Move sLine to Block.asLines[-1]
            End
        Loop 
        
        If (Block.iFieldNumber > 0) Begin
            Move Block to Blocks[iBlock]
        End
        
        Function_Return Blocks
    End_Function 

    // Combines two string arrays. The first parameter is the newly created .int file,
    // and the second is data from the old .int file that existed before this process began.
    Function CombineArrays String[] asNewData String[] asOldData Returns String[]
        tBlock[] BlocksNew BlocksOld CombinedBlocks
        String[] asCombined asCleanUp
        Integer iCount iSize j iSize2 iFieldNumber
        String sLine sFieldNoTxt
        Boolean bFound
        
        Get ParseBlocks asNewData to BlocksNew
        Get ParseBlocks asOldData to BlocksOld
        Move (SizeOfArray(BlocksOld)) to iSize
        Decrement iSize
        
        Move BlocksNew to CombinedBlocks
        For iCount from 0 to (SizeOfArray(BlocksOld) -1)
            Move BlocksOld[iCount].iFieldNumber to iFieldNumber
            For j from 0 to (SizeOfArray(CombinedBlocks) -1)
                If (CombinedBlocks[j].iFieldNumber = iFieldNumber) Begin 
                    // First, remove the "FIELD_NUMBER xx" line, as it already exists in CombinedBlocks. 
                    Move (RemoveFromArray(BlocksOld[iCount].asLines, 0)) to BlocksOld[iCount].asLines
                    Move (AppendArray(CombinedBlocks[j].asLines, BlocksOld[iCount].asLines)) to CombinedBlocks[j].asLines
                    Move -1 to iFieldNumber
                    Move (SizeOfArray(CombinedBlocks)) to j // Get out of loop.    
                End
            Loop
            If (iFieldNumber <> -1) Begin
                Move (ResizeArray(CombinedBlocks, SizeOfArray(CombinedBlocks) + 1)) to CombinedBlocks
                Move BlocksOld[iCount] to CombinedBlocks[SizeOfArray(CombinedBlocks) - 1]
            End
        Loop
        
        Move (SortArray(CombinedBlocks)) to CombinedBlocks
        Move (SizeOfArray(CombinedBlocks)) to iSize
        Decrement iSize
        For iCount from 0 to iSize
            Move (SizeOfArray(CombinedBlocks[iCount].asLines)) to iSize2 
            Decrement iSize2
            For j from 0 to iSize2
                Get FieldTextToColumnNumber CombinedBlocks[iCount].asLines[j] to iFieldNumber
                // Insert an empty line before each "FIELD_NUMBER xx"
                If (iFieldNumber <> -1) Begin
                    Move "" to asCombined[-1]
                End
                Move CombinedBlocks[iCount].asLines[j] to asCombined[-1]
            Loop
        Loop 
        
        Get RemoveDuplicates asCombined to asCombined
        
        Move "" to asCombined[-1]
        Function_Return asCombined
    End_Function

    Function RemoveDuplicates String[] asIntFileData Returns String[]
        Integer iCount j iBlockStart iBlockEnd
        Integer iSize
        String sLine
        String[] asUniqueAttr asSeenAttrib asResult asEmpty
    
        Move "" to asResult[-1]
        Move (SizeOfArray(asIntFileData)) to iSize
        Decrement iSize
        // Loop through the array to find the start and end of each block
        For iCount from 0 to iSize
            Move asIntFileData[iCount] to sLine
    
            // Detect the start of a new block by finding "FIELD_NUMBER" at the start of the line
            If (Left(sLine, 12) = "FIELD_NUMBER") Begin
                // Clear the unique attributes array and reset block markers
                Move iCount to iBlockStart
                Move iCount to iBlockEnd
                Move asEmpty to asUniqueAttr
                Move asEmpty to asSeenAttrib
    
                // Process each line in the current block
                While (iBlockEnd < iSize)
                    Increment iBlockEnd
                    Move asIntFileData[iBlockEnd] to sLine
    
                    // Break when we hit a blank line, marking the end of the block
                    If (Trim(sLine) = "") Break
    
                    // Check if this line is a duplicate attribute within the block 
                    If (not(SearchArray(Trim(sLine), asSeenAttrib) <> -1)) Begin
                        // If it's unique, add it to both seen and unique attributes arrays
                        Move sLine to asSeenAttrib[-1]
                        Move sLine to asUniqueAttr[-1]
                    End
                Loop
    
                // Append the FIELD_NUMBER line, unique attributes, and blank line to result
                Move asIntFileData[iBlockStart] to asResult[-1]
                For j from 0 to (SizeOfArray(asUniqueAttr) - 1)
                    Move asUniqueAttr[j] to asResult[-1]
                Loop
                Move "" to asResult[-1]
            End
        Loop
        Move (RemoveFromArray(asResult, -1)) to asResult
        Function_Return asResult
    End_Function

    // Extracts the top part of the string array that preceeds all
    // "FIELD_NUMBER xx" data, and stops does not include IntFileBottomData.
    Function IntFileTopData String[] asIntFile Returns String[]
        String[] asResult
        String sLine
        Integer iSize iCount iFieldNumber
        Move (SizeOfArray(asIntFile)) to iSize
        Decrement iSize
        For iCount from 0 to iSize
            Move asIntFile[iCount] to sLine    
            Get FieldTextToColumnNumber sLine to iFieldNumber
            If (iFieldNumber = -1) Begin
                Move asIntFile[iCount] to asResult[-1]
            End
            Else Begin
                Move iSize to iCount
            End
        Loop
        Function_Return asResult
    End_Function

    // Extracts the bottom part of the string array, that deals
    // with index information.
    Function IntFileBottomData String[] asIntFile Returns String[]
        String[] asResult
        String sLine
        Integer iSize iCount iFieldNumber
        Boolean bFound
        Move False to bFound
        Move (SizeOfArray(asIntFile)) to iSize
        Decrement iSize
        For iCount from 0 to iSize
            Move (Trim(Uppercase(asIntFile[iCount]))) to sLine
            // INDEX_NUMBER 1    
            If (not(bFound)) Begin
                Move (Left(sLine, 12) = "INDEX_NUMBER") to bFound
            End
            If (bFound = True) Begin
                Move asIntFile[iCount] to asResult[-1]
            End
        Loop
        Function_Return asResult
    End_Function

    // Adds previously gathered data (asIntFileData) from a current/old .int file, to be added/inserted into
    // a newly created .int file (sIntFile).
    // The gather of data should be made with CollectIntFileRelations
    Function MergeIntFileData Handle hTable String sIntFile String[] asIntFileData Returns Boolean
        Boolean bOK bOpen
        Integer iCh iItem iSize iCount iFieldNumber iColumnData
        String[] asIntfile asFieldsData asTopData asBottomData asResultData
        String sLine sDummy
        
        // This is data from the "old" .int file:
        If (SizeOfArray(asIntFileData) = 0) Begin
            Function_Return True
        End
        Move False to Err
        
        // Read the newly created .int file:
        Get ReadFileToArray sIntFile                   to asIntfile  
        // Get top part of .int file:
        Get IntFileTopData asIntfile                   to asTopData
        // Get the bottom "INDEX_NUMBER xx" data from .int file:
        Get IntFileBottomData asIntfile                to asBottomData
        // Combine the "FIELD_NUMBER xx" data from the two arrays:
        Get CombineArrays asIntfile asIntFileData      to asFieldsData
        Move (AppendArray(asTopData, asFieldsData))    to asResultData
        Move (AppendArray(asResultData, asBottomData)) to asResultData
        
        // Write the updated .int file:      
        Get WriteArrayToFile sIntFile asResultData to bOK 
        
        Move (not(Err)) to bOK
        Move False to Err
        Function_Return bOK
    End_Function

    // Returns the field number from an .int file's line.
    // sLine = "FIELD_NUMBER 2" returns a 2.
    // If no "FIELD_NUMBER" keyword found, or no integer was found
    // after that keyword, a -1 is returned.
    Function FieldTextToColumnNumber String sLine Returns Integer
        Integer iFieldNumber
        Move (Trim(Uppercase(sLine))) to sLine
        If (not(Left(sLine, 12) = "FIELD_NUMBER")) Begin
            Function_Return -1
        End
        Move (Integer(Mid(sLine, 4, 13))) to iFieldNumber
        If (iFieldNumber = 0) Begin
            Move -1 to iFieldNumber 
        End
        Function_Return iFieldNumber
    End_Function

    // Reads a file from disk and returns it as a string array.
    // Note: If the sFileName param does not contain a path,
    //       it is assumed the file resides in the Data folder.
    //       Reads a file and returns it as a string array.
    Function ReadFileToArray String sFileName Returns String[]
        String[] asData
        Integer iCh
        String sPath sLine
        Boolean bFound
        
        Get Seq_New_Channel to iCh
        If (iCh < 0) Begin 
            Error DFERR_PROGRAM "No free channel to read file into string array."
            Function_Return asData
        End
        
        Get FullDataPathFileName sFileName to sFileName
        Direct_Input channel iCh sFileName
        While (not(SeqEof))
            Readln channel iCh asData[-1]
        Loop
        Close_Input channel iCh
        Send Seq_Release_Channel iCh
        
        Function_Return asData
    End_Function

    Function WriteArrayToFile String sFileName String[] asResultData Returns Boolean
        Boolean bOK bFound
        Integer iSize iCount iCh iEmpty 
        
        Get Seq_New_Channel to iCh
        If (iCh < 0) Begin
            Function_Return False
        End 

        // Remove any more than two consequitive lines:
        Move 0 to iEmpty
        Move (SizeOfArray(asResultData)) to iSize
        Decrement iSize
        For iCount from 0 to iSize
            If (Trim(asResultData[iCount]) = "") Begin
                Increment iEmpty
            End
            If (iEmpty >= 2) Begin
                Move (RemoveFromArray(asResultData, iCount)) to asResultData
                Decrement iSize
                If (iCount < iSize and Trim(asResultData[iCount +1]) = "") Begin
                    Move (RemoveFromArray(asResultData, iCount)) to asResultData
                    Decrement iSize
                End
                Move 0 to iEmpty 
            End
            Move (Uppercase(asResultData[iCount]) contains "FIELD_NUMBER " or Uppercase(asResultData[iCount]) contains "INDEX_NUMBER ") to bFound
            If (bFound = True) Begin
                Move 0 to iEmpty
            End
        Loop
        // Remove the very last empty line
        Move (RemoveFromArray(asResultData, -1)) to asResultData

        Get FullDataPathFileName sFileName to sFileName
        // Write the updated .int file:
        Move (SizeOfArray(asResultData)) to iSize
        Decrement iSize
        Direct_Output channel iCh sFileName
            For iCount from 0 to iSize
                Writeln channel iCh asResultData[iCount]
            Loop        
        Flush_Output channel iCh
        Close_Output channel iCh
        Send Seq_Release_Channel iCh
        
        Function_Return True
    End_Function
    
    Function FullDataPathFileName String sFileName Returns String
        String sPath
        Boolean bFound
        Get ParseFolderName sFileName to sPath
        If (sPath <> "") Begin
            Get vFolderExists sPath to bFound
        End
        If (bFound = False) Begin
            Get psDataPath of (phoWorkspace(ghoApplication)) to sPath
        End
        Get vFolderFormat sPath to sPath
        Get ParseFileName sFileName to sFileName
        Move (sPath + sFileName) to sFileName
        Function_Return sFileName
    End_Function

    // To get the DataFlex type from a SQL column DateTime(x) data type, as a text string
    // For usage in .int files.
    // Note: The hTable needs to be open before calling this function.
    Function FieldNumberToDataTimeText Handle hTable String sFieldNoTxt String sDriver Integer iDbType Returns String
        String sDataType
        Integer iFieldNumber iType iDFType iColumns
        Boolean bIsSQLTable bOpen
        
        Get FieldTextToColumnNumber sFieldNoTxt to iFieldNumber
        If (iFieldNumber = -1) Begin
            Function_Return "" 
        End
        Get _IsSQLEntry of ghoDUF hTable to bIsSQLTable
        If (bIsSQLTable = False) Begin
            Function_Return ""
        End
        Get_Attribute DF_FILE_OPENED of hTable to bOpen
        If (bOpen = False) Begin
            Function_Return ""
        End
        Get_Attribute DF_FILE_NUMBER_FIELDS of hTable to iColumns
        If (iFieldNumber > iColumns) Begin
            Function_Return ""
        End
        Get_Attribute DF_FIELD_NATIVE_TYPE of hTable iFieldNumber to iType
        Get UtilColumnTypeToString of ghoDUF sDriver iDbType iType to sDataType
        If (not(Uppercase(sDataType) contains "TIME")) Begin
            Move "" to sDataType
        End
        Else Begin
            Move (Replace("DF_", sDataType, "")) to sDataType
            Move ("FIELD_TYPE " + Uppercase(sDataType)) to sDataType
        End
        
        Function_Return sDataType
    End_Function

    // The hTable needs to be open before calling this function.
    Function NextFieldNumberHidden Handle hTable String sFieldNoTxt Returns String
        String sHidden
        Integer iFieldNumber iType iDFType iNumColumns
        Boolean bIsSQLTable bOpen
        
        Get FieldTextToColumnNumber sFieldNoTxt to iFieldNumber
        If (iFieldNumber = -1) Begin
            Function_Return "" 
        End
        Get _IsSQLEntry of ghoDUF hTable to bIsSQLTable
        If (bIsSQLTable = False) Begin
            Function_Return ""
        End
        Get_Attribute DF_FILE_OPENED of hTable to bOpen
        If (bOpen = False) Begin
            Function_Return ""
        End
        Move "" to sHidden
        Get_Attribute DF_FILE_NUMBER_FIELDS of hTable to iNumColumns
        Increment iFieldNumber
        If (iFieldNumber <= iNumColumns) Begin
            Get_Attribute DF_FIELD_NAME of hTable iFieldNumber to sHidden
            If (not(Uppercase(sHidden) contains "U_")) Begin
                Function_Return ""
            End
            Else Begin
                Move "NEXT_COLUMN_HIDDEN UPPERCASED" to sHidden    
            End
        End
        
        Function_Return sHidden
    End_Function        

    // Not used anymore. Instead files are backed up file-by-file when processed.
//    Function BackupAllIntFiles String sBackupFolder Returns Integer
//        Integer iSize iCount iRetval iCounter
//        String sDataPath sFilter sFileDateExt
//        String[] asFiles asInUseDatFiles 
//        Boolean bExists
//        
//        Get psDataPath of (phoWorkspace(ghoApplication)) to sDataPath
//        Get vFolderFormat sDataPath to sDataPath
//        Move (sDataPath + sBackupFolder) to sBackupFolder
//        Get vFolderExists sBackupFolder to bExists
//        If (bExists = False) Begin
//            Get vCreateDirectory sBackupFolder to iRetval
//            If (iRetval <> 0) Begin
//                Function_Return -1
//            End
//        End
//        Send StartStatusPanel "Backing up *.int files to backup folder:" sBackupFolder 1
//
//        Move "int" to sFilter
//        Get CollectFilteredFiles sDataPath sFilter to asFiles
//        Get FileDatePrefix to sFileDateExt
//        Get vFolderFormat sBackupFolder to sBackupFolder 
//        Set piMaximum of ghoStatusPanel to (SizeOfArray(asFiles))
//        Move (SizeOfArray(asFiles)) to iSize
//        If (iSize = 0) Begin
//            Function_Return 0
//        End
//        Move 0 to iCounter
//        Decrement iSize
//        For iCount from 0 to iSize
//            Send UpdateStatusPanel (sDataPath + asFiles[iCount]) 
//            Get vCopyFile (sDataPath + asFiles[iCount]) (sBackupFolder + String(sFileDateExt) + String(asFiles[iCount])) to iRetval
//            If (iRetval = 0) Begin
//                Increment iCounter
//            End
//            Send DoAdvance of ghoStatusPanel
//        Loop
//        Send StopStatusPanel
//        Function_Return iCounter
//    End_Function 
    
    // The sFileName should not contain any path. Creates a backup copy of the passed sFileName
    // in the sBackup folder with a "sFileDateExt" file name suffix (prior to the file name extension).
    // Example: A passed sFileName of "register.int" will become: "register.2024-11-06__21_34_42.int"
    //          So "register.YYYY-MM-DD__HH_MM_SS.int 
    //          Note that the "YYYY-MM-DD" format depends on your Windows local date settings.
    Function BackupIntFile String sDataPath String sFileName String sBackupFolder Returns Boolean
        String sFileDateExt sExt
        Integer iRetval
        Boolean bExists
        
        Get vFolderFormat sDataPath to sDataPath
        Move (sDataPath + sBackupFolder) to sBackupFolder
        Get vFolderExists sBackupFolder to bExists
        If (bExists = False) Begin
            Get vCreateDirectory sBackupFolder to iRetval
            If (iRetval <> 0) Begin
                Function_Return False
            End
        End
        Get vFolderFormat sBackupFolder to sBackupFolder
        Get FileDatePrefix to sFileDateExt
        Get ParseFileExtension sFileName to sExt 
        Move (Replace(sExt, sFileName, "")) to sFileName
        Get vCopyFile (sDataPath + sFileName + sExt) (sBackupFolder + String(sFileName) + String(sFileDateExt) + sExt) to iRetval
        Function_Return (iRetval = 0)
    End_Function

    Function FileDatePrefix Returns String
        String sFileDateExt sDateTime
        DateTime dDateTime
        Integer iPos
        
        Move (CurrentDateTime()) to dDateTime
        Move dDateTime to sDateTime
        Move (Replaces("/", sDateTime, "-"))  to sDateTime
        Move (Replaces(" ", sDateTime, "__")) to sDateTime
        Move (Replaces(":", sDateTime, "_"))  to sDateTime
        Move (Pos(",", sDateTime)) to iPos
        If (iPos <> 0) Begin
            Move (Left(sDateTime, (iPos -1))) to sDateTime
        End
        Move (sDateTime + ".") to sDateTime
        Function_Return sDateTime 
    End_Function

    Procedure GENERATE_ALL_INT_FILES_CODE_ENDS_HERE
    End_Procedure

    // To move all *.dat related files to a Data subfolder (sBackupFolder)
    // Returns -1 if it failed
    // Returns a positive integer with number of moved files if successful.
    // Note: The sBackupFolder should *not* contain a path, just a folder name.
    Function MoveUnusedDatFileToBackupFolder String sBackupFolder Returns Integer
        Integer iSize iCount iRetval iCounter
        String sDataPath sFilter
        String[] asFiles asInUseDatFiles
        Boolean bExists
        
        Get psDataPath of (phoWorkspace(ghoApplication)) to sDataPath
        Get vFolderFormat sDataPath to sDataPath
        Move (sDataPath + sBackupFolder) to sBackupFolder
        Get vFolderExists sBackupFolder to bExists
        If (bExists = False) Begin
            Get vCreateDirectory sBackupFolder to iRetval
            If (iRetval <> 0) Begin
                Function_Return -1
            End
        End
        Send StartStatusPanel "Moving *.dat files to backup folder:" sBackupFolder 1

        Move "dat,hdr,vld,k1,k2,k3,k4,k5,k6,k7,k8,k9,k10,k11,k12,k13,k14,k15,k16,k17,k18,k19,k20" to sFilter
        Get CollectFilteredFiles sDataPath sFilter to asFiles 
        Set piMaximum of ghoStatusPanel to (SizeOfArray(asFiles))
        Get InUseDatFiles to asInUseDatFiles
        Get SanitizeDatRelatedFiles asFiles asInUseDatFiles to asFiles
        Move (SizeOfArray(asFiles)) to iSize
        If (iSize = 0) Begin
            Send StopStatusPanel
            Function_Return 0
        End
        Move 0 to iCounter
        Decrement iSize
        For iCount from 0 to iSize
            Set Action_Text of ghoStatusPanel to (sDataPath + asFiles[iCount]) 
            Get vMoveFile (sDataPath + asFiles[iCount]) sBackupFolder to iRetval 
            Send DoAdvance of ghoStatusPanel
            If (iRetval = 0) Begin
                Increment iCounter
            End
        Loop
        
        Send StopStatusPanel
        Function_Return iCounter
    End_Function

    // Returns a string array with all *.dat related files from the passed sPath parameter,
    // as a string array.
    Function CollectFilteredFiles String sPath String sFilter Returns String[]
        Integer iCounter iCh iItem
        String sLine sExt 
        String[] asFiles asExt
        
        Get Seq_New_Channel to iCh
        If (iCh < 1) Begin
            Error DFERR_PROGRAM "No free channel to read *.dat files to string array."
            Function_Return asFiles
        End
        
        Move (StrSplitToArray(sFilter, ",")) to asExt
        Direct_Input channel iCh ("dir:" * String(sPath))
        Repeat
            Readln sLine
            Get ParseFileExtension sLine to sExt
            Move (SearchArray(sExt, asExt, Desktop, (RefFunc(DFSTRICMP)))) to iItem
            If (iItem <> -1) Begin
                Move sLine to asFiles[-1]
            End
        Until (SeqEof)
        Close_Input channel iCh
        Send Seq_Release_Channel iCh
        
        Function_Return asFiles
    End_Function

    Function SanitizeDatRelatedFiles String[] asFiles String[] asDatFilesInUse Returns String[]
        Integer iSize iCount iItem
        String sFileName sFileNameNoExt sExt sFileNameShort
        
        // We add these files to the .dat files array as we don't want them to be moved:
        Move "dbversion.dat" to asDatFilesInUse[-1]
        Move "flexerrs.dat"  to asDatFilesInUse[-1]
        Move "dferr001.dat"  to asDatFilesInUse[-1]
        Move "dferr002.dat"  to asDatFilesInUse[-1]
        Move "dferr003.dat"  to asDatFilesInUse[-1]  
        Move (SizeOfArray(asDatFilesInUse)) to iSize
        Decrement iSize
        For iCount from 0 to iSize
            Move (SearchArray(asDatFilesInUse[iCount], asFiles, Desktop, (RefFunc(DFSTRICMP)))) to iItem
            If (iItem <> -1) Begin
                Get RemoveArrayDatRelatedFiles asFiles asDatFilesInUse[iCount] to asFiles
            End
        Loop
        
        Function_Return asFiles
    End_Function

    // Removes all files with the same name as param sFileName, without the extension,
    // from the passed asFiles string array.
    Function RemoveArrayDatRelatedFiles String[] asFiles String sFileName Returns String[]
        String sExt sFileNameShortOrg sFileNameShortNew
        Integer iSize iCount iItem
        
        Move (SizeOfArray(asFiles)) to iSize
        If (iSize = 0) Begin
            Function_Return asFiles
        End

        Get ParseFileExtension sFileName to sExt
        Move (Replace("." + sExt, sFileName, "")) to sFileNameShortOrg
        Move (SearchArray(sFileName, asFiles, Desktop, (RefFunc(DFSTRICMP)))) to iItem
        If (iItem = -1) Begin
            Function_Return asFiles
        End
        Repeat
            Move (RemoveFromArray(asFiles, iItem)) to asFiles
            If (iItem < SizeOfArray(asFiles)) Begin
                Get ParseFileExtension asFiles[iItem] to sExt
                Move (Replace("." + sExt, asFiles[iItem], "")) to sFileNameShortNew 
            End
        Until (Lowercase(sFileNameShortOrg) <> Lowercase(sFileNameShortNew) or iItem >= SizeOfArray(asFiles))
        
        Function_Return asFiles    
    End_Function

    Function InUseDatFiles Returns String[]
        tFilelist[] FilelistTables 
        String[] asFiles
        Integer iSize iCount
        Boolean bIsIntTable
        
        Get pFileListArray of ghoDUF to FileListTables
        If (SizeOfArray(FilelistTables) = 0) Begin
            Send RefreshData
            Get pFileListArray of ghoDUF to FileListTables
        End
        Move (SizeOfArray(FilelistTables)) to iSize
        Decrement iSize
        For iCount from 0 to iSize
            Get _IsIntEntry of ghoDUF FilelistTables[iCount].hTable to bIsIntTable
            If (bIsIntTable = False and FilelistTables[iCount].bIsAlias = False and FilelistTables[iCount].sDriver = DATAFLEX_ID) Begin
                Move (FilelistTables[iCount].sRootName + ".dat") to asFiles[-1]
            End
        Loop
        Function_Return asFiles
    End_Function
                
    // To remove any "Alias" word from the DisplayName
    Function RemoveDisplayNameAlias Handle hTable String sDisplayNameOrg Returns String
        Integer iPos
        String sDisplayNameNew
        Move sDisplayNameOrg to sDisplayNameNew
        If (Lowercase(sDisplayNameOrg) contains "alias") Begin
            Move (Pos("alias", Lowercase(sDisplayNameOrg))) to iPos
            Move (Overstrike("XXXXXXX", sDisplayNameOrg, iPos -1)) to sDisplayNameNew
            Move (Replace("XXXXXXX", sDisplayNameNew, "")) to sDisplayNameNew
            Set_Attribute DF_FILE_DISPLAY_NAME of hTable to sDisplayNameNew
        End
        Function_Return sDisplayNameNew
    End_Function

    // Helper procedures for status panel/progress bar
    Procedure StartStatusPanel String sMessage String sMessage2 Integer iSize
        Send StartStatusPanel of ghoDUF sMessage sMessage2 iSize
        Set Caption_text of ghoStatusPanel to "The Database Update Framework"
        Set Progress_Bar_Overall_Visible_State of ghoStatusPanel to False
    End_Procedure
    
    Procedure StopStatusPanel
        Send Stop_StatusPanel of ghoStatusPanel
    End_Procedure

    Procedure UpdateStatusPanel String sMessage
        Send Update_StatusPanel of ghoStatusPanel sMessage
    End_Procedure
    
    Procedure WriteError String sErrorText
        Integer iCh
        Boolean bOpenLogFile
        
        Get pbOpenLogFile to bOpenLogFile
        If (bOpenLogFile = False) Begin
            Send OpenLogFile
        End
        Get piChannel to iCh
        If (iCh < 0) Begin
            Procedure_Return
        End
        Writeln channel iCh sErrorText 
        Flush_Output channel iCh
    End_Procedure

    Procedure OpenLogFile
        String sLogFile sTimeStamp sFilelist
        Integer iCh
        Boolean bOpenLogFile
        
        Get Value of oFilelist_fm to sFilelist
        If (sFilelist = "") Begin
            Procedure_Return
        End
        Get pbOpenLogFile to bOpenLogFile
        If (bOpenLogFile = True) Begin
            Procedure_Return
        End
        Get Value of oLogFile_fm to sLogFile
        Get piChannel to iCh
        If (iCh >= 0) Begin
            Send Seq_Close_Channel iCh
        End
        Get Seq_Append_Output_Channel sLogFile to iCh
        If (iCh < 0) Begin
            Error DFERR_PROGRAM ("No free channel to write logfile:" * String(sLogFile))
            Procedure_Return
        End
        Set piChannel to iCh
        Set pbOpenLogFile to True
        Move (CurrentDateTime()) to sTimeStamp  
        Writeln channel iCh ""
        Writeln channel iCh "Log file Opened date/time: " (String(sTimeStamp))
    End_Procedure

    Procedure CloseLogFile
        String sTimeStamp
        Integer iCh
        Boolean bOpenLogFile
        
        Get pbOpenLogFile to bOpenLogFile
        If (bOpenLogFile = False) Begin
            Procedure_Return
        End

        Get piChannel to iCh  
        If (iCh < 0) Begin
            Showln "iCh = " iCh " Err = " (Err) " LastErr = " LastErr " ErrLine = " ErrLine
        End
        If (iCh >= 0) Begin
            Move (CurrentDateTime()) to sTimeStamp
            Writeln channel iCh "Log file closed date/time: " (String(sTimeStamp))
            Flush_Output channel iCh
            Close_Output channel iCh
            Send Seq_Close_Channel iCh
        End
        Set piChannel to -1  
        Set pbOpenLogFile to False
    End_Procedure
                
    Procedure WriteAliasEntryError Boolean bIsIntFile Handle hTable String sRootNameAlias String sLogicalNameAlias String sRootNameMaster String sLogicalNameMaster
        Integer iCh
        
        Send OpenLogFile
        Get piChannel to iCh
        Writeln channel iCh "File Number        = " hTable
        Writeln channel iCh "Alias RootName     = " sRootNameAlias
        Writeln channel iCh "Alias LogicalName  = " sLogicalNameAlias
        Writeln channel iCh "Master RootName    = " sRootNameMaster
        Writeln channel iCh "Master LogicalName = " sLogicalNameMaster
        If (bIsIntFile = False) Begin
            Writeln channel iCh "Alias RootName Error"
        End
        Else Begin
            Writeln channel iCh "Alias '.int' Filelist error OR the .int file doesn't exist."    
        End
        Writeln channel iCh  
        Send CloseLogFile            
    End_Procedure
    
    Procedure WriteToLogFile Boolean bIsAlias Handle hTable String sLogicalNameOrg String sRootNameOrg String sRootNameNew String sDisplayNameOrg String sDisplayNameNew
        Integer iCh

        Send OpenLogFile
        Get piChannel to iCh
        Writeln channel iCh "File Number       = " hTable
        Writeln channel iCh "Alias RootName    = " sRootNameOrg
        If (sRootNameNew <> "") Begin
            Writeln channel iCh "NEW RootName      = " sRootNameNew
        End
        Writeln channel iCh "Alias LogicalName = " sLogicalNameOrg
        Writeln channel iCh "Alias DisplayName = " sDisplayNameOrg 
        If (sDisplayNameNew <> "") Begin
            Writeln channel iCh "NEW DisplayName   = " sDisplayNameNew
        End
        Writeln channel iCh ""
        Send CloseLogFile            
    End_Procedure   
    
    Procedure RefreshData
        String sFileList  
        Get psFileList to sFileList
        If (sFileList = "") Begin
            Procedure_Return
        End
        Send ShowSQLTablesCount
        Send ShowFileListData
        Send CloseLogFile
    End_Procedure  
    
    Procedure ClearData
        Broadcast Recursive Send ClearData of (oFilelistFixerView(Self))
        Set psConnId to ""
        Set psConnIdFile to ""
        Set piChannel to -1  
    End_Procedure  
    
    // To automatically maximize the view size.
    // Way more complicated than it should be!
    Procedure Page Integer iPageObject
        Forward Send Page iPageObject
        Set View_Mode to Viewmode_Zoom 
        Set Maximize_Icon to False     
        Set Minimize_Icon to False     
        Set Sysmenu_Icon to False
        // This is the crucial bit:
        Set Border_Style of (Client_Id(ghoCommandBars)) to Border_None
    End_Procedure

    On_Key kClear Send RefreshData
End_Object    
