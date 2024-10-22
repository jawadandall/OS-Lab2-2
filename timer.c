/* hello_timer.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int global_flag = 0; // global flag to communicate between signal handler and main function
int alarm_count = 0;
time_t start_time;

void handler(int signum) //signal handler
{
  printf("Hello World!\n");
  alarm_count++;
  global_flag = 1; // set the flag when handler is called
}

void sigint_handler(int signum) //signal handler for interupt
{
  time_t end_time = time(NULL); // get the current time
  printf("Total alarms: %d\n", alarm_count);
  printf("Total execution time: %ld seconds\n", end_time - start_time);
  exit(0);
}


int main(int argc, char * argv[])
{  
  signal(SIGALRM, handler); //register handler to handle SIGALRM
  signal(SIGINT, sigint_handler); //register handler to handle SIGINT (CTRL+C)
  start_time = time(NULL);
  while(1) //will loop indefinitely since argument set to 1
  {
    alarm(1); //Schedule a SIGALRM for 1 second
    while(!global_flag); //runs without doing anything until handler sets flag to 1
    printf("Turing was right!\n"); // print message after handler executes
    global_flag = 0; //reset flag so inner while loop waits for alarm at next iteration
  }
  return 0; //never reached
}