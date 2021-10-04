// APPfoo implementation

#include "APPfoo.h"

#include <BAS/BASstring.h>
#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

APPfoo::APPfoo(){
   BAS_METHOD(APPfoo::APPfoo);
}
APPfoo::~APPfoo(){
   BAS_METHOD(APPfoo::~APPfoo);
}

void APPfoo::run(const BASstring& Value, int Count){
   BAS_METHOD(APPfoo::run);
   BAS_VAR2(Value, Count);
   for (int i=0; i < Count; i++){
      BAS_VAR(i);
      BASout << Value << newline;
   }
}


