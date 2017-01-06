@echo off

//get the date
date >> date.txt

echo --- new backup >> backup.log

Echo Backing up DFM files...
echo --- DFMs >> backup.log
"c:\program files\winzip\wzzip" -^ -u c:\projects\best\backup.zip c:\projects\best\source\*.dfm >> backup.log
If not ErrorLevel 0 Goto error

Echo Backing up H files...
echo --- Hs >> backup.log
"c:\program files\winzip\wzzip" -u c:\projects\best\backup.zip c:\projects\best\source\*.h >> backup.log
If not ErrorLevel 0 Goto error

Echo Backing up CPP files...
echo --- CPPs >> backup.log
"c:\program files\winzip\wzzip" -u c:\projects\best\backup.zip c:\projects\best\source\*.cpp >> backup.log
If not ErrorLevel 0 Goto error

Echo Backing up BPR files...
echo --- BPRs >> backup.log
"c:\program files\winzip\wzzip" -u c:\projects\best\backup.zip c:\projects\best\source\*.bpr >> backup.log
If not ErrorLevel 0 Goto error
goto ok

:error
Echo ERRORS DETECTED. 
echo Backup did not complete!
Goto end

:ok
Echo Completed backup.
Echo Copying to Backup directory on Server...
copy c:\projects\best\backup.zip "\\MNL_SERVER_NT\User Backups\Ian"
echo All done.

:end
Echo Press any key to close the window...
pause >> backup.log