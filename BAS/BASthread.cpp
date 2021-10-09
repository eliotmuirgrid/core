//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BASthread
// 
// Implementation
//-------------------------------------------------------
#include "BASthread.h"
#include "BAStrace.h"
BAS_TRACE_INIT;

#ifndef _WIN32
#include <pthread.h>


class BASthreadInfo{
public:
   BASthreadInfo(BASthreadProc pProcedure, void* pData) : m_pProc(pProcedure), m_pData(pData) {}   
   BASthreadProc m_pProc;
   void* m_pData;
};

static void* ThreadProc(void* pObject){
   BAS_FUNCTION(ThreadProc);
   BASthreadInfo* pInfo = (BASthreadInfo*)pObject;
   BAS_VAR2(pInfo->m_pProc, pInfo->m_pData);
   (*pInfo->m_pProc)(pInfo->m_pData);
   BAS_TRC("Exited function");
   delete pInfo;
   return 0;
}

void BASthread(BASthreadProc pProcedure, void* pData){
   BAS_FUNCTION(BASthread);
   pthread_t Thread;
   int Result = pthread_create(&Thread, NULL, &ThreadProc, (void*)new BASthreadInfo(pProcedure, pData));
   pthread_detach(Thread);
}

#endif
