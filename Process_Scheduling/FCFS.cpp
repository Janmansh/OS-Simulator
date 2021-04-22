/**
 * @author: Janmansh Agarwal 
 * @course: Operating Systems Lab.
 * @course_id: CS255
 * @roll:   191CS205
 *   
 * */

#include<bits/stdc++.h>
using namespace std;

void FCFS() {
    
	cout << "\nEnter the number of processes: ";
	int n,i;
	cin >> n;
	while(n<0){
		cout<<RED "Wrong input, try again" WHITE "\nEnter number of processes: ";
		cin>>n;
	}
	vector<tuple<int, int, int, int, int>>times(n); // {at, bt, ct, tat, wt}
	
	cout << UN "Process Details" RESET << endl <<endl;
	for(i=0;i<n;i++){
	    int t;
		cout << "Arrival Time P"<<i<<": ";
	    cin>>t;
		while(t<0){
			cout<<"Wrong input, try again\nArrival Time P"<<i<<": ";
			cin>>t;
		}
	    get<0>(times[i])=t;  // Arrival time
		cout << "Burst Time   P"<<i<<": ";
	    cin>>t;
		while(t<0){
			cout<<"Wrong input, try again\nBurst Time   P"<<i<<": ";
			cin>>t;
		}
		cout << endl;
	    get<1>(times[i])=t;  // Burst time
	    get<2>(times[i])=0;  // Completion time
	    get<3>(times[i])=0;  // Turn around time
	    get<4>(times[i])=0;  // Waiting time
	}
	
	sort(times.begin(),times.end()); // sorting according to Arrival time
	
	int ti=0;   // current time
	
	for(i=0;i<n;i++){
	    
	    if(ti < get<0>(times[i]) ) ti = get<0>(times[i]);
	    
	    get<2>(times[i]) = ti + get<1>(times[i]);
	    ti+=get<1>(times[i]);
	    
	    get<3>(times[i]) = get<2>(times[i]) - get<0>(times[i]);
	    get<4>(times[i]) = get<3>(times[i]) - get<1>(times[i]);
	}
	
	double TAT=0,TWT=0;
	
	for(i=0;i<n;i++){
	    TAT += get<3>(times[i]);
	    TWT += get<4>(times[i]);
	}

	cout << "\n" MAGENTA "Process No.\tArrival Time\tBurst Time\tCompletion Time\t\tTurn-around Time\tWaiting Time\n" WHITE;
	for(i=0;i<n;i++){
		cout << i+1 << "\t\t" << get<0>(times[i]) << "\t\t" << get<1>(times[i]) << "\t\t" << get<2>(times[i]) << "\t\t\t" << get<3>(times[i]) << "\t\t\t" << get<4>(times[i]) << "\n";
	}
	
	TAT = TAT/(1.0*n);    // Average TAT
	TWT = TWT/(1.0*n);    // Average WT
	
	cout << GREEN "\nAverage Turn around time is: " << TAT <<"\n";
	cout <<         "Average Waiting time is    : " << TWT <<"\n" RESET;
	
	return;
}
