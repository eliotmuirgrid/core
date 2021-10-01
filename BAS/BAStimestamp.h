#ifndef _BAS_TIMESTAMP_H_
#define _BAS_TIMESTAMP_H_
//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BAStimestamp
// 
// Core timestamp
//-------------------------------------------------------

#include "BAStypes.h"

class BAStimestamp{
public:
   BASint64 Seconds;
   BASint64 NanoSeconds;
};

// Think for a POD this is neglible overhead.
BAStimestamp BAScurrentTime();

#endif
