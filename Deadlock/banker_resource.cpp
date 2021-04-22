#include <bits/stdc++.h>

using namespace std;

void banker_resource()
{
	int process, resource;
	printf("Enter number of processes : ");
	scanf("%d", &process);

	printf("Enter number of resources : ");
	scanf("%d", &resource);

	int total[resource], available[resource], flag[process];
	printf("Enter total available resource of each type \n");
	for(int i = 0; i < resource; i++)
	{
		printf("Resource %c : ", 65+i);
		scanf("%d", &total[i]);
		available[i] = total[i];
	}

	int table_alloc[process][resource], table_max[process][resource], table_need[process][resource];
	for(int i = 0; i < process; i++)
	{
		flag[i] = 0;
		printf("\nFor process %d enter the number of resources allocated : \n", i);
		for(int j = 0; j < resource; j++)
		{
			printf("Resource %c : ", 65+j);
			scanf("%d", &table_alloc[i][j]);
			available[j] -= table_alloc[i][j];
		}
		printf("\nFor process %d enter the maximum number of resources required : \n", i);
		for(int j = 0; j < resource; j++)
		{
			printf("Resource %c : ", 65+j);
			scanf("%d", &table_max[i][j]);
			if(table_max[i][j] > total[j])
			{
				printf("Not enough resources for process %d", i);
				return;
			}
				
			table_need[i][j] = table_max[i][j] - table_alloc[i][j];
			if(table_need[i][j] < 0)
				table_need[i][j] = 0;
		}
	}
	
	for(int i = 0; i < resource; i++)
	{
		if(available[i] < 0)
		{
			printf("\nInvalid Configuration, More resources allocated than available\n");
			return;
		}
	}

	printf("\ntotal number of each resource available freely initially\n");
	for(int i = 0; i < resource; i++)
		printf("Resource %c = %d\n", 65+i, available[i]);

	int done = process;
	while(done--)
	{
		for(int i = 0; i < process; i++)
		{
			if(flag[i])
				continue;

			bool check = true;
			for(int j = 0; j < resource; j++)
			{
				if(available[j] < table_need[i][j])
				check = false;
			}
			if(check)
			{
				flag[i] = 1;
				printf("Process %d is done\n", i);

				for(int j = 0; j < resource; j++)
					available[j] += table_alloc[i][j];
			}
		}
	}
	
	bool ans = true;
	for(int i = 0; i < process; i++)
	{
		if(flag[i] == 0)
		{
			printf("Process %d could not be allocated resources\n", i);
			ans = false;
		}
	}
	
	if(ans == true)	
	printf("All proccesses are done this was a safe execution sequence\n");
	return;
}


