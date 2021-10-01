//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BASsinkStandardOut
//-------------------------------------------------------

#include "BASsinkStandardOut.h"
#include <io.h>
#include <stdio.h>

#ifdef _WIN32
#define fsync _commit
#endif

BASsinkStandardOut::BASsinkStandardOut(){

}

BASsinkStandardOut::~BASsinkStandardOut(){

}

void BASsinkStandardOut::write(const char* pData, int Size){
   ::write(1, pData, Size);
} 

void BASsinkStandardOut::flush(){
   fsync(1);
}