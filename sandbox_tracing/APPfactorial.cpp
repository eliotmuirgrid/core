// Recurse - an example recursive function to see tracing work
// The problem doesn't really warrant recursion but it's good to see
// it in action.
#include "APPfactorial.h"

#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

int APPfactorial(int N){
   BAS_FUNCTION(APPfactorial);
   BAS_VAR(N);
   if (N == 1){
      BAS_TRC("Ending recursion");
      return 1;   
   }
   int Result = N * APPfactorial(N-1);
   BAS_VAR(Result);
   return Result;
}

