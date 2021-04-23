#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct mvt_best_process{
    int id=-1;
    int tot_size;
    int starting;
    int end;
}mvt_best_p[100];

vector <pair<int,int>> mvt_best_empty_slots;

void insert_mvt_best()
{
    int i=0;
    while(mvt_best_p[i].id!=-1)
    i++;
    cout<<"\nEnter process id:  ";
    cin>>mvt_best_p[i].id;
    cout<<"Enter size : 	  ";
    cin>>mvt_best_p[i].tot_size;
    
    // set initial value to
    // infinite [large number]
    int min_starting=5000;
    int best_size=5000;
    
    //initialise total empty to 0
    int total_empty=0;
    
    // Iterate over empty slots 
    for(auto a=mvt_best_empty_slots.begin();a!=mvt_best_empty_slots.end();a++)
    {
	// Find the first available 
	// smallest slot that can
	// accomodate the current processs
        if(mvt_best_p[i].tot_size<=(a->second)-(a->first))
        {
            if(best_size>(a->second)-(a->first))
            {
                best_size=(a->second)-(a->first);
                min_starting=a->first;
            }
            else if(best_size==(a->second)-(a->first))
            {
                if(min_starting>a->first)
                min_starting=a->first;
            }
        }
	// update unused space to total 
	// available memmory
        total_empty+=(a->second)-(a->first);
    }
    // Check if process has not been allocated
    if(min_starting==5000)
    {
        if(total_empty>=mvt_best_p[i].tot_size)
            cout<< RED "Process cannot be accomodated due to external fragementation" RESET<<endl;
        
        else
		cout<<RED "Process too large. Not enough space in memory" RESET<<endl;
        // Mark Process as not allocated
	mvt_best_p[i].id=-1;
	mvt_best_p[i].tot_size=0;
        mvt_best_p[i].starting=0;
        mvt_best_p[i].end=0;
    }
    // if process is allocated
    else{
	// Iterate over empty
	// Print the slot in which the process is allocated
	// and add fragmentation to empty slots (if any are created)
        for(auto a=mvt_best_empty_slots.begin();a!=mvt_best_empty_slots.end();a++)
        {
            if(a->first==min_starting)
            {
                mvt_best_p[i].starting=min_starting;
                mvt_best_p[i].end=min_starting+mvt_best_p[i].tot_size;
                int to_be_inserted=a->second;
                
		// remove current fragment from empty slots
		mvt_best_empty_slots.erase(a);
                
		// insert fragment of remaining size.
		if(mvt_best_p[i].end!=to_be_inserted)
                {
                    mvt_best_empty_slots.push_back(make_pair(mvt_best_p[i].end,to_be_inserted));
                }
		
		// Output to the user.
                cout<< GREEN "Process inserted successfully. START: "<<mvt_best_p[i].starting<<" END: "<<mvt_best_p[i].end << RESET <<endl;
                break;
            }
        }
    }
}

void del_mvt_best()
{
    int pid;
    cout<<"\nEnter process id : ";
    cin>>pid;
    int i=0;

    // Find location of process to be found
    while(mvt_best_p[i].id!=pid&&i<=100)
    	i++;
    
    // Check if process is not found
    if(i>100)
    {
        cout<<RED "Process not in memory" RESET <<endl;
        return;
    }

    // Find empty slots that need to merged
    // after deleting this process and remove them
    for(auto a=mvt_best_empty_slots.begin();a!=mvt_best_empty_slots.end();a++)
    {
        if(a->first==mvt_best_p[i].end)
        {
            mvt_best_p[i].end=a->second;
            mvt_best_empty_slots.erase(a);
            a--;
        }
        if(a->second==mvt_best_p[i].starting)
        {
            mvt_best_p[i].starting=a->first;
            mvt_best_empty_slots.erase(a);
            a--;
        }
        mvt_best_p[i].id=-1;
        mvt_best_p[i].tot_size=0;
    }
    
    // Add new empty slot to list.  
    mvt_best_empty_slots.push_back(make_pair(mvt_best_p[i].starting,mvt_best_p[i].end));
    cout<<GREEN "Process removed successfully" RESET<<endl;
}
// Auxillary func to display
// the memory state
void display_mvt_best()
{
    int count=0;
    cout<< CYAN "\nThe processes in memory are as follows :\n" RESET;
    for(int i=0;i<100;i++)
    {	
	// Find active processes
        if(mvt_best_p[i].id!=-1)
        {
            cout<<YELLOW "Process "<<mvt_best_p[i].id<<" START: "<<mvt_best_p[i].starting<<" END: "<<mvt_best_p[i].end<< RESET <<endl;
            count++;
        }
    }
    // if no process is active
    if(count==0)
    	cout<<MAGENTA "No process in memory" RESET<<endl;
    
    // if no slots are empty
    if(mvt_best_empty_slots.empty())
    {
        cout<<RED "Memory is full. Delete processes to accomodate new ones" RESET<<endl;
        return;
    }
    
    //
    cout<<CYAN "\nThe empty partitions in memory are " RESET<<endl;
    for(auto a=mvt_best_empty_slots.begin();a!=mvt_best_empty_slots.end();a++)
    {
        cout<<YELLOW "START: "<<a->first<<" END: "<<a->second<< RESET <<endl;
    }         
}

// MAIN DRIVER CODE
int Best_Fit(){
    int memory_size;
    cout << UN << "Program to illustratve MVT partitioning Scheme" RESET << endl;
    cout<<" Enter size of main memory :	";
    
    cin >>memory_size;

    // create empty slot of full memory size
    mvt_best_empty_slots.push_back(make_pair(0,memory_size));
    
    int choice=1;
    
    // Print menu
    cout<<"\n :: USER MENU ::\n 1 to Enter new process\n 2 to Delete an existing process\n 3 to Display present state of memory\n ANY OTHER KEY to exit\n";
    
    // Menu driven code
    while(true)
    {		
        cout<<"\nEnter choice :	";
        cin>>choice;
        switch (choice)
        {
            case 1: 
		    insert_mvt_best();
                    break;
            case 2: 
		    del_mvt_best();
                    break;
            case 3: 
		    display_mvt_best();
                    break;
            default: 
		    cout<<"Exiting..."<<endl;
		    return 0;
        }
    }
    return 0;
}
