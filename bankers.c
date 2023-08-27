#include <stdio.h>

void main()
{
    int alloc[10][10], max[10][10];
    int avail[10], work[10], total[10];
    int need[10][10];
    int i, j, n, m;
    int count = 0;

    printf("Enter the number of processes and resources:");
    scanf("%d %d", &n, &m);
    printf("Enter the claim matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter the allocation matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Resource vector:");
    for (i = 0; i < m; i++)
        scanf("%d", &total[i]);

    for (i = 0; i < m; i++)
    {
        avail[i] = total[i];
        for (j = 0; j < n; j++)
            avail[i] -= alloc[j][i];
    }

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    while (count < n)
    {
        int found = 0;

        for (i = 0; i < n; i++)
        {
            if (avail[i] != -1)
            {
                int canExecute = 1;

                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        canExecute = 0;
                        break;
                    }
                }

                if (canExecute)
                {
                    printf("Process %d can execute\n", i + 1);
                    count++;
                    for (j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    avail[i] = -1;
                    found = 1;
                }
            }
        }

        if (!found)
        {
            printf("System is in an unsafe state\n");
            break;
        }
    }

    if (count == n)
        printf("System is in a safe state\n");
}
