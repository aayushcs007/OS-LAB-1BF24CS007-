
#include <stdio.h>

struct Process {
    int pid;        // Process ID
    int bt;         // Burst Time
    int at;         // Arrival Time
    int pr;         // Priority
    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time
    int rt;         // Remaining Time (for preemptive)
    int finished;   // Flag
};

struct Gantt {
    int pid;
    int start;
    int end;
};

// Function to print Gantt Chart
void print_gantt_chart(struct Gantt g[], int count) {
    printf("\n--- Gantt Chart ---\n");

    // Top bar
    printf(" ");
    for (int i = 0; i < count; i++) {
        for (int j = g[i].start; j < g[i].end; j++) printf("--");
        printf(" ");
    }
    printf("\n|");

    // Process IDs
    for (int i = 0; i < count; i++) {
        int len = g[i].end - g[i].start;
        for (int j = 0; j < len - 1; j++) printf(" ");
        printf("P%d", g[i].pid);
        for (int j = 0; j < len - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");

    // Bottom bar
    for (int i = 0; i < count; i++) {
        for (int j = g[i].start; j < g[i].end; j++) printf("--");
        printf(" ");
    }
    printf("\n");

    // Timeline
    printf("%d", g[0].start);
    for (int i = 0; i < count; i++) {
        int len = g[i].end - g[i].start;
        for (int j = 0; j < len; j++) printf("  ");
        printf("%d", g[i].end);
    }
    printf("\n");
}

// Non-preemptive Priority Scheduling
void priority_non_preemptive(struct Process p[], int n) {
    int time = 0, completed = 0;
    struct Gantt g[100];
    int gcount = 0;

    while (completed < n) {
        int idx = -1;
        int highest = 9999;
        for (int i = 0; i < n; i++) {
            if (!p[i].finished && p[i].at <= time) {
                if (p[i].pr < highest) {
                    highest = p[i].pr;
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        g[gcount].pid = p[idx].pid;
        g[gcount].start = time;
        time += p[idx].bt;
        g[gcount].end = time;
        gcount++;

        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].finished = 1;
        completed++;
    }

    printf("\n--- Non-preemptive Priority Scheduling ---\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
    }
    int avg_tat=0,avg_wt=0;
    for(int i=0; i<n; i++){
        avg_tat+= p[i].tat;
        avg_wt+= p[i].wt;
    }
    printf("Avg TAT= %0.2f\t",(float)avg_tat/n);
    printf("Avg WT= %0.2f\n",(float)avg_wt/n);
    print_gantt_chart(g, gcount);
}

// Preemptive Priority Scheduling
void priority_preemptive(struct Process p[], int n) {
    int time = 0, completed = 0;
    struct Gantt g[100];
    int gcount = 0;
    int current = -1;

    while (completed < n) {
        int idx = -1;
        int highest = 9999;
        for (int i = 0; i < n; i++) {
            if (!p[i].finished && p[i].at <= time) {
                if (p[i].pr < highest) {
                    highest = p[i].pr;
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }

        if (current != idx) {
            if (current != -1) {
                g[gcount].end = time;
                gcount++;
            }
            g[gcount].pid = p[idx].pid;
            g[gcount].start = time;
            current = idx;
        }

        p[idx].rt--;
        time++;

        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].finished = 1;
            completed++;

            g[gcount].end = time;
            gcount++;
            current = -1;
        }
    }

    printf("\n--- Preemptive Priority Scheduling ---\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
    }
    int avg_tat=0,avg_wt=0;
    for(int i=0; i<n; i++){
        avg_tat+= p[i].tat;
        avg_wt+= p[i].wt;
    }
    printf("Avg TAT= %0.2f\t",(float)avg_tat/n);
    printf("Avg WT= %0.2f\n",(float)avg_wt/n);
    print_gantt_chart(g, gcount);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter AT, BT, Priority for P%d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].rt = p[i].bt;
        p[i].finished = 0;
    }

    // Copy array for separate simulations
    struct Process p1[n], p2[n];
    for (int i = 0; i < n; i++) {
        p1[i] = p[i];
        p2[i] = p[i];
    }

    priority_non_preemptive(p1, n);
    priority_preemptive(p2, n);

    return 0;
}
