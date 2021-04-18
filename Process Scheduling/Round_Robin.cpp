#include<bits/stdc++.h>
using namespace std;

void Round_Robin(){
    
	cout << "Enter the number of processes: ";
	int n,i,j;
	cin>>n;
	while(n<0){
		cout<<"Wrong input, try again\nEnter number of processes: ";
		cin>>n;
	}
	vector<tuple<int, int, int, int, int>>times(n); // {at, bt, ct, tat, wt}
	
	cout << "Enter the Arrival time and Burst time respectively of "<<n<<" programs:\n";
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
	    get<2>(times[i])=0;  // Completion time
	    get<3>(times[i])=0;  // Turn around time
	    get<4>(times[i])=0;  // Waiting time
	}
	
	int ti=INT_MAX;   // current time

	int slicetime;
	
	cout << "Enter slice time: ";
	cin >> slicetime;

	while(slicetime <=0 ){
		cout << "Wrong input, try again\nEnter slice time: ";
		cin >> slicetime;
	}
	
	for(i=0;i<n;i++){
	    ti = min(ti, get<0>(times[i]));
	}
	
	int visited[n]={0}, bt[n];      // completed programs and Burst time
	
	for(i=0;i<n;i++){
	    bt[i]=get<1>(times[i]);
	}
	
	while(1){
	    
	    int f=0;
	    
	    for(i=0;i<n;i++){
	        
	        if(visited[i])continue;
	        
	        if(get<0>(times[i])<=ti&&get<1>(times[i])>0){
	            f=1;
	            ti += min(bt[i], 2);
	            bt[i] = max(0, bt[i]-slicetime);
	            
	            if(bt[i]==0){
	                get<2>(times[i]) = ti;
	                get<3>(times[i]) = get<2>(times[i]) - get<0>(times[i]);
	                get<4>(times[i]) = get<3>(times[i]) - get<1>(times[i]);
	                visited[i]=1;
	            }
	            
	        }
	    }
	    
	    if(f==0){
	        ti++;
	    }
	    
	    f=0;
	    
	    // checking if all programs completed
	    for(i=0;i<n;i++){
	        if(visited[i]==0){
	            f=1;
	            break;
	        }
	    }
	    
	    if(f==0)break;
	}
	
	double TAT=0,TWT=0;
	
	for(i=0;i<n;i++){
	    TAT += get<3>(times[i]);
	    TWT += get<4>(times[i]);
	}

	cout << "\nProcess No.  Arrival Time  Burst Time  Completion Time  Turn-around Time  Waiting Time\n";
	for(i=0;i<n;i++){
		cout << "    " << i+1 << "            " << get<0>(times[i]) << "             " << get<1>(times[i]) << "             " << get<2>(times[i]) << "               " << get<3>(times[i]) << "                " << get<4>(times[i]) << "\n";
	}
	
	TAT = TAT/(1.0*n);    // Average TAT
	TWT = TWT/(1.0*n);    // Average WT
	
	cout << "\nAverage Turn around time is: " << TAT <<"\n";
	cout << "Average Waiting time is: " << TWT <<"\n";
	
	return;
}

int main(){
	Round_Robin();
	return 0;
}
