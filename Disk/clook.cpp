#include <bits/stdc++.h>

using namespace std;

void disk_clook()
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
	for(int i = pos-1; i >= 0; i--) // left
	{
		cout<<req[i+1]<<"->"<<req[i]<<" : "<<abs(req[i+1]-req[i])<<"\n";
		seek += abs(req[i+1] - req[i]);
	}
	
	if(pos != n) // go to right end
	{
		cout<<req[0]<<"--->"<<req[n]<<" : "<<abs(req[n]-req[0])<<"\n";
		seek += abs(req[n] - req[0]);
	}
	
	for(int i = n; i > pos + 1; i--) // right to left
	{
		cout<<req[i]<<"->"<<req[i-1]<<" : "<<abs(req[i]-req[i-1])<<"\n";
		seek += abs(req[i] - req[i-1]);
	}
		
	cout<<CYAN<<"\nTotal Head Movement : "<<seek;
}

/*int main()
{
	disk_clook();
}*/
