/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
                               
sem_t seatMutex;      
sem_t customers;        
sem_t smfBarber;        

int numberOfFreeSeats; 
int customersCount;     
int getHCn;             
bool flag_barber_thread;

pthread_t barberThread;          
pthread_t customersThreads[20];    

void *barber()
{
    int wait_time;
    
    while(flag_barber_thread) {
	    sem_wait(&customers);
	    sem_wait(&seatMutex);

	    numberOfFreeSeats += 1;
	    wait_time = (rand() % 5) + 1;
	    printf("\nBarber took a new customer, and he will take %d seconds for haircut\n",wait_time);
	  	printf("Number of free seats: %d\n",numberOfFreeSeats);
	    
	    sem_post(&smfBarber);
	    sem_post(&seatMutex);
	    sleep(wait_time);
    } 
}

void *customer(void *arg)
{
    int id = *((int*)arg);
    printf("Custome %d is created\n", id);
	   
	sem_wait(&seatMutex); 
	    
    if(numberOfFreeSeats <= 0)
    {
	    printf("Customer %d left without haircut\n", id);
	    sem_post(&seatMutex); 
    }
    else
    {
	    numberOfFreeSeats -= 1;
	    printf("Customer %d is waiting\n", id);
	    printf("Number of free seats: %d\n",numberOfFreeSeats);
	   
	    sem_post(&customers); 
	    sem_post(&seatMutex); 
	    sem_wait(&smfBarber); // wait for barber
	    printf("Customer %d get a haircut\n", id);
	    // increse the number of customers who get haircut
	    getHCn += 1;
    }
}


void sleeping_barber() 
{
    printf("Enter the number of free seats: ");
    scanf("%d",&numberOfFreeSeats);
    printf("Enter the customers count: ");
    scanf("%d",&customersCount);
    
    getHCn = 0;  
    sem_init(&seatMutex,0,1);
    sem_init(&customers,0,0);
    sem_init(&smfBarber,0,0);
   
    // Creating barber thread
    flag_barber_thread = true;
    pthread_create(&barberThread, NULL, barber, NULL);
    printf("Barber has been created\n");
    int id[customersCount];
    int spread;
    // Creating customers threads
    for (int i = 0; i < customersCount; i++){
        id[i] = i;
        spread = (rand() % 2);
        sleep(spread); // to randomize creation times
	    pthread_create(&customersThreads[i], NULL, customer, &id[i]); 
    }
   
    for (int i = 0; i < customersCount; i++)
    {
        pthread_join(customersThreads[i], NULL);
    }
    flag_barber_thread = false;
    pthread_join(barberThread, NULL);   
    printf("%d out of %d customers get haircut\n",getHCn,customersCount);
    
    sem_destroy(&seatMutex);
    sem_destroy(&customers);
    sem_destroy(&smfBarber);
}

/*int main()
{
    while(1)
    {
        int ch;
        scanf("%d", &ch);
        if(ch == 1)
            sleeping_barber();
        else
            break;
    }
    return 0;
}*/
