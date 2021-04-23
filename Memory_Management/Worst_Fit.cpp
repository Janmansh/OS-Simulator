#include <bits/stdc++.h>

using namespace std;

struct process{
    int id=-1;
    int tot_size;
    int starting;
    int end;
}p1[100];

vector <pair<int,int>> empty_slots1;

void insert()
{
    int i=0;
    while(p1[i].id!=-1)
    i++;
    cout<<"Enter process id ";
    cin>>p1[i].id;
    cout<<"Enter process size ";
    cin>>p1[i].tot_size;
    int min_starting=5000;
    int worst_size=-1;
    int total_empty=0;
    for(auto a=empty_slots1.begin();a!=empty_slots1.end();a++)
    {
        if(p1[i].tot_size<=(a->second)-(a->first))
        {
            if(worst_size<(a->second)-(a->first))
            {
                worst_size=(a->second)-(a->first);
                min_starting=a->first;
            }
            else if(worst_size==(a->second)-(a->first))
            {
                if(a->first<min_starting)
                min_starting=a->first;
            }
        }
        total_empty+=(a->second)-(a->first);
    }
    if(min_starting==5000)
    {
        if(total_empty>=p1[i].tot_size)
        {
            cout<< RED "Process cannot be accomodated due to external fragementation" RESET<<endl;
        }
        else 
    		cout<< RED "Process too large. Not enough space in memory" RESET<<endl;
        p1[i].id=-1;
        p1[i].tot_size=0;
        p1[i].starting=0;
        p1[i].end=0;
    }
    else{
        for(auto a=empty_slots1.begin();a!=empty_slots1.end();a++)
        {
            if(a->first==min_starting)
            {
                p1[i].starting=min_starting;
                p1[i].end=min_starting+p1[i].tot_size;
                int to_be_inserted=a->second;
                empty_slots1.erase(a);
                if(p1[i].end!=to_be_inserted)
                {
                    empty_slots1.push_back(make_pair(p1[i].end,to_be_inserted));
                }
                cout<<GREEN "Process inserted successfully. START: "<<p1[i].starting<<" END:"<<p1[i].end<< RESET <<endl;
                break;
            }
        }
    }
}

void del()
{
    int pid;
    cout<<"Enter process id to be deleted ";
    cin>>pid;
    int i=0;
    while(p1[i].id!=pid&&i<=100)
    i++;
    if(i==101)
    {
        cout<<"Process not in memory"<<endl;
        return;
    }
    for(auto a=empty_slots1.begin();a!=empty_slots1.end();a++)
    {
        if(a->first==p1[i].end)
        {
            p1[i].end=a->second;
            empty_slots1.erase(a);
            a--;
        }
        if(a->second==p1[i].starting)
        {
            p1[i].starting=a->first;
            empty_slots1.erase(a);
            a--;
        }
        p1[i].id=-1;
        p1[i].tot_size=0;
    }
    empty_slots1.push_back(make_pair(p1[i].starting,p1[i].end));
    cout<<GREEN "Process removed successfully" RESET <<endl;
}

// Auxillary func to display
// the memory state
void display()
{
    int count=0;
    cout<< CYAN "\nThe processes in memory are as follows :\n" RESET;
    for(int i=0;i<100;i++)
    {	
	// Find active processes
        if(p1[i].id!=-1)
        {
            cout<<YELLOW "Process "<<p1[i].id<<" START: "<<p1[i].starting<<" END: "<<p1[i].end<< RESET <<endl;
            count++;
        }
    }
    // if no process is active
    if(count==0)
    	cout<<MAGENTA "No process in memory" RESET<<endl;
    
    // if no slots are empty
    if(empty_slots1.empty())
    {
        cout<<RED "Memory is full. Delete processes to accomodate new ones" RESET<<endl;
        return;
    }
    
    //
    cout<<CYAN "\nThe empty partitions in memory are " RESET<<endl;
    for(auto a=empty_slots1.begin();a!=empty_slots1.end();a++)
    {
        cout<<YELLOW "START: "<<a->first<<" END: "<<a->second<< RESET <<endl;
    }         
}

// MAIN DRIVER CODE
int Worst_Fit(){
    int memory_size;
    cout << "Program to illustratve MVT partitioning Scheme"<< endl;
    cout << " * Author : Addhyan Malhotra\n";	
    cout << " * Roll   : 191CS202\n\n";
    cout<<" Enter size of main memory :	";
    
    cin >>memory_size;

    // create empty slot of full memory size
    empty_slots1.push_back(make_pair(0,memory_size));
    
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
		    insert();
                    break;
            case 2: 
		    del();
                    break;
            case 3: 
		    display();
                    break;
            default: 
		    cout<<"Exiting..."<<endl;
		    return 0;
        }
    }
    return 0;
}
