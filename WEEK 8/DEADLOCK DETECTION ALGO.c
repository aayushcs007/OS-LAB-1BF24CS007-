#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[MAX][MAX], request[MAX][MAX];
    int available[MAX];

    printf("Enter Allocation Matrix:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&alloc[i][j]);

    printf("Enter Request Matrix:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&request[i][j]);

    printf("Enter Available:\n");
    for(int i=0;i<m;i++)
        scanf("%d",&available[i]);

    bool finish[MAX];

    // Initialize finish
    for(int i=0;i<n;i++) {
        bool zero = true;
        for(int j=0;j<m;j++) {
            if(alloc[i][j] != 0) {
                zero = false;
                break;
            }
        }
        finish[i] = zero;
    }

    int work[MAX];
    for(int i=0;i<m;i++)
        work[i] = available[i];

    while(true) {
        bool found = false;

        for(int i=0;i<n;i++) {
            if(!finish[i]) {
                bool possible = true;

                for(int j=0;j<m;j++) {
                    if(request[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }

                if(possible) {
                    for(int j=0;j<m;j++)
                        work[j] += alloc[i][j];

                    finish[i] = true;
                    found = true;
                }
            }
        }

        if(!found)
            break;
    }

    // Check deadlock
    bool deadlock = false;
    for(int i=0;i<n;i++) {
        if(!finish[i]) {
            deadlock = true;
            printf("Process P%d is in deadlock\n", i);
        }
    }

    if(!deadlock)
        printf("No deadlock detected\n");

    return 0;
}
