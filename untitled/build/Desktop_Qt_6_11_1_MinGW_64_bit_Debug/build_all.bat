@echo off
set PATH=D:\qt\Tools\mingw1310_64\bin;%PATH%
cd /d "D:\AAAAAAwork base\untitled\untitled\build\Desktop_Qt_6_11_1_MinGW_64_bit_Debug"
if exist debug rmdir /s /q debug
"D:\qt\6.11.1\mingw_64\bin\qmake.exe" "D:\AAAAAAwork base\untitled\untitled\untitled.pro" -spec win32-g++ CONFIG+=debug CONFIG+=qml_debug > qmake_log.txt 2>&1
"D:\qt\Tools\mingw1310_64\bin\mingw32-make.exe" -j1 > build_log.txt 2>&1
echo EXITCODE=%ERRORLEVEL% >> build_log.txt