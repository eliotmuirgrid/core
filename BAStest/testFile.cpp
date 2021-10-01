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

static void testReadWrite(){
   BAS_FUNCTION(testReadWrite);
   BASstring Data = "The quick brown fox jumped over puff.";

   BASfile Source;
   Source.open("dummy.txt", BASfile::Rewrite);
   Source.write(Data);
   Source.close();

   BAS_TRC("Create reader file.");
   BASfile Destination;
   BAS_TRC("Going to open file.");
   Destination.open("dummy.txt", BASfile::Read);
   BAS_TRC("Open");
   BASstring Out;
   int AmountRead = Destination.read(&Out);
   BAS_VAR(Data);
   BAS_VAR(Out);
   BAS_TRC("Test equality");
   BAS_VAR((Data != Out));
   TEST_EQUAL(Data, Out);
   BAS_TRC("Done");
}

void testFile(TESTapp* pApp){
   BAS_FUNCTION(testFile);
   pApp->add("file/readwrite", &testReadWrite);
}
