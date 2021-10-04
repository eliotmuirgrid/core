// C++ tracing sandbox


#include <BAS/BASargParser.h>

#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

#include "APPfoo.h"

void APPlocalFunction(){
   BAS_FUNCTION(APPlocalFunction);
   BASout << "Hello world!" << newline;
}

int main(int argc, const char** argv){
   BASargParser Parser;
   if (!Parser.parse(argc, argv)){
      Parser.showUsage(BASout);
   }
   BAS_FUNCTION(main);
   APPlocalFunction();
   APPfoo Foo;
   Foo.run("Rabbit", 5);;

   return 0;
}
