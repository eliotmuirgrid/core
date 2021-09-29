//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BAStrace
// 
// Implementation
//-------------------------------------------------------

#include "BAStrace.h"
BAS_TRACE_INIT;

#include "BASsinkStandardOut.h"
#include "BASglob.h"

#include <time.h>
#include <stdio.h>  // for printf

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

BASmutex s_LogMutex;

BASstream BAStrace(new BASsinkStandardOut(), false);  // purposely leaked.

static thread_local int s_BASindentLevel=0;

// TODO - how do we get millisecond timing?
void  BAStimeStampOld() {
   time_t t = time(NULL);
   struct tm* tm = localtime(&t);
   char s[64];
   strftime(s, sizeof(s), "T %H:%M:%S ", tm);
   BAStrace << s;
}

long BASthreadId(){
   return (long)pthread_self();
}

void BAStimeStamp(const char* pModule){
   int            ms; // Milliseconds
   time_t          t;  // Seconds
   struct timespec spec;

   clock_gettime(CLOCK_REALTIME, &spec);

   t  = spec.tv_sec;
   ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
   if (ms > 999) {
       t++;
       ms = 0;
   }
   struct tm* tm = localtime(&t);
   char s[64];
   strftime(s, sizeof(s), "\nT %H:%M:%S", tm);  // prepend newline.
   BAStrace << s << ".";
   char Buffer[3];
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
   s_TracePattern = strdup(pPattern);  // purposely leaked.
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
      BAStimeStamp(pModule); BAStrace << ">" << Name << " Line:" << Line;
      s_BASindentLevel++;
   }
}

BASraiiFunc::BASraiiFunc(const char* Name, const char* pModule, int Line, const void* pInstance, bool Trace) : m_pModule(pModule), m_pName(Name), m_Trace(Trace) {
   if (Trace){
      BASlocker Lock(s_LogMutex);
      BAStimeStamp(pModule); BAStrace << ">" << Name << " Line:" << Line << " this=" << pInstance;
      s_BASindentLevel++;
   }
}

BASraiiFunc::~BASraiiFunc(){
   if (m_Trace){
      s_BASindentLevel--;
      BASlocker Lock(s_LogMutex);
      BAStimeStamp(m_pModule); BAStrace << "<" << m_pName;
   }
}

#define G ". . . . . . . . . . . . . . . . . . . . . . . . . "
static const char* s_pIndent = G G G G G G G G G G G G G G G G G G G G G G G G G G G G G G;

void BASwriteIndent(BASsink* pSink, int Level){
   pSink->write(s_pIndent, Level*2);
}
