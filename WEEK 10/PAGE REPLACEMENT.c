#include <stdio.h>

#define MAX 50

/* Function to check if page is present in frame */
int isPresent(int frames[], int n, int page)
{
    for (int i = 0; i < n; i++)
    {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}

/* ---------------- FIFO ---------------- */
void FIFO(int pages[], int n, int capacity)
{
    int frames[MAX], index = 0, faults = 0;

    for (int i = 0; i < capacity; i++)
        frames[i] = -1;

    printf("\nFIFO Page Replacement\n");

    for (int i = 0; i < n; i++)
    {
        if (!isPresent(frames, capacity, pages[i]))
        {
            frames[index] = pages[i];
            index = (index + 1) % capacity;
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        for (int j = 0; j < capacity; j++)
        {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);
}

/* ---------------- LRU ---------------- */
void LRU(int pages[], int n, int capacity)
{
    int frames[MAX], time[MAX];
    int faults = 0, counter = 0;

    for (int i = 0; i < capacity; i++)
    {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Replacement\n");

    for (int i = 0; i < n; i++)
    {
        int found = 0;

        for (int j = 0; j < capacity; j++)
        {
            if (frames[j] == pages[i])
            {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if (!found)
        {
            int pos = 0;

            for (int j = 1; j < capacity; j++)
            {
                if (time[j] < time[pos])
                    pos = j;
            }

            counter++;
            frames[pos] = pages[i];
            time[pos] = counter;
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        for (int j = 0; j < capacity; j++)
        {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);
}

/* ---------------- Optimal ---------------- */
void Optimal(int pages[], int n, int capacity)
{
    int frames[MAX];
    int faults = 0;

    for (int i = 0; i < capacity; i++)
        frames[i] = -1;

    printf("\nOptimal Page Replacement\n");

    for (int i = 0; i < n; i++)
    {
        if (!isPresent(frames, capacity, pages[i]))
        {
            int pos = -1, farthest = i + 1;

            for (int j = 0; j < capacity; j++)
            {
                int k;
                for (k = i + 1; k < n; k++)
                {
                    if (frames[j] == pages[k])
                    {
                        if (k > farthest)
                        {
                            farthest = k;
                            pos = j;
                        }
                        break;
                    }
                }

                if (k == n)
                {
                    pos = j;
                    break;
                }
            }

            if (pos == -1)
                pos = 0;

            frames[pos] = pages[i];
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        for (int j = 0; j < capacity; j++)
        {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);
}

/* ---------------- Main Function ---------------- */
int main()
{
    int pages[MAX], n, capacity;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter frame capacity: ");
    scanf("%d", &capacity);

    FIFO(pages, n, capacity);
    LRU(pages, n, capacity);
    Optimal(pages, n, capacity);

    return 0;
}
