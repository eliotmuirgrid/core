//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BASutil
//
// Implementation
//-------------------------------------------------------

#include "BASutil.h"
#include "BAStrace.h"
BAS_TRACE_INIT;

#include <time.h>

void BASsleep(int Milliseconds){
   BAS_FUNCTION(BASsleep);
   timespec I;
   I.tv_sec = Milliseconds / 1000;
   I.tv_nsec = (Milliseconds % 1000) * 1000000;
   nanosleep(&I, NULL);
}

