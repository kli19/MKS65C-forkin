# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>

//returns a random integer between 5 and 20
int rand_num(){
  int random_data = open("/dev/random", O_RDONLY);
  int * p = (int *)malloc(sizeof(int));
  read(random_data, p, sizeof(p));
  int num = abs(*p);
  free(p);
  if (close(random_data) < 0){
    printf("ERROR CLOSING FILE");
  };
  return num%16+5;
}

int main(){
  //initial message before forking
  printf("I am the parent process pid: %d ppid: %d\n", getpid(), getppid());
  
  //fork the parent
  int f = fork();

  //error
  if (f == -1) {
    printf("error");
  }

  //fork again if parent
  if(f) {
    f = fork();
  }

  //sleep if child
  if(f==0){
    printf("I am a sleepy child pid: %i ppid: %i\n", getpid(), getppid());
    int nap_time = rand_num();
    sleep(nap_time);
    printf("Sleepy child is awake now\n");

    //child process returns number of seconds slept
    return nap_time;
  }

  //parent process stuff
  int status;
  int sleepy_child = wait(&status);
  int seconds = WEXITSTATUS(status);
  printf("My sleepy child %d slept for %d seconds\n", sleepy_child, seconds);
  printf("Parent process is done!\n");

  return 0;
}
