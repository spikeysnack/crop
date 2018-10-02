@echo off

set "cropdir=C:\Program Files (x86)\Crop"

if not exists %cropdir% ( 
 mkdir "%cropdir%"
 mkdir "%cropdir%\doc"
 xcopy * "%cropdir%"

 xcopy /s doc "%cropdir%\doc"	
)


if not exists "C:\Windows\crop.exe" (
copy crop.exe "C:Windows\crop.exe"
)


if not exists "C:\Windows\cygwin1.dll" (
copy cygwin1.dll "C:Windows\cygwin1.dll"
)

start /k crop.exe 


 




