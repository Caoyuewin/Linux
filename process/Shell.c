#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

int main(){
    char buf[1024];
    pid_t pid;
    int status;

    printf("%% ");
    while(fgets(buf,1024,stdin) != NULL) {
        
    }
}
