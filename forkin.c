# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>

void forking(int f){
  if (f == -1) {
    printf("error");
  } else if(f) {
    printf("Parent of %i pid: %i ppid: %i\n", f, getpid(), getppid());
  } else {
    printf("I am a child pid: %i ppid: %i\n\n", getpid(), getppid());
  }
}


int rand_num(){
  int random_data = open("/dev/random", O_RDONLY);
  int * p = (int *)malloc(sizeof(int));
  read(random_data, p, sizeof(p));
  int num = abs(*p);
  free(p);
  if (close(random_data) < 0){
    printf("ERROR CLOSING FILE");
  };
  while(num>15){
    num = num%20;
    num+=5;
  }
  return num;
}


int main(){
  printf("%d\n", rand_num());
  printf("%d\n", rand_num());
  printf("%d\n", rand_num());
  printf("%d\n", rand_num());
  /*
  int a = fork();
  forking(a);

  int b = fork();
  forking(b);

  int c = fork();
  forking(c);
  */

  return 0;
}
