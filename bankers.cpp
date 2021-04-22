/* Bankers problem*/
#include <bits/stdc++.h>
using namespace std;
int bankers()
{

    int m, n, i, j, flag = 0, count = 0; /* m for no. of process and n for no. of resources */
    cout << "\n" UN YELLOW "You Have Selected Baankers Algo." RESET << endl << endl;

    cout << "Enter number of processes : ";
    cin >> m;
    cout << "Enter number of Resources   ";
    cin >> n;

    int alloc[m][n], need[m][n], max[m][n], initial[n], available[n], sum[n], proc[m];
    cout << "\n" UN YELLOW "MAXIMUM AVAILABLE RESORCES." RESET << endl << endl;
    for (i = 0; i < n; i++)
    {
        cout << " => Total R" << i << " : ";
        scanf("%d", &initial[i]);
    }
    printf(UN "Enter Allocated" RESET "\n\n");
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++){
            printf(" => ALLOC[P%d][R%d] :\t",i,j);
            scanf("%d", &alloc[i][j]);
        }
    printf(UN "Enter Max Need" RESET "\n\n");
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++){
            printf(" => MAX[P%d][R%d]   :\t",i,j);
            scanf("%d", &max[i][j]);
        }
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            need[i][j] = max[i][j] - alloc[i][j]; /* finding required resources */

    for (i = 0; i < n; i++)
    {
        sum[i] = 0;
        for (j = 0; j < m; j++)
            sum[i] += alloc[j][i];

        available[i] = initial[i] - sum[i]; /* findinng available resources */
    }
    printf("\nChecking user inputs.....\n");
    flag = 0;
    for (i = 0; i < n; i++)
    {
        if (sum[i] > initial[i])
            flag++;
        for (j = 0; j < m; j++)
        {
            if (max[j][i] > initial[i])
                flag++;
        }
    }
    if (flag == 0)
        printf(GREEN "\nAll entries are valid\n" WHITE);
    else
    {
        printf(RED "\nEntries are invalid\n" WHITE);
        return 0;
    }
    for (i = 0; i < m; i++)

    {
        if (need[i][0] < available[0] || need[i][1] < available[1] || need[i][2] < available[2])
            flag++;
    }
    if (flag == m)
        printf("This is unsafe configuration\n");
    else
    {
        i = -1;
        j = 0;
        flag = 0;
        while (flag == 0)
        {
            i = (i + 1) % m;
            if ((need[i][0] <= available[0] && need[i][1] <= available[1] && need[i][2] <= available[2]) && (need[i][0] != -1))
            {
                available[0] += alloc[i][0];
                available[1] += alloc[i][1];
                available[2] += alloc[i][2];
                need[i][0] = -1;
                count++;
                proc[j] = i + 1;
                j++;
            }
            if (available[0] >= initial[0] && available[1] >= initial[1] && available[2] >= initial[2])
                flag = 1;
        }
        if (count == m)
        {
            printf(GREEN "\nThis is safe configuration\nAnd the order of run is ");
            for (i = 0; i < m; i++)
                printf(BLUE "process %d-> ", proc[i]);
            printf("\n" WHITE);
        }
        else
            printf(RED "\nThis is unsafe configuration\n" RESET);
    }
    return 0;
}