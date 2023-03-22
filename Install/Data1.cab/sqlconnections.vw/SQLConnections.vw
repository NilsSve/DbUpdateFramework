Use Windows.pkg
Use DFClient.pkg
Use cDbScrollingContainer.pkg
Use cDbUpdateFunctionLibrary.pkg
Use cButtonDPI.pkg
Use DatabaseSelection.dg
Use ServerSelection.dg
Use SQLConnections.dg

Activate_View Activate_oSQLConnections_vw for oSQLConnections_vw
Object oSQLConnections_vw is a dbView
    Set Border_Style to Border_Thick
    Set Size to 251 427
    Set Location to 2 2
    Set Label to "SQL Connections"
    Set pbAutoActivate to True
    Set Icon to "SQLConnections.ico"

    Object oScrollingContainer1 is a cDbScrollingContainer
        Object oScrollingClientArea1 is a cDbScrollingClientArea

            Object oCurrentSettings_grp is a Group
                Set Size to 232 402
                Set Location to 6 12
                Set Label to "Current Connection Settings"
                Set peAnchors to anAll

                Object oConnectionID_fm is a Form
                    Set Size to 13 100
                    Set Location to 12 68
                    Set Label to "Connection ID"
                    Set Label_Col_Offset to 2
                    Set Label_Justification_Mode to JMode_Right
                    Set Prompt_Button_Mode to PB_PromptOn
                    Set Prompt_Object to (oSQLConnections(Self))

                    Procedure Prompt
                        String[] sTheData
                        String sCurrentVal sNewVal
                        Handle hoIniFile ho
                        Integer iSize iCount
                        tSQLConnection[] SQLConnectionArray

                        Get phoSQLConnectionIniFile of ghoSQLConnectionHandler to hoIniFile
                        Get SQLIniFileReadConnections of hoIniFile to SQLConnectionArray
                        Move (SizeOfArray(SQLConnectionArray)) to iSize
                        Decrement iSize
                        For iCount from 0 to iSize
                            Move (SQLConnectionArray[iCount].sConnectionID + "|" + SQLConnectionArray[iCount].sDriverID) to sTheData[iCount]
                        Loop

                        Get Value to sCurrentVal
                        Get Prompt_Object to ho
                        Set psTheData     of ho to sTheData

                        Forward Send Prompt
                        Get Value to sNewVal
                        If (sCurrentVal <> sNewVal) Begin
                            Send Cursor_Wait of Cursor_Control
                            Set psConnectionID of ghoSQLConnectionHandler to sNewVal
                            Broadcast Recursive Send Refresh of (phoMainPanel(ghoApplication))
                            Send Cursor_Ready of Cursor_Control
                            Send KeyAction of oTestLogin_btn
                        End
                    End_Procedure

                    Procedure Refresh
                        String sValue
                        Get psConnectionID of ghoSQLConnectionHandler to sValue
                        Set Value to sValue
                    End_Procedure

                End_Object

                Object oDatabase_fm is a Form
                    Set Size to 13 91
                    Set Location to 27 222
                    Set Label to "Database"
                    Set Label_Col_Offset to 2
                    Set Label_Justification_Mode to JMode_Right
                    Set Prompt_Button_Mode to PB_PromptOn
                    Set Prompt_Object to (oDatabaseSelection_sl(Self))
                    Set peAnchors to anNone
                    Set Entry_State to False

                    Procedure Refresh
                        String sDatabase

                        Get psDatabase of ghoSQLConnectionHandler to sDatabase
                        Set Value to sDatabase
                    End_Procedure

                    Procedure Prompt
                        String[] sTheData
                        Handle ho
                        String sDriverID

                        Get Value of oDriverID_cf to sDriverID
                        Get SqlUtilEnumerateDatabases of ghoDbUpdateFunctionLibrary sDriverID to sTheData

                        Get Prompt_Object to ho
                        Set psTheData of ho to sTheData

                        Forward Send Prompt
                    End_Procedure

                    Procedure OnChange
                        String sValue sOrgValue
                        Get Value to sValue
                        Get psDatabase of ghoSQLConnectionHandler to sOrgValue
                        If (Uppercase(Trim(sValue)) <> Uppercase(Trim(sOrgValue))) Begin
                            Set psDatabase of ghoSQLConnectionHandler to sValue
                            Get psConnectionString of ghoSQLConnectionHandler to sValue
                            Set Value of oConnectionString_fm to sValue
                        End
                    End_Procedure

                End_Object

                Object oTrusted_cb is a CheckBox
                    Set Size to 10 50
                    Set Location to 45 68
                    Set Label to "Use Trusted Connection"

                    Procedure Refresh
                        Boolean bValue
                        Get pbTrusted of ghoSQLConnectionHandler to bValue
                        Set Checked_State to bValue
                    End_Procedure

                    Procedure OnChange
                        Boolean bChecked

                        Get Checked_State to bChecked
                        Set Enabled_State of oUserID_fm   to (bChecked = False)
                        Set Enabled_State of oPassword_fm to (bChecked = False)
                    End_Procedure

                End_Object

                Object oUserID_fm is a Form
                    Set Size to 13 100
                    Set Location to 57 68
                    Set Label to "UserID"
                    Set Label_Col_Offset to 2
                    Set Label_Justification_Mode to JMode_Right

                    Procedure Refresh
                        String sValue
                        Get psUserID of ghoSQLConnectionHandler to sValue
                        Set Value to sValue
                    End_Procedure

                End_Object

                Object oPassword_fm is a Form
                    Set Size to 13 91
                    Set Location to 57 222
                    Set Label to "Password"
                    Set Label_Col_Offset to 2
                    Set Label_Justification_Mode to JMode_Right
                    // Set psToolTip to "Note: The password form does _not_ have it's password state set to True because the view is for testing purposes only. And we can see the password - if set - from the connection string as well."
                    Set psToolTip to "Press the 'Toggle Password' button to reveal the password"
                    Set Password_State to True

                    Procedure Refresh
                        String sValue
                        Get psPassword of ghoSQLConnectionHandler to sValue
                        Set Value to sValue
                    End_Procedure

                End_Object

                Object oViewPassword_btn is a cButtonDPI
                    Set Size to 13 19
                    Set Location to 57 319
                    Set psToolTip to "Toggle password"  
                    Set psImage to "PasswordView.ico"
                    
                    Property String psImageL "PasswordView.ico"
                    Property String psImageU "PasswordViewUnlock.ico"
                    
                    Procedure OnClick                
                        Boolean bState
                        Get Password_State of oPassword_fm item 0 to bState
                        Send Page_Object   of oPassword_fm False
                        Set Password_State of oPassword_fm item 0 to (not(bState)) 
                        Send Page_Object   of oPassword_fm True 
                        Set psImage to (If(bState = False, psImageL(Self), psImageU(Self)))
                    End_Procedure
                
                End_Object

                Object oConnectionString_fm is a Form
                    Set Size to 13 245
                    Set Location to 75 68
                    Set Label to "Connection String"
                    Set Label_Col_Offset to 2
                    Set Label_Justification_Mode to JMode_Right
                    Set peAnchors to anTopLeftRight
                    Set Enabled_State to False

                    Procedure Refresh
                        String sValue
                        tSQLConnection SQLConnection
                        
                        Get pSQLConnection of ghoSQLConnectionHandler to SQLConnection
                        Move (Replace(("PWD=" + SQLConnection.sPassword), SQLConnection.sConnectionString, "PWD=***")) to sValue
                        Set Value to sValue
                    End_Procedure

                End_Object

                Object oTestLogin_btn is a cButtonDPI
                    Set Size to 13 67
                    Set Location to 75 319
                    Set Label to "Test Login"
                    Set peAnchors to anTopRight
                    Set MultiLineState to True
                    Set psToolTip to "Changes the connection string with any changes made and tries to login to the server with the connection string."
                    Set FontWeight to fw_Bold
                    Set psImage to "ActionLogin.ico"

                    Procedure OnClick
                        tSQLConnection SQLConnection
                        String sServer sDatabase sDriverID sUserID sPassword sConnectionID sConnectionString
                        Boolean bTrusted bMertechDriver bLoginSuccessful
                        Integer iDriverID
                        Handle hoDriver

                        Get Value of oDriverID_cf        to SQLConnection.sDriverID
                        Get Value of oConnectionID_fm    to SQLConnection.sConnectionID
                        Get Value of oServer_fm          to SQLConnection.sServer
                        Get Value of oDatabase_fm        to SQLConnection.sDatabase
                        Get Checked_State of oTrusted_cb to SQLConnection.bTrusted
                        Get Value of oUserID_fm          to SQLConnection.sUserID
                        Get Value of oPassword_fm        to SQLConnection.sPassword

                        Get ConstructConnectionString of (phoSQLConnectionIniFile(ghoSQLConnectionHandler)) SQLConnection.sDriverID SQLConnection.sServer SQLConnection.sDatabase SQLConnection.bTrusted SQLConnection.sUserID SQLConnection.sPassword to sConnectionString

                        Get DriverIndex of ghoSQLConnectionHandler SQLConnection.sDriverID to iDriverID
                        If (iDriverID = 0) Begin
                            Send Info_Box ("The driver" * SQLConnection.sDriverID * "could not be loaded. Is the driver installed? And equally imporant; Is the corresponding database server or client software installed?")
                            Procedure_Return
                        End

                        Get IsMertechDriver of ghoSQLConnectionHandler SQLConnection.sDriverID to bMertechDriver
                        If (bMertechDriver = False) Begin
                            Set_Attribute DF_DRIVER_SILENT_LOGIN of iDriverID to True
                        End

                        Send Ignore_Error of Error_Object_Id CLIERR_LOGIN_UNSUCCESSFUL
                        Get Create (RefClass(cDbUpdateDatabaseDriver)) to hoDriver
                        Set psDriverID of hoDriver to SQLConnection.sDriverID
                        Get DbLogin    of hoDriver sConnectionString SQLConnection.sServer SQLConnection.sDatabase SQLConnection.bTrusted SQLConnection.sUserID SQLConnection.sPassword to bLoginSuccessful
                        Send Destroy   of hoDriver

                        Send Trap_Error of Error_Object_Id CLIERR_LOGIN_UNSUCCESSFUL
                        If (LastErr <> CLIERR_LOGIN_UNSUCCESSFUL) Begin
                            Move (Replace(("PWD=" + SQLConnection.sPassword), sConnectionString, "PWD=***")) to sConnectionString
                            Set Value of oConnectionString_fm to sConnectionString
                            Send Info_Box "Login Successful!"
                        End
                        Else Begin
                            Send Info_Box "Nope, that didn't work. Login failed."
                        End
                        Broadcast Recursive Send Combo_Fill_List of (Client_Id(phoMainPanel(ghoApplication)))
                        Move 0 to LastErr
                    End_Procedure

                End_Object

                Object oInfo_tb is a TextBox
                    Set Auto_Size_State to False
                    Set Size to 18 303
                    Set Location to 106 8
                    Set Label to "Note: The above settings was read from the SQLConnections.ini file when the object was created and are properties of the 'ghoSQLConnectionHandler' object."
                    Set Justification_Mode to JMode_Left
                    Set FontItalics to True
                End_Object

                Object oDriverID_cf is a ComboForm
                    Set Size to 11 91
                    Set Location to 13 222
                    Set Label_Col_Offset to 2
                    Set Label_Justification_Mode to JMode_Right
                    Set Label to "Driver ID"
                    Set Entry_State to False
                    Set Enabled_State to False

                    Procedure Combo_Fill_List
                        Send Combo_Add_Item MSSQLDRV_ID
                        Send Combo_Add_Item DB2_DRV_ID
                        Send Combo_Add_Item ODBC_DRV_ID
                        #IFDEF DUF_Use_Mertech_Drivers
                        Send Combo_Add_Item SQLFLEX
                        Send Combo_Add_Item MDSDB2
                        Send Combo_Add_Item MDSMySQL
                        Send Combo_Add_Item MDSPgSQL
                        Send Combo_Add_Item ORAFLEX
                        #ENDIF
                    End_Procedure

                    Procedure OnChange
                        String sValue sOrgValue
                        Boolean bEnabled bChecked

                        Get Value to sValue
                        Get psDriverID of ghoSQLConnectionHandler to sOrgValue
                        If (sValue <> "" and sValue <> sOrgValue and sValue <> "None") Begin
                            Set psDriverID of ghoSQLConnectionHandler to sValue
                        End
                        Move (sValue <> "None") to bEnabled
                        Broadcast Set Enabled_State of (Parent(Self)) to bEnabled
                        Set Enabled_State to False
                        Set Enabled_State of oConnectionString_fm to False
                        Set Enabled_State of oDatabase_fm to (sValue <> DB2_DRV_ID)

                        Get Checked_State of oTrusted_cb  to bChecked
                        Set Enabled_State of oUserID_fm   to (bChecked = False)
                        Set Enabled_State of oPassword_fm to (bChecked = False)
                    End_Procedure

                    Procedure Refresh
                        String sValue

                        Get psDriverID of ghoSQLConnectionHandler to sValue
                        Set Value to sValue
                    End_Procedure

                End_Object

                Object oServer_fm is a Form
                    Set Size to 13 100
                    Set Location to 27 68
                    Set Label to "Server"
                    Set Label_Col_Offset to 2
                    Set Label_Justification_Mode to JMode_Right
                    Set Prompt_Button_Mode to PB_PromptOn
                    Set Prompt_Object to (oServerSelection_sl(Self))

                    Procedure Refresh
                        String sValue
                        Get psServer of ghoSQLConnectionHandler to sValue
                        Set Value to sValue
                    End_Procedure

                    Procedure Prompt
                        String[] sTheData
                        String sDriverID
                        Handle ho

                        Send Cursor_Wait of Cursor_Control
                        Get Prompt_Object to ho
                        Get Value of oDriverID_cf to sDriverID
                        Get SqlUtilEnumerateServers of ghoDbUpdateFunctionLibrary sDriverID 2 to sTheData
                        Set psTheData of ho to sTheData
                        Send Cursor_Ready of Cursor_Control

                        Forward Send Prompt
                    End_Procedure

                End_Object

                Object oRunSQLConnectionsProgram_btn is a cButtonDPI
                    Set Size to 21 75
                    Set Location to 106 319
                    Set Label to "SQL Connections Manager"
                    Set peAnchors to anTopRight
                    Set MultiLineState to True
                    Set psImage to "SQLConnections.ico"

                    Procedure OnClick
                        Runprogram Background "SQLConnections.exe"
                    End_Procedure

                End_Object

                Procedure Page Integer iPageObject
//                    Broadcast Send Refresh
                    Broadcast Recursive Send Refresh of (phoMainPanel(ghoApplication))
                    Forward Send Page iPageObject
                End_Procedure

            End_Object

        End_Object

    End_Object

End_Object
