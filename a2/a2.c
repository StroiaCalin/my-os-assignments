#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "a2_helper.h"
#include <pthread.h>

void *functies(void* arg)
{
	int index = *(int *)arg;
	info(BEGIN, 3, index+1);
	info(END,3,index+1);
	return NULL;
}

void *functie(void* arg)
{
	int index = *(int *)arg;
	info(BEGIN, 2, index+1);
	info(END,2,index+1);
	return NULL;
}

void *functie1(void* arg)
{

info(BEGIN, 5, 1);
return NULL;
}

void *functie2(void* arg)
{


info(BEGIN, 5, 2);
info(END, 5, 2);
return NULL;
}

void *functie3(void* arg)
{

info(BEGIN, 5, 3);

info(END, 5, 3);
info(END, 5, 1);
return NULL;
}

void *functie4(void* arg)
{


info(BEGIN, 5, 4);
info(END, 5, 4);
return NULL;
}

int main(){

    init();


    info(BEGIN, 1, 0);

    
    if (fork() == 0) {
    
        info(BEGIN, 2, 0);
  pthread_t tids[42];
  int args[42];
  for(int i=0;i<42;i++)
  {
  args[i]=i;
    pthread_create(&tids[i], NULL, functie, &args[i]);
}

for(int i=0;i<42;i++)
{
pthread_join(tids[i],NULL);
}
      
        if (fork() == 0) {
       
            info(BEGIN, 6, 0);
            info(END, 6, 0);
            return 0;
        }
        if (fork() == 0) {
       
            info(BEGIN, 9, 0);

       
            info(END, 9, 0);
            return 0;
        }

   
        wait(NULL);
        wait(NULL);

     
       info(END, 2, 0);
       return 0;
    }


    if (fork() == 0) {
      
        info(BEGIN, 3, 0);
        
         pthread_t tidss[6];
  int argss[6];
  for(int i=0;i<6;i++)
  {
  argss[i]=i;
    pthread_create(&tidss[i], NULL, functies, &argss[i]);
}

for(int i=0;i<6;i++)
{
pthread_join(tidss[i],NULL);
}

  
        if (fork() == 0) {
         
            info(BEGIN, 5, 0);
    
    pthread_t tid1,tid2,tid3,tid4;
    pthread_create(&tid1, NULL, functie1, NULL);
    pthread_join(tid1, NULL);
       pthread_create(&tid2, NULL, functie2, NULL);
          pthread_create(&tid3, NULL, functie3, NULL);             
            pthread_create(&tid4, NULL, functie4, NULL);
             
    	
     	 pthread_join(tid2, NULL);
        pthread_join(tid3, NULL);
          pthread_join(tid4, NULL);
            info(END, 5, 0);
    
            return 0;
        }
        if (fork() == 0) {
        
            info(BEGIN, 7, 0);

           
            info(END, 7, 0);
            return 0;
        }

    
        wait(NULL);
        wait(NULL);
        info(END, 3, 0);
        return 0;
    }

  
    if (fork() == 0) {
    
        info(BEGIN, 4, 0);
        info(END, 4, 0);
        return 0;
    }

 
    if (fork() == 0) {
   
        info(BEGIN, 8, 0);

   
        info(END, 8, 0);
        return 0;
    }
    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);
    info(END, 1, 0);

    return 0;
}
