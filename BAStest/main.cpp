//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// main.cpp
// 
// What will become a unit test.
//-------------------------------------------------------

#include <BAS/BASstring.h>
#include <BAS/BASstream.h>

#include <stdio.h>

int main(){
   BASout << "ggg" << newline;
   BASstring String;
   String = "Hello world!";
  
   printf("%s\n", String.data());

   return 0;
}
