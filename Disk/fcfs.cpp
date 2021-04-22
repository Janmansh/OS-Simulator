#include <iostream>

using namespace std;

void disk_fcfs()
{
	int n;
	cout<<"\nEnter Number Of Requests : ";
	cin>>n;
	int req[n+1];
	cout<<"\nEnter Current Postions of R/W Head : ";
	cin>>req[0];
	cout<<"\nEnter the Requests\n";
	for(int i = 1; i <= n; i++)
	cin>>req[i];
	
	int seek = 0;
	cout<<"\nHead Movement\n";
	for(int i = 1; i <= n; i++)
	{
		cout<<req[i-1]<<"->"<<req[i]<<" : "<<abs(req[i]-req[i-1])<<"\n";
		seek += abs(req[i] - req[i-1]);
	}
	
	cout<<"\nTotal Head Movement : "<<seek;
}
