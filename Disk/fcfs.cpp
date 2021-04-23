
#include <iostream>

using namespace std;

void disk_fcfs()
{
	int n;
	cout<<WHITE<<"\nEnter Number Of Requests : ";
	cin>>n;
	int req[n+1];
	cout<<WHITE<<"\nEnter Current Postions of R/W Head : ";
	cin>>req[0];
	cout<<CYAN<<"\nEnter the Requests\n";
	for(int i = 1; i <= n; i++)
	cin>>req[i];
	
	int seek = 0;
	cout<<GREEN<<"\nHead Movement\n";
	for(int i = 1; i <= n; i++)
	{
		cout<<req[i-1]<<"->"<<req[i]<<" : "<<abs(req[i]-req[i-1])<<"\n";
		seek += abs(req[i] - req[i-1]);
	}
	
	cout<<CYAN<<"\nTotal Head Movement : "<<seek;
}

/*int main()
{
	disk_fcfs();
}*/
