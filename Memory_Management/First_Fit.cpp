#include <bits/stdc++.h>

using namespace std;

struct process_mvt_first{
    int id=-1;
    int tot_size;
    int starting;
    int end;
}p[100];

vector <pair<int,int>> empty_mvt_first_slots;

void insert_mvt_first()
{
    int i=0;
    while(p[i].id!=-1)
    i++;
    cout<<"Enter process id   : ";
    cin>>p[i].id;
    cout<<"Enter process size : ";
    cin>>p[i].tot_size;
    int min_starting=5000;
    int total_empty=0;
    for(auto a=empty_mvt_first_slots.begin();a!=empty_mvt_first_slots.end();a++)
    {
        if(p[i].tot_size<=(a->second)-(a->first))
        {
            if(min_starting>a->first)
            {
                min_starting=a->first;
            }
        }
        total_empty+=(a->second)-(a->first);
    }
    if(min_starting==5000)
    {
        if(total_empty>=p[i].tot_size)
        {
            cout<< RED "Process cannot be accomodated due to external fragementation" RESET<<endl;
        }
        else 
    		cout<< RED "Process too large. Not enough space in memory" RESET<<endl;
        p[i].id=-1;
        p[i].tot_size=0;
        p[i].starting=0;
        p[i].end=0;
    }
    else{
        for(auto a=empty_mvt_first_slots.begin();a!=empty_mvt_first_slots.end();a++)
        {
            if(a->first==min_starting)
            {
                p[i].starting=min_starting;
                p[i].end=min_starting+p[i].tot_size;
                int to_be_inserted=a->second;
                empty_mvt_first_slots.erase(a);
                if(p[i].end!=to_be_inserted)
                {
                    empty_mvt_first_slots.push_back(make_pair(p[i].end,to_be_inserted));
                }
                cout<<"Process inserted successfully. START "<<p[i].starting<<" END "<<p[i].end<<endl;
                break;
            }
        }
    }
}

void del_mvt_first()
{
    int pid;
    cout<<"\nEnter process id : ";
    cin>>pid;
    int i=0;

    // Find location of process to be found
    while(p[i].id!=pid&&i<=100)
    	i++;
    
    // Check if process is not found
    if(i>100)
    {
        cout<<RED "Process not in memory" RESET <<endl;
        return;
    }

    // Find empty slots that need to merged
    // after deleting this process and remove them
    for(auto a=empty_mvt_first_slots.begin();a!=empty_mvt_first_slots.end();a++)
    {
        if(a->first==p[i].end)
        {
            p[i].end=a->second;
            empty_mvt_first_slots.erase(a);
            a--;
        }
        if(a->second==p[i].starting)
        {
            p[i].starting=a->first;
            empty_mvt_first_slots.erase(a);
            a--;
        }
        p[i].id=-1;
        p[i].tot_size=0;
    }
    
    // Add new empty slot to list.  
    empty_mvt_first_slots.push_back(make_pair(p[i].starting,p[i].end));
    cout<<GREEN "Process removed successfully" RESET<<endl;
}

// Auxillary func to display
// the memory state
void display_mvt_first()
{
    int count=0;
    cout<< CYAN "\nThe processes in memory are as follows :\n" RESET;
    for(int i=0;i<100;i++)
    {	
	// Find active processes
        if(p[i].id!=-1)
        {
            cout<<YELLOW "Process "<<p[i].id<<" START: "<<p[i].starting<<" END: "<<p[i].end<< RESET <<endl;
            count++;
        }
    }
    // if no process is active
    if(count==0)
    	cout<<MAGENTA "No process in memory" RESET<<endl;
    
    // if no slots are empty
    if(empty_mvt_first_slots.empty())
    {
        cout<<RED "Memory is full. Delete processes to accomodate new ones" RESET<<endl;
        return;
    }
    
    //
    cout<<CYAN "\nThe empty partitions in memory are " RESET<<endl;
    for(auto a=empty_mvt_first_slots.begin();a!=empty_mvt_first_slots.end();a++)
    {
        cout<<YELLOW "START: "<<a->first<<" END: "<<a->second<< RESET <<endl;
    }         
}

// MAIN DRIVER CODE
int First_Fit(){
    int memory_size;
    cout << "Program to illustratve MVT partitioning Scheme"<< endl;
    cout << " * Author : Addhyan Malhotra\n";	
    cout << " * Roll   : 191CS202\n\n";
    cout<<" Enter size of main memory :	";
    
    cin >>memory_size;

    // create empty slot of full memory size
    empty_mvt_first_slots.push_back(make_pair(0,memory_size));
    
    int choice=1;
    
    // Print menu
    cout<<"\n :: USER MENU ::\n 1. to Enter new process\n 2. to Delete an existing process\n 3. to Display present state of memory\n 9. to exit\n";
    
    // Menu driven code
    while(true)
    {		
        cout<<"\nEnter choice :	";
        cin>>choice;
        switch (choice)
        {
            case 1: 
		    insert_mvt_first();
                    break;
            case 2: 
		    del_mvt_first();
                    break;
            case 3: 
		    display_mvt_first();
                    break;
            default: 
		    cout<<"Exiting..."<<endl;
		    return 0;
        }
    }
    return 0;
}
