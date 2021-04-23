//All Local functions are named with RW_<func_name>
//Main funtion is ReadersWriters()

#include<stdio.h>
#include<stdlib.h>

#include<pthread.h>
#include<unistd.h>

typedef struct
{
    int p_no;
    char type;
    int AT;
    int BT;
}PS_process;

typedef struct{

    //Pointer to the array that will contain the processes
    PS_process *ar;
    int n;

    //Creating a pointer to point to an array of thread IDs
    pthread_t *threadIDs;
    int reader_count;      //writer count is not required as only one writer is allowed at a time

    //Declaring mutex variables (acts as binary semaphore)
    pthread_mutex_t mutex_read;
    pthread_mutex_t mutex_write;

}RW_global;

//Function to get the index in the PS_process array based on thread ID
int RW_get_index(RW_global *globals, pthread_t KEY)
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
void* RW_Reader(void *arg)
{
    
    RW_global *globals = (RW_global*)arg;
    
    pthread_t currID = pthread_self();
    int index = RW_get_index(globals, currID);
    int p_no = globals->ar[index].p_no;
    unsigned int BT = (unsigned int) globals->ar[index].BT;

    //Entry code
    printf("\nReader (p_no = %d) is attempting to read", p_no);
    pthread_mutex_lock(&globals->mutex_read);

    globals->reader_count++;
    if(globals->reader_count == 1)
    {
        pthread_mutex_lock(&globals->mutex_write);
    }
    printf("\nReader (p_no = %d) entered. Starting to read", p_no);

    pthread_mutex_unlock(&globals->mutex_read);

    //Reading section
    //Simulating burst time using delay
    sleep(BT);
    //Some contents are read

    //Exit code
    pthread_mutex_lock(&globals->mutex_read);
    printf("\nReader (p_no = %d) is exiting.", p_no);

    globals->reader_count--;
    if(globals->reader_count == 0)   //No more readers reading now. Writers are free to write
    {
        pthread_mutex_unlock(&globals->mutex_write);
    }

    pthread_mutex_unlock(&globals->mutex_read);
    //Reader has exited    

    pthread_exit(NULL);
}

void* RW_Writer(void *arg)
{

    RW_global *globals = (RW_global*)arg;

    pthread_t currID = pthread_self();
    int index = RW_get_index(globals, currID);
    int p_no = globals->ar[index].p_no;
    unsigned int BT = (unsigned int) globals->ar[index].BT;

    printf("\nWriter (p_no  = %d) is attempting to write", p_no);

    //Start of critical section
    pthread_mutex_lock(&globals->mutex_write);
    printf("\nWriter (p_no = %d) has entered. Starting to write", p_no);

    //Writing section
    //Simulating burst time using delay
    sleep(BT);
    //Writer writes content
   
    printf("\nWriter (p_no = %d) is exiting.", p_no);
    //End of critical section 
    pthread_mutex_unlock(&globals->mutex_write);

    pthread_exit(NULL);
}

void RW_Sort(RW_global *globals);
void RW_ReadersWritersFCFS(RW_global *globals)
{

    globals->reader_count = 0;
    pthread_mutex_init(&globals->mutex_read, NULL);
    pthread_mutex_init(&globals->mutex_write, NULL);

    //Sorting the processes according to arrival time and priority 
    //(writer is given higher priority if a writer and reader 
    //arrives at the same time)
    RW_Sort(globals);

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
        if(globals->ar[i].type == 'r')
        {
            printf("\nReader thread created (p_no = %d).", p_no);
            pthread_create(&globals->threadIDs[i], NULL, RW_Reader, (void*)globals);
        }
        else
        {
            printf("\nWriter thread created (p_no = %d).", p_no);
            pthread_create(&globals->threadIDs[i], NULL, RW_Writer, (void*)globals);
        }
    }

    for(i=0; i<globals->n; i++)
    {
        pthread_join(globals->threadIDs[i], &status);
    }

    pthread_mutex_destroy(&globals->mutex_read);
    pthread_mutex_destroy(&globals->mutex_write);

    return;
}

//Utility Functions
void RW_inputProcessInfo(RW_global *globals)
{
    int i;

    printf("\nEnter number of processes: ");
    scanf("%d", &globals->n);

    globals->ar = (PS_process*)malloc(sizeof(PS_process)*globals->n);

    printf("\nEnter PS_process details: ");
    for(i=0; i<globals->n; i++)
    {
        globals->ar[i].p_no = i;

        printf("\nEnter 'r' for reader and 'w' for writer: ");
        scanf("\n%c", &(globals->ar[i].type));

        printf("Enter arrival time: ");
        scanf("%d", &(globals->ar[i].AT));

        printf("Enter burst time: ");
        scanf("%d", &(globals->ar[i].BT));
    }

} 

void RW_DeepCopy(PS_process *p1, PS_process *p2)
{
    p1->p_no = p2->p_no;
    p1->AT = p2->AT;
    p1->BT = p2->BT;
    p1->type = p2->type;
}

void RW_Sort(RW_global *globals)
{
    int i, j, min;
    PS_process temp;

    for(i=0; i<globals->n-1; i++)
    {
        min = i;
        for(j= i+1; j<globals->n; j++)
        {
            if(globals->ar[j].AT < globals->ar[min].AT || (globals->ar[j].AT == globals->ar[min].AT && globals->ar[j].type == 'w' && globals->ar[min].type == 'r') )
            {
                min = j;
            }
        }

        if(min != i)
        {
            RW_DeepCopy(&temp, &globals->ar[i]);
            RW_DeepCopy(&globals->ar[i], &globals->ar[min]);
            RW_DeepCopy(&globals->ar[min], &temp);
        }
    }
}

void RW_displayProcessInfo(RW_global *globals)
{
    int i;

    printf("\nPrinting the process information:");
    printf("\nPNo.\tType\tAT\tBT");

    for(i=0; i<globals->n; i++)
    {
        printf("\n%d\t%c\t%d\t%d", globals->ar[i].p_no, globals->ar[i].type, globals->ar[i].AT, globals->ar[i].BT);
    }
} 

void ReadersWriters(){

    RW_global *globals = (RW_global*)malloc(sizeof(RW_global));

    RW_inputProcessInfo(globals);
    RW_ReadersWritersFCFS(globals);
    
    RW_displayProcessInfo(globals);
}
