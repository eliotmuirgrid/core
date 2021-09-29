#ifndef _BAS_SINK_STANDARD_OUT_H_
#define _BAS_SINK_STANDARD_OUT_H_
//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BASsinkStandardOut
// 
// Sink which writes to standard out.
//-------------------------------------------------------

#include "BASsink.h"

class BASsinkStandardOut : public BASsink{
public:
   BASsinkStandardOut();
   virtual ~BASsinkStandardOut();

   virtual void write(const char* pData, int Size); 
   virtual void flush();
};

#endif
