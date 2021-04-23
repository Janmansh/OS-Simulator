#include <bits/stdc++.h>

using namespace std;

void disk_scan()
{
	int n, track;
	cout<<WHITE<<"\nEnter Number Of Requests : ";
	cin>>n;
	cout<<"\nEnter Number Of Tracks : ";
	cin>>track;
	int req[n+1];
	cout<<GREEN<<"\nEnter Current Postions of R/W Head : ";
	cin>>req[0];
	cout<<CYAN<<"\nEnter the Requests\n";
	for(int i = 1; i <= n; i++)
	cin>>req[i];
	
	int first = req[0];
	sort(req, req+n+1);
	int seek = 0, pos;
	for(int i = 0; i <= n; i++)
	{
		if(req[i] == first)
			pos = i;
	}
	
	cout<<GREEN<<"\nHead Movement\n";
	for(int i = pos-1; i >= 0; i--) // head to left
	{
		cout<<req[i+1]<<"->"<<req[i]<<" : "<<abs(req[i+1]-req[i])<<"\n";
		seek += abs(req[i+1] - req[i]);
	}
	if(req[0] != 0)
	{
		cout<<req[0]<<"->"<<0<<" : "<<abs(req[0]-0)<<"\n";
		seek += abs(req[0] - 0);
	}
	
	if(pos != n) // right of initial head
	{
		cout<<0<<"->"<<req[pos+1]<<" : "<<abs(req[pos+1]-0)<<"\n";
		seek += abs(req[pos+1] - 0);
	}
	for(int i = pos+2; i <= n; i++) // from head to right
	{
		cout<<req[i-1]<<"->"<<req[i]<<" : "<<abs(req[i-1]-req[i])<<"\n";
		seek += abs(req[i-1] - req[i]);
	}
	if(req[n] != track-1)
	{
		cout<<req[n]<<"->"<<track-1<<" : "<<abs(req[n]-track+1)<<"\n";
		seek += abs(req[n] - track + 1);
	}
		
	cout<<CYAN<<"\nTotal Head Movement : "<<seek;
}

/*int main()
{
	disk_scan();
}*/

