/**
 * @author: Addhyan Malhotra 
 * @course: Operating Systems Lab.
 * @course_id: CS255
 * @roll:   191CS202
 *   
 * */
#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
#define debug(x) cout << #x << " = " << x << "\n"

using namespace std;

// Struct to hold block
struct Block{
    int size;
	bool full=false;
    int used=0;
    int pid =-1;
    Block(int s){
        size =s;
    }
};


void worstfit(vector <Block*>& blocks, int largest_block, int unused){
    int num_blocks = blocks.size();
    int pid = 0,pid1=0, max_size, max_i, p_size;
    bool flag;
    int x, remaining_size;
    int choice;
    
    cout << "\nStarting Worst Fit Scheme" << endl;
    cout << "\n 1. Insert Process."<<endl;
    cout << " 2. Delete Process."<<endl;
    cout << " 3. Stop\n"<<endl;
    cout << " **ANY OTHER KEY TO EXIT**\n"<<endl;
    
    while(true){
    cout << "Enter choice : ";
    cin >> choice;
        switch (choice)
    {
        
    case 1:
        max_size = -1;
        max_i  =-1;
        for (int i=0; i<num_blocks; ++i){
            if(!blocks[i]->full && max_size < (blocks[i]->size)){
                max_size = blocks[i]->size;
                max_i = i;
            }
        }
        
        cout << "Enter Process size for P" << pid << " : ";
        cin >> p_size;

        if (max_i == -1 || max_size==0){
            cout << "No Empty Blocks please delete some process before inserting" << endl;
        }
        else if(p_size > blocks[max_i]->size){
            flag = false;
            remaining_size=0;
            for (auto b : blocks){
                remaining_size += b->size - b->used;
                if ((b->size - b->used)>= p_size){
                    flag = true;
                    break;
                }
            }
            if (p_size > largest_block){
                cout << "Process is larger than largest partition" <<endl;
            }
            else if (p_size > remaining_size)
            {
                cout << "insufficient space for process" <<endl;
            }
            else if(flag){
                cout << "Cant be occupied due to Internal fragmentation."<<endl;
            }else{
                cout << "Cant be occupied due to External fragmentation."<<endl;
            }
        }
        else
        {
            cout << "Process P" << pid << " is accomodated in PA" << max_i << endl;
            blocks[max_i]->full = true;
            blocks[max_i]->used = p_size;
            blocks[max_i]->pid = pid;
        }
        ++pid;
        break;
    case 2:
        cout << "Enter Process id to empty : ";
        cin >> pid1;
        flag = 0;
        for(int i = 0; i<blocks.size();++i){
            if(blocks[i]->pid == pid1)
            {
                blocks[i]->full = false;
                blocks[i]->used = 0;
                blocks[i]->pid = -1;
                cout << "Partition PA" << i << " has been emptied "<<endl;
                flag=1;
                break;
            }
        }
        if(flag==0){
            cout << "Process doesnt exist in memory" <<endl;
        }
        break;
    case 3:
        remaining_size =0;
        x=0;
        cout << "Partition Table\n";
        for (auto b : blocks){
            if(b->size==0)
                continue;
            if(b->full)
                remaining_size += b->size - b->used;
            printf("PA%d size=%d used=%d process_id=%d internal_frag=%d\n",x++,b->size,b->used,b->pid,((b->pid)==-1?0:b->size - b->used));
        }
        cout << "Unused Space = " << unused <<endl;
        cout << "Net Internal fragments = " << remaining_size <<endl<<endl;
        break;
    default:
        return;
    }
    }

}

int worst_fit_delete(){
    vector <Block*> blocks;
    int total_size, block_size, remaining_size, n, pos=0, largest_block=-1;
    
    cout << "Enter Total size          : ";
    cin >> total_size;
    remaining_size = total_size;

    cout << "Enter Number of Patitions : ";
    cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        cout << "Enter Size of PA" << i << " : ";
        cin >> block_size;
        if (block_size > remaining_size){
            cout << "Partition can not be accomodated in memory, only " << remaining_size <<"KB space is remaining" << endl;
            blocks.push_back(new Block(0));
        }
        else{
            if(block_size > largest_block)
                largest_block = block_size;
            remaining_size -= block_size;
            blocks.push_back(new Block (block_size));
            pos++;
            cout << "PA" << i << " is accomodated" << endl;
        }
    }
    worstfit(blocks, largest_block, remaining_size);

    return 0;
}