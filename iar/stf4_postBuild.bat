:: Fill and checksum an IAR elf file and then convert to Intel Hex.
:: Example Usage, add one of these lines to the IAR EWARM IDE (Build Actions -> Post-build)
::  BB:
::    "$PROJ_DIR$\stf4_postBuild.bat" "$PROJ_DIR$\bin" "$TOOLKIT_DIR$" "$TARGET_PATH$" 0x08000000 0x08007FFF
::  ID:
::    "$PROJ_DIR$\stf4_postBuild.bat" "$PROJ_DIR$\bin" "$TOOLKIT_DIR$" "$TARGET_PATH$" 0x08008000 0x0800BFFF
::  CD:
::    "$PROJ_DIR$\stf4_postBuild.bat" "$PROJ_DIR$\bin" "$TOOLKIT_DIR$" "$TARGET_PATH$" 0x08010000 0x0803FFFF
::  AP:
::    "$PROJ_DIR$\stf4_postBuild.bat" "$PROJ_DIR$\bin" "$TOOLKIT_DIR$" "$TARGET_PATH$" 0x08040000 0x080FFFFF

set srecDir="%~dp0..\tools\srec"
set outDir=%1
set iarBinDir=%2\bin
set iarOutFile=%3
set outFile=%outDir%\%~n3.hex
set startAddr=%4
set endAddr=%5

if not exist %outDir% mkdir %outDir%
if exist %outFile% del %outFile%

%iarBinDir%\ielftool --fill 0xFF;%startAddr%-%endAddr% %iarOutFile% %iarOutFile%
%iarBinDir%\ielftool --checksum=__checksum:4,sum32:2;%startAddr%-%endAddr% %iarOutFile% %iarOutFile%
%iarBinDir%\ielftool --ihex %iarOutFile% %outFile%

REM Cleanup IAR's intel hex file
%srecDir%\srec_cat %outFile% -Intel -o %outFile% -Intel -disable execution-start-address

REM Unfilling memory
%srecDir%\srec_cat %outFile% -Intel -unfill 0xFF 16 -o %outFile% -Intel
