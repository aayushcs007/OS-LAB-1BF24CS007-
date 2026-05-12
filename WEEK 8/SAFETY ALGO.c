#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int main() {
    int n, m;

    // Input number of processes and resources
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

    // Calculate Need matrix = Max - Allocation
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Safety Algorithm
    int work[MAX], safeSeq[MAX];
    bool finish[MAX];

    // Initialize
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
                    // Add allocation to work
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
            printf("\nSystem is NOT in a safe state (Deadlock possible)\n");
            return 0;
        }
    }

    // Safe state
    printf("\nSystem is in a safe state.\n");
    printf("Safe sequence is: ");

    for(int i = 0; i < n; i++) {
        printf("P%d", safeSeq[i]);
        if(i != n - 1)
            printf(" -> ");
    }

    printf("\n");

    return 0;
}
