#include <bits/stdc++.h>
#include "animations.cpp"
#include "Paging/paging.cpp"
#include "Deadlock/banker_resource.cpp"
#include "Memory_Management/Worst_Fit.cpp"
#include "Memory_Management/Worst_Fit_f.cpp"
#include "Memory_Management/Best_Fit.cpp"
#include "Memory_Management/First_Fit.cpp"

#include "Process_Scheduling/FCFS.cpp"
#include "Process_Scheduling/SJF.cpp"
#include "Process_Scheduling/Round_Robin.cpp"
#include "Process_Scheduling/Priority_preemptive.cpp"
#include "Process_Scheduling/HRRN.cpp"
#include "Process_Scheduling/LJF.cpp"
#include "Process_Scheduling/LRTF.cpp"
#include "Process_Scheduling/SRTF.cpp"
#include "Process_Scheduling/Priority_non_preemptive.cpp"

#include "Disk/clook.cpp"
#include "Disk/look.cpp"
#include "Disk/cscan.cpp"
#include "Disk/fcfs.cpp"
#include "Disk/scan.cpp"
#include "Disk/sstf.cpp"

int main()
{
	int choice;
	int algo;

	main_animation();
	cout << "Print any key to continue : ";
	getchar();

	while (true)
	{
		// Print the menu
		// defined in animations
		print_main_menu();

		//user choice
		cin >> choice;
		switch (choice)
		{
		case 1:
			paging_animation();
			paging();
			break;
		case 2:
			dead_safe_animation();
			cout << RESET;
			banker_resource();
			cout << YELLOW "\n\nPress Any Key to continue : " RESET;
			getchar();
			getchar();
			break;
		case 3:
			process_sched_animation();
			cout << " \n" YELLOW UN "Choose Algorithm to simulate" RESET << endl
				 << endl;
			cout << "\n 1. First Come First Serve [FCFS]" << endl;
			cout << " 2. Shortest Job First [SJF]" << endl;
			cout << " 3. Round Robin [RR]" << endl;
			cout << " 4. Longest Job First [LJF]" << endl;
			cout << " 5. Shortest Remaining Time First [SRTF]" << endl;
			cout << " 6. Longest Remaining Time First [LRTF]" << endl;
			cout << " 7. Highest Response Ratio Next [HRRN]" << endl;
			cout << " 8. Priority Non-preemptive [Pri_non]" << endl;
			cout << " 9. Priority Preemptive [Pri_p]\n"
				 << endl;
			cout << " 0. TO EXIT**\n"
				 << endl;
			cout << YELLOW "Your choice : ";
			cin >> algo;
			cout << RESET;
			switch (algo)
			{
			case 0:
				break;
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
				LJF();
				break;
			case 5:
				SRTF();
				break;
			case 6:
				LRTF();
				break;
			case 7:
				HRRN();
				break;
			case 8:
				Priority_non_preemptive();
				break;
			case 9:
				Priority_preemptive();
				break;
			default:
				cout << "Wrong input\n";
				break;
			}
			cout << YELLOW "\n\nPress Any Key to continue : " RESET;
			getchar();
			getchar();
			break;

		case 4:
			mem_animations();
			cout << " \n" YELLOW UN "Choose Algorithm to simulate" RESET << endl
				 << endl;
			cout << "\n 1. MFT [worst fit]" << endl;
			cout << " 2. MVT [first fit]" << endl;
			cout << " 3. MVT [worst fit]" << endl;
			cout << " 4. MVT [best  fit]\n"
				 << endl;
			cout << " 9. TO EXIT**\n"
				 << endl;
			cout << YELLOW "Your choice : ";
			cin >> algo;
			cout << RESET;
			switch (algo)
			{
			case 1:
				worst_fit_delete();
				break;
			case 2:
				First_Fit();
				break;
			case 3:
				Worst_Fit();
				break;
			case 4:
				Best_Fit();
				break;
			case 5:

				break;
			case 6:
				break;
			}
			cout << YELLOW "\n\nPress Any Key to continue : " RESET;
			getchar();
			getchar();
			break;
		case 5:
			sync_animations();
			cout << " \n" YELLOW UN "Choose Algorithm to simulate" RESET << endl
				 << endl;
			cout << "\n 1. Producer Consumer" << endl;
			cout << " 2. Reader Writer" << endl;
			cout << " 3. Sleeping Barber" << endl;
			cout << " 4. Dining Philosphers\n"
				 << endl;
			cout << " 9. TO EXIT**\n"
				 << endl;
			cout << YELLOW "Your choice : ";
			cin >> algo;
			cout << RESET;
			switch (algo)
			{
			case 1:
				// TODO : Add call to PC
				break;
			case 2:
				// TODO : Add RW();
				break;
			case 3:
				// TODO : Add SB();
				break;
			case 4:
				// TODO : Add DP();
				break;
			}
			cout << YELLOW "\n\nPress Any Key to continue : " RESET;
			getchar();
			getchar();
			break;
		case 6:
			disk_animations();
			cout << " \n" YELLOW UN "Choose Algorithm to simulate" RESET << endl
				 << endl;
			cout << "\n 1. C-LOOK" << endl;
			cout << " 2. C-SCAN" << endl;
			cout << " 3. FCFS" << endl;
			cout << " 4. LOOK" << endl;
			cout << " 5. SCAN" << endl;
			cout << " 6. SSTF\n"
				 << endl;
			cout << " 9. TO EXIT**\n"
				 << endl;
			cout << YELLOW "Your choice : ";
			cin >> algo;
			cout << RESET;
			switch (algo)
			{
			case 1:
				disk_clook();
				break;
			case 2:
				disk_cscan();
				break;
			case 3:
				disk_fcfs();
				break;
			case 4:
				disk_look();
				break;
			case 5:
				disk_scan();
				break;
			case 6:
				disk_sstf();
				break;
			}
			cout << YELLOW "\n\nPress Any Key to continue : " RESET;
			getchar();
			getchar();
			break;
		default:
			cout << "Wrong input" << endl;
		}
	}
	return 0;
}
