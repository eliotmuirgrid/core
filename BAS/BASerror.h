#ifndef _BAS_ERROR_H__
#define _BAS_ERROR_H__
//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BASerror
// 
// Exception class - KISS design.
//-------------------------------------------------------

#include "BASstring.h"
#include "BASsinkString.h"
#include "BASstream.h"

class BASerror{
public:
   BASerror(const BASstring& Message, int Code);
   BASerror(const BASerror& Orig);
   ~BASerror();

   const BASstring& message() const{ return m_Message; } 
   int code() const                { return m_Code;    }
private:
   int m_Code;
   BASstring m_Message;
};

BASstream& operator<<(BASstream& Stream, const BASerror& Error);

#define BAS_RAISE_ERROR(X, C) {\
      BASsinkString Sink;\
      BASstream Stream(Sink);\
      Stream << X;\
      throw BASerror(Sink.string(), C);\
   }

#endif
