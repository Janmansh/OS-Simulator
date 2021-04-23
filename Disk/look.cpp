#include <bits/stdc++.h>

using namespace std;

void disk_look()
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
	
	if(pos != n) // go to right
	{
		cout<<req[0]<<"->"<<req[pos+1]<<" : "<<abs(req[pos+1]-req[0])<<"\n";
		seek += abs(req[pos+1] - req[0]);
	}
	
	for(int i = pos+2; i <= n; i++) // right to left
	{
		cout<<req[i-1]<<"->"<<req[i]<<" : "<<abs(req[i-1]-req[i])<<"\n";
		seek += abs(req[i-1] - req[i]);
	}
		
	cout<<CYAN<<"\nTotal Head Movement : "<<seek;
}

/*int main()
{
	disk_look();
}*/

