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
#include <BAS/BASerror.h>
#include <BAS/BASsinkString.h>

typedef void (*TESTappFunc)();

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
      BASsinkString StringSink;\
      BASstream ErrStream(StringSink);\
      ErrStream  << "Expected: " #LHS << " = " << #RHS << newline << "Actual: " << (LHS);\
      throw BASerror(StringSink.string(), 0);\
   }}

#define TEST_NOT_EQUAL(LHS,RHS) { if ((LHS) == (RHS)) {\
      BASsinkString StringSink;\
      BASstream ErrStream(StringSink);\
      ErrStream  << "Expected: " #LHS << " != " << #RHS;\
      throw BASerror(StringSink.string(), 0);\
   }}


#endif
