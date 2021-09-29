//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// main.cpp
// 
// What will become a unit test.
//-------------------------------------------------------

#include <BAS/BASstring.h>

#include <stdio.h>

int main(){
   BASstring String;
   String = "Hello world!";
  
   printf("%s\n", String.data());

   return 0;
}
