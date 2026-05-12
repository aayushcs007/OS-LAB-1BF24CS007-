#include <stdio.h>
#include <math.h>

#define MAX 10

typedef struct {
    int id;
    int burst;
    int deadline;
    int period;
    int completion;
    int waiting;
    int turnaround;
} Process;

// Sort by Deadline (EDF)
void sortEDF(Process p[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(p[i].deadline > p[j].deadline) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

// Sort by Period (RMS)
void sortRMS(Process p[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(p[i].period > p[j].period) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

// Calculate CT, WT, TAT
void calculateTimes(Process p[], int n) {
    int time = 0;
    for(int i = 0; i < n; i++) {
        time += p[i].burst;
        p[i].completion = time;
        p[i].turnaround = p[i].completion;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }
}

// Utilization Calculation
float calculateUtilization(Process p[], int n) {
    float u = 0;
    for(int i = 0; i < n; i++) {
        u += (float)p[i].burst / p[i].period;
    }
    return u;
}

// EDF Schedulability
void checkEDF(Process p[], int n) {
    float u = calculateUtilization(p, n);

    printf("\nEDF Utilization = %.2f\n", u);
    if(u <= 1.0)
        printf("Result: SCHEDULABLE (EDF)\n");
    else
        printf("Result: NOT SCHEDULABLE (EDF)\n");
}

// RMS Schedulability
void checkRMS(Process p[], int n) {
    float u = calculateUtilization(p, n);
    float bound = n * (pow(2, 1.0/n) - 1);

    printf("\nRMS Utilization = %.2f\n", u);
    printf("RMS Bound = %.2f\n", bound);

    if(u <= bound)
        printf("Result: SCHEDULABLE (RMS)\n");
    else
        printf("Result: NOT SCHEDULABLE (RMS)\n");
}

// Print EDF Table
void printEDF(Process p[], int n) {
    printf("\n===== Earliest Deadline First (EDF) =====\n");
    printf("-------------------------------------------------------------\n");
    printf("| ID | BT | Deadline | CT | WT | TAT |\n");
    printf("-------------------------------------------------------------\n");

    for(int i = 0; i < n; i++) {
        printf("| %2d | %2d | %8d | %2d | %2d | %3d |\n",
               p[i].id,
               p[i].burst,
               p[i].deadline,
               p[i].completion,
               p[i].waiting,
               p[i].turnaround);
    }

    printf("-------------------------------------------------------------\n");
}

// Print RMS Table
void printRMS(Process p[], int n) {
    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");
    printf("---------------------------------------------------------\n");
    printf("| ID | BT | Period | CT | WT | TAT |\n");
    printf("---------------------------------------------------------\n");

    for(int i = 0; i < n; i++) {
        printf("| %2d | %2d | %6d | %2d | %2d | %3d |\n",
               p[i].id,
               p[i].burst,
               p[i].period,
               p[i].completion,
               p[i].waiting,
               p[i].turnaround);
    }

    printf("---------------------------------------------------------\n");
}

int main() {
    int n;
    Process p[MAX], edf[MAX], rms[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process details:\n");

    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;

        printf("\nProcess %d:\n", i + 1);

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        printf("Deadline (EDF): ");
        scanf("%d", &p[i].deadline);

        printf("Period (RMS): ");
        scanf("%d", &p[i].period);
    }

    // Copy arrays
    for(int i = 0; i < n; i++) {
        edf[i] = p[i];
        rms[i] = p[i];
    }

    // EDF
    sortEDF(edf, n);
    calculateTimes(edf, n);
    printEDF(edf, n);
    checkEDF(p, n);

    // RMS
    sortRMS(rms, n);
    calculateTimes(rms, n);
    printRMS(rms, n);
    checkRMS(p, n);

    return 0;
}
