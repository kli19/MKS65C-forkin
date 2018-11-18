# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>

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
  
  int id = getpid();
  fork();

  if (id == -1) {
    printf("error");
  }
  if(id==getpid()) {
    fork();
  }
  if(id!=getpid()){
    printf("I am a sleepy child pid: %i ppid: %i\n", getpid(), getppid());
    int nap_time = rand_num();
    sleep(nap_time);
    printf("Sleepy child is awake now\n");
    return nap_time;
  }
  int status;
  int sleepy_child = wait(&status);
  int seconds = WEXITSTATUS(status);
  printf("My sleepy child %d slept for %d seconds\n", sleepy_child, seconds);

  return 0;
}
