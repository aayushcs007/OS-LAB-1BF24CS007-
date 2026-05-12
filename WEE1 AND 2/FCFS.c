#include<stdio.h>

void sort(int at[], int bt[], int pid[], int n){
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(at[j] > at[j+1]){
                int temp = at[j];
                at[j] = at[j+1];
                at[j+1] = temp;

                temp = bt[j];
                bt[j] = bt[j+1];
                bt[j+1] = temp;

                temp = pid[j];
                pid[j] = pid[j+1];
                pid[j+1] = temp;
            }
        }
    }
}

int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n], rt[n], pid[n], sumCT=0;
    float sumTAT=0, sumWT=0, sumRT=0;

    printf("Enter the arrival time and burst time for each process:\n");

    for(int i=0; i<n; i++){
        pid[i] = i+1;

        printf("\nArrival Time for P%d : ", i+1);
        scanf("%d", &at[i]);

        printf("Burst Time for P%d : ", i+1);
        scanf("%d", &bt[i]);
    }

    sort(at, bt, pid, n);

    for(int i=0; i<n; i++){
        sumCT += bt[i];
        ct[i] = sumCT;

        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        rt[i] = wt[i];

        sumTAT += tat[i];
        sumWT += wt[i];
        sumRT += rt[i];
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT");
    for(int i=0; i<n; i++){
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\n\nAverage Turnaround Time: %.2f", sumTAT/n);
    printf("\nAverage Waiting Time: %.2f", sumWT/n);
    printf("\nAverage Response Time: %.2f\n", sumRT/n);

    // Gantt Chart
    printf("\nGantt Chart:\n");

    printf(" ");
    for(int i=0;i<n;i++){
        printf("--------");
    }
    printf("\n|");

    for(int i=0;i<n;i++){
        printf("  P%d  |", pid[i]);
    }

    printf("\n ");
    for(int i=0;i<n;i++){
        printf("--------");
    }

    printf("\n0");
    for(int i=0;i<n;i++){
        printf("      %d", ct[i]);
    }
    printf("\n");

    return 0;
}
