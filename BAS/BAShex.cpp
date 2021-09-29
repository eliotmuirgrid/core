//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BAShex
// 
// Implementation
//-------------------------------------------------------
#include "BAShex.h"

#include "BASsink.h"

#include "BAStrace.h"
BAS_TRACE_INIT;

void BASwriteCharacter(char Char, BASsink* pSink){
   BAS_FUNCTION(BASwriteCharacter);
   int High = (Char & 0xF0) >> 4 ;
   int Low = Char & 0xF;
   BAS_VAR2(High, Low);
   char Buffer[3];
   Buffer[0] =  High <= 10 ? '0' + High : 'A' + High -10;
   Buffer[1] =  Low <= 10 ? '0' + Low : 'A' + Low -10;
   Buffer[2] = ' ';
   pSink->write(Buffer, 3);
}


void BAShex(int Size, const char* pData, BASsink* pSink){
   BAS_FUNCTION(BAShex);
   BAS_VAR2(Size, pData);
   for (int j=0; j < Size; j+=8){
      for (int i=j; i < j+8; i++){
         BASwriteCharacter(pData[i], pSink);
      }
      pSink->write(pData + j, 8);
      pSink->write("\n", 1);
   }
   pSink->write("\n", 1);
}