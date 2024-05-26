#include <unistd.h>
#include <stdio.h>
int main()
{
    pid_t pid;
    pid_t pid1;
    pid = fork();
    if ( pid > 0 ) {

    pid1=fork();
    printf("Hello");
    }

    else
    {
       printf("World");
    }

}
