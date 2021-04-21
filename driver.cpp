#include <bits/stdc++.h>
#include "animations.cpp"
#include "paging.cpp"
#include "bankers.c"
#include "Process_Scheduling/FCFS.cpp"
#include "Process_Scheduling/SJF.cpp"
#include "Process_Scheduling/Round_Robin.cpp"
#include "Process_Scheduling/Priority_preemptive.cpp"

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
				bankers();
				break;
			case 3:
				int algo;
				cout << "Enter 1 for FCFS\nEnter 2 for SJF\nEnter 3 for Round Robin\nEnter 4 for Priority Preemptive\n";
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
					default:
						cout << "Wrong input\n" << endl;
				}
			default:
				cout << "Wrong input" <<endl;
		}
	}
	return 0;
}
