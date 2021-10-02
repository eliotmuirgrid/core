//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BASerror
// 
// Implementation
//-------------------------------------------------------

#include "BASerror.h"
#include "BASstring.h"
#include "BAStrace.h"
BAS_TRACE_INIT;

#include <errno.h>

BASstring BASerrorMessage(int ErrorCode){
   BAS_FUNCTION(BASerrorMessage);
   BASstring Result;
   Result.setCapacity(255);
   strerror_r(ErrorCode, Result.data(), Result.capacity());
   Result.setSize(strlen(Result.data()));
   BAS_VAR2(ErrorCode, Result);
   return Result;
}
