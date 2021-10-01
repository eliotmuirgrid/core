//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// main.cpp
// 
// What will become a unit test.
//-------------------------------------------------------

#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

#include <TEST/TESTapp.h>

int main(int argc, const char** argv){
   TESTapp App;
   return App.run(argc, argv);
}
