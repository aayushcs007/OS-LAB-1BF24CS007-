#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int available[MAX];

    // Allocation matrix
    printf("Enter Allocation Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Maximum matrix
    printf("Enter Maximum Demand Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Available resources
    printf("Enter Available Resources:\n");
    for(int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    // Need = Max - Allocation
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // 🔹 RESOURCE REQUEST PART
    int process;
    int request[MAX];

    printf("\nEnter process number making request: ");
    scanf("%d", &process);

    printf("Enter request vector:\n");
    for(int i = 0; i < m; i++) {
        scanf("%d", &request[i]);
    }

    // Check Request <= Need
    for(int i = 0; i < m; i++) {
        if(request[i] > need[process][i]) {
            printf("Error: Process exceeded maximum claim\n");
            return 0;
        }
    }

    // Check Request <= Available
    for(int i = 0; i < m; i++) {
        if(request[i] > available[i]) {
            printf("Resources not available. Process must wait.\n");
            return 0;
        }
    }

    // Pretend allocation
    for(int i = 0; i < m; i++) {
        available[i] -= request[i];
        alloc[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // 🔹 SAFETY ALGORITHM (same as your code)
    int work[MAX], safeSeq[MAX];
    bool finish[MAX];

    for(int i = 0; i < m; i++)
        work[i] = available[i];

    for(int i = 0; i < n; i++)
        finish[i] = false;

    int count = 0;

    while(count < n) {
        bool found = false;

        for(int i = 0; i < n; i++) {
            if(!finish[i]) {
                bool possible = true;

                for(int j = 0; j < m; j++) {
                    if(need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }

                if(possible) {
                    for(int j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if(!found) {
            // Rollback
            for(int i = 0; i < m; i++) {
                available[i] += request[i];
                alloc[process][i] -= request[i];
                need[process][i] += request[i] ;
            }

            printf("\nRequest CANNOT be granted (Unsafe state)\n");
            return 0;
        }
    }

    // Safe state
    printf("\nRequest CAN be granted.\n");
    printf("System is in a safe state.\n");

    printf("Safe sequence is: ");
    for(int i = 0; i < n; i++) {
        printf("P%d", safeSeq[i]);
        if(i != n - 1)
            printf(" -> ");
    }

    printf("\n");

    return 0;
}
