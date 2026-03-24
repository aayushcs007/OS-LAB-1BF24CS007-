#include <stdio.h>

int main()
{
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int id[n], at[n], bt[n], rt[n];
    int ct[n], tat[n], wt[n], start[n];

    for(int i = 0; i < n; i++)
    {
        id[i] = i + 1;

        printf("\nArrival Time for P%d: ", i + 1);
        scanf("%d", &at[i]);

        printf("Burst Time for P%d: ", i + 1);
        scanf("%d", &bt[i]);

        rt[i] = bt[i];
        start[i] = -1;
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(at[j] > at[j+1])
            {
                int temp;
                temp = at[j]; at[j] = at[j+1]; at[j+1] = temp;
                temp = bt[j]; bt[j] = bt[j+1]; bt[j+1] = temp;
                temp = rt[j]; rt[j] = rt[j+1]; rt[j+1] = temp;
                temp = id[j]; id[j] = id[j+1]; id[j+1] = temp;
            }
        }
    }

    int queue[100], front = 0, rear = 0;
    int visited[n];
    for(int i = 0; i < n; i++) visited[i] = 0;

    int time = at[0];
    queue[rear++] = 0;
    visited[0] = 1;

    int ganttP[200], ganttT[200], g = 0;

    float sumTAT = 0, sumWT = 0, sumRT = 0;

    printf("\n--- Round Robin Scheduling ---");

    while(front < rear)
    {
        int i = queue[front++];

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

            sumTAT += tat[i];
            sumWT += wt[i];
            sumRT += (start[i] - at[i]);
        }

        for(int j = 0; j < n; j++)
        {
            if(at[j] <= time && visited[j] == 0)
            {
                queue[rear++] = j;
                visited[j] = 1;
            }
        }

       
        if(rt[i] > 0)
        {
            queue[rear++] = i;
        }

        if(front == rear)
        {
            for(int j = 0; j < n; j++)
            {
                if(visited[j] == 0)
                {
                    time = at[j];
                    queue[rear++] = j;
                    visited[j] = 1;
                    break;
                }
            }
        }
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

    return 0;
}

