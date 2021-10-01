//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BASerror
// 
// Implementation
//-------------------------------------------------------

#include "BASerror.h"
#include "BAStrace.h"
BAS_TRACE_INIT;

BASerror::BASerror(const BASstring& Message, int Code) : m_Message(Message), m_Code(Code){
   BAS_METHOD(BASerror::BASerror);
   BAS_VAR(m_Message);
}

BASerror::BASerror(const BASerror& Orig) : m_Message(Orig.m_Message), m_Code(Orig.m_Code) {
   BAS_METHOD(BASerror::BASerror);
   BAS_VAR(m_Message);
}

BASerror::~BASerror(){

}

BASstream& operator<<(BASstream& Stream, const BASerror& Error){
   Stream << "Exception: " << Error.message() << " (" << Error.code() << ")";
   return Stream;
}
