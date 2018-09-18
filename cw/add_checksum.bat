:: This MS-DOS batch file adds a SLE control-Application software checksum to the "s-record" file
:: created by CodeWarior.  The argument to this batch file is the "s-record" file created by CodeWarrior.

:: To automatically include this files execution into the CodeWarrior build process...
::
:: 1) Add the "BatchRunner PostLinker" under the "Target"->"Target Settings"->"Post-linker" setting.
:: 2) Under the setting "Linker"->"BatchRunner Postlinker", choose this file and select the
::    "Pass linker output file as %1 parameter to batch file" checkbox.
@echo off

:: checksum address range
set SW_AR=0x006000..0x3CBFFD
set CD_AR=0x004200..0x3DBFFD

:: checksum address
set SW_CAD=0x3CBFFE
set CD_CAD=0x3DBFFE

:: checksum addresses (within the checksum address range) to exclude
set X0=0x006000..0x007FFF
set X1=0x008000..0x387FFF
set X1a=0x008000..0x307FFF
set X1b=0x30C000..0x317FFF
set X1c=0x31C000..0x327FFF
set X1d=0x32C000..0x337FFF
set X1e=0x33C000..0x347FFF
set X1f=0x34C000..0x357FFF
set X1g=0x35C000..0x367FFF
set X1h=0x36C000..0x377FFF
set X1i=0x37C000..0x387FFF
set X2=0x38C000..0x397FFF
set X3=0x39C000..0x3A7FFF
set X4=0x3AC000..0x3B7FFF
set X5=0x3BC000..0x3C7FFF
set X6=0x3CC000..0x3D7FFF

set X1_XCLUD=-cx %X1a% -cx %X1b% -cx %X1c% -cx %X1d% -cx %X1e% -cx %X1f% -cx %X1g% -cx %X1h% -cx %X1i% 

set SW_CHKSUM_XCLUD=%X1_XCLUD% -cx %X2% -cx %X3% -cx %X4% -cx %X5% 
set CD_CHKSUM_XCLUD=-cx 0x006000..0x3D7FFF

set P3B_XCLUD=-x 0x3B8000..0x3BBFFF 
set P3A_XCLUD=-x 0x3A8000..0x3ABFFF 
set P39_XCLUD=-x 0x398000..0x39BFFF 
set P38_XCLUD=-x 0x388000..0x38BFFF 
set P37_XCLUD=-x 0x378000..0x37BFFF 
set P36_XCLUD=-x 0x368000..0x36BFFF 
set P35_XCLUD=-x 0x358000..0x35BFFF 
set P34_XCLUD=-x 0x348000..0x34BFFF 
set P33_XCLUD=-x 0x338000..0x33BFFF 
set P32_XCLUD=-x 0x328000..0x32BFFF 
set P31_XCLUD=-x 0x318000..0x31BFFF 
set P30_XCLUD=-x 0x308000..0x30BFFF 

set F04_XCLUD=-x 0x006000..0x007FFF
set F10_XCLUD=-x 0x3D8000..0x3DBFFF
set F11_XCLUD=-x 0x3C8000..0x3CBFFF
set F12_XCLUD=%P3B_XCLUD% %P3A_XCLUD% %P39_XCLUD% %P38_XCLUD% 
set F13_XCLUD=%P37_XCLUD% %P36_XCLUD% %P35_XCLUD% %P34_XCLUD% %P33_XCLUD% %P32_XCLUD% %P31_XCLUD% %P30_XCLUD%

set BB_XCLUD=-x 0x00C000..0x00FFFF -x 0x004000..0x0041FF
set SW_XCLUD=%F04_XCLUD%  %F11_XCLUD%  %F12_XCLUD% %F13_XCLUD%
set CD_XCLUD=-x 0x004200..0x005FFF %F10_XCLUD%

set SIZE=-size 3952

:: remove any double-quote characters from the argument %1
set arg1=%1
set arg1=%arg1:"=%

echo on

:: "xtool" input files need an extension of ".sre" or ".hex"  
copy "%arg1%.s19" temp.sre

set XPATH=..\..\tools\xtool\
set SW_XARGS=%SIZE% -chksum wwi %SW_AR% %SW_CAD% %SW_CHKSUM_XCLUD%   
set CD_XARGS=%SIZE% -chksum wwi %CD_AR% %CD_CAD% %CD_CHKSUM_XCLUD%



:: -> add correct application code checksum
%XPATH%xtool temp.sre  -S %SW_XARGS%               > temp2.sre

:: -> add correct constant data section checksum
%XPATH%xtool temp2.sre -S %CD_XARGS%               > temp3.sre

	 


:: -> Create a Motorola "s-record" and Intel ".hex" file containing the correct checksum.  
%XPATH%xtool temp3.sre -S  %SIZE%                       > "%arg1%.s19"
%XPATH%xtool temp3.sre -:4 %SIZE%                       > "%arg1%.hex"
%XPATH%xtool temp3.sre -S  %SIZE% %BB_XCLUD%            > "ap_%arg1%.s19"
%XPATH%xtool temp3.sre -:4 %SIZE% %BB_XCLUD%            > "ap_%arg1%.hex"
%XPATH%xtool temp3.sre -S  %SIZE% %BB_XCLUD% %CD_XCLUD% > "sw_%arg1%.s19"
%XPATH%xtool temp3.sre -:4 %SIZE% %BB_XCLUD% %CD_XCLUD% > "sw_%arg1%.hex"
%XPATH%xtool temp3.sre -S  %SIZE% %BB_XCLUD% %SW_XCLUD% > "cd_%arg1%.s19"
%XPATH%xtool temp3.sre -:4 %SIZE% %BB_XCLUD% %SW_XCLUD% > "cd_%arg1%.hex"


del temp.sre  
del temp2.sre
del temp3.sre


@echo Successfully created flash memory image files:

@echo   SLE control- flash image                file:    "%arg1%.*"
@echo   SLE control- (code+const, emask:0x3DF0) file: "ap_%arg1%.*"
@echo   SLE control- (code      , emask:0x3810) file: "sw_%arg1%.*"
@echo   SLE control- (     const, emask:0x05E0) file: "cd_%arg1%.*"


@pause

