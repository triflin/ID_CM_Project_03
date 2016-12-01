REM - Clean .lib files
del IDLib-dist\lib-x86\* /Q
del IDLib-dist\lib-x64\* /Q

REM - Clean intermediate files
del IDLib\Debug\* /Q
del IDLib\Release\* /Q
del IDLib\x64\Debug\* /Q
del IDLib\x64\Release\* /Q

REM - Delete Intellisense DB File
del SocketLib.VC.db