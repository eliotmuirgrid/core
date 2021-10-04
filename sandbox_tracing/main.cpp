// C++ tracing sandbox


#include <BAS/BASargParser.h>

#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

#include "APPfoo.h"

void APPlocalFunction(){
   BAS_FUNCTION(APPlocalFunction);
   BAS_TRC("About to print hello world...");
   BASout << "Hello world!" << newline;
   BAS_TRC("Printed hello world!");
}

int main(int argc, const char** argv){
   BASargParser Parser;
   if (!Parser.parse(argc, argv)){
      Parser.showUsage(BASout);
   }
   BAS_FUNCTION(main);
   BAS_TRC("Going to call APPlocalFunction");
   APPlocalFunction();
   BAS_TRC("Creating Foo object");
   APPfoo Foo;
   BAS_TRC("About to call run on Foo");
   Foo.run("Rabbit", 5);;
   BAS_TRC("All done!");
   return 0;
}
