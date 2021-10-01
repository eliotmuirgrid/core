//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// testString
// 
// Implementation
//-------------------------------------------------------

#include "testString.h"

#include <TEST/TESTapp.h>
#include <BAS/BAStrace.h>
BAS_TRACE_INIT; 

static void testChangeCapacity(){
   BAS_FUNCTION(testChangeCapacity);
   BASstring A = "ABC";
   A.setCapacity(8); // short --> short
   TEST_EQUAL(A.capacity(), 8);
   TEST_EQUAL(A.size(), 3);
   TEST_EQUAL(A, "ABC");
   A.setCapacity(16); // short --> short
   TEST_EQUAL(A.capacity(), 16);
   TEST_EQUAL(A.size(), 3);
   TEST_EQUAL(A, "ABC");
   A.setCapacity(32); // short --> long
   TEST_EQUAL(A.capacity(), 32);
   TEST_EQUAL(A.size(), 3);
   TEST_EQUAL(A, "ABC");
   A.setCapacity(64); // long --> long
   TEST_EQUAL(A.capacity(), 64);
   TEST_EQUAL(A.size(), 3);
   TEST_EQUAL(A, "ABC");
   A.setCapacity(8); // long --> short
   TEST_EQUAL(A.capacity(), 8);
   TEST_EQUAL(A.size(), 3);
   TEST_EQUAL(A, "ABC");
}

static void testGrowToNonShort(){
   BAS_FUNCTION(testGrowToNonShort);
   BASstring Short;
   Short.append("1234567890");
   Short.append("1234567890");
   Short.append("1234567890");
   TEST_EQUAL(Short, "123456789012345678901234567890");
}

static void testAppend(){
   BAS_FUNCTION(testAppend);
   BASstring A= "0123456789012345";
   A += "6";
   A += "7";
   A += "8";
   A += "9";
}

static void testEqual(){
   BAS_FUNCTION(testEqual);
   BASstring A = "Foo";
   BASstring B = "Foo";
   BASstring C = "Bar";
   TEST_EQUAL(A==B, true);
   TEST_EQUAL(A==C, false);
}

void testString(TESTapp* pApp){
   BAS_FUNCTION(testString);
   pApp->add("string/grow/nonshort", &testGrowToNonShort);
   pApp->add("string/grow/capacity", &testChangeCapacity);
   pApp->add("string/append", &testAppend);
   pApp->add("string/equal", &testEqual);
}
