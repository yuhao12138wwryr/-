@echo off

set MATLAB=D:\MATLAB2017b

cd .

if "%1"=="" ("D:\MATLAB2017b\bin\win64\gmake"  -f testangle_rtw.mk all) else ("D:\MATLAB2017b\bin\win64\gmake"  -f testangle_rtw.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
An_error_occurred_during_the_call_to_make
