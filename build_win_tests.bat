mkdir .\tests\bin
mkdir .\tests\obj

setlocal enabledelayedexpansion

set build_ok=1
set INCLUDE=%INCLUDE%%cd%\src\;

for /f %%f in ('dir /b ".\tests\%1\*.cpp"') do (
  echo "compiling test %VisualStudioVersion% %%~nf"
  cl -EHsc -W4 -Fo.\tests\obj\%%~nf.obj -c ".\tests\%%f"
  if /I "%ERRORLEVEL%" NEQ "0" (
    %build_ok%=0
  )

  if /I "%build_ok%" NEQ "0" (
    cl /I \%cd%\src\ .\tests\obj\%%~nf.obj -Fe.\tests\bin\%%~nf.exe -link
  )
)

if /I "%build_ok%" NEQ "1" (
  echo "tests build failed"
  exit /B 1
)

del /Q .\tests\obj\*.obj