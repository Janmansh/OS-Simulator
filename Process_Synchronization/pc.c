#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define MaxItems 3
#define BufferSize 3 
#define total_processes 6

sem_t pc_empty_slots;
sem_t pc_full_slots;
int pc_wait_flag=0;
int pc_in = 0;
int pc_out = 0;
int pc_buffer[BufferSize];
int pc_p_burst_time[3]= {2,3,2};
int pc_c_burst_time[3]= {2,2,3};
int pc_p_arrival_time[3] = {0,1,2};
int pc_c_arrival_time[3] = {0,1,2};
pthread_mutex_t pc_mutex;

int generate_random_number(){
    // Generates random number in range 0-17
    return clock()%17;
}

void *producer(void *pno)
{   
    int item;
    item = generate_random_number();
    
    //Give user output is process has to wait    
    if(pc_wait_flag)
        printf(" -> \x1b[36mProd %d: is waiting for lock...\x1b[0m\n",*(int *)pno);
    
    // wait while there are no empty slots to produce in
    sem_wait(&pc_empty_slots);
        
    // wait while someother process in in Critical Section
    pthread_mutex_lock(&pc_mutex);

    // set pc_wait_flag
    pc_wait_flag = 1;

    // Add item to pc_buffer        
    pc_buffer[pc_in] = item;

    printf(" -> \x1b[32mProducer %d: Insert Item %d at %d\n\x1b[0m", *((int *)pno),pc_buffer[pc_in],pc_in);
    pc_in = (pc_in+1)%BufferSize;

    // Add deleay to simulate burst time
    usleep(100000*pc_p_burst_time[*((int *)pno)]);
        
    // reset pc_wait_flag
    pc_wait_flag = 0;

    //Release locks
    pthread_mutex_unlock(&pc_mutex);
    sem_post(&pc_full_slots);

    printf(" -> \x1b[36mProducer %d: has finished...\x1b[0m\n",*(int *)pno);
    return NULL;
}

void *consumer(void *cno)
{   
    // give user output
    if(pc_wait_flag)
        printf(" -> \x1b[33mConsumer %d: is waiting for locks...\x1b[0m\n",*(int *)cno);

    // wait while there are no full slots
    sem_wait(&pc_full_slots);
    
    // wait if another process is using critical section
    pthread_mutex_lock(&pc_mutex);
    
    // set pc_wait_flag
    pc_wait_flag = 1;
    
    // Deque item from pc_buffer 
    int item = pc_buffer[pc_out];
    
    printf(" -> \x1b[31mConsumer %d: Consumes Item %d from position %d\x1b[0m\n",*((int *)cno),item, pc_out);
    
    // update pc_buffer pointer
    pc_out = (pc_out+1)%BufferSize;

    // Add deleay to simulate burst time
    usleep(100000*pc_c_burst_time[*((int *)cno)]);
    
    // set pc_wait_flag
    pc_wait_flag = 0;
    
    // release the locks
    pthread_mutex_unlock(&pc_mutex);
    sem_post(&pc_empty_slots);

    printf(" -> \x1b[36mConsumer %d: has finished...\x1b[0m\n",*(int *)cno);
    return NULL;
}

int pc()
{   
    printf(YELLOW "\n\e[4mPROGRAM TO IMPLEMENT PRODUCER CONSUMER PROBLEM\x1b[0m\n\n" RESET);
    printf("* This program uses Pthread and time library to simulate AT and BT of processes\n");
    printf("* The scheduling is taken care of by default CPU scheduler\n");
    printf("* Threads are syncronised using Mutex and Semaphores\n");
    printf("* Arrival Time and burst time is simulated using realtime mapping of system clock\n");
    printf("* Output varies each time due to unpridictable context switch time\n\n");
    
    // Take userinpur
    printf(YELLOW "\n\e[4mPRODUCER DETAILS\x1b[0m\n");
    for(int i=0;i<3;i++){
        printf("\nEnter AT for P%d: ",i);
        scanf("%d",&pc_p_arrival_time[i]);
        printf("Enter BT for P%d: ",i);
        scanf("%d",&pc_p_burst_time[i]);
    }
    printf(YELLOW "\n\e[4mCONSUMER DETAILS\x1b[0m\n");
    for(int i=0;i<3;i++){
        printf("\nEnter AT for C%d: ",i);
        scanf("%d",&pc_c_arrival_time[i]);
        printf("Enter BT for C%d: ",i);
        scanf("%d",&pc_c_burst_time[i]);
    }
    printf("\n\e[4mSTARTING EXECUTION\x1b[0m\n\n");

    // Create an array to store threads
    pthread_t pro[3],con[3];
    
    // Initialise Mutex
    pthread_mutex_init(&pc_mutex, NULL);
    
    // Initialize Semaphores
    sem_init(&pc_empty_slots,0,BufferSize);
    sem_init(&pc_full_slots,0,0);
    
    // Record clock time
    clock_t start_time = clock();

    // Initialise visited arrays
    int c_visited[3]={0};
    int p_visited[3]={0};

    // Initialise temporary variable
    int processes_created = 0;

    //Just used for numbering the producer and consumer
    int a[3] = {0,1,2};

    // While processes in wait queue 
    while (processes_created<total_processes)
    {   
        // Create Producer processes as threads
        for(int i = 0; i < 3; i++) {
            if(!p_visited[i] && (clock()>=(start_time+(pc_p_arrival_time[i]*1000)))){
                p_visited[i]=1;
                pthread_create(&pro[i], NULL, &producer, (void *)&a[i]);
                processes_created++;
		usleep(100);    
            }
        }

        // Create Consumer processes as threads
        for(int i = 0; i < 3; i++) {
            if(!c_visited[i] && (clock()>=start_time+(pc_c_arrival_time[i]*1000))){
                c_visited[i]=1;
                pthread_create(&con[i], NULL, &consumer, (void *)&a[i]);
                processes_created++;    
            }
        }
    }
    // printf("\n\nALL PROCESSES HAVE BEEN CREATED\n\n");
    for(int i = 0; i < 3; i++) {
        pthread_join(pro[i], NULL);
     //   printf("P%d THREAD HAS BEEN JOINED\n\n",i);
    }
    for(int i = 0; i < 3; i++) {
        pthread_join(con[i], NULL);
    //    printf("C%d THREAD HAS BEEN JOINED\n\n",i);
    }
    printf("\nALL THREADS JOINED...\n");
    pthread_mutex_destroy(&pc_mutex);
    sem_destroy(&pc_empty_slots);
    sem_destroy(&pc_full_slots);
    printf("ALL LOCKS DESTROYED...\nExiting gracefully...\n\n");


    return 0;
    
}