#include <stdio.h>

#include <BAS/BAStimestamp.h>
#include <time.h>

BAStimestamp BAScurrentTime(){
   struct timespec spec;
   clock_gettime(CLOCK_REALTIME, &spec);
   BAStimestamp Timestamp;
   Timestamp.Seconds = spec.tv_sec;
   Timestamp.NanoSeconds = spec.tv_nsec;
   return Timestamp;
}

int main(){
   printf("Hello world of C!\n");
   BAStimestamp Now = BAScurrentTime();
   printf("%lli.%lli\n", Now.Seconds, Now.NanoSeconds);
   return 0;
}
