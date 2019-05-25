mkdir .\tests\bin
mkdir .\tests\obj

setlocal enabledelayedexpansion

set "build_ok=true"
set INCLUDE=%INCLUDE%%cd%\src\;

call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\vsvars32.bat"

for /f %%f in ('dir /b ".\tests\%1\*.cpp"') do (
  echo "compiling test %VisualStudioVersion% %%~nf"
  cl -EHsc -W4 -Fo.\tests\obj\%%~nf.obj -c ".\tests\%1\%%f"
  IF ERRORLEVEL 1 (
    set "build_ok=false"
  )

  if "%build_ok%" == "true" (
    cl /I \%cd%\src\ .\tests\obj\%%~nf.obj -Fe.\tests\bin\%%~nf.exe -link
    IF ERRORLEVEL 1 (
      set "build_ok=false"
    )
  )
)

if "%build_ok%" == "false" (
  echo "tests build failed"
  exit /B 1
)

del /Q .\tests\obj\*.obj