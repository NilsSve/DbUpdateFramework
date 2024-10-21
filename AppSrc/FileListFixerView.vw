Use Windows.pkg
Use Dfclient.pkg
Use MSSqldrv.pkg 
Use db2_drv.pkg
Use odbc_drv.pkg
Use seq_chnl.pkg
Use File_dlg.pkg
Use cRichEdit.pkg
Use cRDCForm.pkg
Use vWin32fh.pkg

// Just to get a shorter handle name
Global_Variable Handle ghoDUF 
Move ghoDbUpdateFunctionLibrary to ghoDUF

Define CS_ReportFileName for "FileListFixes.txt"
Define CS_BackupFolder   for "Backup"

Class cNumForm is a Form
    Procedure Construct_Object
        Forward Send Construct_Object
        Set Label_Col_Offset to 2
        Set Label_Justification_Mode to JMode_Right
        Set Form_Datatype to Mask_Numeric_Window  
        Set Numeric_Mask 0 to 4 0
    End_Procedure
End_Class

Activate_View Acivate_oFileListFixerView for oFileListFixerView
Object oFilelistFixerView is a dbView 
    Set Size to 388 556
    Set piMinSize to 384 556
    Set Location to 2 2
    Set Maximize_Icon to True
    Set Border_Style to Border_Thick
    Set pbAutoActivate to True

    Property String psConnId
    Property Integer piChannel -1

    Object oFilelist_fm is a cRDCForm
        Set Size to 12 323
        Set Location to 14 11
        Set Label_Col_Offset to 0
        Set Label_Row_Offset to 1
        Set Label_Justification_Mode to JMode_Top
        Set Label to "Filelist.cfg:"
        Set peAnchors to anTopLeftRight
        Set Prompt_Button_Mode to PB_PromptOn
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
            String sFileList sPath
            Boolean bExists bCfgFile bOK

            Get Value to sFileList
            Get vFilePathExists sFileList to bExists
            Move (Lowercase(sFileList) contains ".cfg") to bCfgFile
            If (bExists = True and bCfgFile) Begin
                // A little trick to show the filelist.cfg in the form before we start filling the grid.
                Send PumpMsgQueue of Desktop
                Get ChangeFilelistPathing of ghoApplication sFileList to bOK
                If (bOK = True) Begin
                    Set psFilelistFrom of ghoApplication to sFileList
                    Send UpdateConnIdData of oConnidInfo_edt
                    Get ParseFolderName sFileList to sPath
                    Get vFolderFormat sPath to sPath
                    Set Value of oLogFile_fm to (sPath + CS_ReportFileName)
                End
            End
        End_Procedure

        Procedure Page Integer iPageObject
            String sFileName sDataPath sVal
            
            Forward Send Page iPageObject
            Get psFilelistFrom of ghoApplication to sFileName
            If (sFileName <> "") Begin
                Move sFileName to sVal
            End
            Else Begin
                Get psDataPath of (phoWorkspace(ghoApplication)) to sDataPath
                Move "Filelist.cfg" to sFileName
                Move (sDataPath + "\" + sFileName) to sVal
            End
            Set Value to sVal
        End_Procedure
        
    End_Object

    Object oConnidInfo_edt is a cRichEdit
        Set Size to 75 318
        Set Location to 28 12
        Set peAnchors to anTopLeftRight
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
            
            Get psDataPath of (phoWorkspace(ghoApplication)) to sDatapath
            File_Exist (sDatapath + "\" + String(C_ConnectionIniFileName)) bExists
            If (bExists = True) Begin
                Move (sDatapath + "\" + String(C_ConnectionIniFileName)) to sDFConnidFile
            End
            
            Send Delete_Data
            Get ConnectionIDs of ghoConnection to Connections
            If (SizeOfArray(Connections) <> 0) Begin
                Set psConnId to Connections[0].sId
                Send AppendTextLn ("DFConnId File=" + String(sDFConnidFile))
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

    Object oDatabase_fm is a Form
        Set Label to "SQL Database Name:"
        Set Size to 12 151
        Set Location to 119 12
        Set Label_Col_Offset to 0
        Set Label_Justification_Mode to JMode_Top
        Set peAnchors to anNone
        Set Label_Row_Offset to 1
        Set Label_FontWeight to fw_Bold
        Set FontWeight to fw_Bold
    End_Object

    Object oIntTableErrors_edt is a cRichEdit
        Set Size to 70 86
        Set Location to 28 386
        Set Label to "*.int File DFCONNID Changes"
        Set peAnchors to anTopRight
    End_Object

    Object oChangeAllIntFiles_btn is a Button
        Set Size to 28 61
        Set Location to 70 478
        Set Label to "Check/change .int files to use DFConnid"
        Set psToolTip to "Changes or updates all .int files in the Data folder - except for DAW driver .int files (MSSQL_DRV.int, DB2_DRV.int & ODBC_DRV.int) - to use 'SERVER_NAME DFCONNID=xxx'"
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
            Set Value of oNoOfOpenErrorTables_fm to 0
            Move oIntTableErrors_edt to ho     
            Send Delete_Data of ho
            Send StartStatusPanel "Changing to Connection ID's in .int files" "" -1

            Get SqlUtilChangeIntFilesToConnectionIDs of ghoDUF sDataPath sConnectionID True to asFileChanges

            Send Update_StatusPanel of ghoStatusPanel ""
            Get Active_State of ghoStatusPanel to bActive
            If (bActive = False) Begin
                Send StopStatusPanel
                Send Info_Box "Process interupted..."
                Procedure_Return
            End

            Move (SizeOfArray(asFileChanges)) to iSize
            Set Value of oNoOfOpenErrorTables_fm to (iSize max 0)
            Send StopStatusPanel
            If (SizeOfArray(asFileChanges) <> 0) Begin
                Decrement iSize
                For iCount from 0 to iSize
                    Send AppendTextLn of ho asFileChanges[iCount]
                Loop          
                // Note: Removes all cache-files:
                EraseFile (sDataPath + "\*.cch")
                Send Info_Box ("Ready!" * String(iSize + 1) * ".int files contained errors and were changed to be using DFConnID's.")
            End
            Else Begin
                Send Info_Box "Ready! No problems found."    
            End
            Send StopStatusPanel
        End_Procedure

    End_Object

    Object oNoOfOpenErrorTables_fm is a cNumForm
        Set Size to 12 34
        Set Location to 104 438
        Set Label to "Counter:"
        Set peAnchors to anTopRight
    End_Object

    Object oNumberOfSQLTables_fm is a cNumForm
        Set Label to "Number of Tables in SQL Database:"
        Set Size to 12 34
        Set Location to 119 438
        Set peAnchors to anTopRight
    End_Object

    Object oCount_gp is a Group
        Set Size to 166 537
        Set Location to 133 12
        Set Label to "Counters:"
        Set peAnchors to anTopLeftRight

        Object oDatTables_edt is a cRichEdit
            Set Size to 110 67
            Set Location to 29 6
            Set Label to "RootName *.dat"
        End_Object

        Object oNoOfDatTables_fm is a cNumForm
            Set Size to 12 34
            Set Location to 144 39
            Set Label to "Counter:"
            Set peAnchors to anBottomLeft 
            Procedure OnChange
                String sVal
                Get Value to sVal
                Set Value of oNoOfDatTables2_fm to sVal
            End_Procedure
        End_Object

        Object oRootNameIntTables_edt is a cRichEdit
            Set Size to 110 69
            Set Location to 29 80
            Set Label to "RootName *.int"
        End_Object

        Object oNoOfRootNameIntTables_fm is a cNumForm
            Set Size to 12 34
            Set Location to 144 115
            Set Label to "Counter:"
            Set peAnchors to anBottomLeft
        End_Object

        Object oAliasErrors_edt is a cRichEdit
            Set Size to 110 82
            Set Location to 29 155
            Set Label to "Alias Table Errors"
        End_Object

        Object oNoOfAliasErrorTables_fm is a cNumForm
            Set Size to 12 34
            Set Location to 144 203
            Set Label to "Counter:"
        End_Object

        Object oOpenErrorTables_edt is a cRichEdit
            Set Size to 110 76
            Set Location to 29 242
            Set Label to "Open Table Errors"
            Set peAnchors to anTopLeftRight
        End_Object

        Object oNoOfOpenErrorTables_fm is a cNumForm
            Set Size to 12 34
            Set Location to 144 284
            Set Label to "Counter:"
            Set peAnchors to anBottomRight
        End_Object

        Object oFileList_grp is a Group
            Set Size to 137 209
            Set Location to 25 323
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
            
            Object oRefresh_btn is a Button
                Set Size to 26 61
                Set Location to 104 141
                Set Label to "Refresh!"
                Set Default_State to True
                Set Form_FontWeight to fw_Bold
                Set psToolTip to "Refreshes all data by reading the Filelist.cfg and SQL database tables"
                
                Procedure OnClick
                    Send Refresh
                End_Procedure
            
                Procedure Refresh
                    Send ShowSQLTablesCount
                    Send ShowFileListData
                End_Procedure
            
            End_Object
            
        End_Object
        
    End_Object

    Object oFixProblems_grp is a Group
        Set Size to 46 537
        Set Location to 302 12
        Set Label to "Actions:"
        Set peAnchors to anTopLeftRight

        Object oFixAliasProblems_btn is a Button
            Set Size to 32 61
            Set Location to 10 5
            Set Label to "1. Fix Filelist Alias Errors"
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
                    Send ShowFileListData
                    Send Info_Box ("Ready!" * String(iCounter) * "Alias problems fixed in Filelist.cfg. See Also: Logfile")
                End
                Else Begin
                    Send Info_Box "Ready! Filelist checked and NO Alias problems found."
                End
            End_Procedure
                          
        End_Object

        Object oFixFileListSQLMissingTables_btn is a Button
            Set Size to 32 61
            Set Location to 10 70
            Set Label to "2. Make Filelist RootNames equal to SQL Database"
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

        // Will remove non Alias Filelist entries that:
        //   - Does not have a corresponding .Dat file, 
        Object oFixFileListErrors_btn is a Button
            Set Size to 32 61
            Set Location to 10 135
            Set Label to "3. Fix Filelist .dat Errors"
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

        Object oFixOpenTableErrors_btn is a Button
            Set Size to 32 61
            Set Location to 10 200
            Set Label to "4. Fix Filelist Open Errors"
            Set peAnchors to anTopRight
            Set MultiLineState to True
            Set psToolTip to "The fix will spin through the Filelist and \n1. Try to fix or removes Non SQL entries for tables that cannot be opened."
        
            Procedure OnClick
                Integer iRetval iCounter iOpenErrors
                
                Get YesNo_Box "The fix will spin through the Filelist and \n1. Try to fix or remove Non SQL Filelist entries for tables that cannot be opened.\n\nPlease take a copy of the Filelist.cfg file first!\n\nContinue?" to iRetval
                If (iRetval <> MBR_Yes) Begin
                    Procedure_Return    
                End

                Get FixOpenErrorTables to iCounter
                Get _CountFileListOpenErrors of ghoDUF to iOpenErrors
                
                If (iOpenErrors <> 0 and iCounter = 0) Begin 
                    Send ShowFileListData
                    Send Info_Box ("Ready! No Errors were fixed. NOTE:" * String(iOpenErrors) * "Open errors still exists and needs your attention. Please run the Studio's 'SQL Connect/Repair Wizard' for those tables!)")
                End
                Else If (iOpenErrors <> 0 and iCounter <> 0) Begin
                    Send ShowFileListData
                    Send Info_Box ("Ready!" * String(iCounter) * "RootName entries were changed. See: Log file!")
                End
                Else Begin
                    Send Info_Box "Ready! No problems found"
                End
            End_Procedure
                          
        End_Object

        Object oRefreshAllIntFiles_btn is a Button
            Set Size to 32 61
            Set Location to 10 265
            Set Label to "5. Refresh all *.int files"
            Set peAnchors to anTopRight
            Set MultiLineState to True
            Set psToolTip to "This will refresh all .int files."
            
            Property Boolean pbErrorProcessingState
            Property Integer piError
            Property String psErrorText

            Procedure OnClick
                Integer iRetval iCounter
                
                Get YesNo_Box "This will refresh all .int files.\n\nContinue?" to iRetval
                If (iRetval <> MBR_Yes) Begin
                    Procedure_Return    
                End
                
                Get RefreshAllIntFiles Self to iCounter
                If (iCounter <> 0) Begin
                    Send Info_Box ("Ready! Refresh of:" * String(iCounter) * ".int files done.")
                End
                Else Begin
                    Send Info_Box "Ready! No .int files to refresh."
                End
            End_Procedure
            
            Procedure Error_Report Integer iErrNum Integer iErrLine String sErrText 
                If (pbErrorProcessingState(Self)) ; 
                    Procedure_Return 
            
                Set pbErrorProcessingState to True 
                Set piError to iErrNum
                Set psErrorText to sErrText
            
                Set pbErrorProcessingState to False 
            End_Procedure

        End_Object

        Object oRecreateAllIntFiles_btn is a Button
            Set Size to 32 61
            Set Location to 10 396
            Set Label to "7. Force a restruct of all *.int files"
            Set peAnchors to anTopRight
            Set MultiLineState to True
            Set psToolTip to "This will recreate all .int files."
            
            Property Boolean pbErrorProcessingState
            Property Integer piError
            Property String psErrorText

            Procedure OnClick
                Integer iRetval iCounter
                
                Get YesNo_Box ("This will recreate all .int files. Relations and column index segment info will be preserved. A backup of all .int files will be created in the" * String(CS_BackupFolder) * "folder.\n\nContinue?") to iRetval
                If (iRetval <> MBR_Yes) Begin
                    Procedure_Return    
                End
                
                Get RecreateAllIntFiles Self to iCounter
                If (iCounter <> 0) Begin
                    Send Info_Box ("Ready!" * String(iCounter) * ".int files recreated.")
                End
                Else Begin
                    Send Info_Box "Ready! No .int files found to recreate."
                End
            End_Procedure
            
            Procedure Error_Report Integer iErrNum Integer iErrLine String sErrText 
                If (pbErrorProcessingState(Self)) ; 
                    Procedure_Return 
            
                Set pbErrorProcessingState to True 
                Set piError to iErrNum
                Set psErrorText to sErrText
            
                Set pbErrorProcessingState to False 
            End_Procedure

        End_Object

        Object oFixIntFileError_btn is a Button
            Set Size to 32 61
            Set Location to 10 331
            Set Label to "6. Recreate *.int files with open errors"
            Set peAnchors to anTopRight
            Set MultiLineState to True
            Set psToolTip to "This will try recreate the .int files listed in the 'Open Table Errors' list."
            
            Property Boolean pbErrorProcessingState
            Property Integer piError
            Property String psErrorText

            Procedure OnClick
                Integer iRetval iCounter
                
                Get YesNo_Box "This will recreate the .int files listed in the 'Open Table Errors' list.\n\n\nContinue?" to iRetval
                If (iRetval <> MBR_Yes) Begin
                    Procedure_Return    
                End
                
                Get FixAllIntFileErrors Self to iCounter
                If (iCounter <> 0) Begin
                    Send Info_Box ("Ready! Update to:" * String(iCounter) * ".int files done.")
                End
                Else Begin
                    Send Info_Box "Ready! No problems found."
                End
            End_Procedure
            
            Procedure Error_Report Integer iErrNum Integer iErrLine String sErrText 
                If (pbErrorProcessingState(Self)) ; 
                    Procedure_Return 
            
                Set pbErrorProcessingState to True 
                Set piError to iErrNum
                Set psErrorText to sErrText
            
                Set pbErrorProcessingState to False 
            End_Procedure

        End_Object

        Object oMoveUnusedDatFiles_btn is a Button
            Set Size to 32 61
            Set Location to 8 463
            Set Label to "8. Move unused .dat files to Backup folder"
            Set peAnchors to anTopRight
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
        Set Size to 30 537
        Set Location to 351 12
        Set Label to "Log File"
        Set peAnchors to anTopLeftRight

        Object oLogFile_fm is a Form
            Set Size to 12 455
            Set Location to 10 12
            Set Enabled_State to False
            Set Label to "Log File:"
            Set peAnchors to anTopLeftRight
    
            Procedure Page Integer iPageObject
                String sFileName sHomePath
                Forward Send Page iPageObject
                Get psHome of (phoWorkspace(ghoApplication)) to sHomePath
                Move CS_ReportFileName to sFileName
                Set Value to (sHomePath + sFileName)
            End_Procedure
            
        End_Object

        Object oOpenLogFile_btn is a Button
            Set Size to 14 49
            Set Location to 10 473
            Set Label to "View Log File"
            Set peAnchors to anTopRight
        
            Procedure OnClick
                String sFileName
                Get Value of oLogFile_fm to sFileName
                Runprogram Shell Background sFileName
            End_Procedure
        
        End_Object  

    End_Object
    
    // Dummy message that shows as delimiter in the Studio's Code Explorer:
    Procedure COMMON_MESSAGES
    End_Procedure
    
    Procedure ShowAliasErrorTables
        tFilelist[] FileListArray
        Integer iSize iCount
        Handle ho
        
        Move (oAliasErrors_edt(Self)) to ho
        Send Delete_Data of ho
        Set Value of oNoOfAliasErrorTables_fm to 0
        Get _CountFileListAliasErrors of ghoDUF to FileListArray
        Move (SizeOfArray(FileListArray)) to iSize
        If (iSize = 0) Begin
            Procedure_Return
        End
        Decrement iSize
        For iCount from 0 to iSize
            Send AppendTextLn of ho (FileListArray[iCount].sRootName * "(" + String(FileListArray[iCount].hTable) + ")")
        Loop
        Set Value of oNoOfAliasErrorTables_fm to (iSize + 1)
    End_Procedure

    Procedure ShowSQLTablesCount
        String[] asSQLTables
        Send UtilFillSQLTables of ghoDUF
        Get pasSQLDataTables   of ghoDUF to asSQLTables
        Set Value of oNumberOfSQLTables_fm to (String(SizeOfArray(asSQLTables))) 
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
        Set Value of oNoOfOpenErrorTables_fm to iCount
        Send ShowAliasErrorTables
        
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
        Set Value of oNoOfDatTables_fm to iCounter
    End_Procedure

    Function InUseDatFiles Returns String[]
        tFilelist[] FilelistTables 
        String[] asFiles
        Integer iSize iCount
        Boolean bIsIntTable
        
        Get pFileListArray of ghoDUF to FileListTables
        If (SizeOfArray(FilelistTables) = 0) Begin
            Send ShowFileListData
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
        Set Value of oNoOfRootNameIntTables_fm to iCounter
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
        
        Set pErrorTables of ghoDUF to ErrorFilesArray
    End_Procedure
    
    Function FixFileListAliasProblems Returns Integer
        Integer iCounter iIntError
        Handle hTable hMasterTable
        String sLogicalNameOrg sRootNameOrg sDisplayNameOrg 
        String sDriver sNoDriverRootname sRootNameNew sLogicalNameNew sDisplayNameNew
        Boolean bIsAlias bIsIntTable bIsAliasSQL bIsMasterSQL
        tFilelist[] FilelistArray
        
        Move 0 to iCounter 
        Move 0 to hTable

        Get pFileListArray of ghoDUF to FilelistArray
        If (SizeOfArray(FilelistArray) = 0) Begin
            Send ShowFileListData
            Get pFileListArray of ghoDUF to FilelistArray
        End
                
        Repeat
            Get_Attribute DF_FILE_NEXT_USED of hTable to hTable
            // Table 50 is FlexErrs
            If (hTable <> 0 and hTable <> 50) Begin
                Get_Attribute DF_FILE_ROOT_NAME    of hTable to sRootNameOrg
                Get_Attribute DF_FILE_LOGICAL_NAME of hTable to sLogicalNameOrg
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
                    
                    // ToDo: If the table is Alias but the Master couldn't be found, should we remove the Alias from Filelist.cfg?
                    Else If (hMasterTable = 0) Begin
                        Set_Attribute DF_FILE_ROOT_NAME    of hTable to ""
                        Set_Attribute DF_FILE_LOGICAL_NAME of hTable to ""
                        Set_Attribute DF_FILE_DISPLAY_NAME of hTable to ""
                        Send WriteToLogFile True hTable sLogicalNameOrg sRootNameOrg "" sNoDriverRootname sDisplayNameOrg "Alias Filelist entry SHOULD BE REMOVED!"
                        Increment iCounter
                    End
                    Get_Attribute DF_FILE_DISPLAY_NAME of hTable to sDisplayNameNew
                    Get_Attribute DF_FILE_LOGICAL_NAME of hTable to sLogicalNameNew
                    If (not(Lowercase(sDisplayNameNew) contains "alias")) Begin
                        Move (sLogicalNameNew * "(" + sNoDriverRootname * "ALIAS)") to sDisplayNameNew
                        Set_Attribute DF_FILE_DISPLAY_NAME of hTable to sDisplayNameNew
                        Send WriteToLogFile True hTable sLogicalNameOrg sRootNameOrg sRootNameNew sNoDriverRootname sDisplayNameOrg sDisplayNameNew
                        Increment iCounter
                    End
                End
                // Adjust DisplayName?
                If (bIsAlias = False and Lowercase(sDisplayNameOrg) contains "alias") Begin
                    Get RemoveDisplayNameAlias hTable sDisplayNameOrg to sDisplayNameNew
                    Send WriteToLogFile False hTable sLogicalNameOrg sRootNameOrg sRootNameNew sNoDriverRootname sDisplayNameOrg sDisplayNameNew
                    Increment iCounter
                End
            End
        Until (hTable = 0)
        Function_Return iCounter
    End_Function

    Function FixFileListSQLMissingTables Returns Integer
        Integer iRetval hTable iSize iCount iItem iCh iCounter iAliases iPos
        String[] asSQLTables
        tFilelist[] FileListArray
        String sNoDriverRootname sDriver sRootName sRootNameNew sDatabase sLogicalName sDisplayName
        Boolean bIsAlias bIsIntTable bExists
        
        Send Cursor_Wait of Cursor_Control
        Move 0 to iCounter 
        Move 0 to hTable
        Get pasSQLDataTables of ghoDUF to asSQLTables
        If (SizeOfArray(asSQLTables) = 0) Begin
            Send UtilFillSQLTables of ghoDUF
            Get pasSQLDataTables of ghoDUF to asSQLTables
        End
        Get pFileListArray of ghoDUF to FileListArray
        If (SizeOfArray(FileListArray) = 0) Begin
            Send ShowFileListData
            Get pFileListArray of ghoDUF to FileListArray
        End    
        
        Send OpenLogFile
        Get piChannel to iCh
        Get psDatabase of ghoDUF to sDatabase
        Writeln channel iCh ("Adjustment of RootNames for tables that exists in the SQL database:" * String(sDatabase))
        
        Move (SizeOfArray(FileListArray)) to iSize
        Decrement iSize
        
        For iCount from 0 to iSize
            Move FileListArray[iCount].hTable to hTable
            Move FileListArray[iCount].sRootName to sRootName
            Get _RemoveDriverFromRootName of ghoDUF sRootName (&sDriver) to sNoDriverRootname
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
        Send Cursor_Ready of Cursor_Control
        If (iCounter <> 0) Begin
            Send ShowFileListData
        End
        Function_Return iCounter
    End_Function

    Function FixFileListErrors Returns Integer
        Integer iRetval hTable iSize iCount iItem iCh iCounter iAliases
        tFilelist[] FileListArray
        String sNoDriverRootname sDriver sRootName sRootNameNew sDatabase sLogicalName sDisplayName sDataPath
        Boolean bIsAlias bIsDatEntry bExists
        
        Move 0 to iCounter 
        Move 0 to hTable

        Get pFileListArray of ghoDUF to FileListArray
        If (SizeOfArray(FileListArray) = 0) Begin
            Send ShowFileListData
            Get pFileListArray of ghoDUF to FileListArray
        End    
        Send Cursor_Wait of Cursor_Control
        Send OpenLogFile
        Get piChannel to iCh
        Move (SizeOfArray(FileListArray)) to iSize
        Decrement iSize
        
        For iCount from 0 to iSize
            Move FileListArray[iCount].hTable to hTable
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
        Send Cursor_Ready of Cursor_Control
        If (iCounter <> 0) Begin
            Send ShowFileListData
        End     
        Function_Return iCounter
    End_Function

    Function FixOpenErrorTables Returns Integer        
        Integer iRetval hTable iSize iCount iItem iCh iCounter iAliases iOpenErrors
        tFilelist[] FileListArray
        String sNoDriverRootname sDriver sRootName sRootNameNew sDatabase sLogicalName sDisplayName sDataPath
        Boolean bIsAlias bExists bChange bFirst bIsSQLTable bIsIntTable
        
        Move False to bFirst
        Move 0 to iCounter 
        Move 0 to hTable
        Get pFileListArray of ghoDUF to FileListArray
        If (SizeOfArray(FileListArray) = 0) Begin
            Send ShowFileListData
            Get pFileListArray of ghoDUF to FileListArray
        End    
        
        Send Cursor_Wait of Cursor_Control
        Get psDataPath of (phoWorkspace(ghoApplication)) to sDataPath
        Send OpenLogFile
        Get piChannel to iCh
        Get psDatabase of ghoDUF to sDatabase
        Move (SizeOfArray(FileListArray)) to iSize
        Decrement iSize
        
        For iCount from 0 to iSize
            Move False to bChange
            Move FileListArray[iCount].hTable to hTable 
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
        Send Cursor_Ready of Cursor_Control  
        Function_Return iCounter
    End_Function

    Function RefreshAllIntFiles Handle hoFrom Returns Integer
        Integer iRetval iSize iCount iCounter
        tFilelist[] FileListArray
        String sDriver sRootName sIntFileName sConnectionID sErrorText sText sDataPath
        Boolean bExists bOK bIsSystem bAnsi bIsAlias
        Handle hTable hoCurrentErrorObject
    
        Move 0 to iCounter
        Move Error_Object_Id to hoCurrentErrorObject
        Move hoFrom to Error_Object_Id
    
        Get pFileListArray of ghoDUF to FileListArray
        If (SizeOfArray(FileListArray) = 0) Begin
            Send ShowFileListData
            Get pFileListArray of ghoDUF to FilelistArray
        End
    
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
            Set Message_Text of ghoStatusPanel to ("Table number:" * String(hTable))
            Get _RemoveDriverFromRootName of ghoDUF FileListArray[iCount].sRootName (&sDriver) to sRootName
            If (sDriver = "") Begin
                Get psDriverID of ghoDUF to sDriver
            End
            Move FileListArray[iCount].bIsAlias to bIsAlias
            If (bIsAlias = False) Begin
                Move (FileListArray[iCount].sNoDriverRootname + ".int") to sIntFileName
                File_Exist (sDataPath + "\" + sIntFileName) bExists
                If (bExists and sDriver <> DATAFLEX_ID) Begin
                    Get _IsSystemFile of ghoDUF hTable to bIsSystem
                    Send Update_StatusPanel of ghoStatusPanel ("Refreshing .int file:" * String(sRootName))
                    
                    // Refresh!
                    Get _SqlUtilRefreshIntFile of ghoDUF hTable sDriver sConnectionID bansi bIsSystem to bOK
    
                    If (bOK) Begin
                        Increment iCounter
                        Set_Attribute DF_FILE_ROOT_NAME of hTable to (sDriver + ":" + FileListArray[iCount].sNoDriverRootname)
                    End
                End
            End
        Loop
    
        Send CloseLogFile
        Send StopStatusPanel
    
        If (iCounter <> 0) Begin
            Send ShowFileListData
        End
        Else Begin
            Move hoCurrentErrorObject to Error_Object_Id
        End
    
        Function_Return iCounter
    End_Function
    
    Function RecreateAllIntFiles Handle hoFrom Returns Integer
        Integer iRetval iSize iCount iCounter
        tFilelist[] FileListArray
        String[] asIntFileData
        String sDriver sIntFileName sConnectionID sErrorText sText sDataPath
        Boolean bExists bOK bIsSystem bAnsi bIsAlias bIsSQL
        Handle hTable hoCurrentErrorObject
    
        Move 0 to iCounter
        Move Error_Object_Id to hoCurrentErrorObject
        Move hoFrom to Error_Object_Id
    
        Get pFileListArray of ghoDUF to FileListArray
        If (SizeOfArray(FileListArray) = 0) Begin
            Send ShowFileListData
            Get pFileListArray of ghoDUF to FilelistArray
        End
    
        Move (SizeOfArray(FileListArray)) to iSize     
        // Each Start_Restructure/End_Restructure calls the "Callback" message 3 times,
        // which does a "Send DoAdvance" to the ghoProgressBar...
        Send StartStatusPanel "Recreating Int Files" "" (iSize * 3)
        Decrement iSize 
        Get BackupAllIntFiles CS_BackupFolder to iCount 
        
        Get psDataPath of (phoWorkspace(ghoApplication)) to sDataPath
        Get psConnId to sConnectionID 
        Get pbToANSI of ghoDUF to bAnsi 
    
        Send OpenLogFile
    
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
                    Get _IsSystemFile of ghoDUF hTable to bIsSystem
                    Send Update_StatusPanel of ghoStatusPanel ("Recreating .int file:" * String(FileListArray[iCount].sRootName))
                    
                    // 1. Collect relation and index info:
                    Get CollectIntFileRelationAndIndexFields hTable sIntFileName sDriver to asIntFileData
                    // 2. Recreate .int file!
                    Get _SqlUtilCreateIntFile of ghoDUF hTable sDriver sConnectionID bAnsi bIsSystem False to bOK
                    If (bOK and (SizeOfArray(asIntFileData) <> 0)) Begin
                        // 3. Add collected relation and index info:
                        Get AddIntFileRelationsAndIndexes sIntFileName asIntFileData to bOK
                    End
                    Increment iCounter
                End
            End
        Loop
    
        Send CloseLogFile
        Send StopStatusPanel
    
        If (iCounter <> 0) Begin
            Send ShowFileListData
        End
        Else Begin
            Move hoCurrentErrorObject to Error_Object_Id
        End
    
        Function_Return iCounter
    End_Function
    
    Function FixAllIntFileErrors Handle hoFrom Returns Integer
        Integer iRetval iSize iCount iCounter
        tFilelist[] ErrorFilesArray
        String sDriver sRootName sIntFileName sConnectionID sErrorText sText
        Boolean bExists bOK bIsSystem
        Handle hTable hoCurrentErrorObject
    
        Move Error_Object_Id to hoCurrentErrorObject
        Move hoFrom to Error_Object_Id
    
        Get pErrorTables of ghoDUF to ErrorFilesArray
        If (SizeOfArray(ErrorFilesArray) = 0) Begin
            Function_Return 0
        End
    
        Move (SizeOfArray(ErrorFilesArray)) to iSize
        Send StartStatusPanel "Fixing Int File Errors" "" iSize
    
        String sDataPath
        Get psDataPath of (phoWorkspace(ghoApplication)) to sDataPath
        Get psConnId to sConnectionID
    
        Send OpenLogFile
    
        For iCount from 0 to (iSize - 1)
    
            Move ErrorFilesArray[iCount].sDriver to sDriver
            If (sDriver = "") Begin
                Get _RemoveDriverFromRootName of ghoDUF ErrorFilesArray[iCount].sRootName (&sDriver) to sRootName
                If (sDriver = "") Begin
                    Get psDriverID of ghoDUF to sDriver
                End
            End

            Send Update_StatusPanel of ghoStatusPanel ("Fixing .int file problems for table:" * String(sRootName))
            Move (ErrorFilesArray[iCount].sNoDriverRootname + ".int") to sIntFileName
            File_Exist (sDataPath + "\" + sIntFileName) bExists
            If (bExists and sDriver <> DATAFLEX_ID) Begin
                Move ErrorFilesArray[iCount].hTable to hTable
                Get _IsSystemFile of ghoDUF hTable to bIsSystem
    
                Get FixSingleIntFile hTable sDriver sConnectionID bIsSystem sIntFileName to bOK
                If (bOK) Begin
                    Increment iCounter
                    Set_Attribute DF_FILE_ROOT_NAME of hTable to (sDriver + ":" + ErrorFilesArray[iCount].sNoDriverRootname)
                End
            End
        Loop
    
        Send CloseLogFile
        Send StopStatusPanel
    
        If (iCounter <> 0) Begin
            Send ShowFileListData
        End
        Else Begin
            Move hoCurrentErrorObject to Error_Object_Id
        End
    
        Function_Return iCounter
    End_Function
    
    // Helper function to fix a single .int file
    Function FixSingleIntFile Handle hTable String sDriver String sConnectionID Boolean bIsSystem String sIntFileName Returns Boolean
        Boolean bOK
        String sErrorText sText
        Integer iRetval
        String[] asIntFileData
    
        // First try to refresh the .int file:
        Get _SqlUtilRefreshIntFile of ghoDUF hTable sDriver sConnectionID True bIsSystem to bOK
        If (bOK) Begin
            Function_Return True
        End
    
        Get psErrorText to sErrorText
        If (Lowercase(sErrorText) contains "invalid int file index definition") Begin
            Move ("There seems to be something wrong with the index definitions and the following error occurred:\n\n" + String(sErrorText) + "\n\nDo you want to try to re-create the .int file?\nContinue?") to sText
        End
        Else Begin
            Move ("There seems to be something wrong with the .int file:\n" + sIntFileName + "\n\nDo you want to try to re-create the .int file?\nContinue?") to sText
        End
    
        Get YesNoCancel_Box sText to iRetval
        If (iRetval <> MBR_Yes) Begin
            Function_Return False
        End
    
        // If it didn't work to refresh, try re-create the .int file:
        Get CollectIntFileRelationAndIndexFields sIntFileName to asIntFileData
        Get _SqlUtilCreateIntFile of ghoDUF hTable sDriver sConnectionID True bIsSystem to bOK
        If (bOK) Begin
            Get AddIntFileRelationsAndIndexes sIntFileName asIntFileData to bOK
            Function_Return True
        End
        Else Begin
            Send Info_Box ("The .int file for table number:" * String(hTable) * "(" + sIntFileName + ") could not be created." )
            Function_Return False
        End
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

    Function AddIntFileRelationsAndIndexes String sIntFile String[] asIntFileData Returns Boolean
        Boolean bOK
        Integer iCh iItem iSize iCount
        String[] asFileData
        String sLine sDummy
        
        Get Seq_New_Channel to iCh
        If (iCh < 0) Begin
            Function_Return False
        End
        
        If (SizeOfArray(asIntFileData) = 0) Begin
            Function_Return False
        End

        Direct_Input channel iCh sIntFile
        While (not(SeqEof))
            Readln channel iCh sLine
            If (Uppercase(sLine) contains "FIELD_NUMBER ") Begin
                Move (SearchArray(sLine, asIntFileData, Desktop, (RefFunc(DFSTRICMP)))) to iItem
                If (iItem <> -1) Begin
                    Repeat
                        Move asIntFileData[iItem] to asFileData[-1]
                        Increment iItem
                    Until (iItem >= SizeOfArray(asIntFileData) or asIntFileData[iItem] = "")
                    Move "" to asFileData[-1] 
                    Repeat
                        Readln channel iCh sDummy
                    Until (Trim(sDummy) = "")
                End
                Else Begin
                    Move sLine to asFileData[-1]
                End
            End
            Else Begin
                Move sLine to asFileData[-1]
            End
        Loop
        Close_Input channel iCh
        
        Move (SizeOfArray(asFileData)) to iSize
        If (iSize = 0) Begin
            Function_Return False
        End
        Decrement iSize
        
        Direct_Output channel iCh sIntFile
            For iCount from 0 to iSize
                Writeln channel iCh asFileData[iCount]
            Loop
        Close_Output channel iCh
        
        Send Seq_Release_Channel iCh
        Function_Return bOK
    End_Function
    
    // ToDo: Improve to also insert new lines with "FIELD_TYPE DATETIME"
    //       The logic currently will not set the FIELD_TYPE, unless the FIELD_NUMBER xx already exists in the .int file.
    Function CollectIntFileRelationAndIndexFields Handle hTable String sIntFile String sDriver Returns String[]
        Integer iCh iColumn iPos iType iDbType iDFType
        String sLine sFileRelTxt sFieldNoTxt sDataType sIndexNoTxt sPath sFileName sDummy
        String[] asIntFileData
        Boolean bFound bOpen
        
        Get Seq_New_Channel to iCh
        If (iCh < 0) Begin
            Function_Return asIntFileData
        End
        
        Open hTable
        Get_Attribute DF_FILE_OPENED of hTable to bOpen
        Move False to bFound
        Get ParseFolderName sIntFile to sPath
        If (sPath <> "") Begin
            Get vFolderExists sPath to bFound
        End
        If (bFound = False) Begin
            Get psDataPath of (phoWorkspace(ghoApplication)) to sPath
        End
        Get vFolderFormat sPath to sPath
        Get ParseFileName sIntFile to sFileName
        Move (sPath + sFileName) to sIntFile
        Get piDbType of ghoDUF to iDbType
        
        Direct_Input channel iCh sIntFile
        While (not(SeqEof))
            Readln channel iCh sLine
            If (Uppercase(sLine) contains "FIELD_NUMBER ") Begin
                Move sLine to sFieldNoTxt
                Get FieldNumberToDataTimeText hTable sFieldNoTxt sDriver iDbType to sDataType
                Move ""          to asIntFileData[-1]    
                Move sFieldNoTxt to asIntFileData[-1]    
                If (sDataType <> "") Begin
                    Move sDataType  to asIntFileData[-1]
                    Readln channel iCh sDummy    
                End
                Repeat
                    Readln channel iCh sLine
                    If (Trim(sLine) <> "" and not(Uppercase(sLine) contains "FIELD_NUMBER ")) Begin
                        Move sLine to asIntFileData[-1]
                    End
                Until (Trim(sLine) = "" or Uppercase(sLine) contains "FIELD_NUMBER ")
            End
        Loop
        
        Close hTable
        Close_Input channel iCh
        Send Seq_Release_Channel iCh
        Function_Return asIntFileData
    End_Function   
    
    // To get the DataFlex type from a SQL column DateTime(x) data type, as a text string
    // For usage in .int files.
    // Note: The hTable needs to be open before calling this function.
    Function FieldNumberToDataTimeText Handle hTable String sFieldNoTxt String sDriver Integer iDbType Returns String
        String sDataType
        Integer iPos iColumn iType iDFType
        
        Move (Pos(" ", sFieldNoTxt)) to iPos
        Move (Mid(sFieldNoTxt, Length(sFieldNoTxt), iPos)) to iColumn
        If (iColumn <= 0) Begin
            Function_Return "" 
        End

        Get_Attribute DF_FIELD_TYPE of hTable iColumn to iType
        Get UtilDataFlexDataTypeToString of ghoDUF iType to sDataType
        If (not(Uppercase(sDataType) contains "TIME")) Begin
            Move "" to sDataType
        End
        Else Begin
            Move (Replace("DF_", sDataType, "")) to sDataType
            Move ("FIELD_TYPE " + sDataType)     to sDataType
        End
        
        Function_Return sDataType
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

    Function BackupAllIntFiles String sBackupFolder Returns Integer
        Integer iSize iCount iRetval iCounter
        String sDataPath sFilter sFileDateExt
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
        Send StartStatusPanel "Backing up *.int files to backup folder:" sBackupFolder 1

        Move "int" to sFilter
        Get CollectFilteredFiles sDataPath sFilter to asFiles
        Get FileDatePrefix to sFileDateExt
        Get vFolderFormat sBackupFolder to sBackupFolder 
        Set piMaximum of ghoStatusPanel to (SizeOfArray(asFiles))
        Move (SizeOfArray(asFiles)) to iSize
        If (iSize = 0) Begin
            Function_Return 0
        End
        Move 0 to iCounter
        Decrement iSize
        For iCount from 0 to iSize
            Send Update_StatusPanel of ghoStatusPanel (sDataPath + asFiles[iCount]) 
            Get vCopyFile (sDataPath + asFiles[iCount]) (sBackupFolder + String(sFileDateExt) + String(asFiles[iCount])) to iRetval
            If (iRetval = 0) Begin
                Increment iCounter
            End
            Send DoAdvance of ghoStatusPanel
        Loop
        
        Function_Return iCounter
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
        Send Seq_Release_Channel iCh
        
        Function_Return asFiles
    End_Function
    
    Function SanitizeDatRelatedFiles String[] asFiles String[] asDatFilesInUse Returns String[]
        Integer iSize iCount iItem
        String sFileName sFileNameNoExt sExt sFileNameShort
        Boolean bOK
        
        // We add these files to the .dat files array as we don't want them to be moved:
        Move "flexerrs.dat" to asDatFilesInUse[-1]
        Move "dferr001.dat" to asDatFilesInUse[-1]
        Move "dferr002.dat" to asDatFilesInUse[-1]
        Move "dferr003.dat" to asDatFilesInUse[-1]
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
            
    Procedure OpenLogFile
        String sLogFile sTimeStamp sFilelist
        Integer iCh
        
        Get Value of oLogFile_fm to sLogFile
        Get piChannel to iCh
        If (iCh >= 0) Begin
            Send Seq_Close_Channel iCh
        End
        Get Seq_Append_Output_Channel sLogFile to iCh
        Set piChannel to iCh
        Get Value of oFilelist_fm to sFilelist
        Move (CurrentDateTime()) to sTimeStamp
        Writeln channel iCh "Log file Opened date/time: " (String(sTimeStamp))
    End_Procedure

    Procedure CloseLogFile
        String sLogFile sTimeStamp sFilelist
        Integer iCh

        Get Value of oLogFile_fm to sLogFile
        Get piChannel to iCh
        If (iCh >= 0) Begin
            Move (CurrentDateTime()) to sTimeStamp
            Writeln channel iCh "Log file closed date/time: " (String(sTimeStamp))
            Send Seq_Close_Channel iCh
        End
        Set piChannel to -1
    End_Procedure
                
    Procedure WriteAliasEntryError Boolean bIsIntFile Handle hTable String sRootNameAlias String sLogicalNameAlias String sRootNameMaster String sLogicalNameMaster
        Integer iCh
        
        Get piChannel to iCh
        If (iCh = -1) Begin
            Send OpenLogFile
            Get piChannel to iCh 
        End
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
    
    Procedure WriteToLogFile Boolean bIsAlias Handle hTable String sLogicalNameOrg String sRootNameOrg String sRootNameNew String sNoDriverRootname String sDisplayNameOrg String sDisplayNameNew
        Integer iCh

        Get piChannel to iCh
        If (iCh = -1) Begin
            Send OpenLogFile
            Get piChannel to iCh 
        End
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
        Writeln channel iCh  
        Send CloseLogFile            
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

    // Note: Tell the MSSQLDRV_ID driver to *not* create cache-files (.cch):
    Procedure Activating 
        Integer iDriver
        Get DriverIndex of ghoDUF MSSQLDRV_ID to iDriver
        If (iDriver <> 0) Begin
            Set_Attribute DF_DRIVER_USE_CACHE of iDriver to False 
        End
    End_Procedure 
    

    On_Key kClear Send KeyAction of oRefresh_btn
End_Object    
