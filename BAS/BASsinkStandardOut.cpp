//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BASsinkStandardOut
//-------------------------------------------------------

#include "BASsinkStandardOut.h"
#include <stdio.h>

#ifdef _WIN32
   #include <io.h>
   #define BASfsync _commit
   #define BASwrite _write
#else
   #include <unistd.h>
   #define BASfsync ::fsync
   #define BASwrite ::write
#endif

void BASsinkStandardOut::write(const char* pData, int Size){
   BASwrite(1, pData, Size);
} 

void BASsinkStandardOut::flush(){
   BASfsync(1);
} 