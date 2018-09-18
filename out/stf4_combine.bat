set outDir=%~dp0
set binDir=%~dp0..\iar\bin
set srecDir=%~dp0..\tools\srec

if exist "%outDir%\mex_gateway_combined.hex" del "%outDir%\mex_gateway_combined.hex"

"%srecDir%\srec_cat" ^
  "%outDir%\m4Bootblock_stf4.hex"  -Intel ^
  "%binDir%\mex_gateway_ecuid.hex"  -Intel ^
  "%binDir%\mex_gateway_cdata.hex"  -Intel ^
  "%binDir%\mex_gateway_Release.hex"  -Intel ^
  -o "%outDir%\mex_gateway_combined.hex" -Intel -disable execution-start-address

pause
