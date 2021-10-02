//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// testFile
// 
// Implementation
//-------------------------------------------------------

#include "testFile.h"

#include <TEST/TESTapp.h>
#include <BAS/BAStrace.h>
BAS_TRACE_INIT; 

#include <BAS/BASfile.h>

static bool testReadWrite(){
   BAS_FUNCTION(testReadWrite);
   BASstring Data = "The quick brown fox jumped over puff.";
   BASwriteFile("dummy.txt", Data);
   BASstring Out;
   BASreadFile("dummy.txt", &Out);
   BAS_VAR((Data != Out));
   TEST_EQUAL(Data, Out);
   return true;
}

void testFile(TESTapp* pApp){
   BAS_FUNCTION(testFile);
   pApp->add("file/readwrite", &testReadWrite);
}
