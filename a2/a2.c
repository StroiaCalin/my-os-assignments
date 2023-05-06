#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "a2_helper.h"
#include <pthread.h>

void *my_function1(void* arg)
{

info(BEGIN, 5, 1);


return NULL;
}

void *my_function2(void* arg)
{


info(BEGIN, 5, 2);


info(END, 5, 2);
return NULL;
}

void *my_function3(void* arg)
{

info(BEGIN, 5, 3);

info(END, 5, 3);
info(END, 5, 1);
return NULL;
}

void *my_function4(void* arg)
{


info(BEGIN, 5, 4);
info(END, 5, 4);
return NULL;
}

int main(){
    // tester initialization
    init();

    // inform the tester about (main) process’ start
    info(BEGIN, 1, 0);

    // create child process P2
    if (fork() == 0) {
        // inform the tester about process’ start
        info(BEGIN, 2, 0);

        // create child processes P6 and P9
        if (fork() == 0) {
            // inform the tester about process' start
            info(BEGIN, 6, 0);

            // child process P6 terminates immediately
            info(END, 6, 0);
            return 0;
        }
        if (fork() == 0) {
            // inform the tester about process' start
            info(BEGIN, 9, 0);

            // child process P9 terminates immediately
            info(END, 9, 0);
            return 0;
        }

        // wait for child processes P6 and P9 to terminate
        wait(NULL);
        wait(NULL);

        // inform the tester about process’ termination
        info(END, 2, 0);
       return 0;
    }

    // create child process P3
    if (fork() == 0) {
        // inform the tester about process’ start
        info(BEGIN, 3, 0);

        // create child processes P5 and P7
        if (fork() == 0) {
            // inform the tester about process' start
            info(BEGIN, 5, 0);
    
    pthread_t tid1,tid2,tid3,tid4;
    pthread_create(&tid1, NULL, my_function1, NULL);
    pthread_join(tid1, NULL);
       pthread_create(&tid2, NULL, my_function2, NULL);
          pthread_create(&tid3, NULL, my_function3, NULL);             
            pthread_create(&tid4, NULL, my_function4, NULL);
             
    	
     	 pthread_join(tid2, NULL);
        pthread_join(tid3, NULL);
          pthread_join(tid4, NULL);
            info(END, 5, 0);
            // child process P5 terminates immediately
            return 0;
        }
        if (fork() == 0) {
            // inform the tester about process' start
            info(BEGIN, 7, 0);

            // child process P7 terminates immediately
            info(END, 7, 0);
            return 0;
        }

        // wait for child processes P5 and P7 to terminate
        wait(NULL);
        wait(NULL);

        // inform the tester about process’ termination
        info(END, 3, 0);
        return 0;
    }

    // create child process P4
    if (fork() == 0) {
        // inform the tester about process’ start
        info(BEGIN, 4, 0);

        // child process P4 terminates immediately
        info(END, 4, 0);
        return 0;
    }

    // create child process P8
    if (fork() == 0) {
        // inform the tester about process’ start
        info(BEGIN, 8, 0);

        // child process P8 terminates immediately
        info(END, 8, 0);
        return 0;
    }

    // wait for child processes P2, P3, P4, and P8 to terminate
    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);

    // inform the tester about (main) process’ termination
    info(END, 1, 0);

    return 0;
}
