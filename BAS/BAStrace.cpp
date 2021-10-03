//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BAStrace
// 
// Implementation
//-------------------------------------------------------

#include "BAStrace.h"
BAS_TRACE_INIT;

#include "BASsinkFile.h"
#include "BASglob.h"
#include "BAShex.h"
#include "BAStimestamp.h"
#include "BASfile.h"
#include "BASsinkFile.h"

#include <time.h>
#include <stdio.h>  // for printf

#include <inttypes.h>
#include <math.h>
#include <string.h>


#ifdef _WIN32
#include <windows.h>
long BASthreadId(){ return (long)GetCurrentThreadId(); }
#else
#include <pthread.h>
long BASthreadId(){ return (long)pthread_self(); }
#endif


BASmutex s_LogMutex;

BASstream BAStrace(new BASsinkFile(1), false);  // purposely leaked.

static thread_local int s_BASindentLevel=0;

// TODO - how do we get millisecond timing?
void  BAStimeStampOld() {
   time_t t = time(NULL);
   struct tm* tm = localtime(&t);
   char s[64];
   strftime(s, sizeof(s), "T %H:%M:%S ", tm);
   BAStrace << s;
}

void BAStimeStamp(const char* pModule){
   BAStimestamp Time = BAScurrentTime();
   struct tm* tm = localtime(&Time.Seconds);
   char s[64];
   strftime(s, sizeof(s), "T %H:%M:%S", tm);  // prepend newline.
   BAStrace << s << ".";
   char Buffer[3];
   int ms = Time.Microseconds / 1000;
   sprintf(Buffer,"%03i", ms);  // zero pad the millseconds
   BAStrace << Buffer << " " << (void*)BASthreadId() << " ";
   BAStrace << pModule << " ";  // TODO should output size.
   BASwriteIndent(BAStrace.sink(), s_BASindentLevel);
}

BASmodule::BASmodule(const char* pFileName){
   int Length = strlen(pFileName)-4;
   strncpy(ModuleName, pFileName, Length);
   char* pEnd = ModuleName + sizeof(ModuleName)-2;
   for (char* i = ModuleName + Length; i != pEnd; i++){
      *i = ' ';
   }
   ModuleName[sizeof(ModuleName)-1] = 0;
}

static const char* s_TracePattern = "";

void BASsetTracePattern(const char* pPattern){
   BASout << "### Tracing files matching: " << pPattern << newline;
   s_TracePattern = strdup(pPattern);  // purposely leaked.
}

void BASsetTraceFile(const char* FileName){
   int ErrorCode;
   int FileHandle = BASfileOpen(FileName, BASFrewrite,&ErrorCode);
   BAStrace.setSink(new BASsinkFile(FileHandle));  // Does it matter that we don't close the file handle?
   BASout << "### Tracing redirected into " << FileName << newline;
}

bool BASloggingEnabled(const char* ModuleName, int* pResult){
   if (BASglobMatch(ModuleName, s_TracePattern)){
      *pResult = 1;
      return true;
   } else {
      *pResult = -1;
      return false;
   }
}

BASraiiFunc::BASraiiFunc(const char* Name, const char* pModule, int Line, bool Trace) : m_pModule(pModule), m_pName(Name), m_Trace(Trace) {
   if (Trace){
      BASlocker Lock(s_LogMutex);
      BAStimeStamp(pModule); BAStrace << ">" << Name << " Line:" << Line << newline;
      s_BASindentLevel++;
   }
}

BASraiiFunc::BASraiiFunc(const char* Name, const char* pModule, int Line, const void* pInstance, bool Trace) : m_pModule(pModule), m_pName(Name), m_Trace(Trace) {
   if (Trace){
      BASlocker Lock(s_LogMutex);
      BAStimeStamp(pModule); BAStrace << ">" << Name << " Line:" << Line << " this=" << pInstance << newline;
      s_BASindentLevel++;
   }
}

BASraiiFunc::~BASraiiFunc(){
   if (m_Trace){
      s_BASindentLevel--;
      BASlocker Lock(s_LogMutex);
      BAStimeStamp(m_pModule); BAStrace << "<" << m_pName << newline;
   }
}

#define G ". . . . . . . . . . . . . . . . . . . . . . . . . "
static const char* s_pIndent = G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G;

void BASwriteIndent(BASsink* pSink, int Level){
   pSink->write(s_pIndent, Level*2);
}


void BAShexTrace(int Size, const void* pBuffer, BASstream& Stream){
   Stream << " (size=" << Size << ")" << newline;
   BAShex(Size, pBuffer, Stream.sink(), 60);
}
