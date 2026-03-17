
#include <stdio.h>

void RoundRobin(int id[], int at[], int bt[], int n, int tq)
{
    int rt[n], ct[n], tat[n], wt[n], start[n];
    int completed = 0, time = 0;

    float sumTAT = 0, sumWT = 0, sumRT = 0;

    int ganttP[200], ganttT[200], g = 0;

    for(int i = 0; i < n; i++)
    {
        rt[i] = bt[i];
        ct[i] = tat[i] = wt[i] = -1;
        start[i] = -1;
    }

    printf("\n--- Round Robin Scheduling ---");

    while(completed < n)
    {
        int executed = 0;

        for(int i = 0; i < n; i++)
        {
            if(at[i] <= time && rt[i] > 0)
            {
                if(start[i] == -1)
                    start[i] = time;

                ganttP[g] = id[i];
                ganttT[g] = time;
                g++;

                if(rt[i] > tq)
                {
                    time += tq;
                    rt[i] -= tq;
                }
                else
                {
                    time += rt[i];
                    rt[i] = 0;

                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];

                    int response = start[i] - at[i];

                    sumTAT += tat[i];
                    sumWT += wt[i];
                    sumRT += response;

                    completed++;
                }

                executed = 1;
            }
        }

        if(!executed)
            time++;
    }

    ganttT[g] = time;

    printf("\nGantt Chart:\n|");
    for(int i = 0; i < g; i++)
        printf(" P%d |", ganttP[i]);

    printf("\n%d", ganttT[0]);
    for(int i = 1; i <= g; i++)
        printf("   %d", ganttT[i]);

    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT");

    for(int i = 0; i < n; i++)
    {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d",
        id[i], at[i], bt[i], ct[i], tat[i], wt[i], start[i] - at[i]);
    }

    printf("\n\nAverage TAT: %.2f", sumTAT/n);
    printf("\nAverage WT: %.2f", sumWT/n);
    printf("\nAverage RT: %.2f\n", sumRT/n);
}


int main()
{
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int id[n], at[n], bt[n];

    for(int i = 0; i < n; i++)
    {
        id[i] = i + 1;

        printf("\nArrival Time for P%d: ", i + 1);
        scanf("%d", &at[i]);

        printf("Burst Time for P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    RoundRobin(id, at, bt, n, tq);

    return 0;
}
