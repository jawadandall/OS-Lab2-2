/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int global_flag = 0; // global flag to communicate between signal handler and main function

void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  global_flag = 1; // set the flag when handler is called
}

int main(int argc, char * argv[])
{
  signal(SIGALRM,handler); //register handler to handle SIGALRM
  while(1){ //will loop indefinitely since argument set to 1
    alarm(5); //Schedule a SIGALRM for 5 seconds
    while(!global_flag); //runs without doing anything until handler sets flag to 1
    printf("Turing was right!\n"); // print message after handler executes and before exit
    global_flag = 0; //reset flag so while loop waits for alarm at next iteration
  }
  return 0; //never reached
}