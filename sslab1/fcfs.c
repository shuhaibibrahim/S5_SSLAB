//Program expects to input the process in the ascending order of arrival time

#include<stdio.h>
 // Function to find the waiting time for all
// processes
void findWaitingTime(int n, int bt[], int wt[], int at[])
{
    int service_time[n];
    service_time[0] = 0;
    wt[0] = 0;
    // calculating waiting time
    for (int i = 1; i < n; i++) {
        // Add burst time of previous processes
        service_time[i] = service_time[i - 1] + bt[i - 1];
        // Find waiting time for current process =
        // sum - at[i]
        wt[i] = service_time[i] - at[i];
        // If waiting time for a process is in negative
        // that means it is already in the ready queue
        // before CPU becomes idle so its waiting time is 0
        if (wt[i] < 0)
            wt[i] = 0;
    }
}

// Function to calculate turn around time
void findTurnAroundTime(int n, int bt[],int wt[], int tat[])
{
    // Calculating turnaround time by adding bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}
// Function to calculate average waiting and turn-around
// times.
void findavgTime(int n, int bt[], int at[]) {
    int wt[n], tat[n];
    // Function to find waiting time of all processes
    findWaitingTime(n, bt, wt, at);
    // Function to find turn around time for all processes
    findTurnAroundTime(n, bt, wt, tat);
    // Display processes along with all details
    printf("Processes Burst Time Arrival Time Waiting Time Turn-Around Time \n");
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        int compl_time = tat[i] + at[i];
        printf("%d \t\t %d \t\t %d \t\t %d \t\t %d\n", i, bt[i], at[i], wt[i], tat[i]);
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
// Driver code
void main() {
    // Process id’s
    int n, bt[100], at[100];
    printf("Enter the number of processes : ");
    scanf("%d", & n);

    for (int i = 0; i < n; i++) {
        printf("Enter the burst time and arrival time for process %d : ", i);
        scanf("%d %d", & bt[i], & at[i]);
    }
    findavgTime(n, bt, at);
}


