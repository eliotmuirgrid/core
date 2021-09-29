//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BAShex
// 
// Implementation
//-------------------------------------------------------
#include "BAShex.h"

#include "BAStrace.h"
BAS_TRACE_INIT;


void BAShex(int Size, void* pData){
   BAS_FUNCTION(BAShex);
   BAS_VAR2(Size, pData);
   printf("%s", "Life...");
}