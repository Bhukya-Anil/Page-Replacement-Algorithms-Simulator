#include<stdio.h>

void print(int frameno, int frame[]) {
    for (int j = 0; j < frameno; j++)
        printf("%d\t", frame[j]);
    printf("\n");
}

void optimal(int n, int page[], int frameno) {
    int frame[frameno], move = 0, count = 0, hits = 0;
    
    for (int i = 0; i < frameno; i++)
        frame[i] = -1;

    printf("Page reference string\tFrames (Optimal)\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t\t", page[i]);
        int flag = 0;
        
        for (int j = 0; j < frameno; j++) {
            if (page[i] == frame[j]) {
                flag = 1;
                printf("No replacement\n");
                hits++;
                break;
            }
        }
        
        if (flag == 0 && count < frameno) {
            frame[move] = page[i];
            move = (move + 1) % frameno;
            count++;
            print(frameno, frame);
        } else if (flag == 0) {
            int temp[frameno];
            for (int j = 0; j < frameno; j++) {
                temp[j] = -1;
                for (int k = i + 1; k < n; k++) {
                    if (frame[j] == page[k]) {
                        temp[j] = k;
                        break;
                    }
                }
            }

            int pos = -1;
            for (int j = 0; j < frameno; j++) {
                if (temp[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1) {
                int max = temp[0];
                pos = 0;

                for (int j = 1; j < frameno; j++) {
                    if (temp[j] > max) {
                        max = temp[j];
                        pos = j;
                    }
                }
            }

            frame[pos] = page[i];
            count++;
            print(frameno, frame);
        }
    }

    printf("Number of page faults (Optimal) is %d\n", count);
    printf("Number of page hits (Optimal) is %d\n", hits);
    printf("Hit ratio (Optimal) is %.2f\n", (float)hits / n);
    printf("Fault rate (Optimal) is %.2f\n", 1.0 - ((float)hits / n));
}

void lfu(int n, int page[], int frameno) {
    int frame[frameno], move = 0, count = 0, hits = 0, count1[10] = {0};

    for (int i = 0; i < frameno; i++)
        frame[i] = -1;

    printf("Page reference string\tFrames (LFU)\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t\t", page[i]);
        int flag = 0;

        for (int j = 0; j < frameno; j++) {
            if (page[i] == frame[j]) {
                flag = 1;
                count1[j]++;
                printf("No replacement\n");
                hits++;
                break;
            }
        }

        if (flag == 0 && count < frameno) {
            frame[move] = page[i];
            count1[move] = 1;
            move = (move + 1) % frameno;
            count++;
            print(frameno, frame);
        } else if (flag == 0) {
            int repindex = 0, leastcount = count1[0];

            for (int j = 1; j < frameno; j++) {
                if (count1[j] < leastcount) {
                    repindex = j;
                    leastcount = count1[j];
                }
            }

            frame[repindex] = page[i];
            count1[repindex] = 1;
            count++;
            print(frameno, frame);
        }
    }

    float rate = (float)count / (float)n;
    printf("Number of page faults (LFU) is %d\n", count);
    printf("Number of page hits (LFU) is %d\n", hits);
    printf("Hit ratio (LFU) is %.2f\n", (float)hits / n);
    printf("Fault rate (LFU) is %.2f\n", 1.0 - ((float)hits / n));
}

void fifo(int n, int page[], int frameno) {
    int frame[frameno], move = 0, count = 0, hits = 0;
    
    for (int i = 0; i < frameno; i++)
        frame[i] = -1;

    printf("Page reference string\tFrames (FIFO)\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t\t", page[i]);
        int flag = 0;
        
        for (int j = 0; j < frameno; j++) {
            if (page[i] == frame[j]) {
                flag = 1;
                printf("No replacement\n");
                hits++;
                break;
            }
        }
        
        if (flag == 0 && count < frameno) {
            frame[move] = page[i];
            move = (move + 1) % frameno;
            count++;
            print(frameno, frame);
        } else if (flag == 0) {
            frame[move] = page[i];
            move = (move + 1) % frameno;
            count++;
            print(frameno, frame);
        }
    }

    printf("Number of page faults (FIFO) is %d\n", count);
    printf("Number of page hits (FIFO) is %d\n", hits);
    printf("Hit ratio (FIFO) is %.2f\n", (float)hits / n);
    printf("Fault rate (FIFO) is %.2f\n", 1.0 - ((float)hits / n));
}

void lru(int n, int page[], int frameno) {
    int frame[frameno], move = 0, count = 0, hits = 0, counter[10] = {0};

    for (int i = 0; i < frameno; i++)
        frame[i] = -1;

    printf("Page reference string\tFrames (LRU)\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t\t", page[i]);
        int flag = 0;

        for (int j = 0; j < frameno; j++) {
            if (page[i] == frame[j]) {
                flag = 1;
                counter[j] = 0;
                printf("No replacement\n");
                hits++;
                break;
            }
        }

        if (flag == 0 && count < frameno) {
            frame[move] = page[i];
            counter[move] = 0;
            move = (move + 1) % frameno;
            count++;
            print(frameno, frame);
        } else if (flag == 0) {
            int max = counter[0];
            int repindex = 0;

            for (int j = 1; j < frameno; j++) {
                if (counter[j] > max) {
                    max = counter[j];
                    repindex = j;
                }
            }

            frame[repindex] = page[i];
            counter[repindex] = 0;
            count++;
            print(frameno, frame);
        }

        for (int j = 0; j < frameno; j++)
            counter[j]++;
    }

    float rate = (float)count / (float)n;
    printf("Number of page faults (LRU) is %d\n", count);
    printf("Number of page hits (LRU) is %d\n", hits);
    printf("Hit ratio (LRU) is %.2f\n", (float)hits / n);
    printf("Fault rate (LRU) is %.2f\n", 1.0 - ((float)hits / n));
}

int main() {
    int n, frameno;
    
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    
    int page[n];
    
    printf("Enter the page reference numbers: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &page[i]);
    
    printf("Enter the number of frames: ");
    scanf("%d", &frameno);

    int choice;
    
    printf("Choose the page replacement algorithm:\n");
    printf("1. Optimal\n2. LFU\n3. FIFO\n4. LRU\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            optimal(n, page, frameno);
            break;
        case 2:
            lfu(n, page, frameno);
            break;
        case 3:
            fifo(n, page, frameno);
            break;
        case 4:
            lru(n, page, frameno);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    return 0;
}