#include <iostream>

using namespace std;

void disk_sstf()
{
	int n;
	cout<<WHITE<<"\nEnter Number Of Requests : ";
	cin>>n;
	int req[n+1];
	cout<<"\nEnter Current Postions of R/W Head : ";
	cin>>req[0];
	cout<<CYAN<<"\nEnter the Requests\n";
	for(int i = 1; i <= n; i++)
	cin>>req[i];
	
	int seek = 0, prev = req[0];
	int done[n+1];
	memset(done, 0, sizeof(done));
	done[0] = 1;
	
	cout<<GREEN<<"\nHead Movement\n";
	for(int i = 1; i <= n; i++)
	{
		int idx, small = 1e5;
		for(int j = 1; j <= n; j++)
		{
			if(done[j] != 1 && abs(req[j] - prev) < small)
			{
				idx = j;
				small = abs(req[j] - prev);
			}
		}
		done[idx] = 1;
		cout<<prev<<"->"<<req[idx]<<" : "<<small<<"\n";
		seek += small;
		prev = req[idx];
	}
	
	cout<<CYAN<<"\nTotal Head Movement : "<<seek;
}
/*
int main()
{
	disk_sstf();
}*/

