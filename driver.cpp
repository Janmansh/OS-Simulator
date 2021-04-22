#include <bits/stdc++.h>
#include "animations.cpp"
#include "Paging/paging.cpp"
#include "Deadlock/banker_resource.cpp"
#include "Process_Scheduling/FCFS.cpp"
#include "Process_Scheduling/SJF.cpp"
#include "Process_Scheduling/Round_Robin.cpp"
#include "Process_Scheduling/Priority_preemptive.cpp"
#include "Process_Scheduling/HRRN.cpp"

int main(){
	int choice;
	main_animation();
	cout << "Print any key to continue : ";
	getchar();
	
	while(true){
	// Print the menu
	// defined in animations
	print_main_menu();
	
	//user choice
	cin >> choice;
		switch(choice){
			case 1:
				paging_animation();
				paging();
				break;
			case 2:
				dead_safe_animation();
				banker_resource();
				break;
			case 3:
				int algo;
				cout << "Enter 1 for FCFS\nEnter 2 for SJF\nEnter 3 for Round Robin\nEnter 4 for Priority Preemptive\nEnter 5 for HRRN\n";
				cin >> algo;
				switch(algo){
					case 1:
						FCFS();
						break;
					case 2:
						SJF();
						break;
					case 3:
						Round_Robin();
						break;
					case 4:
						Priority_preemptive();
						break;
					case 5:
						HRRN();
						break;
					default:
						cout << "Wrong input\n" << endl;
				}
				break;
			default:
				cout << "Wrong input" <<endl;
		}
	}
	return 0;
}
