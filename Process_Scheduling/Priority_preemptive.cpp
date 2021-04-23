/**
 * @author: Janmansh Agarwal 
 * @course: Operating Systems Lab.
 * @course_id: CS255
 * @roll:   191CS205
 *   
 * */

#include<bits/stdc++.h>
using namespace std;

void Priority_preemptive(){
    
	cout << "Enter the number of processes: ";
	int n,i,j;
	cin>>n;
	while(n<0){
		cout<<"Wrong input, try again\nEnter number of processes: ";
		cin>>n;
	}
	vector<tuple<int, int, int, int, int, int>>times(n); // {at, bt, priority ct, tat, wt}
	
	cout << "Enter the Arrival time and Burst time respectively of " << n << " programs:\n";

    int bt[n];  // Burst time

	for(i=0;i<n;i++){
	    int t;
		cout << "Arrival Time: ";
	    cin>>t;
		while(t<0){
			cout<<"Wrong input, try again\nArrival time: ";
			cin>>t;
		}
	    get<0>(times[i])=t;  // Arrival time
	    cout << "Burst Time: ";
	    cin>>t;
		while(t<0){
			cout<<"Wrong input, try again\nBurst time: ";
			cin>>t;
		}
	    get<1>(times[i])=t;  // Burst time
        bt[i] = t;
        cout << "Priority(0 means highest priority): ";
	    cin>>t;
		while(t<0){
			cout<<"Wrong input, try again\nPriority: ";
			cin>>t;
		}
        get<2>(times[i]) = t;
	    get<3>(times[i])=0;  // Completion time
	    get<4>(times[i])=0;  // Turn around time
	    get<5>(times[i])=0;  // Waiting time
	}
    
    int time = 0;

    while(1){
        int priority = -1;
        int mi = INT_MAX;
        int c=0;
        for(i=0;i<n;i++){
            if(bt[i]==0)c++;
            mi = min(mi, get<0>(times[i]));
            if(get<0>(times[i])<=time && bt[i]!=0){
                if(priority == -1){
                    priority = i;
                }
                else{
                    if(get<2>(times[i])<get<2>(times[priority])){
                        priority = i;
                    }
                    else if(get<2>(times[i]) == get<2>(times[priority]) && get<0>(times[i]) < get<0>(times[priority])){
                        priority = i;
                    }
                }
            }
        }
        if(c==n)break;
        if(priority == -1){
            time = mi;
            continue;
        }
        bt[priority]--;
        time++;
        if(bt[priority]==0){
            get<3>(times[priority]) = time; // CT
            get<4>(times[priority]) = get<3>(times[priority]) - get<0>(times[priority]);
            get<5>(times[priority]) = get<4>(times[priority]) - get<1>(times[priority]);
        }
    }
	
	double TAT=0,TWT=0;
	
	for(i=0;i<n;i++){
	    TAT += get<4>(times[i]);
	    TWT += get<5>(times[i]);
	}

	cout << CYAN<<"\nProcess No.\tArrival Time\tBurst Time\tPriority\tCompletion Time\t\tTurn-around Time\tWaiting Time\n"<<WHITE;
	for(i=0;i<n;i++){
		cout<< i+1 << "\t\t" << get<0>(times[i]) << "\t\t" << get<1>(times[i]) << "\t\t" << get<2>(times[i]) << "\t\t" << get<3>(times[i]) << "\t\t\t" << get<4>(times[i]) << "\t\t\t" << get<5>(times[i]) << "\n";
	}
	
	TAT = TAT/(1.0*n);    // Average TAT
	TWT = TWT/(1.0*n);    // Average WT
	
	cout << GREEN<<"\nAverage Turn around time is: " << TAT <<"\n";
	cout << "Average Waiting time is: " << TWT <<"\n"<<WHITE;
	
	return;
}


