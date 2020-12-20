Simple arduino script to act as a custom keyboard controller.

Original plan was to use AutoHotKey to catch the shorcuts and execute custom scripts to interact with programs. After realizing leaving AHK running will get me banned from most video games I had to switch gears, and came up with a short term solution which is to setup hotkeys to shortcuts that run the `hotkeys.ps1` script with the appropriate arguments and flags to start / stop various programs. If another application supports global hotkeys I will use that instead of running through the powershell script, since windows takes a second or two to start the shortcut.

shortcut format is:
C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe -windowstyle hidden -noprofile -ExecutionPolicy Bypass -File {fileLocation}\hotkeys.ps1 --app {APPNAME} {-kill}
