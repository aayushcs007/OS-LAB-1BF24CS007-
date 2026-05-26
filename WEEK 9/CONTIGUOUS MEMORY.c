#include <stdio.h>

#define MAX 100

void allocate(int blocks[], int m, int processes[], int n, int type) {
    int allocation[MAX];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {

        int idx = -1;

        for (int j = 0; j < m; j++) {

            if (blocks[j] >= processes[i]) {

                if (type == 1) {          // First Fit
                    idx = j;
                    break;
                }

                else if (type == 2) {     // Best Fit
                    if (idx == -1 || blocks[j] < blocks[idx])
                        idx = j;
                }

                else if (type == 3) {     // Worst Fit
                    if (idx == -1 || blocks[j] > blocks[idx])
                        idx = j;
                }
            }
        }

        if (idx != -1) {
            allocation[i] = idx;
            blocks[idx] -= processes[i];
        }
    }

    if (type == 1)
        printf("\nFirst Fit Allocation:\n");
    else if (type == 2)
        printf("\nBest Fit Allocation:\n");
    else
        printf("\nWorst Fit Allocation:\n");

    printf("Process\tSize\tBlock\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t", i + 1, processes[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {

    int blocks[MAX], p[MAX];
    int b1[MAX], b2[MAX], b3[MAX];
    int m, n;

    printf("Enter number of blocks: ");
    scanf("%d", &m);

    printf("Enter block sizes:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blocks[i]);

        b1[i] = blocks[i];
        b2[i] = blocks[i];
        b3[i] = blocks[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter process sizes:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);

    allocate(b1, m, p, n, 1);
    allocate(b2, m, p, n, 2);
    allocate(b3, m, p, n, 3);

    return 0;
}
