#include <bits/stdc++.h>

using namespace std;

void disk_cscan()
{
	int n, track;
	cout<<"\nEnter Number Of Requests : ";
	cin>>n;
	cout<<"\nEnter Number Of Tracks : ";
	cin>>track;
	int req[n+1];
	cout<<"\nEnter Current Postions of R/W Head : ";
	cin>>req[0];
	cout<<"\nEnter the Requests\n";
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
	
	if(pos != n) // to right end
	{
		cout<<0<<"--->"<<track-1<<" : "<<abs(track-1)<<"\n";
		seek += abs(track-1);
	}
	int prev = track-1;
	for(int i = n; i > pos; i--) // right to left
	{
		cout<<prev<<"->"<<req[i]<<" : "<<abs(prev-req[i])<<"\n";
		seek += abs(prev - req[i]);
		prev = req[i];
	}
	cout<<"\nTotal Head Movement : "<<seek;
}

/*int main()
{
	disk_cscan();
}*/
