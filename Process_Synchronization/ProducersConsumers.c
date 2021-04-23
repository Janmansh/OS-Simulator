//All Local functions are named with PC_<func_name>
//Main funtion is ProducerConsumer()

#include<stdio.h>
#include<stdlib.h>

#include<assert.h>
#include<pthread.h>
#include<unistd.h>

#define BufSize 5


typedef struct{

    //Pointer to the array that will contain the processes
    PS_process *ar;
    int n;

    //Creating a pointer to point to an array of thread IDs
    pthread_t *threadIDs;

    //Declaring mutex variable (acts as binary semaphore)
    pthread_mutex_t mutex;

    //Declaring condition variables (act as counting semaphores)
    pthread_cond_t empty;
    pthread_cond_t filled;

}PC_global;

int nextin= 0, nextout= 0, PC_count= 0;
char BUF[BufSize];

int PC_get_index(PC_global *globals, pthread_t KEY)
{
    int i, index = -1;

    for(i=0; i<globals->n; i++)
    {
        if(globals->threadIDs[i] == KEY)
        {
            index = i;
            break;
        }
    }

    return index;
}

//Core Functions
void* PC_Producer(void *arg)
{
    PC_global *globals = (PC_global*)arg;

    //Getting the PS_process number of the current thread
    pthread_t currID = pthread_self();
    int index = PC_get_index(globals, currID);
    int p_no = globals->ar[index].p_no;
    unsigned int BT = (unsigned int) globals->ar[index].BT;
    
    //Securing the predicate variable empty by locking mutex lock
    pthread_mutex_lock(&globals->mutex);

    //Checking if there is space on the buffer
    while(PC_count >= BufSize)
    {
        //Wait for a signal from customer that a slot is empty, and release the mutex.
        printf("\nBuffer is full. Producer (p_no = %d) is waiting for consumption", p_no);
        pthread_cond_wait(&globals->empty, &globals->mutex);
    }

    //Since the return from function pthread_cond_wait() maybe due to spurious wakeups
    //we must manually check if a slot is free
    assert(PC_count < BufSize);

    
    //Acquiring item and adding it to the buffer
    char ITEM;
    printf("\nProducer (p_no = %d) is ready. Enter item to be produced: ", p_no);
    scanf("\n%c", &ITEM);
    //Simulating burst time using delay
    sleep(BT);
    BUF[nextin] = ITEM;
    
    nextin = (nextin + 1)%BufSize;
    PC_count++;

    //Signalling waiting customers of product addition
    pthread_cond_signal(&globals->filled);

    //Unlocking the mutex lock
    pthread_mutex_unlock(&globals->mutex);

    pthread_exit(NULL);
}

void* PC_Consumer(void *arg)
{
    PC_global *globals = (PC_global*)arg;
    
    //Getting the PS_process number of the current thread
    pthread_t currID = pthread_self();
    int index = PC_get_index(globals, currID);
    int p_no = globals->ar[index].p_no;
    unsigned int BT = (unsigned int) globals->ar[index].BT;

    //Securing the predicate variable filled by locking the mutex lock
    pthread_mutex_lock(&globals->mutex);

    //Checking if there is a product on the buffer
    while(PC_count <= 0)
    {
        //Wait for a signal from the producer indicating a product is added, and release the mutex
        printf("\nBuffer is empty. Consumer (p_no = %d) is waiting for a product to be added", p_no);
        pthread_cond_wait(&globals->filled, &globals->mutex);
    }

    //Using assert to account for spurious wakeups
    assert(PC_count > 0);

    //Consuming item
    char ITEM = BUF[nextout];
    //Simulating burst time using delay
    sleep(BT);
    printf("\nConsumer (p_no = %d) is ready. Item consumed = %c", p_no, ITEM);
    BUF[nextout] = (char)0;

    nextout = (nextout + 1)%BufSize;
    PC_count--;

    //Signalling waiting producers of free slot
    pthread_cond_signal(&globals->empty);

    //Unlocking the mutex lock
    pthread_mutex_unlock(&globals->mutex);

    pthread_exit(NULL);
}

void PC_Sort(PC_global *globals);
void PC_ProducerConsumerFCFS(PC_global *globals)
{

    pthread_mutex_init(&globals->mutex, NULL);
    pthread_condattr_t cond_attr;
    pthread_condattr_init(&cond_attr);
    pthread_cond_init(&globals->empty, &cond_attr);
    pthread_cond_init(&globals->filled, &cond_attr);

    //Sorting the processes according to arrival time and priority 
    //(producer is given higher priority if a producer and consumer 
    //arrives at the same time)
    PC_Sort(globals);

    globals->threadIDs = (pthread_t*)malloc(sizeof(pthread_t)*globals->n);
    void *status;
    int i, p_no;
    unsigned int delay;
    for(i=0; i<globals->n; i++)
    {
        p_no = globals->ar[i].p_no;

        //Simulating arrival time using delay
        if(i != 0)
        {
            delay = (unsigned int)(globals->ar[i].AT - globals->ar[i-1].AT);
            sleep(delay);
        }

        //Creating required thread
        if(globals->ar[i].type == 'p')
        {
            printf("\nProducer thread created (p_no = %d).", p_no);
            pthread_create(&globals->threadIDs[i], NULL, PC_Producer, (void*)globals);
        }
        else
        {
            printf("\nConsumer thread created (p_no = %d).", p_no);
            pthread_create(&globals->threadIDs[i], NULL, PC_Consumer, (void*)globals);
        }
    }

    for(i=0; i<globals->n; i++)
    {
        pthread_join(globals->threadIDs[i], &status);
    }

    pthread_mutex_destroy(&globals->mutex);
    pthread_cond_destroy(&globals->empty);
    pthread_cond_destroy(&globals->filled);

    return;
}

//Utility Functions
void PC_inputProcessInfo(PC_global *globals)
{
    int i;

    printf("\nEnter number of processes: ");
    scanf("%d", &globals->n);

    globals->ar = (PS_process*)malloc(sizeof(PS_process)*globals->n);

    printf("\nEnter process details: ");
    for(i=0; i<globals->n; i++)
    {
        globals->ar[i].p_no = i;

        printf("\nEnter 'c' for customer and 'p' for producer: ");
        scanf("\n%c", &(globals->ar[i].type));

        printf("Enter arrival time: ");
        scanf("%d", &(globals->ar[i].AT));

        printf("Enter burst time: ");
        scanf("%d", &(globals->ar[i].BT));
    }

} 

void PC_DeepCopy(PS_process *p1, PS_process *p2)
{
    p1->p_no = p2->p_no;
    p1->AT = p2->AT;
    p1->BT = p2->BT;
    p1->type = p2->type;
}

void PC_Sort(PC_global *globals)
{
    int i, j, min;
    PS_process temp;

    for(i=0; i<globals->n-1; i++)
    {
        min = i;
        for(j= i+1; j<globals->n; j++)
        {
            if(globals->ar[j].AT < globals->ar[min].AT || (globals->ar[j].AT == globals->ar[min].AT && globals->ar[j].type == 'p' && globals->ar[min].type == 'c') )
            {
                min = j;
            }
        }

        if(min != i)
        {
            PC_DeepCopy(&temp, &globals->ar[i]);
            PC_DeepCopy(&globals->ar[i], &globals->ar[min]);
            PC_DeepCopy(&globals->ar[min], &temp);
        }
    }
}

void PC_displayProcessInfo(PC_global *globals)
{
    int i;

    printf("\nPrinting the process information:");
    printf("\nPNo.\tType\tAT\tBT");

    for(i=0; i<globals->n; i++)
    {
        printf("\n%d\t%c\t%d\t%d", globals->ar[i].p_no, globals->ar[i].type, globals->ar[i].AT, globals->ar[i].BT);
    }
} 

void ProducerConsumer(){

    PC_global *globals = (PC_global*)malloc(sizeof(PC_global));

    PC_inputProcessInfo(globals);
    PC_ProducerConsumerFCFS(globals);
    
    PC_displayProcessInfo(globals);

}

