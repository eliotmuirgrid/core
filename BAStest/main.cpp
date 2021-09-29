//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// main.cpp
// 
// What will become a unit test.
//-------------------------------------------------------

#include <BAS/BAStrace.h>
BAS_TRACE_INIT;


#include <BAS/BASstring.h>
#include <BAS/BASstream.h>
#include <BAS/BAShex.h>
#include <BAS/BASsinkStandardOut.h>



#include <stdio.h>

int main(){
   //BASsetTracePattern("*");
   BASout << "Hello world..." << newline;
   BASsinkStandardOut Sink;
   BASstring Me = "Hello world...";

   BAShex(Me.size(), Me.data(), &Sink);

   return 0;
}
