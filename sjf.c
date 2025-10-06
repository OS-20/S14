#include <stdio.h>

int main() {
    int n, i, time = 0, completed = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n], done[n];

    for(i = 0; i < n; i++){
        pid[i] = i+1;
        printf("P%d arrival & burst time: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        done[i] = 0;
    }

    printf("\nGantt Chart:\n|");
    while(completed < n){
        int idx = -1, minBT = 100000;
        for(i = 0; i < n; i++){
            if(!done[i] && at[i] <= time && bt[i] < minBT){
                minBT = bt[i];
                idx = i;
            }
        }

        if(idx == -1){ time++; continue; } // CPU idle

        printf(" P%d |", pid[idx]);
        time += bt[idx];
        ct[idx] = time;
        done[idx] = 1;
        completed++;
    }

    int totalTAT = 0, totalWT = 0;
    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++){
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        totalTAT += tat[i];
        totalWT += wt[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage TAT=%.2f, Average WT=%.2f\n", (float)totalTAT/n, (float)totalWT/n);
    return 0;
}
