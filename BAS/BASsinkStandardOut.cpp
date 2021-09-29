//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BASsinkStandardOut
//-------------------------------------------------------

#include "BASsinkStandardOut.h"

#include <unistd.h>

BASsinkStandardOut::BASsinkStandardOut(){

}

BASsinkStandardOut::~BASsinkStandardOut(){

}

void BASsinkStandardOut::write(const char* pData, int Size){
   ::write(STDOUT_FILENO, pData, Size);
} 

void BASsinkStandardOut::flush(){
   fsync(STDOUT_FILENO);
}