#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
  int pid = fork();
  if(pid == 0){
    printf("i am a child\n");
    //execl("/bin/sdfsdf", "ls","-l","-a", NULL);
    //execlp("ls", "ls", "-l", "-a",NULL);
    char* argv[] = {"/bin/ls","-l", "-a", NULL};
    char* env[] = { "PATH = ./TEST", "HOME=~", NULL};
    execve(argv[0], argv, env);
    perror("execl error");
  }
  printf("hello world\n");
  return 0;
}
