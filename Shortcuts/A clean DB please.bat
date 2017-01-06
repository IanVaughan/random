@echo off

echo Overwriting DB...
copy "c:\projects\best\source\data\clean pop bestdatabase.mdb" c:\projects\best\source\data\BestdataBase.mdb 
if errorlevel 0 goto error
goto ok

:error
echo Failed to copy database!
goto end

:ok
echo Copying QVCS Demo Airspace...
copy c:\projects\best\source\demo.* c:\projects\best\source\data\demo >> clean.log
echo Done OK.

:end
echo Press any key to close this window...
pause >> clean.log
