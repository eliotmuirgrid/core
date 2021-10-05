// C++ tracing sandbox


#include "APPfactorial.h"

#include <BAS/BASargParser.h>
#include <BAS/BAStrace.h>
BAS_TRACE_INIT;   // Need this to initialize tracing.

void APPrepeatSentence(const BASstring& Sentence){
   BAS_FUNCTION(APPrepeatSentence);
   BAS_VAR(Sentence);
   BASstring Result;
   BAS_TRC("About to print hello world...");
   for (int i=0; i < 4; i++){
      BAS_VAR(i);
      Result = Result + Sentence + "\n";
   }
   BAS_HEX("Result", Result.data(), Result.size());
   BASout << Result;
}

int main(int argc, const char** argv){
   BASargParser Parser;
   if (!Parser.parse(argc, argv)){
      Parser.showUsage(BASout);
   }
   BAS_FUNCTION(main);
   BAS_TRC("Going to call APPlocalFunction");
   BASstring Sentence="The quick brown fox jumped over the lazy dog.";
   APPrepeatSentence(Sentence);
   int N = 6;
   BASout << "Factorial  " << N << "! = " << APPfactorial(N) << newline;
   BAS_TRC("All done!");
   return 0;
}
