//Longest Job First
#include <bits/stdc++.h>

using namespace std;

class Process_LJF //class for processes
{
public:
    int a_t, b_t, w_t, ta_t, p_no, c_t, priority, rem_t;
    bool isdone = false;
};

bool LJF_sort_process(Process_LJF p1, Process_LJF p2) //sort process acc. to arrival time
{
    return (p1.a_t < p2.a_t);
}

void LJF()
{
    int n, i;
    cout << "Enter the number of processes: "; //Getting the number of processes
    cin >> n;
    while (n < 1)
    {
        cout << "Invalid input, try again\nEnter the number of processes: ";
        cin >> n;
    }
    Process_LJF p[n];
    for (i = 0; i < n; i++) //Taking input Arrival times and Burst times for every process
    {
        p[i].p_no = i + 1;
        cout << "Enter the arrival time for process " << i + 1 << ": ";
        cin >> p[i].a_t;
        while (p[i].a_t < 0)
        {
            cout << "Invalid input, try again\nEnter the arrival time for process " << i + 1 << ": ";
            cin >> p[i].a_t;
        }
        cout << "Enter the burst time for process " << i + 1 << ": ";
        cin >> p[i].b_t;
        while (p[i].b_t < 0)
        {
            cout << "Invalid input, try again\nEnter the burst time for process " << i + 1 << ": ";
            cin >> p[i].b_t;
        }
    }
    sort(p, p + n, LJF_sort_process);
    int t = p[0].a_t, k, m, finished = 0;
    float sum_tat = 0.0, sum_wt = 0.0; //variables to get total Turn around time and Waiting time
    while (finished != n)
    {
        m = 0, k = -1;
        for (i = 0; p[i].a_t <= t && i < n; i++) //Inner loop to cover processes which have arrived until current time
        {
            if (p[i].b_t > m && p[i].isdone == 0) //Finding the process with longest burst time which is not completed yet
            {
                m = p[i].b_t;
                k = i;
            }
        }
        if (i < n && k == -1)       // If no process arrived, increase time
        {
            t = p[i].a_t;
            continue;
        }
        p[k].c_t = t + p[k].b_t;         //Calculate completion time using k
        t = p[k].c_t;                    //Updating time
        p[k].ta_t = p[k].c_t - p[k].a_t; //Calculate Turn around time
        p[k].w_t = p[k].ta_t - p[k].b_t; //Calculate Waiting time
        p[k].isdone = true;
        finished++;
    }
    cout << "\nProcess No.  Arrival Time  Burst Time  Completion Time  Turn Around Time  Waiting Time\n";
    for (i = 0; i < n; i++)
    {
        cout << p[i].p_no << "\t\t" << p[i].a_t << "\t\t" << p[i].b_t << "\t\t" << p[i].c_t << "\t\t" << p[i].ta_t << "\t\t" << p[i].w_t << "\n"; //Output the values
        sum_tat += p[i].ta_t;                                                                                                                     //Calculate total Turn around time
        sum_wt += p[i].w_t;                                                                                                                       //Calculate total Waiting time
    }
    cout << "\nAverage Turn Around Time = " << sum_tat / n << "\nAverage Waiting Time = " << sum_wt / n; //Print Average Turn around time and Waiting time
}

