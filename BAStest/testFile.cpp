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
#include <BAS/BASerror.h>

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

static bool testError(){
   BAS_FUNCTION(testError);
   BASstring Out;
   int ErrorCode = BASreadFile("nonexistent.txt", &Out);
   TEST_NOT_EQUAL(ErrorCode, 0);
   BASstring Error = BASerrorMessage(ErrorCode);
   BAS_VAR(Error);
   return true;
}

void testFile(TESTapp* pApp){
   BAS_FUNCTION(testFile);
   pApp->add("file/readwrite", &testReadWrite);
   pApp->add("file/error", &testError);
   
}
