/**
 * @author: Addhyan Malhotra 
 * @course: Operating Systems Lab.
 * @course_id: CS255
 * @roll:   191CS202
 *   
 * */
#include <bits/stdc++.h>
#include "optimal.cpp"
#include "Address_space.cpp"

using namespace std;

// Structure to hold page
struct Page{
    int id;
    int timestamp;

    // Default initializer
    Page(int x, int y){
        id =x;
        timestamp = y;
    }
};

// Driver code for LRU
// Page replacement Algo
void lru(int num_frames){

    // Declare and initialize variables
    struct Page* frames[num_frames];
    int faults=0, reqs=0,pid,i,time=0,min,min_index;
    char choice;
    
    // initialize each frame to empty.
    for(i=0;i<num_frames;++i)
        frames[i]=nullptr;
    
    //  Print user menu.
    cout << "\n" UN YELLOW "You Have Selected LRU Replacement Scheme" RESET<< endl;
    cout << "\n 1. Request Page"<<endl;
    cout << " 2. Stop Adding page\n"<<endl;
    cout << " **ANY OTHER KEY TO EXIT**\n"<<endl;
    
    // Menu Driven Logic
    while (true)
    {
        // Get user Input
        cout << "Your choice   : ";
        scanf("%c%c",&choice,&choice);

        // Switch Case of choices
        switch(choice){

            // Case 1 => Addition of Page.
            case '1':
                // Take User Input
                cout << "Enter Page id : ";
                cin >> pid;
                
                // increment requests
                ++reqs;
                
                // Linear search for requested page in
                // available frames
                for (i=0;i<num_frames;++i){
                    
                    // If Page is found
                    // Update user
                    if(frames[i] && frames[i]->id == pid){
                        
                        // Update access time to current time.
                        frames[i]->timestamp = time++;
                        printf(GREEN "\nPage P%d is already present in memory." CYAN "\nLocated at frame%d\n\n" RESET, pid, i);
                        break;

                    }
                }
                
                // Exit case if page was found.
                // Else increment number of page faults.
                if(i < num_frames)
                    break;
                else
                    ++faults;

                // Search for Empty Frames
                for(i=0;i<num_frames;++i){
                    // Accomodate the page in the first
                    // Empty frame found.
                    if(frames[i]==nullptr){
                        frames[i] = new Page(pid, time++);
                        printf(YELLOW "\nPage P%d is accomodated in frame%d\n\n" RESET, pid, i);
                        break;
                    }
                }
                
                // exit case, if frame has been assigned
                if (i < num_frames)
                    break;
                
                // Initialize variables 
                // to search for least recently used process 
                min = frames[0]->timestamp;
                min_index = 0;
                
                // find the LRU process.
                for(i=1;i<num_frames;++i){
                    if(min>frames[i]->timestamp){
                        min = frames[i]->timestamp;
                        min_index = i;
                    }
                }
                
                // Replace LRU with requested page 
                printf(YELLOW "\nP%d was accomodated in F%d after removing P%d\n\n" RESET, pid, min_index, frames[min_index]->id);
                
                // Delete LRU from memory. 
                delete(frames[min_index]);

                // Add requested page to frame.
                frames[min_index] = new Page(pid,time++);
                break;
            
            // Page request are completed
            // Update user with runtime statistics    
            case '2':

                cout << CYAN "\nNumber of page faults  => " << faults << endl;
                
                // Calc fault ratio as fr = no(faults)/no(requests)
                cout << "Page fault ratio       => " << (double) faults / reqs << endl << endl; 
                cout << RESET;
                break;
            
            // Default case
            // exit to main menu
            default:
                return;
        }
            
    }
    return;
}
void mru(int num_frames){

    // Declare and initialize variables
    struct Page* frames[num_frames];
    int faults=0, reqs=0,pid,i,time=0,max,max_index;
    char choice;
    
    // initialize each frame to empty.
    for(i=0;i<num_frames;++i)
        frames[i]=nullptr;
    
    //  Print user menu.
    cout << "\n" UN YELLOW "You Have Selected MRU Replacement Scheme" RESET<< endl;
    cout << "\n 1. Request Page"<<endl;
    cout << " 2. Stop Adding page\n"<<endl;
    cout << " **ANY OTHER KEY TO EXIT**\n"<<endl;
    
    // Menu Driven Logic
    while (true)
    {
        // Get user Input
        cout << "Your choice   : ";
        scanf("%c%c",&choice,&choice);

        // Switch Case of choices
        switch(choice){

            // Case 1 => Addition of Page.
            case '1':
                // Take User Input
                cout << "Enter Page id : ";
                cin >> pid;
                
                // increment requests
                ++reqs;
                
                // Linear search for requested page in
                // available frames
                for (i=0;i<num_frames;++i){
                    
                    // If Page is found
                    // Update user
                    if(frames[i] && frames[i]->id == pid){
                        
                        // Update access time to current time.
                        frames[i]->timestamp = time++;
                        printf(GREEN "\nPage P%d is already present in memory." CYAN "\nLocated at frame%d\n\n" RESET, pid, i);
                        break;

                    }
                }
                
                // Exit case if page was found.
                // Else increment number of page faults.
                if(i < num_frames)
                    break;
                else
                    ++faults;

                // Search for Empty Frames
                for(i=0;i<num_frames;++i){
                    // Accomodate the page in the first
                    // Empty frame found.
                    if(frames[i]==nullptr){
                        frames[i] = new Page(pid, time++);
                        printf(YELLOW "\nPage P%d is accomodated in frame%d\n\n" RESET, pid, i);
                        break;
                    }
                }
                
                // exit case, if frame has been assigned
                if (i < num_frames)
                    break;
                
                // Initialize variables 
                // to search for least recently used process 
                max = frames[0]->timestamp;
                max_index = 0;
                
                // find the LRU process.
                for(i=1;i<num_frames;++i){
                    if(max<frames[i]->timestamp){
                        max = frames[i]->timestamp;
                        max_index = i;
                    }
                }
                
                // Replace MRU with requested page 
                printf(YELLOW "\nP%d was accomodated in F%d after removing P%d\n\n" RESET, pid, max_index, frames[max_index]->id);
                
                // Delete MRU from memory. 
                delete(frames[max_index]);

                // Add requested page to frame.
                frames[max_index] = new Page(pid,time++);
                break;
            
            // Page request are completed
            // Update user with runtime statistics    
            case '2':

                cout << CYAN "\nNumber of page faults  => " << faults << endl;
                
                // Calc fault ratio as fr = no(faults)/no(requests)
                cout << "Page fault ratio       => " << (double) faults / reqs << endl << endl; 
                cout << RESET;
                break;
            
            // Default case
            // exit to main menu
            default:
                return;
        }
            
    }
    return;
}
void fifo(int num_frames){
    struct Page* frames[num_frames];
    int faults=0, reqs=0,pid,i,time=0,min,min_index;
    char choice;
    // initialize each frame to empty.
    for(i=0;i<num_frames;++i)
        frames[i]=nullptr;
    
    //  Print user menu.
    cout << "\n" UN YELLOW "You Have Selected FIFO Replacement Scheme" RESET<< endl;
    cout << "\n 1. Request Page"<<endl;
    cout << " 2. Stop Adding page\n"<<endl;
    cout << " **ANY OTHER KEY TO EXIT**\n"<<endl;

    while (true)
    {
        // Get user Input
        cout << "Your choice   : ";
        scanf("%c%c",&choice,&choice);
        switch(choice){
            case '1':
                cout << "Enter Page id : ";
                cin >> pid;
                
                // increment requests
                ++reqs;
                
                for (i=0;i<num_frames;++i){
                    
                    if(frames[i] && frames[i]->id == pid){
                        printf(GREEN "\nPage P%d is already present in memory." CYAN "\nLocated at frame%d\n\n" RESET, pid, i);
                        break;
                    }
                }
                
                // Exit case if page was found.
                if(i < num_frames)
                    break;
                else
                    ++faults;

                // Search for Empty Frames
                for(i=0;i<num_frames;++i){
                    if(frames[i]==nullptr){
                        frames[i] = new Page(pid, time++);
                        printf(YELLOW "\nPage P%d is accomodated in frame%d\n\n" RESET, pid, i);
                        break;
                    }
                }
                
                // exit case, if frame has been assigned
                if (i < num_frames)
                    break;
                
                min = frames[0]->timestamp;
                min_index = 0;
                
                // find the first arrived process
                for(i=1;i<num_frames;++i){
                    if(min>frames[i]->timestamp){
                        min = frames[i]->timestamp;
                        min_index = i;
                    }
                }
                printf(YELLOW "\nP%d was accomodated in F%d after removing P%d\n\n" RESET, pid, min_index, frames[min_index]->id);
                delete(frames[min_index]);
                frames[min_index] = new Page(pid,time++);
                break;
            case '2':
                cout << CYAN "\nNumber of page faults  => " << faults << endl;
                cout << "Page fault ratio       => " << (double) faults / reqs << endl << endl; 
                cout << RESET;
                break;
            default:
                return;
        }
            
    }
    return;
}

// driver code
int paging () {

    int alg;

    cout << " \n" YELLOW UN "Choose Algorithm to simulate" RESET << endl <<endl;
    cout << "\n Enter 1. Address Translator"<<endl;
    cout << " Enter Any key for Paging\n"<<endl;

    cin >> alg;
    if(alg == 1){
        Address_space();
        return 0;
    }

    // declare some common var
    int algo, num_frames;
    
    // Get number of frames
    cout << "Enter Number of Frames : ";
    cin >> num_frames;

    while(true){
        cout << " \n" YELLOW UN "Choose Algorithm to simulate" RESET << endl <<endl;
        cout << "\n 1. First In First Out [fifo]"<<endl;
        cout << " 2. Least Recently Used [lru]"<<endl;
        cout << " 3. Most Recently Used  [mru]"<<endl;
        cout << " 4. Optimal  [opt]"<<endl;
        cout << " 5. Address Translator [AT] \n" << endl;
        cout << " 9. To Exit*\n"<<endl;
        cout << "Your choice : ";
        scanf("%d",&algo);
        switch(algo){
            case 1:
                fifo(num_frames);
                break;
            
            case 2:
                lru(num_frames);
                break;
            case 3:
                mru(num_frames);
                break;
            case 4:
                optimal(num_frames);
                break;
            case 5:
                Address_space();
                break;
            default:
                cout << "Exiting...\n";
                return 0;
        }


    }
    
    return 0;
}