//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BAStimestamp
// 
// Implementation
//-------------------------------------------------------
#include "BAStimestamp.h"

#include <time.h>

BAStimestamp BAScurrentTime(){
   struct timespec spec;
   clock_gettime(CLOCK_REALTIME, &spec);
   BAStimestamp Timestamp;
   Timestamp.Seconds = spec.tv_sec;
   Timestamp.NanoSeconds = spec.tv_nsec;
   return Timestamp;
}