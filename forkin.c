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
  
  int f = fork();

  if (f == -1) {
    printf("error");
  }
  if(f==getpid()) {
    fork();
  }
  if(f!=getpid()){
    printf("I am a sleepy child pid: %i ppid: %i\n\n", getpid(), getppid());
    int nap_time =  5;
    sleep(nap_time);
    printf("Sleepy child is awake now\n");
    return nap_time;
  }
  int status;
  int sleepy_child = wait(&status);
  int sec = WEXITSTATUS(sleepy_child);
  printf("My sleepy child %d slept for %d seconds\n", sleepy_child, sec);

  return 0;
}
