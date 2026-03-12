#include <stdio.h>

int main()
{
    int n, i;
    int at[20], bt[20], rem_bt[20];
    int ct[20], tat[20], wt[20];
    int tq;
    int time = 0, completed = 0;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("\nProcess P%d\n", i+1);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        rem_bt[i] = bt[i];   // copy burst time
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    while(completed < n)
    {
        int executed = 0;   // to check if any process ran in this cycle

        for(i = 0; i < n; i++)
        {
            if(rem_bt[i] > 0 && at[i] <= time)
            {
                executed = 1;

                if(rem_bt[i] > tq)
                {
                    time += tq;
                    rem_bt[i] -= tq;
                }
                else
                {
                    time += rem_bt[i];
                    ct[i] = time;
                    rem_bt[i] = 0;
                    completed++;
                }
            }
        }

        if(executed == 0)
            time++;   // CPU idle
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_tat += tat[i];
        avg_wt += wt[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\nAverage Turnaround Time = %.2f", avg_tat);
    printf("\nAverage Waiting Time = %.2f", avg_wt);

    return 0;
}
