[Setup]
AppName=My Tic-Tac-Toe Game
AppVerName=My Tic-Tac-Toe Game Version 1.0 by AATHI S
AppVersion=1.0
DefaultDirName={pf}\MyTicTacToeGame
DefaultGroupName=Tic-Tac-Toe Game
OutputDir=userdocs:Inno Setup Output
OutputBaseFilename=TicTacToeInstaller

[Files]
[Files]
; Only copy the file a.exe, don't recreate the full path structure
Source: "a.exe*"; DestDir: "{app}"; Flags: ignoreversion
Source: "SDL2.dll*"; DestDir: "{app}"; Flags: ignoreversion

; Copy all files from assets directory to resources subfolder inside the installation folder
Source: "Z:/home/darkemperor/aathi/my-learnig-path-/TIC_TAC_TOE/usr/share/doc/assets\*"; DestDir: "{app}\resources"; Flags: ignoreversion recursesubdirs

; Copy the icon file, no extra folder structure
Source: "app.ico"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\Tic-Tac-Toe Game"; Filename: "{app}\a.exe"; IconFilename: "{app}\app.ico"

[Run]
Filename: "{app}\a.exe"; Description: "Launch Tic-Tac-Toe Game"; Flags: nowait postinstall skipifsilent

