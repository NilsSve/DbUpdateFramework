//
// *** The Database Update Framework Include file ***
// Language constant declarations for all classes included in "DUF - The Database Update Framework"
// They have all been placed in this central spot to make translations to various languages more convenient.
//
//
Use LanguageText.Pkg

// *** cSQLConnectionsIniFile Class Language Constants ***
//
#IFSAME Language$Current Language$English
    Define CS_DUF_DuplicateConnectionIDPre  for "Cannot register connection ID"
    Define CS_DUF_DuplicateConnectionIDPost for "This ID already exists."
#ENDIF

#IFSAME Language$Current Language$Nederlands
    Define CS_DUF_DuplicateConnectionIDPre  for "Kan de connection ID niet registreren"
    Define CS_DUF_DuplicateConnectionIDPost for "Deze ID bestaat al."
#ENDIF

#IFSAME Language$Current Language$Svenska
    Define CS_DUF_DuplicateConnectionIDPre  for "Kan inte registrera anslutnings-ID"
    Define CS_DUF_DuplicateConnectionIDPost for "Detta ID finns redan."
#ENDIF

#IFSAME Language$Current Language$Deutsch
    Define CS_DUF_DuplicateConnectionIDPre  for "Kann Connection ID nicht registrieren"
    Define CS_DUF_DuplicateConnectionIDPost for "Dieses ID existiert schon."
#ENDIF

#IFSAME Language$Current Language$Dansk
    Define CS_DUF_DuplicateConnectionIDPre  for "Cannot register connection ID"
    Define CS_DUF_DuplicateConnectionIDPost for "This ID already exists."
#ENDIF

#IFSAME Language$Current Language$Portugues
    Define CS_DUF_DuplicateConnectionIDPre  for "N„o pÙde registar o ID de conex„o"
    Define CS_DUF_DuplicateConnectionIDPost for "Este ID j· existe."
#ENDIF

#IFSAME Language$Current Language$Francais
    Define CS_DUF_DuplicateConnectionIDPre  for "Cannot register connection ID"
    Define CS_DUF_DuplicateConnectionIDPost for "This ID already exists."
#ENDIF

#IFSAME Language$Current Language$Italiano
    Define CS_DUF_DuplicateConnectionIDPre  for "Cannot register connection ID"
    Define CS_DUF_DuplicateConnectionIDPost for "This ID already exists."
#ENDIF

#IFSAME Language$Current Language$Espanol
    Define CS_DUF_DuplicateConnectionIDPre  for "No se puede registrar conexi¢n ID"
    Define CS_DUF_DuplicateConnectionIDPost for "Este ID ya existe."
#ENDIF

#IFSAME Language$Current Language$Norsk
    Define CS_DUF_DuplicateConnectionIDPre  for "Kan ikke registrere tilkoblings-ID"
    Define CS_DUF_DuplicateConnectionIDPost for "Denne ID-en eksisterer allerede."
#ENDIF

#IFSame Language$Current = Language$Russian
    Define CS_DUF_DuplicateConnectionIDPre  for "Cannot register connection ID"
    Define CS_DUF_DuplicateConnectionIDPost for "This ID already exists."
#ENDIF

#IFSame Language$Current = Language$Polish
    Define CS_DUF_DuplicateConnectionIDPre  for "Cannot register connection ID"
    Define CS_DUF_DuplicateConnectionIDPost for "This ID already exists."
#ENDIF

#IFSame Language$Current = Language$Hungarian
    Define CS_DUF_DuplicateConnectionIDPre  for "Cannot register connection ID"
    Define CS_DUF_DuplicateConnectionIDPost for "This ID already exists."
#ENDIF


// *** cSQLConnectionsHandler Class Language Constants ***
//
#IFSAME Language$Current Language$English
    Define CS_DUF_SetupErrorcConnection  for "Cannot login to the database server as the cConnection hasn't been setup properly. Can't continue. Program will now exit."
    Define CS_DUF_CannotLoginToServer    for "Could not login to the database server. Can't continue. Program will now exit."
    Define CS_DUF_ErrorText              for "\n\nError Text:"
#ENDIF

#IFSAME Language$Current Language$Nederlands
    Define CS_DUF_CannotLogincConnection for "Kan niet inloggen op de databaseserver, omdat cConnection niet correct is ingesteld. Kan niet doorgaan. Het programma wordt beâindigd."
    Define CS_DUF_CannotLoginToServer    for "Kan niet inloggen op de databaseserver. Kan niet doorgaan. Het programma wordt beâindigd."
    Define CS_DUF_ErrorText              for "\n\nFoutmelding:"
#ENDIF

#IFSAME Language$Current Language$Svenska
    Define CS_DUF_CannotLogincConnection for "Kan inte logga in pÜ databasservern dÑrfîr att en 'cConnection' inte har konfigurerats. Kan ej fortsÑtta. Programmet kommer nu att avbrytas."
    Define CS_DUF_CannotLoginToServer    for "Kunde ej logga in till databasservern. Kan ej fortsÑtta. Programmet kommer nu att avslutas."
    Define CS_DUF_ErrorText              for "\n\nError Text:"
#ENDIF

#IFSAME Language$Current Language$Deutsch
    Define CS_DUF_CannotLogincConnection for "Anmeldung am Datenbank-Server nicht mîglich, die cConnection ist nicht richtig eingerichtet. Fortfahren nicht mîglich. Das Programm wird beendet."
    Define CS_DUF_CannotLoginToServer    for "Anmeldung am Datenbank-Server nicht mîglich. Fortfahren nicht mîglich. Das Programm wird beendet."
    Define CS_DUF_ErrorText              for "\n\nFehler Text:"
#ENDIF

#IFSAME Language$Current Language$Dansk
    Define CS_DUF_CannotLogincConnection for "Cannot login to the database server as the cConnection hasn't been setup properly. Can't continue. Program will now exit."
    Define CS_DUF_CannotLoginToServer    for "Could not login to the database server. Can't continue. Program will now exit."
    Define CS_DUF_ErrorText              for "\n\nError Text:"
#ENDIF

#IFSAME Language$Current Language$Portugues
    Define CS_DUF_CannotLogincConnection for "N„o pÙde conectar-se ao servidor de banco de dados, pois o objeto cConnetion n„o fora configurado adequadamente. ImpossÌvel continuar. Programa ser· encerrado."
    Define CS_DUF_CannotLoginToServer    for "N„o pÙde conectar-se ao servidor de banco de dados. ImpossÌvel continuar. Programa ser· encerrado."
    Define CS_DUF_ErrorText              for "\n\nDescriÁ„o do Erro:"
#ENDIF

#IFSAME Language$Current Language$Francais
    Define CS_DUF_CannotLogincConnection for "Cannot login to the database server as the cConnection hasn't been setup properly. Can't continue. Program will now exit."
    Define CS_DUF_CannotLoginToServer    for "Could not login to the database server. Can't continue. Program will now exit."
    Define CS_DUF_ErrorText              for "\n\nError Text:"
#ENDIF

#IFSAME Language$Current Language$Italiano
    Define CS_DUF_CannotLogincConnection for "Cannot login to the database server as the cConnection hasn't been setup properly. Can't continue. Program will now exit."
    Define CS_DUF_CannotLoginToServer    for "Could not login to the database server. Can't continue. Program will now exit."
    Define CS_DUF_ErrorText              for "\n\nError Text:"
#ENDIF

#IFSAME Language$Current Language$Espanol
    Define CS_DUF_CannotLogincConnection for "No se puede iniciar sesi¢n en el servidor de base de datos ya que la conexi¢n no se ha configurado correctamente. No se puede continuar. El programa ser† cerrado."
    Define CS_DUF_CannotLoginToServer    for "No se puede iniciar sesi¢n en el servidor de base de datos. No se puede continuar. El programa ser† cerrado."
    Define CS_DUF_ErrorText              for "\n\nTexto del error:"
#ENDIF

#IFSAME Language$Current Language$Norsk
    Define CS_DUF_CannotLogincConnection for "Kan ikke logge p√• databasetjener, for cConnection er ikke riktig satt opp. Kan ikke fortsette. Programmet avsluttes."
    Define CS_DUF_CannotLoginToServer    for "Kan ikke logge p√• databasetjener. Kan ikke fortsette. Programmet avsluttes."
    Define CS_DUF_ErrorText              for "\n\nFeilbeskrivelse:"
#ENDIF

#IFSame Language$Current = Language$Russian
    Define CS_DUF_CannotLogincConnection for "Cannot login to the database server as the cConnection hasn't been setup properly. Can't continue. Program will now exit."
    Define CS_DUF_CannotLoginToServer    for "Could not login to the database server. Can't continue. Program will now exit."
    Define CS_DUF_ErrorText              for "\n\nError Text:"
#ENDIF

#IFSame Language$Current = Language$Polish
    Define CS_DUF_CannotLogincConnection for "Cannot login to the database server as the cConnection hasn't been setup properly. Can't continue. Program will now exit."
    Define CS_DUF_CannotLoginToServer    for "Could not login to the database server. Can't continue. Program will now exit."
    Define CS_DUF_ErrorText              for "\n\nError Text:"
#ENDIF

#IFSame Language$Current = Language$Hungarian
    Define CS_DUF_CannotLogincConnection for "Cannot login to the database server as the cConnection hasn't been setup properly. Can't continue. Program will now exit."
    Define CS_DUF_CannotLoginToServer    for "Could not login to the database server. Can't continue. Program will now exit."
    Define CS_DUF_ErrorText              for "\n\nError Text:"
#ENDIF

// *** cDbUpdateFunctionLibrary Class Language Constants ***
//
#IFSAME Language$Current Language$English
    Define CS_SQLConnectError       for "SQL error. Could not connect to the SQL database manager"
    Define CS_SQLAttachError        for "Could not attach to the database:"
    Define CS_SQLDeletingIndex      for "Deleting index"
    Define CS_SQLCopyingData        for "Copying data"
    Define CS_SQLCreatingIndex      for "Creating index"
#ENDIF

#IFSAME Language$Current Language$Nederlands
    Define CS_SQLConnectError       for "SQL fout. Kon geen verbinding maken met de SQL database manager"
    Define CS_SQLAttachError        for "Kan niet aan de database koppelen:"
    Define CS_SQLDeletingIndex      for "Verwijderen index"
    Define CS_SQLCopyingData        for "Kopiâren data"
    Define CS_SQLCreatingIndex      for "Aanmaken index"
#ENDIF

#IFSAME Language$Current Language$Svenska
    Define CS_SQLConnectError       for "SQL Fel. Kunde ej fÜ kontakt med SQL Database Manager"
    Define CS_SQLAttachError        for "Fick ej kontakt med databasen:"
    Define CS_SQLDeletingIndex      for "Tar bort index"
    Define CS_SQLCopyingData        for "Kopierar data"
    Define CS_SQLCreatingIndex      for "Skapar index"
#ENDIF

#IFSAME Language$Current Language$Deutsch
    Define CS_SQLConnectError       for "SQL Fehler. Verbindung zum SQL Datenbank Manager nicht mîglich."
    Define CS_SQLAttachError        for "Verbindung zur Datenbank fehlgeschlagen:"
    Define CS_SQLDeletingIndex      for "Index lîschen"
    Define CS_SQLCopyingData        for "Daten kopieren"
    Define CS_SQLCreatingIndex      for "Index erstellen"
#ENDIF

#IFSAME Language$Current Language$Dansk
    Define CS_SQLConnectError       for "SQL error. Could not connect to the SQL database manager"
    Define CS_SQLAttachError        for "Could not attach to the database:"
    Define CS_SQLDeletingIndex      for "Deleting index"
    Define CS_SQLCopyingData        for "Copying data"
    Define CS_SQLCreatingIndex      for "Creating index"
#ENDIF

#IFSAME Language$Current Language$Portugues
    Define CS_SQLConnectError       for "Erro SQL. N„o foi possÌvel conectar-se ao gerenciador de banco de dados SQL"
    Define CS_SQLAttachError        for "N„o foi possÌvel anexar-se ao banco de dados:"
    Define CS_SQLDeletingIndex      for "Excluindo Ìndice"
    Define CS_SQLCopyingData        for "Copiando dados"
    Define CS_SQLCreatingIndex      for "Criando Ìndice"
#ENDIF

#IFSAME Language$Current Language$Francais
    Define CS_SQLConnectError       for "SQL error. Could not connect to the SQL database manager"
    Define CS_SQLAttachError        for "Could not attach to the database:"
    Define CS_SQLDeletingIndex      for "Deleting index"
    Define CS_SQLCopyingData        for "Copying data"
    Define CS_SQLCreatingIndex      for "Creating index"
#ENDIF

#IFSAME Language$Current Language$Italiano
    Define CS_SQLConnectError       for "SQL error. Could not connect to the SQL database manager"
    Define CS_SQLAttachError        for "Could not attach to the database:"
    Define CS_SQLDeletingIndex      for "Deleting index"
    Define CS_SQLCopyingData        for "Copying data"
    Define CS_SQLCreatingIndex      for "Creating index"
#ENDIF

#IFSAME Language$Current Language$Espanol
    Define CS_SQLConnectError       for "Error SQL. No se puede conectar al administrador de base de datos SQL"
    Define CS_SQLAttachError        for "No se puede adjuntar a la base de datos"
    Define CS_SQLDeletingIndex      for "Eliminando °ndice"
    Define CS_SQLCopyingData        for "Copiando datos"
    Define CS_SQLCreatingIndex      for "Creando °ndice"
#ENDIF

#IFSAME Language$Current Language$Norsk
    Define CS_SQLConnectError       for "SQL-feil. Kunne ikke koble til SQL-databasebehandler"
    Define CS_SQLAttachError        for "Kunne ikke koble til database:"
    Define CS_SQLDeletingIndex      for "Sletter indeks"
    Define CS_SQLCopyingData        for "Kopierer data"
    Define CS_SQLCreatingIndex      for "Oppretter indeks"
#ENDIF

#IFSame Language$Current = Language$Russian
    Define CS_SQLConnectError       for "SQL error. Could not connect to the SQL database manager"
    Define CS_SQLAttachError        for "Could not attach to the database:"
    Define CS_SQLDeletingIndex      for "Deleting index"
    Define CS_SQLCopyingData        for "Copying data"
    Define CS_SQLCreatingIndex      for "Creating index"
#ENDIF

#IFSame Language$Current = Language$Polish
    Define CS_SQLConnectError       for "SQL error. Could not connect to the SQL database manager"
    Define CS_SQLAttachError        for "Could not attach to the database:"
    Define CS_SQLDeletingIndex      for "Deleting index"
    Define CS_SQLCopyingData        for "Copying data"
    Define CS_SQLCreatingIndex      for "Creating index"
#ENDIF

#IFSame Language$Current = Language$Hungarian
    Define CS_SQLConnectError       for "SQL error. Could not connect to the SQL database manager"
    Define CS_SQLAttachError        for "Could not attach to the database:"
    Define CS_SQLDeletingIndex      for "Deleting index"
    Define CS_SQLCopyingData        for "Copying data"
    Define CS_SQLCreatingIndex      for "Creating index"
#ENDIF

// *** cDbUpdateVersion Class Language Constants ***
//
#IFSAME Language$Current Language$English
    Define CS_UpdateVersion     for "Updating database"
    Define CS_UpdateFromVersion for "from version"
    Define CS_UpdateToVersion   for "to version:"
    Define CS_DbUpdateTableMissing for "Cannot open the 'DbVersion' table that is used when updating the database! Cannot continue!"
#ENDIF

#IFSAME Language$Current Language$Nederlands
    Define CS_UpdateVersion     for "Bijwerken database"
    Define CS_UpdateFromVersion for "van versie"
    Define CS_UpdateToVersion   for "naar versie:"
    Define CS_DbUpdateTableMissing for "Kan de 'DbVersion' tabel niet openen, die wordt gebruikt bij het bijwerken van de database! Kan niet doorgaan!"
#ENDIF

#IFSAME Language$Current Language$Svenska
    Define CS_UpdateVersion     for "Uppdaterar databas"
    Define CS_UpdateFromVersion for "frÜn version"
    Define CS_UpdateToVersion   for "till version:"
    Define CS_DbUpdateTableMissing for "Kan inte îppna 'DbVersion' tabellen som anvÑnds dÜ databasen ska uppdateras! Kan inte fortsÑtta!"
#ENDIF

#IFSAME Language$Current Language$Deutsch
    Define CS_UpdateVersion     for "Datenbank aktualisieren"
    Define CS_UpdateFromVersion for "von Version"
    Define CS_UpdateToVersion   for "auf Version:"
    Define CS_DbUpdateTableMissing for "Kann die Tabelle 'DbVersion' nicht îffnen, die zum Aktualisieren der Datenbank benutzt wird! Fortfahren nicht mîglich!"
#ENDIF

#IFSAME Language$Current Language$Dansk
    Define CS_UpdateVersion     for "Updating database"
    Define CS_UpdateFromVersion for "from version"
    Define CS_UpdateToVersion   for "to version:"
    Define CS_DbUpdateTableMissing for "Cannot open the 'DbVersion' table that is used when updating the database! Cannot continue!"
#ENDIF

#IFSAME Language$Current Language$Portugues
    Define CS_UpdateVersion     for "Atualizando banco de dados"
    Define CS_UpdateFromVersion for "da vers„o"
    Define CS_UpdateToVersion   for "para a vers„o:"
    Define CS_DbUpdateTableMissing for "N„o foi possiel abrir a tabela 'DbVersion' que È utilizada durante o processo de atualizaÁ„o do banco de dados.! ImpossÌvel continuar!"
#ENDIF

#IFSAME Language$Current Language$Francais
    Define CS_UpdateVersion     for "Updating database"
    Define CS_UpdateFromVersion for "from version"
    Define CS_UpdateToVersion   for "to version:"
    Define CS_DbUpdateTableMissing for "Cannot open the 'DbVersion' table that is used when updating the database! Cannot continue!"
#ENDIF

#IFSAME Language$Current Language$Italiano
    Define CS_UpdateVersion     for "Updating database"
    Define CS_UpdateFromVersion for "from version"
    Define CS_UpdateToVersion   for "to version:"
    Define CS_DbUpdateTableMissing for "Cannot open the 'DbVersion' table that is used when updating the database! Cannot continue!"
#ENDIF

#IFSAME Language$Current Language$Espanol
    Define CS_UpdateVersion     for "Actualizando base de datos"
    Define CS_UpdateFromVersion for "desde versi¢n"
    Define CS_UpdateToVersion   for "hasta versi¢n:"
    Define CS_DbUpdateTableMissing for "No se puede abrir la tabla 'DbVersion' que se utiliza al actualizar la base de datos! No se puede continuar!"
#ENDIF

#IFSAME Language$Current Language$Norsk
    Define CS_UpdateVersion     for "Oppdaterer database"
    Define CS_UpdateFromVersion for "fra versjon"
    Define CS_UpdateToVersion   for "til versjon:"
    Define CS_DbUpdateTableMissing for "Kan ikke √•pne 'DbVersion'-tabellen som brukes ved oppdatering av databasen! Kan ikke fortsette!"
#ENDIF

#IFSame Language$Current = Language$Russian
    Define CS_UpdateVersion     for "Updating database"
    Define CS_UpdateFromVersion for "from version"
    Define CS_UpdateToVersion   for "to version:"
    Define CS_DbUpdateTableMissing for "Cannot open the 'DbVersion' table that is used when updating the database! Cannot continue!"
#ENDIF

#IFSame Language$Current = Language$Polish
    Define CS_UpdateVersion     for "Updating database"
    Define CS_UpdateFromVersion for "from version"
    Define CS_UpdateToVersion   for "to version:"
    Define CS_DbUpdateTableMissing for "Cannot open the 'DbVersion' table that is used when updating the database! Cannot continue!"
#ENDIF

#IFSame Language$Current = Language$Hungarian
    Define CS_UpdateVersion     for "Updating database"
    Define CS_UpdateFromVersion for "from version"
    Define CS_UpdateToVersion   for "to version:"
    Define CS_DbUpdateTableMissing for "Cannot open the 'DbVersion' table that is used when updating the database! Cannot continue!"
#ENDIF

// *** cDbUpdateHandler.inc Class Language Constants ***
//
#IFSAME Language$Current Language$English
    Define CS_DatabaseInUseShort  for "There are others using the application/database. Are you sure you still want to update the database?"
    Define CS_DatabaseNeedsUpdate for ("The database needs to be updated." + "\n\nATTENTION! The database may not be in use while this work is performed. Make sure that nobody else is using the application before clicking 'Yes' below.\n\n" + "Start update now?")
    Define CS_HeaderUpdateText    for "Important!"
    Define CS_DatabaseInUseText   for "There are others using the application/database or at least one table could NOT be opened exclusively. Please close all other applications using the database and try again. The Application will now close."
    Define CS_WorkingHeaderText   for "Working!"
    Define CS_WorkingUpdateText   for "The database is being updated. Please wait..."
    Define CS_DatabaseUpdatedText for "Ready! The database was updated."
    Define CS_DatabaseCheckedText for "Ready! The database was checked but no updates was needed."
    Define CS_DbUpdatedErrorText  for "One or more errors occured while the database was updated. Please check the logfile.\n\nThe program will now close."
    Define CS_UpdateInProgressTxt for ("System locked!\n\nThe database is being updated. Please try again later...\n\n" * "The program will now close.")
#ENDIF

#IFSAME Language$Current Language$Nederlands
    Define CS_DatabaseInUseShort  for "There are others using the application/database. Are you sure you still want to update the database?"
    Define CS_DatabaseNeedsUpdate for ("De database moet worden bijgewerkt." + "\n\nNB! De database mag niet in gebruik zijn, terwijl deze bewerking wordt uitgevoerd. Zorg ervoor dat niemand anders de toepassing gebruikt voordat u hieronder 'Ja' klikt.\n\n" + "Beginnen met bijwerken?")
    Define CS_HeaderUpdateText    for "Belangrijk!"
    Define CS_DatabaseInUseText   for "Er zijn anderen die de applicatie / database gebruiken of tenminste ÇÇn tabel kan NIET exclusief geopend worden. Sluit alstublieft alle andere applicaties met behulp van de database en probeer het opnieuw. De applicatie zal nu sluiten."
    Define CS_WorkingHeaderText   for "Bezig!"
    Define CS_WorkingUpdateText   for "De database wordt bijgewerkt. Even geduld a.u.b. ..."
    Define CS_DatabaseUpdatedText for "Klaar! De database is bijgewerkt."
    Define CS_DatabaseCheckedText for "Klaar! De database is gecontroleerd, maar er waren geen updates nodig."
    Define CS_DbUpdatedErrorText  for "Er zijn ÇÇn of meerdere fouten opgetreden tijdens het bijwerken van de database. Controleer het logbestand.\n\nHet programma wordt nu beâindigd."
    Define CS_UpdateInProgressTxt for ("Het systeem is vergrendeld!\n\nDe database wordt bijgewerkt. Probeer het later nogmaals...\n\n" * "Het programma wordt nu beâindigd.")
#ENDIF

#IFSAME Language$Current Language$Svenska
    Define CS_DatabaseInUseShort  for "There are others using the application/database. Are you sure you still want to update the database?"
    Define CS_DatabaseNeedsUpdate for ("Databasen behîver uppdateras." + "\n\nOBS! Databasen fÜr ej anvÑndas medan detta arbete sker. Var god och sÑkerstÑll att ingen annan kîr programmet eller pÜ annat sÑtt anvÑnder databasen som anvÑnds fîr programmet innan du klicka pÜ 'Ja' nedan.\n\n" + "Starta uppdateringen nu?")
    Define CS_HeaderUpdateText    for "Viktigt!"
    Define CS_DatabaseInUseText   for "Det verkar finnas andra personer som kîr programmet eller anvÑnder databasen, eftersom Ütminstone en tabell ej kunde îppnas exklisivt. Var vÑnlig stÑng alla andra applikationer som kan anvÑnda databasen och fîrsîk igen. Programmet kommer nu att avslutas."
    Define CS_WorkingHeaderText   for "Arbetar!"
    Define CS_WorkingUpdateText   for "Databasen hÜller pÜ att uppdateras. Var god vÑnta..."
    Define CS_DatabaseUpdatedText for "Klart! Databasen Ñr nu uppdaterad."
    Define CS_DatabaseCheckedText for "Ready! The database was checked but no updates was needed."
    Define CS_DbUpdatedErrorText  for "Ett eller flera fel uppstod tyvÑrr under uppdateringen av databasen. Var god kontrollera fel-loggen.\n\nProgrammet kommer nu att avslutas."
    Define CS_UpdateInProgressTxt for ("Systemet Ñr lÜst!\n\nDatabasen hÜller pÜ att uppdateras. Var god vÑnta och fîrsîk Üter senare...\n\n" * "Programmet kommer nu att avslutas.")
#ENDIF

#IFSAME Language$Current Language$Deutsch
    Define CS_DatabaseInUseShort  for "There are others using the application/database. Are you sure you still want to update the database?"
    Define CS_DatabaseNeedsUpdate for ("Die Datenbank muss aktualisiert werden." + "\n\nNB! Die Datenbank darf wÑhrend dieses Prozesses nicht in Benutzung sein. Stellen Sie sicher, dass niemand das Programm benutzt, bevor Sie unten 'Ja' klicken.\n\n" + "Jetzt starten?")
    Define CS_HeaderUpdateText    for "Wichtig!"
    Define CS_DatabaseInUseText   for "Andere Benutzer benutzen das Programm/die Datenbank. Zumindest eine Tabelle konnte nicht EXCLUSIV geîffnet werden. Bitte schliessen Sie alle anderen Programme, die die Datenbank benutzen und versuchen Sie es erneut. Das Programm wir jetzt beendet."
    Define CS_WorkingHeaderText   for "Arbeite!"
    Define CS_WorkingUpdateText   for "Die Datenbank wird aktualisiert. Bitte warten..."
    Define CS_DatabaseUpdatedText for "Fertig! Die Datenbank ist aktualisiert."
    Define CS_DatabaseCheckedText for "Fertig! Die Datenbank wurde ÅberprÅft, es ist aber keine Aktualisierung notwendig."
    Define CS_DbUpdatedErrorText  for "Ein oder mehrere Fehler sind wÑhrend der Aktualisierung aufgetreten. Bitte schauen Sie in die Log-Datei.\n\nDas Programm wird jetzt beendet."
    Define CS_UpdateInProgressTxt for ("System gesperrt!\n\nDie Datenbank wird aktualisiert. Bitte versuchen Sie es spÑter wieder...\n\n" * "Das Programm wird jetzt beendet.")
#ENDIF

#IFSAME Language$Current Language$Dansk
    Define CS_DatabaseInUseShort  for "There are others using the application/database. Are you sure you still want to update the database?"
    Define CS_DatabaseNeedsUpdate for ("The database needs to be updated." + "\n\nATTENTION! The database may not be in use while this work is performed. Make sure that nobody else is using the application before clicking 'Yes' below.\n\n" + "Start update now?")
    Define CS_HeaderUpdateText    for "Important!"
    Define CS_DatabaseInUseText   for "There are others using the application/database or at least one table could NOT be opened exclusively. Please close all other applications using the database and try again. The Application will now close."
    Define CS_WorkingHeaderText   for "Working!"
    Define CS_WorkingUpdateText   for "The database is being updated. Please wait..."
    Define CS_DatabaseUpdatedText for "Ready! The database was updated."
    Define CS_DatabaseCheckedText for "Ready! The database was checked but no updates was needed."
    Define CS_DbUpdatedErrorText  for "One or more errors occured while the database was updated. Please check the logfile.\n\nThe program will now close."
    Define CS_UpdateInProgressTxt for ("System locked!\n\nThe database is being updated. Please try again later...\n\n" * "The program will now close.")
#ENDIF

#IFSAME Language$Current Language$Portugues
    Define CS_DatabaseInUseShort  for "There are others using the application/database. Are you sure you still want to update the database?"
    Define CS_DatabaseNeedsUpdate for ("O banco de dados precisa ser atualizado." + "\n\nAtenÁ„o! O banco de dados n„o pode ser utilizado enquanto essa tarefa È executada. Certifique-se de que ninguÈm mais esteja utilizando a aplicaÁ„o antes de clicar em 'Sim' abaixo.\n\n" + "Iniciar a atualizaÁ„o agora?")
    Define CS_HeaderUpdateText    for "Importante!"
    Define CS_DatabaseInUseText   for "Existem outros usu·rios usando a aplicaÁ„o/banco de dados ou pelo menos uma tabela n„o pÙde ser aberta em modo exclusivo. Por favor, encerre todas as aplicaÁıes que usam esse banco de dados e tente novamente. Esse Aplicativo ser· encerrado agora."
    Define CS_WorkingHeaderText   for "Trabalhando!"
    Define CS_WorkingUpdateText   for "O banco de dados est· sendo atualizado. Por favor aguarde ..."
    Define CS_DatabaseUpdatedText for "Pronto! O banco de dados foi atualizado."
    Define CS_DatabaseCheckedText for "Pronto! O banco de dados foi verificado mas nenhuma atualizaÁ„o era necess·ria."
    Define CS_DbUpdatedErrorText  for "Um ou mais erros aconteceram enquanto o banco de dados era atualizado. Por favor verifique o arquivo de log.\n\nO programa ser· encerrado."
    Define CS_UpdateInProgressTxt for ("Sistema bloqueado!\n\nO banco de dados est· sendo atualizado. Por favor tente novamente mais tarde...\n\n" * "O programa ser· encerrado.")
#ENDIF

#IFSAME Language$Current Language$Francais
    Define CS_DatabaseInUseShort  for "There are others using the application/database. Are you sure you still want to update the database?"
    Define CS_DatabaseNeedsUpdate for ("The database needs to be updated." + "\n\nATTENTION! The database may not be in use while this work is performed. Make sure that nobody else is using the application before clicking 'Yes' below.\n\n" + "Start update now?")
    Define CS_HeaderUpdateText    for "Important!"
    Define CS_DatabaseInUseText   for "There are others using the application/database or at least one table could NOT be opened exclusively. Please close all other applications using the database and try again. The Application will now close."
    Define CS_WorkingHeaderText   for "Working!"
    Define CS_WorkingUpdateText   for "The database is being updated. Please wait..."
    Define CS_DatabaseUpdatedText for "Ready! The database was updated."
    Define CS_DatabaseCheckedText for "Ready! The database was checked but no updates was needed."
    Define CS_DbUpdatedErrorText  for "One or more errors occured while the database was updated. Please check the logfile.\n\nThe program will now close."
    Define CS_UpdateInProgressTxt for ("System locked!\n\nThe database is being updated. Please try again later...\n\n" * "The program will now close.")
#ENDIF

#IFSAME Language$Current Language$Italiano
    Define CS_DatabaseInUseShort  for "There are others using the application/database. Are you sure you still want to update the database?"
    Define CS_DatabaseNeedsUpdate for ("The database needs to be updated." + "\n\nATTENTION! The database may not be in use while this work is performed. Make sure that nobody else is using the application before clicking 'Yes' below.\n\n" + "Start update now?")
    Define CS_HeaderUpdateText    for "Important!"
    Define CS_DatabaseInUseText   for "There are others using the application/database or at least one table could NOT be opened exclusively. Please close all other applications using the database and try again. The Application will now close."
    Define CS_WorkingHeaderText   for "Working!"
    Define CS_WorkingUpdateText   for "The database is being updated. Please wait..."
    Define CS_DatabaseUpdatedText for "Ready! The database was updated."
    Define CS_DatabaseCheckedText for "Ready! The database was checked but no updates was needed."
    Define CS_DbUpdatedErrorText  for "One or more errors occured while the database was updated. Please check the logfile.\n\nThe program will now close."
    Define CS_UpdateInProgressTxt for ("System locked!\n\nThe database is being updated. Please try again later...\n\n" * "The program will now close.")
#ENDIF

#IFSAME Language$Current Language$Espanol
    Define CS_DatabaseInUseShort  for "There are others using the application/database. Are you sure you still want to update the database?"
    Define CS_DatabaseNeedsUpdate for ("La base de datos necesita ser actualizada." + "\n\nNB! La base datos no puede estar en uso mientras se ejecuta esta tarea. Aseg£rese de que nadie m†s estÇ usando la aplicaci¢n antes de hacer clic en 'S°'.\n\n" + "Iniciar actualizaci¢n ahora")
    Define CS_HeaderUpdateText    for "Importante!"
    Define CS_DatabaseInUseText   for "Hay otros utilizando la aplicaci¢n / base de datos o por lo menos una tabla. No se pudo abrir exclusivamente. Cierre todas las dem†s aplicaciones que utilizan la base de datos y vuelva a intentarlo. La aplicaci¢n se cerrar† ahora."
    Define CS_WorkingHeaderText   for "Trabajando!"
    Define CS_WorkingUpdateText   for "a base de datos se esta actualizando. Por favor espere..."
    Define CS_DatabaseUpdatedText for "Listo! La base de datos fue actualizada."
    Define CS_DatabaseCheckedText for "Listo! Se verific¢ la base de datos y no fue necesario actualizar."
    Define CS_DbUpdatedErrorText  for "Uno o m†s errores ocurrieron mientras se actualizaba la base de datos. Por favor verifique el archivo de registro.\n\nEl programa ser† cerrado ahora."
    Define CS_UpdateInProgressTxt for ("Sistema bloqueado!\n\nLa base de datos est† siendo actualizada. Por favor, intÇntelo de nuevo m†s tarde...\n\n" * "El programa ser† cerrado ahora.")
#ENDIF

#IFSAME Language$Current Language$Norsk
    Define CS_DatabaseInUseShort  for "There are others using the application/database. Are you sure you still want to update the database?"
    Define CS_DatabaseNeedsUpdate for ("Database m√• oppdateres." + "\n\nNB! Databasen m√• ikke v√¶re i bruk mens dette p√•g√•r. P√•se at ingen andre bruker databasen/programmet f√∏r du velger 'Ja' nedenfor.\n\n" + "Starte oppdatering n√•?")
    Define CS_HeaderUpdateText    for "Viktig!"
    Define CS_DatabaseInUseText   for "Andre bruker programmet/databasen, eller minst en tabell kunne IKKE √•pnes eksklusivt. Steng alle andre programmer som bruker databasen og fors√∏k igjen. Programmet avsluttes n√•."
    Define CS_WorkingHeaderText   for "Arbeider!"
    Define CS_WorkingUpdateText   for "Databasen oppdateres. Vennligst vent..."
    Define CS_DatabaseUpdatedText for "Klar! Databasen ble oppdatert."
    Define CS_DatabaseCheckedText for "Klar! Database ble sjekket, men ingen oppdatering var n√∏dvendig."
    Define CS_DbUpdatedErrorText  for "En eller flere feil oppsto under oppdatering av databasen. Sjekk loggfil.\n\nProgrammet avsluttes."
    Define CS_UpdateInProgressTxt for ("System l√•st!\n\nDatabasen blir oppdatert. Pr√∏v igjen senere...\n\n" * "Programmet avsluttes.")
#ENDIF

#IFSame Language$Current = Language$Russian
    Define CS_DatabaseInUseShort  for "There are others using the application/database. Are you sure you still want to update the database?"
    Define CS_DatabaseNeedsUpdate for ("The database needs to be updated." + "\n\nATTENTION! The database may not be in use while this work is performed. Make sure that nobody else is using the application before clicking 'Yes' below.\n\n" + "Start update now?")
    Define CS_HeaderUpdateText    for "Important!"
    Define CS_DatabaseInUseText   for "There are others using the application/database or at least one table could NOT be opened exclusively. Please close all other applications using the database and try again. The Application will now close."
    Define CS_WorkingHeaderText   for "Working!"
    Define CS_WorkingUpdateText   for "The database is being updated. Please wait..."
    Define CS_DatabaseUpdatedText for "Ready! The database was updated."
    Define CS_DatabaseCheckedText for "Ready! The database was checked but no updates was needed."
    Define CS_DbUpdatedErrorText  for "One or more errors occured while the database was updated. Please check the logfile.\n\nThe program will now close."
    Define CS_UpdateInProgressTxt for ("System locked!\n\nThe database is being updated. Please try again later...\n\n" * "The program will now close.")
#ENDIF

#IFSame Language$Current = Language$Polish
    Define CS_DatabaseInUseShort  for "There are others using the application/database. Are you sure you still want to update the database?"
    Define CS_DatabaseNeedsUpdate for ("The database needs to be updated." + "\n\nATTENTION! The database may not be in use while this work is performed. Make sure that nobody else is using the application before clicking 'Yes' below.\n\n" + "Start update now?")
    Define CS_HeaderUpdateText    for "Important!"
    Define CS_DatabaseInUseText   for "There are others using the application/database or at least one table could NOT be opened exclusively. Please close all other applications using the database and try again. The Application will now close."
    Define CS_WorkingHeaderText   for "Working!"
    Define CS_WorkingUpdateText   for "The database is being updated. Please wait..."
    Define CS_DatabaseUpdatedText for "Ready! The database was updated."
    Define CS_DatabaseCheckedText for "Ready! The database was checked but no updates was needed."
    Define CS_DbUpdatedErrorText  for "One or more errors occured while the database was updated. Please check the logfile.\n\nThe program will now close."
    Define CS_UpdateInProgressTxt for ("System locked!\n\nThe database is being updated. Please try again later...\n\n" * "The program will now close.")
#ENDIF

#IFSame Language$Current = Language$Hungarian
    Define CS_DatabaseInUseShort  for "There are others using the application/database. Are you sure you still want to update the database?"
    Define CS_DatabaseNeedsUpdate for ("The database needs to be updated." + "\n\nATTENTION! The database may not be in use while this work is performed. Make sure that nobody else is using the application before clicking 'Yes' below.\n\n" + "Start update now?")
    Define CS_HeaderUpdateText    for "Important!"
    Define CS_DatabaseInUseText   for "There are others using the application/database or at least one table could NOT be opened exclusively. Please close all other applications using the database and try again. The Application will now close."
    Define CS_WorkingHeaderText   for "Working!"
    Define CS_WorkingUpdateText   for "The database is being updated. Please wait..."
    Define CS_DatabaseUpdatedText for "Ready! The database was updated."
    Define CS_DatabaseCheckedText for "Ready! The database was checked but no updates was needed."
    Define CS_DbUpdatedErrorText  for "One or more errors occured while the database was updated. Please check the logfile.\n\nThe program will now close."
    Define CS_UpdateInProgressTxt for ("System locked!\n\nThe database is being updated. Please try again later...\n\n" * "The program will now close.")
#ENDIF
