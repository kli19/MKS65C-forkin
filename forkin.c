# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

int main(){
  int f = fork();

  if (f == -1) {
    printf("error");
  } else if(f) {
    printf("Parent of %i pid: %i ppid: %i\n", f, getpid(), getppid());
  } else {
    printf("I am a child pid: %i ppid: %i\n", getpid(), getppid());
  }

  return 0;
}
