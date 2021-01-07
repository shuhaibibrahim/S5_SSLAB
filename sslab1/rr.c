#include<stdio.h>
 // Function to find the waiting time for all
// processes
struct rr {

    int pid;
    int t;
}
r[100]; //to store the sequence to display gantt chart
int k = 0;
void findWaitingTime(int n, int bt[], int wt[], int quantum) {
    // Make a copy of burst times bt[] to store remaining
    // burst times.
    int rem_bt[n];
    for (int i = 0; i < n; i++)
        rem_bt[i] = bt[i];
    int t = 0; // Current time
    // Keep traversing processes in round robin manner
    // until all of them are not done.
    while (1) {
        int done = 1;
        // Traverse all processes one by one repeatedly
        for (int i = 0; i < n; i++) {
            // If burst time of a process is greater than 0
            // then only need to process further
            if (rem_bt[i] > 0) {
                done = 0; // There is a pending process
                r[k].pid = i;
                if (rem_bt[i] > quantum) {
                    // Increase the value of t i.e. shows
                    // how much time a process has been processed
                    t += quantum;
                    // Decrease the burst_time of current process
                    // by quantum
                    rem_bt[i] -= quantum;
                    r[k].t = quantum;
                }
                // If burst time is smaller than or equal to
                // quantum. Last cycle for this process
                else {
                    // Increase the value of t i.e. shows
                    // how much time a process has been processed
                    t = t + rem_bt[i];
                    // Waiting time is current time minus time
                    // used by this process
                    wt[i] = t - bt[i];
                    r[k].t = rem_bt[i];
                    // As the process gets fully executed
                    // make its remaining burst time = 0
                    rem_bt[i] = 0;
                }
                k++;
            }
        }
        // If all processes are done
        if (done)
            break;
    }
}
// Function to calculate turn around time
void findTurnAroundTime(int n, int bt[], int wt[], int tat[]) {
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}
// Function to calculate average time
void findavgTime(int n, int bt[], int quantum) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    // Function to find waiting time of all processes
    findWaitingTime(n, bt, wt, quantum);
    // Function to find turn around time for all processes
    findTurnAroundTime(n, bt, wt, tat);
    // Display processes along with all details
    printf("Processes Burst time Waiting time Turn around time\n");
    // Calculate total waiting time and total turn
    // around time
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf("%d\t\t%d\t %d\t\t %d\n", i, bt[i], wt[i], tat[i]);
    }
    printf("\nAverage waiting time = %.2f", (float) total_wt / (float) n);
    printf("\nAverage turn around time = %.2f", (float) total_tat / (float) n);
    int t = 0;
    printf("\n\nGantt Chart:\n");
    for (int i = 0; i < k; i++) {
        printf("t=%d <----", t);
        printf("P%d---> ", r[i].pid);
        t += r[i].t;
    }
    printf("t=%d\n", t);

}

void main() {
    int n, bt[100];
    printf("Enter the number of processes : ");
    scanf("%d", & n);
    for (int i = 0; i < n; i++) {
        printf("Enter the burst time for process %d : ", i);
        scanf("%d", & bt[i]);
    }
    // Time quantum
    int quantum;
    printf("Enter the time quantum : ");
    scanf("%d", & quantum);
    findavgTime(n, bt, quantum);
}
