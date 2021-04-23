//Longest remaining time first scheduling program
#include <bits/stdc++.h>

using namespace std;

class Process_LRTF //class for processes
{
public:
    int a_t, b_t, w_t, ta_t, rem_t, p_no, c_t, priority;
    bool isdone = false;
};

bool LRTF_sort_process(Process_LRTF p1, Process_LRTF p2) //sort process acc. to arrival time
{
    return (p1.a_t < p2.a_t);
}

void LRTF()
{
    int n, i;
    cout << "Enter the number of processes: "; //Getting the number of processes
    cin >> n;
    while (n < 1)
    {
        cout << "Invalid input, try again\nEnter the number of processes: ";
        cin >> n;
    }
    Process_LRTF p[n];
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
        p[i].rem_t = p[i].b_t;
    }
    sort(p, p + n, LRTF_sort_process);
    int finished = 0, cur_t = p[0].a_t, k = 0, l = 0, m = 0;
    float sum_tat = 0.0, sum_wt = 0.0;
    while (finished != n) //until every process finishes
    {
        m = 0;
        for (k = 0; p[k].a_t <= cur_t && k < n; k++) //check which process has the highest remaining time
        {
            if (p[k].rem_t > m && p[k].isdone == false)
            {
                m = p[k].rem_t;
                l = k;
            }
        }
        p[l].rem_t--;       // execute process for 1 second
        cur_t++;
        if (p[l].rem_t == 0) //if the process completes
        {
            finished++;
            p[l].isdone = true;
            p[l].c_t = cur_t;
            p[l].ta_t = cur_t - p[l].a_t;
            p[l].w_t = p[l].ta_t - p[l].b_t;
        }
    }
    cout <<CYAN<< "\nProcess No.  Arrival Time  Burst Time  Completion Time  Turn Around Time  Waiting Time\n"<<WHITE;
    for (i = 0; i < n; i++)
    {
        cout << p[i].p_no << "\t\t" << p[i].a_t << "\t\t" << p[i].b_t << "\t\t" << p[i].c_t << "\t\t" << p[i].ta_t << "\t\t" << p[i].w_t << "\n"; //Output the values
        sum_tat += p[i].ta_t;                                                                                                                     //Calculate total Turn around time
        sum_wt += p[i].w_t;                                                                                                                       //Calculate total Waiting time
    }
    cout <<GREEN<< "\nAverage Turn Around Time = " << sum_tat / n << "\nAverage Waiting Time = " << sum_wt / n<<WHITE; //Print Average Turn around time and Waiting time
}


