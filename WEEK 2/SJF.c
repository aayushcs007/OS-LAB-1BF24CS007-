#include <stdio.h>

void SJF_NonPreemptive(int id[], int at[], int bt[], int n) {
    int ct[n], tat[n], wt[n], start[n];
    int ganttP[n], ganttT[n+1];
    float sumTAT=0, sumWT=0, sumRT=0;
    int time=0, completed=0, g=0;

    for(int i=0;i<n;i++){
        ct[i]=tat[i]=wt[i]=start[i]=-1;
    }

    while(completed<n){
        int idx=-1, minBT=1e9;

        for(int i=0;i<n;i++){
            if(at[i]<=time && ct[i]==-1 && bt[i]<minBT){
                minBT=bt[i];
                idx=i;
            }
        }

        if(idx==-1){
            time++;
        }
        else{
            start[idx]=time;
            ganttP[g]=idx;
            ganttT[g]=time;
            g++;

            time+=bt[idx];
            ct[idx]=time;

            tat[idx]=ct[idx]-at[idx];
            wt[idx]=tat[idx]-bt[idx];

            int response=start[idx]-at[idx];

            sumTAT+=tat[idx];
            sumWT+=wt[idx];
            sumRT+=response;

            completed++;
        }
    }
    ganttT[g]=time;

    printf("\n--- Non-Preemptive SJF ---");
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT");

    for(int i=0;i<n;i++){
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d",
        id[i],at[i],bt[i],ct[i],tat[i],wt[i],start[i]-at[i]);
    }

    printf("\n\nAverage TAT: %.2f",sumTAT/n);
    printf("\nAverage WT: %.2f",sumWT/n);
    printf("\nAverage RT: %.2f\n",sumRT/n);

    printf("\nGantt Chart:\n");

    for(int i=0;i<g;i++) printf("-------");
    printf("-\n|");

    for(int i=0;i<g;i++)
        printf(" P%d |",id[ganttP[i]]);

    printf("\n");
    for(int i=0;i<g;i++) printf("-------");
    printf("-\n");

    for(int i=0;i<=g;i++)
        printf("%d\t",ganttT[i]);

    printf("\n");
}

void SJF_Preemptive(int id[], int at[], int bt[], int n) {

    int rt[n], ct[n], tat[n], wt[n], start[n];
    int ganttP[100], ganttT[100];
    float sumTAT=0,sumWT=0,sumRT=0;

    int time=0,completed=0,g=0,last=-1;

    for(int i=0;i<n;i++){
        rt[i]=bt[i];
        ct[i]=tat[i]=wt[i]=-1;
        start[i]=-1;
    }

    while(completed<n){

        int idx=-1,minRT=1e9;

        for(int i=0;i<n;i++){
            if(at[i]<=time && rt[i]>0 && rt[i]<minRT){
                minRT=rt[i];
                idx=i;
            }
        }

        if(idx==-1){
            time++;
            continue;
        }

        if(start[idx]==-1)
            start[idx]=time;

        if(last!=idx){
            ganttP[g]=idx;
            ganttT[g]=time;
            g++;
            last=idx;
        }

        rt[idx]--;
        time++;

        if(rt[idx]==0){
            ct[idx]=time;

            tat[idx]=ct[idx]-at[idx];
            wt[idx]=tat[idx]-bt[idx];

            int response=start[idx]-at[idx];

            sumTAT+=tat[idx];
            sumWT+=wt[idx];
            sumRT+=response;

            completed++;
        }
    }

    ganttT[g]=time;

    printf("\n--- Preemptive SJF (SRTF) ---");
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT");

    for(int i=0;i<n;i++){
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d",
        id[i],at[i],bt[i],ct[i],tat[i],wt[i],start[i]-at[i]);
    }

    printf("\n\nAverage TAT: %.2f",sumTAT/n);
    printf("\nAverage WT: %.2f",sumWT/n);
    printf("\nAverage RT: %.2f\n",sumRT/n);

    printf("\nGantt Chart:\n");

    for(int i=0;i<g;i++) printf("-------");
    printf("-\n|");

    for(int i=0;i<g;i++)
        printf(" P%d |",id[ganttP[i]]);

    printf("\n");

    for(int i=0;i<g;i++) printf("-------");
    printf("-\n");

    for(int i=0;i<=g;i++)
        printf("%d\t",ganttT[i]);

    printf("\n");
}

int main(){

    int n;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int id[n],at[n],bt[n];

    for(int i=0;i<n;i++){
        id[i]=i+1;

        printf("\nArrival Time for P%d: ",i+1);
        scanf("%d",&at[i]);

        printf("Burst Time for P%d: ",i+1);
        scanf("%d",&bt[i]);
    }

    SJF_NonPreemptive(id,at,bt,n);
    SJF_Preemptive(id,at,bt,n);

    return 0;
}
