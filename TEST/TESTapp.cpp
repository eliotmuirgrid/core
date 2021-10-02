//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// TESTapp
// 
// Implementation
//-------------------------------------------------------

#include "TESTapp.h"
#include <BAS/BASargParser.h>
#include <BAS/BASglob.h>
#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

#include <stdlib.h>

void TESTapp::add(const BASstring& Path, TESTappFunc pTestFunc){
   BAS_METHOD(TESTapp::add);
   m_Tests.add(Path, pTestFunc); 
}

static void showTests(const BASavlTree<BASstring, TESTappFunc>& Tests){
   BAS_FUNCTION(showTests);
   BASout << "Tests defined:" << newline;
   auto i =Tests.cbegin(); auto end = Tests.cend();
   for (; i != end; ++i){
      BASout << i.key() << newline;
   }
}

static void runTests(const BASavlTree<BASstring, TESTappFunc>& Tests){
   if (Tests.size() ==0){
      return;
   }
   auto End = Tests.cend();
   for (auto i = Tests.cbegin(); i != End; ++i){
       BASout << "Running " << i.key() << "...";
       TESTappFunc pTestFunc = i.value();
       BAS_VAR(pTestFunc);
       if ((*pTestFunc)()){  // Run the test.
         BASout << "OK" << newline;
      } else { 
        BASout << "FAILED" << newline;
       }
   }
   BASout << newline;
}

static void runFilteredTests(const BASavlTree<BASstring, TESTappFunc>& Tests, const BASstring& Match){
   BAS_FUNCTION(runFilteredTests);

   BASavlTree<BASstring, TESTappFunc> Subset;
   auto End = Tests.cend();
   for (auto i = Tests.cbegin(); i != End; ++i){
      if (BASglobMatch(i.key().data(), Match.data())){
         Subset.add(i.key(), i.value());
      }
   }
   if (Subset.size() > 0){
      BASout << "Running " << Subset.size() << " of " << Tests.size() << " tests." << newline;
      runTests(Subset);
   } else {
      BASout << "No tests matched " << Match << newline;
      showTests(Tests);

   }
}

static void addFlags(BASargParser* pParser){
   BAS_FUNCTION(addFlags);
   pParser->addFlag("show", "Show the list of tests.");
   pParser->addArgFlag("test", "glob", "Specify test or group of tests to run with a glob matching expression.  i.e. --test \"string*\"");
}


int TESTapp::run(int argc, const char** argv){
   BAS_METHOD(TESTapp::run);
   BASargParser Parser;
   addFlags(&Parser);
   if (!Parser.parse(argc, argv)){
      BASout << "Unit test application." << newline;
      Parser.showUsage(BASout);
      return EXIT_FAILURE;
   }

   if (Parser.present("show")){
      showTests(m_Tests);
      return EXIT_SUCCESS;
   }
   if (Parser.present("test")){
      runFilteredTests(m_Tests, Parser.flagArg("test"));
      return EXIT_SUCCESS;
   }

   BASout << "Running " << m_Tests.size() << " tests." << newline;
   runTests(m_Tests);

   return EXIT_SUCCESS;
}



