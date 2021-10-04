//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BASargParser
// 
// Implementation
//-------------------------------------------------------

#include "BASargParser.h"

#include <string.h>

#include "BAStrace.h"
BAS_TRACE_INIT;

// We hard code tracing into the BASargParser
static void initTracingFlags(BASargParser* pParser){
   pParser->addArgFlag("trace", "glob", "Turn on debug tracing of C++ code using glob match expression for files. i.e. --trace \"* -BASstring\" (match everything, exclude BASstring).");
   pParser->addArgFlag("out", "filename", "Redirect tracing output to a file.");
}

static void activateTracing(BASargParser* pParser){
   if (pParser->present("out"))  { BASsetTraceFile(pParser->flagArg("out").data());     }
   if (pParser->present("trace")){ BAStrace(pParser->flagArg("trace").data());}
}

BASargParser::BASargParser(){
   BAS_METHOD(BASargParser::BASargParser);
   initTracingFlags(this);
}

BASargParser::~BASargParser(){
   BAS_METHOD(BASargParser::~BASargParser);
}

void BASargParser::addArgFlag(const BASstring& Name, const BASstring& Arg, const BASstring& Description){
   BAS_METHOD(BASargParser::addArgFlag);
   m_Flags.add(Name, LineInfo(Description, Arg));
}

void BASargParser::addFlag(const BASstring& Name, const BASstring& Description){
   BAS_METHOD(BASargParser::addFlag);
   m_Flags.add(Name, LineInfo(Description));
}

void BASargParser::showUsage(BASstream& Stream) const{
   BAS_METHOD(BASargParser::showUsage);
   Stream << "Usage:" << newline
          << " " << m_Bin;
   for(auto i=m_Flags.cbegin(); i != m_Flags.cend(); ++i){
      Stream << " --" << i.key();
      if (i.value().HasArgument){
         Stream << " <" << i.value().Arg << ">";
      }
   }
   Stream << newline << "Flags:" << newline;
   for(auto i=m_Flags.cbegin(); i != m_Flags.cend(); ++i){
       Stream << "   --" << i.key();
       if (i.value().HasArgument){
          Stream << " <" << i.value().Arg << ">";
       }
       Stream << " " << i.value().Description << newline;
   }
   Stream << newline;
}

bool BASargParser::parse(int argc, const char** argv){
   BAS_METHOD(BASargParser::parse);
   BAS_VAR(argv[0]);
   m_Bin = argv[0];
   int i = 1;
   while (i < argc){
      BAS_VAR(argv[i]);
      if (strlen(argv[i]) >= 3){
         if (argv[i][0] == '-' && argv[i][1] == '-'){
            BAS_TRC("Found flag.");
            BASstring Flag(((char*)argv[i])+2);
            BAS_VAR(Flag);
            if (m_Flags.has(Flag)){
               m_Flags.value(Flag).Present = true;
               if (m_Flags.value(Flag).HasArgument){
                 i++;
                 if (i < argc){
                     m_Flags.value(Flag).ArgValue = argv[i];
                 } else {
                     return false;
                }
               }
            } else {
               return false;
            }
         }
      }
      i++;
   }
   activateTracing(this);

   return true;
}

BASstream& operator<<(BASstream& Stream, const BASargParser& Parser){
   Parser.showUsage(Stream);
   return Stream;
}