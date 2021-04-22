#include <iostream>

#define maxN 1000
using namespace std;

struct partition {
	int size;
	bool allocated;
	int pid;
};

struct process {
	int size;
	int part_no;
	int exist;
};

struct partition part[maxN];
struct process proc[maxN];

void print_table(int num)
{
	cout<<"\n\t\tMemory Table\n";

	for(int i = 0; i < num; i++)
	{
		if(!part[i].allocated)
		continue;
		
		cout<<part[i].size<<" | ";
		if(part[i].pid == -1)
			cout<<"Empty\n";
		else
			cout<<"Process "<<part[i].pid<<" Size "<<proc[part[i].pid].size<<"\n";
	}
}

void best_fit_mft()
{
	int tot_mem, n_part, backup;
	cout<<"Enter size of total memory : ";
	cin>>tot_mem;
	backup = tot_mem;
	
	cout<<"Enter total number of partitions : ";
	cin>>n_part;
	int valid_parts = 0, high = 0;

	for(int i = 0; i < n_part; i++)
	{
		cout<<"Enter size of Partition "<<i<<" : ";
		cin>>part[i].size;
		part[i].allocated = false;
		part[i].pid = -1;
		if(backup >= part[i].size) // check if free memory is available
		{
			valid_parts++;
			backup -= part[i].size;
			part[i].allocated = true;
			printf("Partition Allocated\n");
			if(high < part[i].size)
				high = part[i].size;
		}
		else
			printf("Partition %d cannot be allocated memory since only %d memory is remaining\n", i+1, backup);
	}
	
	cout<<"Available Blocks of Memory = "<<valid_parts<<"\n";
	int used = 0;
	tot_mem -= backup;
	
	while(1)
	{
		int choice;
		cout<<"1.Insert 2.Delete 3.Stop\n";
		cin>>choice;
		
		if(choice == 1)
		{
			int id, sz;
			cout<<"Enter Process ID : ";
			cin>>id;
			cout<<"Enter Process size : ";
			cin>>sz;
			
			if(sz > high)
			{
				cout<<"No partition is large enough to accomodate this size\n";
				continue;
			}
			else if(proc[id].exist == 1)
			{
				cout<<"Process already exists in partition "<<proc[id].part_no<<"\n";
				continue;
			}
			else if(sz > tot_mem - used)
			{
				cout<<"Not enough Unused Space\n";
				continue;
			}
			
			int small = 1e4, pos = -1;
			for(int i = 0; i < n_part; i++)
			{
				if(part[i].allocated && part[i].pid == -1 && sz <= part[i].size && part[i].size < small)
				{
					small = part[i].size;
					pos = i;
				}	
			}
			
			if(pos != -1)
			{
				part[pos].pid = id;
				proc[id].part_no = pos;
				proc[id].size = sz;
				proc[id].exist = 1;
				cout<<id<<" is accomadated in partition "<<pos<<"\n";
				used += proc[id].size;
			}
			
			if(proc[id].exist == 0)
			{
				bool find = false;
				for(int i = 0; i < n_part; i++)
				{
					int temp = part[i].pid;
					if(temp != -1)
					{
						if(part[i].size - proc[temp].size >= sz)
						find = true;
					}
				}
				if(find)
					cout<<"Cannot store due to Internal Fragmentation\n";
				else
					cout<<"Cannot store due to External Fragmentation\n";
			}
		}
		else if(choice == 2)
		{
			int id;
			cout<<"Enter Process ID : ";
			cin>>id;
			
			int part_id = proc[id].part_no;
			part[part_id].pid = -1;
			used -= proc[id].size;
			proc[id].exist =  0;
			proc[id].part_no = -1;
			proc[id].size = 0;
			cout<<"Process "<<id<<" Removed from partition "<<part_id<<"\n";
		}
		else
			break;
		
		print_table(n_part);
	}
	print_table(n_part);
	cout<<"Total Unused Space : "<<tot_mem - used;
	return;
}


