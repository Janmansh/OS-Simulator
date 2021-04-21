#include <bits/stdc++.h>
#include "animations.cpp"
#include "paging.cpp"
#include "bankers.c"
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
			default:
				cout << "Wrong input" <<endl;
		}
	}
	return 0;
}
