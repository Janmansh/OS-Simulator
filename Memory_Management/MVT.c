// MVT Algo 

#include <stdio.h>

void MVT()
{
	int i, j, n, m, total, sum = 0, x, waste, rem, count = 0;
	printf("Enter the Total Size: ");
	scanf("%d", &total);

	while (total <= 0)
	{
		printf("Enter a positive total size\nEnter Total Size: ");
		scanf("%d", &total);
	}
	rem = total;

	printf("Enter the Number of Processes: ");
	scanf("%d", &n); //n for no of Process

	while (n <0)
	{
		printf("Enter a non negative no of process \nEnter the Number of Process: ");
		scanf("%d", &n);
	}

	/* taking input the size of each process*/
	for (i = 0; i < n; i++)
	{
		printf("Enter size of P%d: ", i + 1);
		scanf("%d", &x);
		while (x <= 0)
		{
			printf("Enter a positive size for process \nEnter size of P%d: ", i + 1);
			scanf("%d", &x);
		}

		if (rem >= x)
		{
			count++;
			rem = rem - x;
			printf("P%d is alloted\n", i + 1);
		}
		else
			printf("P%d can't be allocated, only %dKB space is remaining\n", i + 1, rem);
	}

	printf("\nWaisted memory is:%d\n", rem);
	printf("No of Process accomodated: %d\n", count);
	// there is no internal fregmentation in the variable partition case.
	
}

int main()
{
	MVT();
	return 0;
}