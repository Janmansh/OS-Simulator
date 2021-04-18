/* MFT with First fit */

#include <stdio.h>

void MFT()
{
	int total, i, j, n, m, x;
	printf("Enter Total Size: ");
	scanf("%d", &total);

	while (total <= 0)
	{
		printf("Enter a positive total size\nEnter Total Size: ");
		scanf("%d", &total);
	}

	printf("Enter the Number of Partitions: ");
	scanf("%d", &n); //n

	while (n <= 0)
	{
		printf("Invalid No of Partition \nEnter the Number of Partitions: ");
		scanf("%d", &n);
	}

	int Partition[2][n];
	for (i = 0; i < n; i++)
	{
		printf("Enter the Partitions size of Partition %d: ", i + 1);
		scanf("%d", &Partition[0][i]);
		while (Partition[0][i] <= 0)
		{
			printf("Invalid Partitions size for Partition %d\nEnter the Partitions size of Partition %d: ", i + 1, i + 1);
			scanf("%d", &Partition[0][i]);
		}
		Partition[1][i] = 0;
	}
	int waist, sum = 0;
	for (i = 0; i < n; i++)
	{
		if (sum + Partition[0][i] <= total)
		{
			sum += Partition[0][i];
			j = i;
		}
		else
		{
			printf("\nPartition-%d cant' be given as only %dKB space is remaining", i + 1, total - sum);
		}
	}
	n = j + 1;			 //no of partition in main memory starting from P0 to Pn-1
	waist = total - sum; // waist memory

	printf("\nEnter the Number of Process: ");
	scanf("%d", &m); // m number of process

	while (m < 0)
	{
		printf("Enter a Non negative no of Process \nEnter the Number of Process: ");
		scanf("%d", &m);
	}

	int Process[m], internal = 0;
	for (i = 0; i < m; i++)
	{
		printf("Enter size of P%d: ", i + 1);
		scanf("%d", &Process[i]);
		while (Process[i] <= 0)
		{
			printf("Enter a positive process size \nEnter size of P%d: ", i + 1);
			scanf("%d", &Process[i]);
		}
	}

	int count = 0;
	printf("\n");
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (Partition[1][j] == 0 && Partition[0][j] >= Process[i])
			{
				Partition[1][j] = 1;
				internal += Partition[0][j] - Process[i];
				count++;
				printf("\nP%d is Allocated to Partition %d", i + 1, j + 1);
				break;
			}
		}
		if (j >= n)
		{
			printf("\nProcess %d Could not Allocated, no Partition Size is Comptible", i + 1);
		}
		if (count == n)
		{
			printf("\nNo More memory Partition Empty, Remaining can't be Allocated...");
			break;
		}
	}
	printf("\n");
	printf("\nSpace with no Partition: %d", waist);
	printf("\nTotal internal Fregmentation is: %d\n", internal);
}

int main()
{
	MFT();
	return 0;
}
