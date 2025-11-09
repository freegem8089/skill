#include <stdio.h>
#include <stdbool.h>

int main() {
    int P, R;

    printf("Enter number of processes: ");
    scanf("%d", &P);
    printf("Enter number of resources: ");
    scanf("%d", &R);

    int allocation[P][R], max[P][R], need[P][R], available[R];
    bool finished[P];
    int safeSequence[P];
    int count = 0;

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Max Matrix
    printf("\nEnter Max Matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources (%d values):\n", R);
    for (int i = 0; i < R; i++) {
        scanf("%d", &available[i]);
    }

    // Initialize finished array
    for (int i = 0; i < P; i++)
        finished[i] = false;

    // Calculate Need Matrix
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Display Need Matrix
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Find Safe Sequence
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finished[i]) {
                bool canAllocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > available[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    // Allocate resources to process
                    for (int j = 0; j < R; j++) {
                        available[j] += allocation[i][j];
                    }
                    safeSequence[count++] = i;
                    finished[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("\nSystem is NOT in a safe state.\n");
            return 1;
        }
    }

    // Print Safe Sequence
    printf("\nSystem is in a SAFE STATE.\nSafe Sequence: ");
    for (int i = 0; i < P; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");

    return 0;
}
