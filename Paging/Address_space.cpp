/**
 * @author: Janmansh Agarwal 
 * @course: Operating Systems Lab.
 * @course_id: CS255
 * @roll:   191CS205
 *   
 * */

#include<bits/stdc++.h>
using namespace std;

void Address_space(){
  
  int n,i,j,vm,pm,ps;
  cout << "Enter the size of virtual memory in KB: ";
  cin >> vm;
  cout << "Enter the size of physical memory in KB: ";
  cin >> pm;

  cout << "Enter the size of page in KB: ";
  cin >> ps;

  while(ps<0){
    cout << "size can not be negative. Try again\n";
    cout << "Enter the size of page in KB: ";
    cin>>ps;
  }

  int pvm = vm/ps, ppm = pm/ps;

  cout << "Number of pages in virtual memory: " << pvm << "\n";
  cout << "Number of pages in physical memory: " << ppm << "\n";
  
  int a[ppm];         // Frame array
  int b[pvm];         // Virtual memory array

  for(i=0;i<ppm;i++)a[i]=-1;
  for(i=0;i<pvm;i++)b[i]=-1;

  int max_offset = ps*1024 - 1;
  
  int k, input = 0, fault=0;
  j = 0;
  
  while(1){
    cout << "Enter 1 to virtual address in the format 'page_no word_offset', Enter 2 to stop adding: ";
    cin >> k;
    
    while(k!=1 && k!=2){
      cout << "wrong input. Try again\n";
      cout << "Enter 1 to virtual address in the format 'page_no word_offset', Enter 2 to stop adding: ";
      cin >> k;
    }

    if(k == 2){
      break;
    }
    
    int p, flag=0, offset;    // page number and flag to check if page already present and word-offset
    cout << "Page No.: ";
    cin >> p;

    while(p<0||p>=pvm){
      cout << "Wrong input. Try again\n";
      cout << "Page No.: ";
      cin >> p;
    }

    cout << "Offset: ";
    cin >> offset;

    while(offset<0){
      cout << "Wrong input. Try again\n";
      cout << "Offset: ";
      cin >> offset;
    }

    if(offset > max_offset ){
      cout << "Offset exceeded maximum offset limit\n";
      continue;
    }
    
    input++;
    
    if(b[p] != -1){
      cout << "The physical address for the above virtual address is " << b[p] << " " << offset << "\n";
      continue;
    }

    cout << "P" << p << " is not present in the physical memory\n";

    for(i=0;i<ppm;i++){
      if(a[i] == -1){
        cout << "So P" << p << " is accomodated in frame F" << i << "\n";
        a[i] = p;
        b[p] = i;
        fault++;
        flag = 1;
        break;
      }
    }

    if(flag)continue;
    
    cout << " So P"<< p << " is accomodated in frame F" << j << " after removing P" << a[j] << " according to FIFO\n";

    b[a[j]] = -1;
    b[p] = j;
    a[j] = p;

    j++;
    j%=ppm;
    fault++;
    
  }
  
  double ratio = (fault*1.0)/(input*1.0);
  
  cout << "No. of page faults: "<<fault<<"\n";
  
  cout << "Page fault ratio = No. of page faults/total inputs\n";
  
  cout <<" = "<<fault<<"/"<<input<<" = "<<ratio<<"\n";

  cout << "Final page table: \n";

  for(i=0;i<pvm;i++){
    cout << "P" << i << " " << b[i] << "\n";
  }
  
  cout << "Final physical memory alloted: \n";

  for(i=0;i<ppm;i++){
    cout << "F" << i << " P" << a[i] << "\n";
  }
  
  return;
}
