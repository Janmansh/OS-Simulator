//All Local functions are named with DP_<func_name>
//Main funtion is Dining_Philosophers()

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include<unistd.h>
#include<pthread.h>

#define THINKING 1
#define HUNGRY 2
#define EATING 3

//Structure containing philosopher thread info
typedef struct{
    pthread_t threadID;
    int state;

    pthread_cond_t available;
}thread_dp;

typedef struct{

    int n;  //Number of processes

    int max_eat_time, max_think_time; //Maximum eating and thinking times

    thread_dp *phil;

    //Stores state of each chopstick
    int *chopsticks;

    //mutex declaration
    pthread_mutex_t mutex;

}DP_global;

void DP_pickUpChopsticks(DP_global *globals, int pno, int left, int right, int eat_time){

    globals->phil[pno].state = HUNGRY;
    printf("\nPhilosopher %d is hungry and is trying to get chopsticks", pno);

    while(globals->chopsticks[left] != 1 || globals->chopsticks[right] != 1){
        printf("\n%sPhilosopher %d is waiting for chopsticks to be free%s",YELLOW, pno, WHITE);
        pthread_cond_wait(&globals->phil[pno].available, &globals->mutex);
    }
    
    //Acquired left and right chopsticks. Now locking them
    globals->chopsticks[left] = globals->chopsticks[right] = 0;

    //Starting to eat
    globals->phil[pno].state = EATING;
    printf("\n%sPhilosopher %d has gotten the chopsticks and started to eat.%s",CYAN, pno, WHITE);   
    
}

void DP_putDownchopsticks(DP_global *globals, int pno, int left, int right){

    globals->chopsticks[left] = globals->chopsticks[right] = 1;
    globals->phil[pno].state = THINKING;
    printf("\nPhilosopher %d has put down chopsticks", pno);

    //Signalling left and right philosophers
    int left_of_left = globals->n-1 - (globals->n-left)%globals->n;
    int right_of_right = (right + 1)%globals->n;
    printf("\nPhilosopher %d is signalling (left) philosopher %d", pno, left_of_left);
    pthread_cond_signal(&globals->phil[left_of_left].available);
    printf("\nPhilosopher %d is signalling (right) philosopher %d", pno, right);
    pthread_cond_signal(&globals->phil[right].available);

}

int DP_getPhilNum(DP_global*, pthread_t);
int DP_getRand(int);
void* DP_Philosopher(void *args){

    DP_global *globals = (DP_global*)args;
    
    int pno, right, left;
    int *retval = (int*)malloc(sizeof(int));
    *retval = 0;
    int eat_time, think_time;

    //Getting thread ID of current thread
    pthread_mutex_lock(&globals->mutex);
    pno = DP_getPhilNum(globals, pthread_self());

    //Getting left and right positions
    left = pno;
    right = (pno + 1)%globals->n;
    
    think_time = DP_getRand(globals->max_think_time);
    eat_time = DP_getRand(globals->max_eat_time);
    pthread_mutex_unlock(&globals->mutex);

    //Thinking state
    printf("\n%sPhilosopher %d is thinking%s",CYAN, pno, WHITE);
    sleep(think_time);

    //Pick up chopsticks
    pthread_mutex_lock(&globals->mutex);
    DP_pickUpChopsticks(globals, pno, left, right, eat_time);
    pthread_mutex_unlock(&globals->mutex);

    //Eat  
    sleep(eat_time);

    //Put down chopsticks and alert right and left philosophers    
    pthread_mutex_lock(&globals->mutex);
    DP_putDownchopsticks(globals, pno, left, right);
    pthread_mutex_unlock(&globals->mutex);

    printf("\nPhilosopher %d is exiting thread", pno);
    pthread_exit((void*)retval);
}

void DP_createThreads(DP_global *globals){

    int i;
    int *status;

    for(i=0; i<globals->n; i++){
        printf("\n%sCreating thread  of philosopher %d %s", GREEN, i, WHITE);
        pthread_create(&globals->phil[i].threadID, NULL, &DP_Philosopher, (void*)globals);
    }

    for(i=0; i<globals->n; i++){
        pthread_join(globals->phil[i].threadID, (void**)&status);
        printf("\n%sPhilosopher %d exited with status %d %s",GREEN, i, *status, WHITE);
    }

    //Destroying mutexes & condition variables after threads have terminated
    printf("\nDestroying the mutexes...");
    pthread_mutex_destroy(&globals->mutex);
    for(i=0; i<globals->n; i++){
        pthread_cond_destroy(&globals->phil[i].available);
    }

    return;
}

//Function to initialize variables
void DP_Initialize(DP_global *globals){

    globals->n = -1;
    while(globals->n<1){
        printf("\nEnter number of philosophers (Should be greater than 1): ");
        scanf("%d", &globals->n);
        if(globals->n<2){
            printf("\nValue should be greater than 1. Please enter again");
        }
    }

    printf("\nEnter maximum thinking time: ");
    scanf("%d", &globals->max_think_time);
    globals->max_think_time = (globals->max_think_time >= 0)?globals->max_think_time : 0;

    printf("\nEnter maximum eating time: ");
    scanf("%d", &globals->max_eat_time);
    globals->max_eat_time = (globals->max_eat_time >= 0)? globals->max_eat_time : 0;

    globals->phil = (thread_dp*)malloc(sizeof(thread_dp)*globals->n);
    globals->chopsticks = (int*)malloc(sizeof(int)*globals->n);

    pthread_condattr_t attr;
    pthread_condattr_init(&attr);
    for(int i=0; i<globals->n; i++){

        globals->phil[i].state = THINKING;
        pthread_cond_init(&globals->phil[i].available, &attr);

        globals->chopsticks[i] = 1;
    }

    return;
}

//Utility functions

//Get pno given thread id
int DP_getPhilNum(DP_global *globals, pthread_t tid){

    int index = -1;

    for(int i=0; i<globals->n; i++){
        if(tid == globals->phil[i].threadID){
            index = i;
            break;
        }
    }

    return index;
}

int DP_getRand(int maxval){
    return (int) ( (float)rand() / RAND_MAX * maxval);  //Returning a random integer between 0 and maxval inclusive
}

void Dining_Philosophers(){

    srand(time(NULL));  //Seeding pseudo random number for eating and thinking times

    DP_global *globals = (DP_global*)malloc(sizeof(DP_global));

    DP_Initialize(globals);
    DP_createThreads(globals);

}

