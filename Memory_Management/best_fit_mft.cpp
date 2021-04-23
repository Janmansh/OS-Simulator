#include <iostream>

using namespace std;

struct bmft_partition {
	int size;
	bool allocated;
	int pid;
};

struct bmft_process {
	int size;
	int part_no;
	int exist;
};


void best_fit_mft()
{
	struct bmft_partition bmft_part[100];
	struct bmft_process bmft_proc[100];

	for(int i = 0; i < 100; i++)
	{
		bmft_proc[i].exist = 0;
		bmft_proc[i].part_no = -1;
		bmft_proc[i].size = 0;
		bmft_part[i].pid = -1;
		bmft_part[i].size = 0;
		bmft_part[i].allocated = false;
	}

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
		cin>>bmft_part[i].size;
		bmft_part[i].allocated = false;
		bmft_part[i].pid = -1;
		if(backup >= bmft_part[i].size) // check if free memory is available
		{
			valid_parts++;
			backup -= bmft_part[i].size;
			bmft_part[i].allocated = true;
			printf("Partition Allocated\n");
			if(high < bmft_part[i].size)
				high = bmft_part[i].size;
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
			else if(bmft_proc[id].exist == 1)
			{
				cout<<"Process already exists in partition "<<bmft_proc[id].part_no<<"\n";
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
				if(bmft_part[i].allocated && bmft_part[i].pid == -1 && sz <= bmft_part[i].size && bmft_part[i].size < small)
				{
					small = bmft_part[i].size;
					pos = i;
				}	
			}
			
			if(pos != -1)
			{
				bmft_part[pos].pid = id;
				bmft_proc[id].part_no = pos;
				bmft_proc[id].size = sz;
				bmft_proc[id].exist = 1;
				cout<<id<<" is accomadated in partition "<<pos<<"\n";
				used += bmft_proc[id].size;
			}
			
			if(bmft_proc[id].exist == 0)
			{
				bool find = false;
				for(int i = 0; i < n_part; i++)
				{
					int temp = bmft_part[i].pid;
					if(temp != -1)
					{
						if(bmft_part[i].size - bmft_proc[temp].size >= sz)
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
			
			int part_id = bmft_proc[id].part_no;
			if(part_id == -1)
			{
				cout<<"Process does not exist\n";
				continue;
			}
			bmft_part[part_id].pid = -1;
			used -= bmft_proc[id].size;
			bmft_proc[id].exist =  0;
			bmft_proc[id].part_no = -1;
			bmft_proc[id].size = 0;
			cout<<"Process "<<id<<" Removed from partition "<<part_id<<"\n";
		}
		else
			break;
		
	
		cout<<GREEN<<"\n\t\tMemory Table\n"<<WHITE;
		for(int i = 0; i < n_part; i++)
		{
			if(!bmft_part[i].allocated)
			continue;
			
			cout<<CYAN<<bmft_part[i].size<<" | ";
			if(bmft_part[i].pid == -1)
				cout<<"Empty\n"<<WHITE;
			else
				cout<<"Process "<<bmft_part[i].pid<<" Size "<<bmft_proc[bmft_part[i].pid].size<<"\n"<<WHITE;
		}
	}
	cout<<"\nTotal Unused Space : "<<tot_mem - used;
	
	for(int i = 0; i < 100; i++)
	{
		bmft_proc[i].exist = 0;
		bmft_proc[i].part_no = -1;
		bmft_proc[i].size = 0;
		bmft_part[i].pid = -1;
		bmft_part[i].size = 0;
		bmft_part[i].allocated = false;
	}

	return;
}


