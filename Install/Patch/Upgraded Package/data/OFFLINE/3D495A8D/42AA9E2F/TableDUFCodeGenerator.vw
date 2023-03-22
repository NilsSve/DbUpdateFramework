Use Windows.pkg
Use DFClient.pkg
Use Cursor.pkg
Use Batchdd.pkg
Use cCJGrid.pkg
Use cCJGridColumnRowIndicator.pkg
Use cCJGridColumn.pkg
Use dfLine.pkg
Use cButton.pkg
Use cDbUpdateFunctionLibrary.pkg
Use DUFStatusPanel.pkg
Use seq_chnl.pkg
Use vWin32fh.pkg
Use cHeaderGroup.pkg
Use cSuggestionIniForm.pkg
Use cSQLCheckBox.pkg

Enum_List
    Define cx_Select_All
    Define cx_Select_None
    Define cx_Select_Invert
End_Enum_List

Enum_List
    Define GenerateOK
    Define GenerateUserCancel
    Define GenerateError
    Define GenerateChannelError
    Define GenerateUserInputError
    Define GenerateOpenTableError
End_Enum_List

Struct tGeneratorRow
    Handle hTable
    String sLogicalName
    String sRootName
    String sDisplayName
    Boolean bIsAlias
    Boolean bSelected
End_Struct

Activate_View Activate_oTableDUFCodeGenerator for oTableDUFCodeGenerator
Object oTableDUFCodeGenerator is a dbView
    Set Size to 311 492
    Set Location to 0 1
    Set Label to "Code Generator"
    Set Icon to "SqlScriptBlack2.ico"
    Set Border_Style to Border_Thick
    Set Color to clWhite
    Set pbAcceptDropFiles to True
    Set pbAutoActivate to True
    Set phoTableDUFCodeGenerator_vw of ghoApplication to Self

    Property String psOrgOpenPath
    Property Handle phtable
    Property String psTableName

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
    Send StartUp

    Object oFromFilelist_grp is a cHeaderGroup
        Set Size to 43 462
        Set Location to 8 19
        Set pbAcceptDropFiles to True
        Set psImage to "ActionOpenBlack.ico"
        Set psLabel to "Select Filelist.cfg"

        // Work around; we need to get the container_handle of the parent, else drag & drop doesn't work.
//        Function Container_Handle Returns Integer
//            Integer rVal
//            Delegate Get Container_Handle to rVal
//            Delegate Get Window_Handle to rVal
//            Function_Return rVal
//        End_Function

        Object oFilelistPath_fm is a cSuggestionIniForm
            Set Size to 13 413
            Set Location to 21 25
            Set Label_Col_Offset to 0
            Set Label_Row_Offset to 1
            Set Label_Justification_Mode to JMode_Top
            Set Prompt_Button_Mode to PB_PromptOn
            Set peAnchors to anTopLeftRight
            Set psToolTip to "Select the FROM database Filelist.cfg. This should be the development workspace Data folder's Filelist.cfg"
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
                String sFileList
                Boolean bOK bExists bCfgFile bHasRecords
                Handle hTable
                Number nVersionNumber

                Get Value to sFileList
                Get vFilePathExists sFileList to bExists
                Move (Lowercase(sFileList) contains ".cfg") to bCfgFile
                If (bExists = True and bCfgFile) Begin
                    // A little trick to show the filelist.cfg in the form before we start filling the grid.
                    Send PumpMsgQueue of Desktop
                    Get ChangeFilelistPathing of ghoApplication sFileList to bOK

                    If (bOK = True) Begin
                        Set psFilelistFrom of ghoApplication to sFileList

                        // *** LOAD DATA ***
                        Send LoadData to oFilelist_grd

                        // It just seem logical to activate the grid after populating it.
                        // At this point there is little use of still having the oFilelist_fm active.
                        Get HasRecords of oFilelist_grd to bHasRecords
                        If (bHasRecords = True) Begin
                            Send Activate of oFilelist_grd
                        End

                        If (bExists = True) Begin
                            Get phDbVersion of oFilelist_grd to hTable
                            If (hTable <> 0) Begin
                                Open hTable
                                Get_Field_Value hTable 1 to nVersionNumber
                                Close hTable
                            End
                        End
                        Else Begin
                            // Send Info_Box ("This workspace has not been setup to use the DUF DbVersion table and thus the current database version can't be retrieved.\nYou need to manually set the 'Next pnVersionNumber' entry window below to an apropriate number before pressing the 'Generate Code' button.")
                            Move 1 to nVersionNumber
                        End
                        Move (nVersionNumber + .1) to nVersionNumber
                        Set Value of oPnVersionNumber_fm to nVersionNumber
                    End
                End
            End_Procedure

            Function Window_Handle Returns Handle
                Integer rVal
                Get Window_Handle of (Parent(Self)) to rVal
                Function_Return rVal
            End_Function

            Function Next_Object_Id Boolean bNoDescend Returns Integer
                Function_Return (oFilelist_grd(Self))
            End_Function

            On_Key Key_Ctrl+Key_W Send None
            On_Key Key_Ctrl+Key_Q Send None
        End_Object

    End_Object

    Object oSelectTables_grp is a cHeaderGroup
        Set Size to 102 462
        Set Location to 60 19
        Set peAnchors to anAll
        Set psImage to "SelectTablesBlack.ico"
        Set psLabel to "Select Tables"

        Object oFilelist_grd is a cCJGrid
            Set Size to 72 412
            Set Location to 21 25
            Set pbUseAlternateRowBackgroundColor to True
            Set psNoItemsText to "No Filelist.cfg selected yet..."
            Set pbRestoreLayout to True
            Set psLayoutSection to (Name(Self) + "_grid")
            Set pbHeaderReorders to True
            Set pbHeaderPrompts to False
            Set pbHeaderTogglesDirection to True
            Set pbSelectionEnable to True
            Set pbAllowInsertRow to False
            Set pbAllowAppendRow to False
            Set pbShowRowFocus to True
            Set pbShowFooter to True
            Set pbAllowDeleteRow to False
            Set pbMultipleSelection to True
            Set pbHotTracking to True
            Set pbEditOnClick to True
            Set peAnchors to anAll
            Set piLayoutBuild to 3
            Set Status_Help to "Select with the spacebar, or use the selection buttons above the grid"
            #IF (Required_RT_Version > 18)
            Set peVisualTheme to xtpReportThemeVisualStudio2012Light
            #ENDIF

            Property Handle phDbVersion
            Property Integer piCurrentRow -1

            Object oCJGridColumnRowIndicator is a cCJGridColumnRowIndicator
                Set piWidth to 26
            End_Object

            Object oFilelistNumber_col is a cCJGridColumn
                Set piWidth to 73
                Set psCaption to "Filelist No"
                Set psToolTip to (psCaption(Self) * "(Read-Only)")
                Set peDataType to Mask_Numeric_Window
                Set pbEditable to False
            End_Object

            Object oLogicalName_col is a cCJGridColumn
                Set piWidth to 119
                Set psCaption to "Logical Name"
                Set psToolTip to (psCaption(Self) * "(Read-Only)")
                Set pbEditable to False
            End_Object

            Object oRootName_col is a cCJGridColumn
                Set piWidth to 187
                Set psCaption to "Table Name (Rootname)"
                Set psToolTip to (psCaption(Self) * "(Read-Only)")
                Set pbEditable to False
            End_Object

            Object oDisplayName_col is a cCJGridColumn
                Set piWidth to 260
                Set psCaption to "Display Name"
                Set psToolTip to (psCaption(Self) * "(Read-Only)")
                Set psFooterText to "No of Tables:"
                Set pbEditable to False
            End_Object

            Object oIsAlias_Col is a cCJGridColumn
                Set piWidth to 83
                Set psCaption to "Is Alias"
                Set pbCheckbox to True
                Set peHeaderAlignment to xtpAlignmentCenter
                Set peFooterAlignment to xtpAlignmentCenter
                Set psFooterText to "Count:"
                Set pbVDFEditControl to False
                Set psToolTip to "Is table an alias table? (Read-Only)"
                // Set pbEditable to False
            End_Object

            // We want oIsAlias_Col to not be editable. But setting
            // pbEditable = False makes it very hard to read.
            // So we disable it here instead.
            Function CanEditColumn Integer iCol Returns Boolean
                Handle hoIsAlias_Col
                Boolean bRetval

                Forward Get CanEditColumn iCol to bRetval
                Get piColumnId of oIsAlias_Col to hoIsAlias_Col
                If (iCol = hoIsAlias_Col) Begin
                    Function_Return False
                End

                Function_Return bRetval
            End_Function

            Object oCheckbox_Col is a cCJGridColumn
                Set piWidth to 79
                Set psCaption to "Select"
                Set psToolTip to "Select with the spacebar, or use the selection buttons above the grid"
                Set pbCheckbox to True
                Set peHeaderAlignment to xtpAlignmentCenter
                Set peFooterAlignment to xtpAlignmentCenter
                Set psFooterText to "Selected:"
                Set peDataType to Mask_Numeric_Window
            End_Object

            Procedure LoadData
                String sFileList sLogicalName
                Handle hoDataSource hTable
                tDataSourceRow[] TheData TheDataEmpty
                Integer iRow iTableNo iRoot iLogical iDisplay iIsAlias iChecked iAliasCount iNoOfTables iCount
                Boolean bExists bIsAlias bUserCancel

                Get_Attribute DF_FILELIST_NAME to sFilelist
                Get vFilePathExists sFileList to bExists
                If (bExists = False) Begin
                    Procedure_Return
                End

                Send Initialize_StatusPanel of ghoStatusPanel "The Database Update Framework" "Loading Filelist.cfg data" "...and checking for Alias tables"
                Send Start_StatusPanel of ghoStatusPanel
                Get UtilFilelistNoOfTables of ghoDbUpdateFunctionLibrary to iNoOfTables
                Set pbVisible of ghoProgressBar to True
                Set pbVisible of ghoProgressBarOverall to False
                Set piMaximum of ghoProgressBar to iNoOfTables
                Move 0 to iCount
                Get phoDataSource to hoDataSource
                Get DataSource of hoDataSource to TheData
                Move TheDataEmpty to TheData
                Get piColumnId of oFilelistNumber_col to iTableNo
                Get piColumnId of oRootName_col       to iRoot
                Get piColumnid of oLogicalName_col    to iLogical
                Get piColumnId of oDisplayName_col    to iDisplay
                Get piColumnId of oIsAlias_Col        to iIsAlias
                Get piColumnId of oCheckbox_Col       to iChecked

                Move 0 to hTable
                Move 0 to iRow
                Repeat
                    Get_Attribute DF_FILE_NEXT_USED of hTable to hTable
                    Set piPosition of ghoProgressBar to iCount

                    If (hTable > 0 and hTable <> 50) Begin
                        Move hTable                                   to TheData[iRow].sValue[iTableNo]
                        Get_Attribute DF_FILE_ROOT_NAME     of hTable to TheData[iRow].sValue[iRoot]
                        Get_Attribute DF_FILE_LOGICAL_NAME  of hTable to sLogicalName
                        Move sLogicalName                             to TheData[iRow].sValue[iLogical]
                        If (Uppercase(sLogicalName) = "DBVERSION") Begin
                            Set phDbVersion to hTable
                        End
                        Get_Attribute DF_FILE_DISPLAY_NAME  of hTable to TheData[iRow].sValue[iDisplay]
                        Get UtilTableIsAlias of ghoDbUpdateFunctionLibrary hTable to bIsAlias
                        Move bIsAlias                                 to TheData[iRow].sValue[iIsAlias]
                        If (bIsAlias = True) Begin
                            Increment iAliasCount
                        End
                        Move False to TheData[iRow].sValue[iChecked]
                        Increment iRow
                    End
                    Increment iCount
                    Get Check_StatusPanel of ghoStatusPanel to bUserCancel
                    If (bUserCancel = True) Begin
                        Move TheDataEmpty to TheData
                        Move 0 to iRow
                        Move 0 to iAliasCount
                        Move 0 to hTable
                    End
                Until (hTable = 0)

                If (iRow <> 0) Begin
                    Send ReInitializeData TheData False
                    Send MoveToFirstRow
                End
                Else Begin
                    Send InitializeData TheDataEmpty
                End
                Set psFooterText of oDisplayName_col to ("No of Tables:" * String(iRow))
                Set psFooterText of oIsAlias_Col     to ("Count:" * String(iAliasCount))
                Send Stop_StatusPanel of ghoStatusPanel
            End_Procedure

            Function SelectedTableNumber Returns Handle
                Integer hTable iTableNo iRowNo
                Handle hoDataSource
                tDataSourceRow[] TheData

                Get phoDataSource to hoDataSource
                Get piColumnId of oFilelistNumber_col to iTableNo
                Get DataSource of hoDataSource to TheData
                Get SelectedRow of hoDataSource to iRowNo
                Move TheData[iRowNo].sValue[iTableNo] to hTable

                Function_Return hTable
            End_Function

            Function GenerateSourceFileName Returns String
                String sRetval sPath sFileListName sTableName sVersionNumber
                Boolean bExists
                Integer iLogical iRowNo iSelected iPos
                tDataSourceRow[] TheData
                Handle hoDataSource
                Number nVersionNumber

                Get Value of oFilelistPath_fm to sFileListName
                Get vFilePathExists sFileListName to bExists
                If (bExists = False) Begin
                    Function_Return ""
                End

                Get Value of oPnVersionNumber_fm to nVersionNumber
                Move nVersionNumber to sVersionNumber
                Move (Pos(".", sVersionNumber)) to iPos
                If (iPos = 0) Begin
                    Move (sVersionNumber + String(".0")) to sVersionNumber
                End
                Move (Replaces(".", sVersionNumber, "_")) to sVersionNumber

                Get ParseFolderName sFileListName to sPath
                Get vParentPath sPath   to sPath
                Get vFolderFormat sPath to sPath
                Move (sPath + "AppSrc") to sPath
                Get vFolderFormat sPath to sPath

                Get phoDataSource to hoDataSource
                Get piColumnid of oLogicalName_col to iLogical
                Get DataSource of hoDataSource to TheData
                Get CheckedItems to iSelected
                If (iSelected > 1) Begin
                    Move "MultipleTables" to sTableName
                End
                Else Begin
                    If (SizeOfArray(TheData) <> 0) Begin
                        Get SelectedRow of hoDataSource to iRowNo
                        Move TheData[iRowNo].sValue[iLogical] to sTableName
                    End
                End
                Move ("DUF_" + sTableName + String(sVersionNumber) + ".pkg") to sTableName

                Move (sPath + sTableName) to sRetval

                Function_Return sRetval
            End_Function

            Function piCheckboxCol Returns Integer
                Integer iIndex
                Get piColumnId of oCheckbox_Col to iIndex
                Function_Return iIndex
            End_Function

            // Returns the checked state for the checkbox column
            // and the passed row number.
            Function FindCheckedState Integer iRow Returns Boolean
                Integer iCol
                Handle hoDataSource
                tDataSourceRow[] TheData
                Boolean bChecked

                Get piCheckboxCol to iCol
                If (iCol < 0) Begin
                    Send UserError "No piCheckboxCol has been set. Cannot return value"
                    Procedure_Return
                End
                Get phoDataSource               to hoDataSource
                Get DataSource of hoDataSource  to TheData
                Move TheData[iRow].sValue[iCol] to bChecked

                Function_Return bChecked
            End_Function

            Procedure DoSetCheckboxFooterText
                Integer iCol iSelected
                Handle hoCol
                Get piCheckboxCol to iCol
                Get ColumnObject iCol to hoCol
                Get CheckedItems to iSelected
                Set psFooterText of hoCol to ("Selected:" * String(iSelected))
            End_Procedure

            { EnumList="cx_Select_All, cx_Select_None, cx_Select_Invert" }
            // Set checkboxes of the first column as selected.
            // iState can be one of the following:
            // cx_Select_All, cx_Select_None or cx_Select_Invert
            Procedure Set SelectItems Integer iState
                Integer i iItems
                Integer iCheckbox_Col
                Boolean bChecked
                Handle hoDataSource
                tDataSourceRow[] TheData
                String[] sFilesArray
                String sSourceFile

                Get piColumnId of oCheckbox_Col to iCheckbox_Col
                Get phoDataSource                to hoDataSource
                Get DataSource of hoDataSource   to TheData
                Move (SizeOfArray(TheData))      to iItems
                Decrement iItems
                For i from 0 to iItems
                    Case Begin
                        Case (iState = cx_Select_All)
                            Move True to TheData[i].sValue[iCheckbox_Col]
                            Break
                        Case (iState = cx_Select_None)
                            Move False to TheData[i].sValue[iCheckbox_Col]
                            Break
                        Case (iState = cx_Select_Invert)
                            Move TheData[i].sValue[iCheckbox_Col] to bChecked
                            Move (not(bChecked)) to  TheData[i].sValue[iCheckbox_Col]
                            Break
                    Case End
                Loop

                Send ReInitializeData TheData False
                Send DoSetCheckboxFooterText
                Get GenerateSourceFileName  to sSourceFile
                Set Value of oSourceName_fm to sSourceFile
            End_Procedure

            // Selects all items
            Procedure SelectAll
                Set SelectItems to cx_Select_All
            End_Procedure

            // Deselects all items
            Procedure SelectNone
                Set SelectItems to cx_Select_None
            End_Procedure

            // Inverts the current selections
            Procedure SelectInvert
                Set SelectItems to cx_Select_Invert
            End_Procedure

            // Returns a string array with the selected items.
            Function SelectedItems Returns tGeneratorRow[]
                Integer[] SelRows
                Integer i iItems iSize iCheckbox_Col iFilelistNo_Col iLogical_Col iRoot_Col iDisplay_Col iIsAlias_Col
                String sFileName
                String[] sFilesArray
                Handle hoDataSource
                tDataSourceRow[] TheData
                Boolean bChecked bIsAlias
                tGeneratorRow[] GeneratorRowArray

                Get piColumnId of oFilelistNumber_col to iFilelistNo_Col
                Get piColumnId of oLogicalName_col    to iLogical_Col
                Get piColumnId of oRootName_col       to iRoot_Col
                Get piColumnId of oDisplayName_col    to iDisplay_Col
                Get piColumnId of oIsAlias_Col        to iIsAlias_Col
                Get piColumnId of oCheckbox_Col       to iCheckbox_Col

                Get phoDataSource to hoDataSource
                Get DataSource of hoDataSource to TheData
                Move (SizeOfArray(TheData)) to iItems
                Decrement iItems

                For i from 0 to iItems
                    Move TheData[i].sValue[iCheckbox_Col] to bChecked
                    If (bChecked = True) Begin
                        Move (SizeOfArray(GeneratorRowArray)) to iSize
                        Move TheData[i].sValue[iFilelistNo_Col] to GeneratorRowArray[iSize].hTable
                        Move TheData[i].sValue[iLogical_Col]    to GeneratorRowArray[iSize].sLogicalName
                        Move TheData[i].sValue[iRoot_Col]       to GeneratorRowArray[iSize].sRootName
                        Move TheData[i].sValue[iDisplay_Col]    to GeneratorRowArray[iSize].sDisplayName
                        Move TheData[i].sValue[iIsAlias_Col]    to GeneratorRowArray[iSize].bIsAlias
                        Move TheData[i].sValue[iCheckbox_Col]   to GeneratorRowArray[iSize].bSelected
                        Move sFileName to sFilesArray[iSize]
                    End
                Loop

                Function_Return GeneratorRowArray
            End_Function

            // Returns the number of items that has been selected.
            // It is a bit confusing with the SelectedItems function above,
            // but it is how it was designed from the beginning. The
            // SelectedItems function returns an array of all selected files,
            // while this function returns the number of selected items only.
            // The purpose is to use it in e.g. a checkbox grid column object
            // to show the current no of selected items.
            Function CheckedItems Returns Integer
                Integer iCount iItems iCheckbox_Col iRetval
                Handle hoDataSource
                tDataSourceRow[] TheData
                Boolean bChecked

                Get piCheckboxCol to iCheckbox_Col
                Get phoDataSource to hoDataSource
                Get DataSource of hoDataSource to TheData
                Move (SizeOfArray(TheData)) to iItems
                Decrement iItems

                For iCount from 0 to iItems
                    Move TheData[iCount].sValue[iCheckbox_Col] to bChecked
                    If (bChecked = True) Begin
                        Increment iRetval
                    End
                Loop

                Function_Return iRetval
            End_Function

            // Toggles the current row on/off (the checkbox)
            Procedure ToggleCurrentItem
                Boolean bChecked
                Integer iCol
                Handle hoCol
                String sSourceFile

                Get piCheckboxCol       to iCol
                Get ColumnObject iCol   to hoCol
                Get SelectedRowValue    of hoCol to bChecked
                Send UpdateCurrentValue of hoCol (not(bChecked))
                Send Request_Save
                Get GenerateSourceFileName  to sSourceFile
                Set Value of oSourceName_fm to sSourceFile
                Send DoSetCheckboxFooterText
            End_Procedure

            Procedure Request_Clear
                Delegate Send Request_Clear
            End_Procedure

            Procedure OnComMouseUp Short llButton Short llShift Integer llx Integer lly
                Forward Send OnComMouseUp llButton llShift llx lly
                Send Request_Save
                Send DoSetCheckboxFooterText
            End_Procedure

            Procedure OnRowChanged Integer iOldRow Integer iNewSelectedRow
                String sSourceFile
                Handle hTable

                Forward Send OnRowChanged iOldRow iNewSelectedRow

                Get SelectedTableNumber to hTable
                Get GenerateSourceFileName  to sSourceFile
                Set Value of oSourceName_fm to sSourceFile
                Set piCurrentRow to iNewSelectedRow
            End_Procedure

            Procedure MoveToNextGroup
                Send Activate of oSelectAll_btn
            End_Procedure

            Procedure MoveToPreviousGroup
                Send Activate of oFilelistPath_fm
            End_Procedure

            Function HasRecords Returns Boolean
                Handle hoDataSource
                tDataSourceRow[] TheData
                Integer iItems

                Get phoDataSource to hoDataSource
                Get DataSource of hoDataSource to TheData
                Move (SizeOfArray(TheData)) to iItems
                Function_Return (iItems <> 0)
            End_Function

            On_Key Key_Space         Send ToggleCurrentItem
            On_Key Key_Tab           Send MoveToNextGroup
            On_Key Key_Shift+Key_Tab Send MoveToPreviousGroup
        End_Object

        Object oSelectAll_btn is a cButtonDPI
            Set Size to 14 45
            Set Location to 4 294
            Set Label to "&All"
            Set MultiLineState to True
            Set peAnchors to anTopRight
            Set psImage to "SelectAllBlack.ico"
            Set psToolTip to "Select all"

            Procedure OnClick
                Set SelectItems of oFilelist_grd to cx_Select_All
            End_Procedure

        End_Object

        Object oDeSelectAll_btn is a cButtonDPI
            Set Size to 14 45
            Set Location to 4 343
            Set Label to "&None"
            Set peAnchors to anTopRight
            Set psImage to "SelectNoneBlack.ico"
            Set psToolTip to "Select none"

            Procedure OnClick
                Set SelectItems of oFilelist_grd to cx_Select_None
            End_Procedure

        End_Object

        Object oInvertSelection_btn is a cButtonDPI
            Set Size to 14 45
            Set Location to 4 392
            Set Label to "&Invert"
            Set peAnchors to anTopRight
            Set psImage to "SelectInvertBlack.ico"
            Set psToolTip to "Invert selection"
            Procedure OnClick
                Set SelectItems of oFilelist_grd to cx_Select_Invert
            End_Procedure
        End_Object

        // Needed to not close the view when Esc is hit in the grid.
        On_Key kCancel Send None
    End_Object

    Object oConfigureGeneration_grp is a cHeaderGroup
        Set Size to 52 462
        Set Location to 172 19
        Set peAnchors to anBottomLeftRight
        Set psImage to "SettingsBlack.ico"
        Set psLabel to "Configure Code Generation"

        Object oUseConnectionID_cb is a cSQLCheckBox
            Set Auto_Size_State to False
            Set Size to 9 78
            Set Location to 23 26
            Set Label to "Use Connection ID"
            Set Checked_State to True
            Set psToolTip to "If True (the default); uses the Connection ID of the connection string as defined by the SQLConnection.ini setting"
        End_Object

        Object oANSI_cb is a cSQLCheckBox
            Set Auto_Size_State to False
            Set Size to 9 73
            Set Location to 23 131
            Set Label to "ANSI/OEM"
            Set Checked_State to True
            Set psToolTip to "DataFlex data is stored in OEM format. Non-DataFlex back ends may expect the data to be stored in ANSI format. When defining the conversion options you can define the table character format to be used in the converted table."
        End_Object

        Object oRecnum_cb is a cSQLCheckBox
            Set Auto_Size_State to False
            Set Size to 9 75
            Set Location to 23 219
            Set Label to "Use Recnum"
            Set Checked_State to True
            Set psToolTip to "If the program that is using the source database uses the recnum programming style, the tables should be converted to recnum tables. If the program uses the RowId programming style, converting to standard tables is recommended."
        End_Object

        Object oApiTableUpdateAuto_cb is a cSQLCheckBox
            Set Auto_Size_State to False
            Set Size to 9 93
            Set Location to 23 321
            Set Label to "Auto Update Table"
            Set Checked_State to True
            Set psToolTip to "When set to True, 'TO' tables will get converted to the same database format as the 'FROM' tables. So if a 'FROM' table is an SQL table and the 'TO' table is in the embedded format (DataFlex table), it will be converted to SQL."
        End_Object

        Object oCompareDate_DataTime_cb is a cSQLCheckBox
            Set Auto_Size_State to False
            Set Size to 9 101
            Set Location to 36 26
            Set Label to "Compare Date/DataTime"
            Set Checked_State to False
            Set psToolTip to "Check Date to DateTime column differences"
        End_Object

        Object oCompareIndexAscending_cb is a cSQLCheckBox
            Set Auto_Size_State to False
            Set Size to 9 84
            Set Location to 36 131
            Set Label to "Compare Ascending"
            Set Checked_State to False
            Set psToolTip to "Compare if Index is Ascending/Descending. (In SQL this setting is set for the whole database by selecting a 'Collation', so then checking this per table doesn't make sense)"
        End_Object

        Object oCompareIndexUppercase_cb is a cSQLCheckBox
            Set Auto_Size_State to False
            Set Size to 9 98
            Set Location to 36 219
            Set Label to "Compare Uppercase"
            Set Checked_State to False
            Set psToolTip to "Compare if Index is Uppercase/Lowercase. (In SQL this setting is set for the whole database by selecting a 'Collation', so then checking this per table doesn't make sense)"
        End_Object

        Object oIgnoreFilelistUppercase_cb is a cSQLCheckBox
            Set Auto_Size_State to False
            Set Size to 9 135
            Set Location to 36 321
            Set Label to "Uppercase/Lowercase Table Names"
            Set Checked_State to True
            Set psToolTip to "Check Filelist.cfg RootName, LogicalName and DisplayName uppercase/lowercase differences"
        End_Object

        Procedure ToggleCurrentItem
            Boolean bChecked
            Handle hObject

            Get Focus to hObject
            Get Checked_State of hObject to bChecked
            Set Checked_State of hObject to (not(bChecked))
        End_Procedure

    End_Object

    Object oGenerateFilename_grp is a cHeaderGroup
        Set Size to 43 462
        Set Location to 234 19
        Set peAnchors to anBottomLeftRight
        Set psImage to "ActionSaveBlack.ico"
        Set psLabel to "Configure Generated File Name"

        Object oPnVersionNumber_fm is a Form
            Set Size to 13 22
            Set Location to 21 108
            Set Label to "Next pnVersionNumber"
            Set psToolTip to "This value is the current DbVersion.DatabaseVersion value, with a value of 0.1 added to it."
            Set Status_Help to "The current DbVersion.DatabaseVersion value, with a value of 0.1 added to it."
            Set Value to 0
            Set peAnchors to anBottomLeft
            Set Label_Justification_Mode to JMode_Right
            Set Label_Col_Offset to 2
            Set Form_Datatype to Mask_Numeric_Window
            Set Numeric_Mask 0 to 4 1

            Procedure OnChange
                String sSourceFile
                Get GenerateSourceFileName of oFilelist_grd  to sSourceFile
                Set Value of oSourceName_fm to sSourceFile
            End_Procedure

        End_Object

        Object oSourceName_fm is a Form
            Set Size to 13 304
            Set Location to 21 134
            Set peAnchors to anBottomLeftRight
            Set Label_Col_Offset to 0
            Set Label_Justification_Mode to JMode_Top
            Set Label_Row_Offset to 1
            Set psToolTip to "The name of the output file to be generated."
            Set Status_Help to "The name of the output file to be generated."
        End_Object

    End_Object

    Object oBusinessProcess is a BusinessProcess
        Set Status_Panel_Id to ghoStatusPanel
        Set Allow_Cancel_State to True
        Set Process_Caption to "The Database Update Framework"
        Set Process_Title to "Generating Database Update Code..."
        Set Process_Message to "For table:"

        Procedure OnProcess
            Send StartGenerateCode
        End_Procedure

        Procedure Ignore_Error Integer iError
        End_Procedure
        Procedure Trap_Error Integer iError
        End_Procedure

    End_Object

    Object oGenerateCode_btn is a cButtonDPI
        Set Size to 23 58
        Set Location to 284 348
        Set Label to "&Generate Code!"
        Set FontWeight to fw_Bold
        Set peAnchors to anBottomRight
        Set psToolTip to "Start generating Database Update Framework code for the selected table(s)."
        Set Default_State to True
        Set MultiLineState to True
        Set psImage to "SqlScriptBlack2.ico"

        Procedure OnClick
            Boolean bExists
            String sSourceFile
            Integer iSelected iRetval

            Get Value of oSourceName_fm to sSourceFile
            Get vFilePathExists sSourceFile to bExists
            If (bExists = True) Begin
                Get YesNo_Box ("Oops, the source file" * sSourceFile * "already exists!\n\nDo you want to overwrite it?") to iRetval
                If (iRetval <> MBR_Yes) Begin
                    Procedure_Return
                End
            End

            Get CheckedItems  of oFilelist_grd to iSelected
            If (iSelected = 0) Begin
                Send Info_Box "No tables selected. Please adjust and try again."
                Procedure_Return
            End

            Send DoProcess of oBusinessProcess
            Send Restore_DF_OPEN_PATH of ghoApplication
        End_Procedure

        Procedure DoEnable
            String sSourceName
            Integer iSelected

            Get Value of oSourceName_fm to sSourceName
            If (sSourceName = "") Begin
                Set Enabled_State to False
                Procedure_Return
            End

            Get CheckedItems  of oFilelist_grd to iSelected
            Set Enabled_State to (iSelected <> 0)
        End_Procedure

    End_Object

    Object oOpenAppSrcFolder_btn is a cButtonDPI
        Set Size to 23 65
        Set Location to 284 418
        Set Label to "&Open Location"
        Set peAnchors to anBottomRight
        Set psToolTip to "Open the source location in Windows Explorer"
        Set MultiLineState to True
        Set psImage to "ActionOpenBlack.ico"

        Procedure OnClick
            String sPath sSourceName
            Get Value of oSourceName_fm to sSourceName
            Get ParseFolderName sSourceName to sPath
            Runprogram Shell Background "Explorer.exe" sPath
        End_Procedure

        Procedure DoEnable
            String sPath sSourceName
            Boolean bExists

            Get Value of oSourceName_fm to sSourceName
            Get ParseFolderName sSourceName to sPath
            Get vFolderExists sPath to bExists
            Set Enabled_State to (bExists = True)
        End_Procedure

    End_Object

    Procedure StartGenerateCode
        String sSourceFile
        Boolean bUseConnectionID bANSI bRecnum bCompareIndexUppercase bCompareIndexAscending
        Handle hTable
        Integer iErrors
        Number nVersionNumber
        tGeneratorRow[] TheData
        tAPITableBooleans CompareTableBooleans

        Get Value of oSourceName_fm                      to sSourceFile
        Get Checked_State of oUseConnectionID_cb         to bUseConnectionID
        Get Checked_State of oANSI_cb                    to bANSI
        Get Checked_State of oRecnum_cb                  to bRecnum
        Get Checked_State of oApiTableUpdateAuto_cb      to CompareTableBooleans.bApiTableUpdateAuto
        Get Checked_State of oCompareDate_DataTime_cb    to CompareTableBooleans.bCompareDate_DateTime
        Get Checked_State of oCompareIndexAscending_cb   to CompareTableBooleans.bCompareIndexAscending
        Get Checked_State of oCompareIndexUppercase_cb   to CompareTableBooleans.bCompareIndexUppercase
        Get Checked_State of oIgnoreFilelistUppercase_cb to CompareTableBooleans.bCompareFilelistUppercase

        Get SelectedItems of oFilelist_grd to TheData
        Get Value of oPnVersionNumber_fm to nVersionNumber
        Get GenerateDUFSourceCode sSourceFile TheData nVersionNumber bUseConnectionID bANSI bRecnum CompareTableBooleans to iErrors

        If (iErrors = GenerateChannelError) Begin
            Send Info_Box "Sorry, couldn't retrieve a free channel number. Process halted."
        End
        If (iErrors = GenerateUserInputError) Begin
            Send Info_Box "Table number and pnVersionNumber both needs to be > 0. Please adjust and try again."
        End

        Send Stop_StatusPanel of ghoStatusPanel
        If (iErrors = GenerateOK) Begin
            Send Info_Box "Ready!"
        End
        If (iErrors = GenerateError) Begin
            Send Info_Box ("Ready! But the code contains ERRORS because there were fields with length = 0! Search the generated code for the word 'ERROR!' to see those fields.")
        End
        If (iErrors = GenerateOpenTableError) Begin
            Send Info_Box ("Sorry, couldn't open the table! (Table No:" * String(phTable(Self)) * String(psFileName(Self)) + ") Process halted.")
        End
        If (iErrors = GenerateUserCancel) Begin
            Send Info_Box "Process cancelled by user."
        End
    End_Procedure

    Function GenerateDUFSourceCode String sSourceFile tGeneratorRow[] TheData Number nVersionNumber Boolean bUseConnectionID Boolean bANSI Boolean bRecnum tAPITableBooleans CompareTableBooleans Returns Integer
        Boolean bApiTableUpdateAuto bCompare_DateTime bCompareIndexAscending bCompareIndexUppercase bCompareFilelistUppercase
        Integer iCh iColumn iLength iPrecision iOptions iCount iSize iTable iTables
        Integer iIndex iIndexes iSegment iNumSegments iType iErrors iStatus
        Boolean bOpened bOK bDawSqlDriver bIsAlias bSqlDriver bSkipTable
        String sRootName sLogicalName sDisplayName sTableName sFieldName sDataType sDriverID
        Handle hTable
        tAPITableNameInfo  APITableNameInfo
        tAPIColumn[]   APIColumns
        tAPIRelation[] APIRelations
        tAPIIndex[]    APIIndexes
        DateTime dtCreationTime

        Move (CurrentDateTime()) to dtCreationTime
        Move 0 to iErrors
        Move (SizeOfArray(TheData)) to iTables
        Decrement iTables
        Move 0 to iTable
        Move TheData[iTable].hTable to hTable

        Get Seq_Open_Output_Channel sSourceFile to iCh
        If (iCh = DF_SEQ_CHANNEL_ERROR) Begin
            Function_Return GenerateChannelError
        End

        If (hTable < 1 or nVersionNumber <= 0) Begin
            Function_Return GenerateUserInputError
        End

        Send Initialize_StatusPanel of ghoStatusPanel "The Database Update Framework" "Generating Update Code" ""
        Send Start_StatusPanel of ghoStatusPanel
        Set pbVisible of ghoProgressBar to True
        Set pbVisible of ghoProgressBarOverall to True
        Set piMaximum of ghoProgressBarOverall to iTables
        
        Move CompareTableBooleans.bApiTableUpdateAuto       to bApiTableUpdateAuto
        Move CompareTableBooleans.bCompareDate_DateTime     to bCompare_DateTime
        Move CompareTableBooleans.bCompareFilelistUppercase to bCompareFilelistUppercase
        Move CompareTableBooleans.bCompareIndexAscending    to bCompareIndexAscending
        Move CompareTableBooleans.bCompareIndexUppercase    to bCompareIndexUppercase

        Get UtilTableOpen of ghoDbUpdateFunctionLibrary hTable "" DF_SHARE to bOpened
        Get_Attribute DF_FILE_OPENED of hTable to bOpened
        If (bOpened = False) Begin
            Send Seq_Close_Channel iCh
            Set phTable to hTable
            Set psFileName to TheData[iTable].sLogicalName
            Function_Return GenerateOpenTableError
        End

        Writeln channel iCh "/" "/ " CS_DatabaseUpdateFramework
        Writeln channel iCh ("/" + "/ Created by: 'DUF Update Code Generator'. Created:" * String(dtCreationTime))
        Writeln channel iCh ("Use cDbUpdateVersion.pkg")
        Writeln channel iCh
        Writeln channel iCh ("Object oDbUdpateVersion" + String(nVersionNumber) * "is a cDbUpdateVersion")
        Writeln channel iCh ("    Set pnVersionNumber to" * String(nVersionNumber))
        Writeln channel iCh ("    Procedure OnUpdate")
        Writeln channel iCh ("        Boolean bOK")
        Writeln channel iCh ("        tAPITableNameInfo APITableNameInfo")
        Writeln channel iCh ("        tAPIColumn[]   APIColumns APIColumnEmpty")
        Writeln channel iCh ("        tAPIIndex[]    APIIndexes APIIndexEmpty")
        Writeln channel iCh ("        tAPIRelation[] APIRelations APIRelationEmpty")
        Writeln channel iCh ("        Integer iCount iSegment")
        Writeln channel iCh ("        Handle hTable")
        Writeln channel iCh
        Writeln channel iCh ("        Set pbUseConnectionID       to" * If(bUseConnectionID, "True", "False"))
        Writeln channel iCh ("        Set pbToAnsi                to" * If(bANSI, "True", "False"))
        Writeln channel iCh ("        Set pbRecnum                to" * If(bRecnum, "True", "False"))
        Writeln channel iCh ("        Set pbApiTableUpdateAuto    to" * If(bApiTableUpdateAuto, "True", "False"))
        Writeln channel iCh ("        Set pbCompareDate_DateTime  to" * If(bCompare_DateTime, "True", "False"))
        Writeln channel iCh ("        Set pbCompareIndexAscending to" * If(bCompareIndexAscending, "True", "False"))
        Writeln channel iCh ("        Set pbCompareIndexUppercase to" * If(bCompareIndexUppercase, "True", "False"))
        Writeln channel iCh
        Writeln channel iCh ("        Set Allow_Cancel_State of ghoStatusPanel  to False")
        Writeln channel iCh ("        Set pbVisible    of ghoProgressBarOverall to True")
        Writeln channel iCh ("        Set piPosition   of ghoProgressBarOverall to 0")
        Writeln channel iCh ("        Set piMaximum    of ghoProgressBarOverall to" * String(iTables))
        Writeln channel iCh ("        Set piAdvanceBy  of ghoProgressBarOverall to 1")
        Writeln channel iCh ("        Send DoAdvance   of ghoProgressBarOverall")   
        Writeln channel iCh ("        Move 0 to iCount")
        Writeln channel iCh

        // Create Definitions:
        Move 0 to iTable
        For iTable from 0 to iTables
            Set piPosition of ghoProgressBarOverall to iTable
            Move TheData[iTable].hTable to hTable
            Get UtilTableOpen of ghoDbUpdateFunctionLibrary hTable "" DF_SHARE to bOpened
            Get_Attribute DF_FILE_OPENED of hTable to bOpened
            If (bOpened = False) Begin
                Send Seq_Close_Channel iCh
                Set phTable to hTable
                Set psTableName to TheData[iTable].sLogicalName
                Function_Return GenerateOpenTableError
            End
            
            Move (Uppercase(TheData[iTable].sLogicalName) = "DBVERSION") to bSkipTable

            If (bSkipTable = False) Begin
                Move TheData[iTable].sLogicalName to APITableNameInfo.sLogicalName
                Set Action_Text of ghoStatusPanel to ("Number:" * String(APITableNameInfo.iTableNumber) * String(sLogicalName))

                Move hTable                       to APITableNameInfo.iTableNumber
                Move TheData[iTable].sRootName    to sRootName
                Get _TableNameOnly of ghoDbUpdateFunctionLibrary sRootName to sTableName
                Move sRootName                    to APITableNameInfo.sRootName

                Move TheData[iTable].sDisplayName to APITableNameInfo.sDisplayName
                Move TheData[iTable].bIsAlias     to bIsAlias
                Move bIsAlias                     to APITableNameInfo.bIsAlias
                Get UtilTableIsSQL of ghoDbUpdateFunctionLibrary hTable to APITableNameInfo.bIsSQL

                // Get the Driver ID
                Get_Attribute DF_FILE_DRIVER of hTable to sDriverID
                Get IsDAWSQLDriver of ghoDbUpdateFunctionLibrary sDriverID to bDawSqlDriver
                Get IsSQLDriver    of ghoDbUpdateFunctionLibrary sDriverID to bSqlDriver

                If (bIsAlias = False) Begin
                    Set Action_Text of ghoStatusPanel to ("Number:" * String(APITableNameInfo.iTableNumber) * String(APITableNameInfo.sLogicalName))
                    Get UtilColumnsStructFill of ghoDbUpdateFunctionLibrary hTable to APIColumns
                    If (APIColumns[0].bError = True) Begin
                        Function_Return GenerateError
                    End
                    If (APIColumns[0].bCancel = True) Begin
                        Function_Return GenerateUserCancel
                    End
                    Move (SizeOfArray(APIColumns)) to iSize
                    Decrement iSize
                    If (iSize >= 0) Begin
                        Writeln channel iCh ("        // Logical Table Name:" * '"' + APITableNameInfo.sLogicalName + '"' * "Filelist.cfg Number:" * String(APITableNameInfo.iTableNumber))
                        Writeln channel iCh ("        Move" * String(APITableNameInfo.iTableNumber)                    * "to APITableNameInfo.iTableNumber")
                        Writeln channel iCh ("        Move" * '"' + String(APITableNameInfo.sRootName)    + '"'        * "to APITableNameInfo.sRootName")
                        Writeln channel iCh ("        Move" * '"' + String(APITableNameInfo.sLogicalName) + '"'        * "to APITableNameInfo.sLogicalName")
                        Writeln channel iCh ("        Move" * '"' + String(APITableNameInfo.sDisplayName) + '"'        * "to APITableNameInfo.sDisplayName")
                        Writeln channel iCh ("        Move" * '"' + String(sDriverID)                     + '"'        * "to APITableNameInfo.sDriverID")
                        Writeln channel iCh ("        Move" * String(If(APITableNameInfo.bIsAlias,      "True", "False")) * "to APITableNameInfo.bIsAlias")
                        Writeln channel iCh ("        Move" * String(If(APITableNameInfo.bIsSQL,        "True", "False")) * "to APITableNameInfo.bIsSQL")
                        Writeln channel iCh ("        Move" * String(If(APITableNameInfo.bIsSystemFile, "True", "False")) * "to APITableNameInfo.bIsSystemFile")
                        Writeln channel iCh
                        Writeln channel iCh ("        // Table:" * '"' + APITableNameInfo.sLogicalName + '"' * "Column: 1")
                    End

                    For iCount from 0 to iSize
                        Writeln channel iCh ("        Move" *       String(APIColumns[iCount].iFieldNumber)       * "to APIColumns[iCount].iFieldNumber")
                        Writeln channel iCh ("        Move" * '"' + String(APIColumns[iCount].sFieldName)   + '"' * "to APIColumns[iCount].sFieldName")
                        Writeln channel iCh ("        Move" *       String(APIColumns[iCount].iType)              * "to APIColumns[iCount].iType")
                        Writeln channel iCh ("        Move" * String(If(APIColumns[iCount].bIsSQLType, "True", "False")) * "to APIColumns[iCount].bIsSQLType")
                        Writeln channel iCh ("        Move" * String(If(APIColumns[iCount].bAllowNULL, "True", "False")) * "to APIColumns[iCount].bAllowNULL")
                        Writeln channel iCh ("        Move" * '"' + String(APIColumns[iCount].sDefaultValue) + '"'       * "to APIColumns[iCount].sDefaultValue")
                        If (APIColumns[iCount].iFieldNumber = 0 and APIColumns[iCount].iLength = 0) Begin
                            Writeln channel iCh ("        ERROR! This field has a length = 0! It must be corrected before running this code")
                            Increment iErrors
                        End
                        Move APIColumns[iCount].sType to sDataType
                        If (Lowercase(sDataType) contains "identity") Begin
                            Move (Replace("identity",sDataType, "")) to sDataType
                            Move (Trim(sDataType)) to sDataType
                        End
                        Writeln channel iCh ("        Move" * '"' + sDataType                               + '"' * "to APIColumns[iCount].sType")
                        Writeln channel iCh ("        Move" *       String(APIColumns[iCount].iLength)            * "to APIColumns[iCount].iLength")
                        Writeln channel iCh ("        Move" *       String(APIColumns[iCount].iPrecision)         * "to APIColumns[iCount].iPrecision")
                        Writeln channel iCh ("        Move" *       String(APIColumns[iCount].iOptions)           * "to APIColumns[iCount].iOptions")

                        If (iCount < iSize) Begin
                            Writeln channel iCh ("        Increment iCount")
                            Writeln channel iCh
                            Writeln channel iCh ("        // Table:" * '"' + APITableNameInfo.sLogicalName + '"' * "Column:" * String(iCount + 2))
                        End
                    Loop

                    // Create Index Definitions:
                    Get UtilIndexesStructFill of ghoDbUpdateFunctionLibrary hTable to APIIndexes
                    If (APIIndexes[0].bError = True) Begin
                        Function_Return GenerateError
                    End
                    If (APIIndexes[0].bCancel = True) Begin
                        Function_Return GenerateUserCancel
                    End
                    Move (SizeOfArray(APIIndexes)) to iIndexes
                    Decrement iIndexes
                    If (iIndexes >= 0) Begin
                        Writeln channel iCh
                        Writeln channel iCh ("        // Table:" * '"' + APITableNameInfo.sLogicalName + '"' * "Index: 1")
                        Writeln channel iCh ("        Move 0 to iCount")
                        Writeln channel iCh ("        Move 0 to iSegment")
                    End
                    For iIndex from 0 to iIndexes
                        Writeln channel     iCh ("        Move" *       String(APIIndexes[iIndex].iIndexNumber)        * "to APIIndexes[iCount].iIndexNumber")
                        Writeln channel     iCh ("        Move" *       String(APIIndexes[iIndex].iPrimaryIndex)       * "to APIIndexes[iCount].iPrimaryIndex")
                        Writeln channel     iCh ("        Move" *       String(APIIndexes[iIndex].iSQLIndexType)       * "to APIIndexes[iCount].iSQLIndexType")
                        Writeln channel     iCh ("        Move" *       If((APIIndexes[iIndex].bIsSQLClustered),  "True", "False") * "to APIIndexes[iCount].bIsSQLClustered")
                        Writeln channel     iCh ("        Move" *       If((APIIndexes[iIndex].bIsSQLPrimaryKey), "True", "False") * "to APIIndexes[iCount].bIsSQLPrimaryKey")
                        If (APIIndexes[iIndex].sSQLIndexName <> "") Begin
                            Writeln channel iCh ("        Move" * '"' + String(APIIndexes[iIndex].sSQLIndexName) + '"' * "to APIIndexes[iCount].sSQLIndexName")
                        End

                        Move (SizeOfArray(APIIndexes[iIndex].IndexSegmentArray)) to iNumSegments
                        Decrement iNumSegments
                        For iSegment from 0 to iNumSegments
                            Writeln channel iCh ("        Move" *       String(APIIndexes[iIndex].IndexSegmentArray[iSegment].iFieldNumber)              * "to APIIndexes[iCount].IndexSegmentArray[iSegment].iFieldNumber")
                            Writeln channel iCh ("        Move" * '"' + String(APIIndexes[iIndex].IndexSegmentArray[iSegment].sFieldName)          + '"' * "to APIIndexes[iCount].IndexSegmentArray[iSegment].sFieldName")
                            Writeln channel iCh ("        Move" *       If((APIIndexes[iIndex].IndexSegmentArray[iSegment].bUppercase), "True", "False") * "to APIIndexes[iCount].IndexSegmentArray[iSegment].bUppercase")
                            Writeln channel iCh ("        Move" *       If((APIIndexes[iIndex].IndexSegmentArray[iSegment].bAscending), "True", "False") * "to APIIndexes[iCount].IndexSegmentArray[iSegment].bAscending")
                            If (iSegment < iNumSegments) Begin
                                Writeln channel iCh ("        Increment iSegment")
                            End
                        Loop

                        If (iIndex < iIndexes) Begin
                            Writeln channel iCh ("        Increment iCount")
                            Writeln channel iCh
                            Writeln channel iCh ("        // Table:" * '"' + APITableNameInfo.sLogicalName + '"' * "Index:" * String(iIndex + 2))
                            Writeln channel iCh ("        Move 0 to iSegment")
                        End
                    Loop

                    // Create Relation Definitions:
                    Get UtilRelationsStructFill of ghoDbUpdateFunctionLibrary hTable to APIRelations
                    If (APIRelations[0].bError = True) Begin
                        Function_Return GenerateError
                    End
                    If (APIRelations[0].bCancel = True) Begin
                        Function_Return GenerateUserCancel
                    End
                    Move (SizeOfArray(APIRelations)) to iSize
                    Decrement iSize
                    If (iSize >= 0) Begin
                        Writeln channel iCh
                        Writeln channel iCh ("        // Table:" * '"' + APITableNameInfo.sLogicalName + '"' * "Relation: 1")
                        Writeln channel iCh ("        Move 0 to iCount")
                    End
                    For iCount from 0 to iSize
                        Writeln channel iCh ("        Move" * String(APIRelations[iCount].hTableFrom)  * "to APIRelations[iCount].hTableFrom")
                        Writeln channel iCh ("        Move" * String(APIRelations[iCount].iColumnFrom) * "to APIRelations[iCount].iColumnFrom")
                        Writeln channel iCh ("        Move" * String(APIRelations[iCount].hTableTo)    * "to APIRelations[iCount].hTableTo")
                        Writeln channel iCh ("        Move" * String(APIRelations[iCount].iColumnTo)   * "to APIRelations[iCount].iColumnTo")
                        If (iCount < iSize) Begin
                            Writeln channel iCh ("        Increment iCount")
                            Writeln channel iCh
                            Writeln channel iCh ("        // Table:" * '"' + APITableNameInfo.sLogicalName + '"' * "Relation:" * String(iCount + 2))
                        End
                    Loop

                    // Create Table Update Definition:
                    Writeln channel iCh
                    Writeln channel iCh ("        Get ApiTableUpdate APITableNameInfo APIColumns APIIndexes APIRelations to bOK")
                    Writeln channel iCh

                    Writeln channel iCh ("        Move APIColumnEmpty   to APIColumns")
                    Writeln channel iCh ("        Move APIRelationEmpty to APIRelations")
                    Writeln channel iCh ("        Move APIIndexEmpty    to APIIndexes")
                    Writeln channel iCh ("        Move 0 to iCount")
                    Writeln channel iCh ("        Send DoAdvance of ghoProgressBarOverall")
                    Writeln channel iCh
                End

                If (bIsAlias = True) Begin
                    // Create Alias Table Definition:
                    Writeln channel iCh ("        // Create Alias Table Definition:")
                    Writeln channel iCh ("        Move" * String(hTable) * "to hTable")
                    If (bSqlDriver = True and not(APITableNameInfo.sRootName contains sDriverID)) Begin
                        Writeln channel iCh ("        Set_Attribute DF_FILE_ROOT_NAME    of hTable to" * '"' + sDriverID + ":" + APITableNameInfo.sRootName    + '"')
                    End
                    Else Begin
                        Writeln channel iCh ("        Set_Attribute DF_FILE_ROOT_NAME    of hTable to" * '"' + APITableNameInfo.sRootName    + '"')
                    End

                    Writeln channel iCh ("        Set_Attribute DF_FILE_LOGICAL_NAME of hTable to" * '"' + APITableNameInfo.sLogicalName + '"')
                    Writeln channel iCh ("        Set_Attribute DF_FILE_DISPLAY_NAME of hTable to" * '"' + APITableNameInfo.sDisplayName + '"')
                    Writeln channel iCh
                End
            End
            Get Check_StatusPanel of ghoStatusPanel to iStatus
            If (iStatus <> 0) Begin
                Send Seq_Close_Channel iCh
                Function_Return GenerateUserCancel
            End         
            
            Close hTable
        Loop // Main TheData loop

        Writeln channel iCh ("    End_Procedure")
        Writeln channel iCh ("End_Object")

        Send Seq_Close_Channel iCh
        Function_Return GenerateOK
    End_Function

    Function DFTypeToDUFType Integer iDataFlexDataType Returns String
        String sRetval
        Case Begin
            Case (iDataFlexDataType = DF_ASCII)
                Move DF_ASCII_DUF to sRetval
                Case Break
            Case (iDataFlexDataType = DF_BCD)
                Move "DF_BCD_DUF" to sRetval
                Case Break
            Case (iDataFlexDataType = DF_BINARY)
                Move "DF_BINARY_DUF" to sRetval
                Case Break
            Case (iDataFlexDataType = DF_DATE)
                Move "DF_DATE_DUF" to sRetval
                Case Break
            Case (iDataFlexDataType = DF_DATETIME)
                Move "DF_DATETIME_DUF" to sRetval
                Case Break
            Case (iDataFlexDataType = DF_TEXT)
                Move "DF_TEXT_DUF" to sRetval
                Case Break
            Case Else
                Move iDataFlexDataType to sRetval
        Case End

        Function_Return sRetval
    End_Function

    Procedure OnFileDropped String sFilename Boolean bLast
        String sTest
        Forward Send OnFileDropped sFilename bLast
        If (bLast = True) Begin
            Get ParseFileName sFilename to sTest
            If (Uppercase(sTest) <> "FILELIST.CFG") Begin
                Send Info_Box "Sorry, only Filist.cfg files can be dropped here..."
                Procedure_Return
            End
            Set Value of oFilelistPath_fm to sFilename
        End
    End_Procedure

    Procedure Request_Clear
        tDataSourceRow[] EmptyData
        Handle hoGrid hoDataSource
        Integer[] iDifferencesEmpty

        Move (oFilelist_grd(Self))  to hoGrid
        Get phoDataSource of hoGrid to hoDataSource
        Send InitializeData of hoGrid EmptyData
        Set Value of oFilelistPath_fm    to ""
        Set Value of oPnVersionNumber_fm to ""
        Set Value of oSourceName_fm      to ""
        Set psFilelistFrom of ghoApplication to ""
        Send Activate of oFilelistPath_fm
    End_Procedure

    Procedure TagChangedTables String sFromFilelist Integer[] iaDifferences
        Integer iSize iCount iItem iItems iTableNo iTableNo_Col iCheckbox_Col
        Handle hoGrid hoDataSource
        tDataSourceRow[] TheData

        Set Value of oFilelistPath_fm to sFromFilelist
        Move (oFilelist_grd(Self)) to hoGrid

        Get piColumnId of (oFilelistNumber_col(hoGrid)) to iTableNo_Col
        Get piColumnId of (oCheckbox_Col(hoGrid))       to iCheckbox_Col
        Get phoDataSource of hoGrid to hoDataSource
        Get DataSource of hoDataSource to TheData
        Move (SizeOfArray(TheData)) to iItems
        Decrement iItems

        Move (SizeOfArray(iaDifferences)) to iSize
        If (iSize = 0) Begin
            Procedure_Return
        End
        Decrement iSize
        If (iSize > 0) Begin
            Send KeyAction of oDeSelectAll_btn
        End

        For iCount from 0 to iSize
            Move iaDifferences[iCount] to iTableNo
            If (iTableNo > 0) Begin
                For iItem from 0 to iItems
                    If (TheData[iItem].sValue[iTableNo_Col] = iTableNo) Begin
                        Move True to TheData[iItem].sValue[iCheckbox_Col]
                        Move iItems to iItem // We found it and we're out of this loop.
                    End
                Loop
            End
        Loop

        Send ReInitializeData of hoGrid TheData False
        Send DoSetCheckboxFooterText of hoGrid
    End_Procedure

    On_Key Key_Ctrl+Key_A  Send KeyAction of oSelectAll_btn
    On_Key Key_Ctrl+Key_N  Send KeyAction of oDeSelectAll_btn
    On_Key Key_Ctrl+Key_I  Send KeyAction of oInvertSelection_btn
    On_Key Key_Ctrl+Key_G  Send KeyAction of oGenerateCode_btn
    On_Key Key_Ctrl+Key_O  Send KeyAction of oOpenAppSrcFolder_btn
    On_Key kClear          Send Request_Clear
    On_Key kClear_All      Send Request_Clear
    On_Key Key_Ctrl+Key_F4 Send None
End_Object

// General purpose access message to auto-fill grid with tables with
// differences (after "Compare Databases" has been run).
Procedure TagFileNamesForCodeGeneration
    String sFileListFrom sCurrentFilelist
    Integer[] iaDifferences
    Handle ho

    Send Activate_oTableDUFCodeGenerator
    Move (oTableDUFCodeGenerator(Self)) to ho
    Get Value of (oFilelistPath_fm(ho)) to sCurrentFilelist
    If (sCurrentFilelist <> "") Begin
        Send Request_Clear of ho
    End

    Get psFilelistFrom of ghoApplication to sFileListFrom
    Get piaDifferences of ghoApplication to iaDifferences
    Send TagChangedTables of ho sFileListFrom iaDifferences
    Send Info_Box ("Ready marking tables. Number of different tables:" * (String(SizeOfArray(iaDifferences))))
End_Procedure
