#include <stdio.h>
#define MAX_FRAMES 10
#define MAX_PAGES 50

// Function to find the Least Recently Used (LRU) page
int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; ++i) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int pages[MAX_PAGES];
    int frames[MAX_FRAMES], time[MAX_FRAMES];
    int n, m; // n = number of pages, m = number of frames
    int count = 0, faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &m);

    // Initialize frames as empty (-1)
    for (int i = 0; i < m; ++i)
        frames[i] = -1;

    printf("\nStep\tPage\tFrames\n");
    printf("--------------------------------\n");

    for (int i = 0; i < n; ++i) {
        int flag = 0;

        // Check if the page already exists in a frame (Page Hit)
        for (int j = 0; j < m; ++j) {
            if (frames[j] == pages[i]) {
                count++;
                time[j] = count; // Update recent use time
                flag = 1;
                break;
            }
        }

        // If not found → Page Fault
        if (!flag) {
            int empty = -1;

            // Check for an empty frame
            for (int j = 0; j < m; ++j) {
                if (frames[j] == -1) {
                    empty = j;
                    break;
                }
            }

            if (empty != -1) {
                // Place in empty frame
                frames[empty] = pages[i];
                count++;
                time[empty] = count;
            } else {
                // Replace least recently used page
                int pos = findLRU(time, m);
                frames[pos] = pages[i];
                count++;
                time[pos] = count;
            }
            faults++;
        }

        // Print current frame status
        printf("%2d\t%2d\t[", i + 1, pages[i]);
        for (int j = 0; j < m; ++j) {
            if (frames[j] != -1)
                printf(" %d", frames[j]);
            else
                printf(" -");
        }
        printf(" ]\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
    return 0;
}
