//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BASsinkStandardOut
//-------------------------------------------------------

#include "BASsinkStandardOut.h"
#include <stdio.h>

#include "BASfileImp.h"

int BASsinkStandardOut::write(const char* pData, int Size){
   return BASwrite(1, pData, Size);
} 

void BASsinkStandardOut::flush(){
   BASfsync(1);
} 