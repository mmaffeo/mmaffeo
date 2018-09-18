// At startup the commands written below will be executed

// Note(s): 
//   -> The "NOPROGRESSBAR" option appears to function as a "PROGRESSBAR" option.
//   -> The ".s19" file is an image of the entire flash memory (bootblock and application)
//      containing a vaild application code checksum.


LOAD "bin\MX_Gateway.abs.s19"    CODEONLY NOPROGRESSBAR NOPRELOADCMD NOPOSTLOADCMD
LOAD "bin\MX_Gateway.abs"       SYMBOLSONLY NOPROGRESSBAR NOPRELOADCMD NOPOSTLOADCMD

RESET