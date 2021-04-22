#include <bits/stdc++.h>

using namespace std;

void disk_look()
{
	int n, track;
	cout<<"\nEnter Number Of Requests : ";
	cin>>n;
	cout<<"\nEnter Number Of Tracks   : ";
	cin>>track;
	int req[n+1];
	cout<<"\nEnter Current Postions of R/W Head : ";
	cin>>req[0];
	cout<<"\n"UN"Enter the Requests"RESET"\n";
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
	
	cout<<"\nHead Movement\n";
	for(int i = pos-1; i >= 0; i--)
	{
		cout<<req[i+1]<<"->"<<req[i]<<" : "<<abs(req[i+1]-req[i])<<"\n";
		seek += abs(req[i+1] - req[i]);
	}
	
	if(pos != n)
	{
		cout<<req[0]<<"->"<<req[pos+1]<<" : "<<abs(req[pos+1]-req[0])<<"\n";
		seek += abs(req[pos+1] - req[0]);
	}
	
	for(int i = pos+2; i <= n; i++)
	{
		cout<<req[i-1]<<"->"<<req[i]<<" : "<<abs(req[i-1]-req[i])<<"\n";
		seek += abs(req[i-1] - req[i]);
	}
		
	cout<<"\nTotal Head Movement : "<<seek;
}