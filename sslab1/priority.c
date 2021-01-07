#include<stdio.h>

void swap(int * a, int * b) {
    int temp = * a;
    * a = * b;
    * b = temp;
}
void arrangePriority(int num, int bt[], int pt[], int pid[]) {
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (pt[j] > pt[j + 1])
	    {
                    swap( & bt[j], & bt[j + 1]);
                    swap( & pt[j], & pt[j + 1]);
                    swap( & pid[j], & pid[j + 1]);
            }
        }
    }
}
void findWaitingTime(int n, int bt[], int wt[], int pt[])
{
    int service_time[n];
    service_time[0] = 0;
    wt[0] = 0;
    // calculating waiting time
    for (int i = 1; i < n; i++) {
        // Add burst time of previous processes
        service_time[i] = service_time[i - 1] + bt[i - 1];
        // Find waiting time for current process =
        // sum - pt[i]
        wt[i] = service_time[i];
        // If waiting time for a process is in negative
        // that means it is already in the ready queue
        // before CPU becomes idle so its waiting time is 0
        if (wt[i] < 0)
            wt[i] = 0;
    }
}
// Function to calculate turn around time
void findTurnAroundTime(int n, int bt[], int wt[], int tat[])
{
    // Calculating turnaround time by adding bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}
// Function to calculate average waiting and turn-around
// times.
void findavgTime(int n, int bt[], int pt[], int pid[]) {
    int wt[n], tat[n];
    // Function to find waiting time of all processes
    findWaitingTime(n, bt, wt, pt);
    // Function to find turn around time for all processes
    findTurnAroundTime(n, bt, wt, tat);
    // Display processes along with all details
    printf("Processes\tBurst Time\tPriority\tWaiting Time\tTurn-Around Time \n");
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        // int compl_time = tat[i] + pt[i];
        printf("%d \t\t %d \t\t %d \t\t %d \t\t %d\n", pid[i], bt[i], pt[i], wt[i], tat[i]);
    }
    printf("\nAverage waiting time = %.2f", (float) total_wt / (float) n);
    printf("\nAverage turn around time = %.2f", (float) total_tat / (float) n);
    int t = 0, tp = 0;
    printf("\n\nGantt Chart:\n<");
    for (int i = 0; i < n; i++) {
        printf("[t=%d P%d]", t, i);
        tp = t;
        while (t - tp < bt[i]) {
            printf("=");
            t++;
        }
    }
    printf(">\n");
}

void main() {

    int n, bt[100], pt[100], pid[100];
    printf("Enter the number of processes : ");
    scanf("%d", & n);
    for (int i = 0; i < n; i++) {
        printf("Enter the burst time and priority for process %d : ", i);
        scanf("%d %d", & bt[i], & pt[i]);
	pid[i]=i;
    }
    arrangePriority(n, bt, pt, pid);
    findavgTime(n, bt, pt, pid);
}
