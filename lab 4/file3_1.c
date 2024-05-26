1. #include <stdio.h>
2. #include <pthread.h>
3. void *kidfunc(void *p) {
4. printf ("Kid ID is ---> %d\n", getpid( ));
5. }
6. main ( ) {
7. pthread_t kid ;
8. pthread_create (&kid,NULL,kidfunc, NULL);
9. printf ("Parent ID is ---> %d\n", getpid( )) ;
10.  pthread_join (kid, NULL) ;
11. printf ("No more kid!\n") ;
12. }
