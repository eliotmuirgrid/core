#include <stdio.h>

#include <BAS/BASthread.h>
#include <BAS/BAStrace.h>
BAS_TRACE_INIT;

static void ThreadProc(void* pObject){
   BAS_FUNCTION(ThreadProc);
   printf("Hello thread %li\n", (long)pObject);
}

int main(){
   BAStrace("*");
   BAS_FUNCTION(main);
   printf("Hello world of threading\n");
   for (int i=0; i < 10; i++){
      BAS_VAR(i);
      BASthread(&ThreadProc, (void*)i);
   }
   return 0;
}
