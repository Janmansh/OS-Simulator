#include <unistd.h> // for usleep function
#include <bits/stdc++.h>
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#define UN "\e[4m"


using namespace std;
int main_animation() {
    for (int i = 0; i < 50; i ++) printf("\n"); // jump to bottom of console
    
    cout << CYAN "░█████╗░░██████╗  ░██████╗██╗███╗░░░███╗██╗░░░██╗██╗░░░░░░█████╗░████████╗░█████╗░██████╗░\n██╔══██╗██╔════╝  ██╔════╝██║████╗░████║██║░░░██║██║░░░░░██╔══██╗╚══██╔══╝██╔══██╗██╔══██╗\n██║░░██║╚█████╗░  ╚█████╗░██║██╔████╔██║██║░░░██║██║░░░░░███████║░░░██║░░░██║░░██║██████╔╝\n██║░░██║░╚═══██╗  ░╚═══██╗██║██║╚██╔╝██║██║░░░██║██║░░░░░██╔══██║░░░██║░░░██║░░██║██╔══██╗\n╚█████╔╝██████╔╝  ██████╔╝██║██║░╚═╝░██║╚██████╔╝███████╗██║░░██║░░░██║░░░╚█████╔╝██║░░██║\n░╚════╝░╚═════╝░  ╚═════╝░╚═╝╚═╝░░░░░╚═╝░╚═════╝░╚══════╝╚═╝░░╚═╝░░░╚═╝░░░░╚════╝░╚═╝░░╚═╝";
    cout <<"\n"<<endl;
    cout << WHITE " * COURSE NAME: Operating Systems Lab" << endl;
    cout << " * COURSE CODE: CS255" << endl;
    cout << " * COURSE INST: Dr. Shashidar S Koolagudi" << endl;
    usleep(1<<16);
    cout << " \n" UN "Team Members" RESET << endl <<endl;
    cout << WHITE " * " CYAN "Addhyan Malhotra " YELLOW "191CS202" << endl;
    cout << WHITE " * " CYAN "Abhinav Gupta    " YELLOW "191CS201" << endl;
    cout << WHITE " * " CYAN "Adithya Rajesh   " YELLOW "191CS203" << endl;
    cout << WHITE " * " CYAN "Aditya Rudra     " YELLOW "191CS204" << endl;
    cout << WHITE " * " CYAN "Agarwal Janmansh " YELLOW "191CS205" << endl;
    cout << WHITE " * " CYAN "Akash Meena      " YELLOW "191CS206" << endl;
    cout << WHITE " * " CYAN "Alan Tony        " YELLOW "191CS207" << endl;
    cout << WHITE " * " CYAN "Aniket Srivastava" YELLOW "191CS208" << endl;
    cout << WHITE " * " CYAN "Anupam Lal       " YELLOW "191CS209" << endl;
    cout << WHITE " * " CYAN "Arnab Das        " YELLOW "191CS210" << endl;


    long int j=1 <<16;
    for (size_t i = 0; i < 10; i++)
    {
        usleep(j); // move faster and faster,
        j = (int)(j * 0.9); // so sleep less each time
        cout << endl;
    }
    
    return 0;
}

int print_main_menu(){
    cout << " \n" YELLOW UN "Choose Algorithm to simulate" RESET << endl <<endl;
    cout << WHITE;
    cout << " 1. Page Replacement Algorithms"<<endl;
    cout << " 2. Deadlock Algorithms"<<endl;
    cout << " 3. Process Scheduling" << endl;
    cout << " 4. Memory Management" << endl;
    cout << " 5. Process Syncronization" << endl;
    cout << " 6. Disk Scheduling" << endl;

    cout << " 9. Exit\n"<<endl;
    long int j=1 <<16;
    for (size_t i = 0; i < 10; i++)
    {
        usleep(j); // move faster and faster,
        j = (int)(j * 0.9); // so sleep less each time
        cout << endl;
    }
    cout << YELLOW "Enter your choice : ";
    return 0;
}
int paging_animation(){
    cout << "\n" <<endl;
    cout << "██████╗  █████╗  ██████╗ ███████╗    ██████╗ ███████╗██████╗ ██╗      █████╗  ██████╗███████╗███╗   ███╗███████╗███╗   ██╗████████╗" << endl;
    cout << "██╔══██╗██╔══██╗██╔════╝ ██╔════╝    ██╔══██╗██╔════╝██╔══██╗██║     ██╔══██╗██╔════╝██╔════╝████╗ ████║██╔════╝████╗  ██║╚══██╔══╝" << endl;
    cout << "██████╔╝███████║██║  ███╗█████╗      ██████╔╝█████╗  ██████╔╝██║     ███████║██║     █████╗  ██╔████╔██║█████╗  ██╔██╗ ██║   ██║ "   << endl;
    cout << "██╔═══╝ ██╔══██║██║   ██║██╔══╝      ██╔══██╗██╔══╝  ██╔═══╝ ██║     ██╔══██║██║     ██╔══╝  ██║╚██╔╝██║██╔══╝  ██║╚██╗██║   ██║ "  << endl;
    cout << "██║     ██║  ██║╚██████╔╝███████╗    ██║  ██║███████╗██║     ███████╗██║  ██║╚██████╗███████╗██║ ╚═╝ ██║███████╗██║ ╚████║   ██║ " << endl;
    cout << "╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚══════╝    ╚═╝  ╚═╝╚══════╝╚═╝     ╚══════╝╚═╝  ╚═╝ ╚═════╝╚══════╝╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝   ╚═╝ " <<endl;
    long int j=1 <<16;
    for (size_t i = 0; i < 10; i++)
    {
        usleep(j); // move faster and faster,
        j = (int)(j * 0.9); // so sleep less each time
        cout << endl;
    }
    return 0;
}

int dead_safe_animation(){
    cout << "██████╗ ███████╗ █████╗ ██████╗     ██╗      ██████╗  ██████╗██╗  ██╗\n";
    cout << "██╔══██╗██╔════╝██╔══██╗██╔══██╗    ██║     ██╔═══██╗██╔════╝██║ ██╔╝╗\n";
    cout << "██║  ██║█████╗  ███████║██║  ██║    ██║     ██║   ██║██║     █████╔╝ \n";
    cout << "██║  ██║██╔══╝  ██╔══██║██║  ██║    ██║     ██║   ██║██║     ██╔═██╗ \n";
    cout << "██████╔╝███████╗██║  ██║██████╔╝    ███████╗╚██████╔╝╚██████╗██║  ██╗\n";
    cout << "╚═════╝ ╚══════╝╚═╝  ╚═╝╚═════╝     ╚══════╝ ╚═════╝  ╚═════╝╚═╝  ╚═╝\n";
    cout <<endl;                                                                                                       
    cout << "███████╗ █████╗ ███████╗███████╗████████╗██╗   ██╗     █████╗ ██╗      ██████╗  ██████╗ ███████╗\n";
    cout << "██╔════╝██╔══██╗██╔════╝██╔════╝╚══██╔══╝╚██╗ ██╔╝    ██╔══██╗██║     ██╔════╝ ██╔═══██╗██╔════╝\n";
    cout << "███████╗███████║█████╗  █████╗     ██║    ╚████╔╝     ███████║██║     ██║  ███╗██║   ██║███████╗\n";
    cout << "╚════██║██╔══██║██╔══╝  ██╔══╝     ██║     ╚██╔╝      ██╔══██║██║     ██║   ██║██║   ██║╚════██║\n";
    cout << "███████║██║  ██║██║     ███████╗   ██║      ██║       ██║  ██║███████╗╚██████╔╝╚██████╔╝███████║██╗\n";
    cout << "╚══════╝╚═╝  ╚═╝╚═╝     ╚══════╝   ╚═╝      ╚═╝       ╚═╝  ╚═╝╚══════╝ ╚═════╝  ╚═════╝ ╚══════╝╚═╝\n";
    long int j=1 <<16;
    for (size_t i = 0; i < 10; i++)
    {
        usleep(j); // move faster and faster,
        j = (int)(j * 0.9); // so sleep less each time
        cout << endl;
    }
    return 0;
}
int process_sched_animation(){
    
    cout << "██████╗░██████╗░░█████╗░░█████╗░███████╗░██████╗░██████╗" << endl;
    cout << "██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔════╝██╔════╝██╔════╝" << endl;
    cout << "██████╔╝██████╔╝██║░░██║██║░░╚═╝█████╗░░╚█████╗░╚█████╗░" << endl;
    cout << "██╔═══╝░██╔══██╗██║░░██║██║░░██╗██╔══╝░░░╚═══██╗░╚═══██╗" << endl;
    cout << "██║░░░░░██║░░██║╚█████╔╝╚█████╔╝███████╗██████╔╝██████╔╝" << endl;
    cout << "╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚══════╝╚═════╝░╚═════╝░" << endl;
    cout << endl;
    cout << "░██████╗░█████╗░██╗░░██╗███████╗██████╗░██╗░░░██╗██╗░░░░░██╗███╗░░██╗░██████╗░" << endl;
    cout << "██╔════╝██╔══██╗██║░░██║██╔════╝██╔══██╗██║░░░██║██║░░░░░██║████╗░██║██╔════╝░" << endl;
    cout << "╚█████╗░██║░░╚═╝███████║█████╗░░██║░░██║██║░░░██║██║░░░░░██║██╔██╗██║██║░░██╗░" << endl;
    cout << "░╚═══██╗██║░░██╗██╔══██║██╔══╝░░██║░░██║██║░░░██║██║░░░░░██║██║╚████║██║░░╚██╗" << endl;
    cout << "██████╔╝╚█████╔╝██║░░██║███████╗██████╔╝╚██████╔╝███████╗██║██║░╚███║╚██████╔╝" << endl;
    cout << "╚═════╝░░╚════╝░╚═╝░░╚═╝╚══════╝╚═════╝░░╚═════╝░╚══════╝╚═╝╚═╝░░╚══╝░╚═════╝░" << endl;
    long int j=1 <<16;
    for (size_t i = 0; i < 10; i++)
    {
        usleep(j); // move faster and faster,
        j = (int)(j * 0.9); // so sleep less each time
        cout << endl;
    }
    return 0;
}
int mem_animations(){
    cout << endl << YELLOW;
    cout << "███╗░░░███╗███████╗███╗░░░███╗░█████╗░██████╗░██╗░░░██╗" << endl;
    cout << "████╗░████║██╔════╝████╗░████║██╔══██╗██╔══██╗╚██╗░██╔╝" << endl;
    cout << "██╔████╔██║█████╗░░██╔████╔██║██║░░██║██████╔╝░╚████╔╝░" << endl;
    cout << "██║╚██╔╝██║██╔══╝░░██║╚██╔╝██║██║░░██║██╔══██╗░░╚██╔╝░░" << endl;
    cout << "██║░╚═╝░██║███████╗██║░╚═╝░██║╚█████╔╝██║░░██║░░░██║░░░" << endl;
    cout << "╚═╝░░░░░╚═╝╚══════╝╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝░░░╚═╝░░░" << endl;
    cout << endl;
    cout << "███╗░░░███╗░█████╗░███╗░░██╗░█████╗░░██████╗░███████╗███╗░░░███╗███████╗███╗░░██╗████████╗" << endl;
    cout << "████╗░████║██╔══██╗████╗░██║██╔══██╗██╔════╝░██╔════╝████╗░████║██╔════╝████╗░██║╚══██╔══╝" << endl;
    cout << "██╔████╔██║███████║██╔██╗██║███████║██║░░██╗░█████╗░░██╔████╔██║█████╗░░██╔██╗██║░░░██║░░░" << endl;
    cout << "██║╚██╔╝██║██╔══██║██║╚████║██╔══██║██║░░╚██╗██╔══╝░░██║╚██╔╝██║██╔══╝░░██║╚████║░░░██║░░░" << endl;
    cout << "██║░╚═╝░██║██║░░██║██║░╚███║██║░░██║╚██████╔╝███████╗██║░╚═╝░██║███████╗██║░╚███║░░░██║░░░" << endl;
    cout << "╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═╝░░╚═╝░╚═════╝░╚══════╝╚═╝░░░░░╚═╝╚══════╝╚═╝░░╚══╝░░░╚═╝░░░" << endl;
    long int j=1 <<16;
    for (size_t i = 0; i < 10; i++)
    {
        usleep(j); // move faster and faster,
        j = (int)(j * 0.9); // so sleep less each time
        cout << endl;
    }
    return 0;
}
int sync_animations(){
    cout << endl << YELLOW;
    cout << "██████╗░██████╗░░█████╗░░█████╗░███████╗░██████╗░██████╗" << endl;
    cout << "██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔════╝██╔════╝██╔════╝" << endl;
    cout << "██████╔╝██████╔╝██║░░██║██║░░╚═╝█████╗░░╚█████╗░╚█████╗░" << endl;
    cout << "██╔═══╝░██╔══██╗██║░░██║██║░░██╗██╔══╝░░░╚═══██╗░╚═══██╗" << endl;
    cout << "██║░░░░░██║░░██║╚█████╔╝╚█████╔╝███████╗██████╔╝██████╔╝" << endl;
    cout << "╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚══════╝╚═════╝░╚═════╝░" << endl;
    cout << endl;
    cout << "░██████╗██╗░░░██╗░█████╗░██████╗░░█████╗░███╗░░██╗██╗░██████╗░█████╗░████████╗██╗░█████╗░███╗░░██╗" << endl;
    cout << "██╔════╝╚██╗░██╔╝██╔══██╗██╔══██╗██╔══██╗████╗░██║██║██╔════╝██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║" << endl;
    cout << "╚█████╗░░╚████╔╝░██║░░╚═╝██████╔╝██║░░██║██╔██╗██║██║╚█████╗░███████║░░░██║░░░██║██║░░██║██╔██╗██║" << endl;
    cout << "░╚═══██╗░░╚██╔╝░░██║░░██╗██╔══██╗██║░░██║██║╚████║██║░╚═══██╗██╔══██║░░░██║░░░██║██║░░██║██║╚████║" << endl;
    cout << "██████╔╝░░░██║░░░╚█████╔╝██║░░██║╚█████╔╝██║░╚███║██║██████╔╝██║░░██║░░░██║░░░██║╚█████╔╝██║░╚███║" << endl;
    cout << "╚═════╝░░░░╚═╝░░░░╚════╝░╚═╝░░╚═╝░╚════╝░╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝" << endl;
    long int j=1 <<16;
    for (size_t i = 0; i < 10; i++)
    {
        usleep(j); // move faster and faster,
        j = (int)(j * 0.9); // so sleep less each time
        cout << endl;
    }
    return 0;
}
int disk_animations(){
    cout << endl << YELLOW;
    cout << "██████╗░██╗░██████╗██╗░░██╗" << endl;
    cout << "██╔══██╗██║██╔════╝██║░██╔╝" << endl;
    cout << "██║░░██║██║╚█████╗░█████═╝░" << endl;
    cout << "██║░░██║██║░╚═══██╗██╔═██╗░" << endl;
    cout << "██████╔╝██║██████╔╝██║░╚██╗" << endl;
    cout << "╚═════╝░╚═╝╚═════╝░╚═╝░░╚═╝" << endl;
    cout << endl;
    cout << "███╗░░░███╗░█████╗░███╗░░██╗░█████╗░░██████╗░███████╗███╗░░░███╗███████╗███╗░░██╗████████╗" << endl;
    cout << "████╗░████║██╔══██╗████╗░██║██╔══██╗██╔════╝░██╔════╝████╗░████║██╔════╝████╗░██║╚══██╔══╝" << endl;
    cout << "██╔████╔██║███████║██╔██╗██║███████║██║░░██╗░█████╗░░██╔████╔██║█████╗░░██╔██╗██║░░░██║░░░" << endl;
    cout << "██║╚██╔╝██║██╔══██║██║╚████║██╔══██║██║░░╚██╗██╔══╝░░██║╚██╔╝██║██╔══╝░░██║╚████║░░░██║░░░" << endl;
    cout << "██║░╚═╝░██║██║░░██║██║░╚███║██║░░██║╚██████╔╝███████╗██║░╚═╝░██║███████╗██║░╚███║░░░██║░░░" << endl;
    cout << "╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═╝░░╚═╝░╚═════╝░╚══════╝╚═╝░░░░░╚═╝╚══════╝╚═╝░░╚══╝░░░╚═╝░░░" << endl;
    long int j=1 <<16;
    for (size_t i = 0; i < 10; i++)
    {
        usleep(j); // move faster and faster,
        j = (int)(j * 0.9); // so sleep less each time
        cout << endl;
    }
    return 0;
}