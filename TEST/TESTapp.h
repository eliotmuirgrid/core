#ifndef _TEST_APP_H__
#define _TEST_APP_H__
//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// TESTapp
// 
// Light weight testing framework.
//-------------------------------------------------------

#include <BAS/BASavlTree.h>
#include <BAS/BASstream.h>
#include <BAS/BASstring.h>

typedef bool (*TESTappFunc)();

class TESTapp{
public:
   TESTapp(){}
   ~TESTapp(){}

   void add(const BASstring& Path, TESTappFunc pTestFunc);

   int run(int argc, const char** argv);

private:
   BASavlTree<BASstring, TESTappFunc> m_Tests; 
};

#define TEST_EQUAL(LHS,RHS) { if ((LHS) != (RHS)) {\
      BASout  << "Expected: " #LHS << " = " << #RHS << newline << "Actual: " << (LHS);\
      return false;\
   }}

#define TEST_NOT_EQUAL(LHS,RHS) { if ((LHS) == (RHS)) {\
      BASout  << "Expected: " #LHS << " != " << #RHS;\
      return false;\
   }}


#endif
