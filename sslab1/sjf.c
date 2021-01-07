//input expects cpu not in idle state

#include <stdio.h>
#include<stdio.h>

int mat[10][6];
void swap(int * a, int * b) {
    int temp = * a;
    * a = * b;
    * b = temp;
}

void arrangeArrival(int num, int mat[][6]) {
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (mat[j][1] > mat[j + 1][1]) {
                for (int k = 0; k < 5; k++) {
                    swap( & mat[j][k], & mat[j + 1][k]);
                }
            }
        }
    }
}
void completionTime(int num, int mat[][6]) {
    int temp, val;
    for (int i = 0; i < num; i++) {
        if (i == 0)
            temp = 0;
        else
            temp = mat[i - 1][3]; //temp is the cpu service time/completion time till i-1
        int low = mat[i][2];
        for (int j = i; j < num; j++) {
            if (temp >= mat[j][1] && low >= mat[j][2]) {
                low = mat[j][2];
                val = j;
            }
        }
        mat[val][3] = temp + mat[val][2]; //completion time of i= service time till i-1 + burst time of i
        mat[val][5] = mat[val][3] - mat[val][1]; //turn aroud time=completion time-arrival time
        mat[val][4] = mat[val][5] - mat[val][2]; //waiting time=turn around time-burst time 
        for (int k = 0; k < 6; k++) {
            swap( & mat[val][k], & mat[i][k]);
        }

    }
}
void main() {
    int num, temp;
    printf("Enter the number of processes : ");
    scanf("%d", & num);
    for (int i = 0; i < num; i++) {
        mat[i][0] = i;
        printf("Enter the arrival time and burst time for process %d : ", i);
        scanf("%d %d", & mat[i][1], & mat[i][2]);
    }
    arrangeArrival(num, mat);
    completionTime(num, mat);
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    int tot_wt = 0, tot_tat = 0;
    for (int i = 0; i < num; i++) {
        tot_wt += mat[i][4];
        tot_tat += mat[i][5];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", mat[i][0], mat[i][1], mat[i][2], mat[i][4], mat[i][5]);
    }
    printf("\nAverage waiting time = %.2f", (float) tot_wt / (float) num);
    printf("\nAverage turn around time = %.2f", (float) tot_tat / (float) num);
    int t = 0, tp = 0;
    printf("\n\nGantt Chart:\n<");
    for (int i = 0; i < num; i++) {
        printf("[t=%d P%d]", t, mat[i][0]);
        tp = t;
        while (t - tp < mat[i][2]) {
            printf("=");
            t++;
        }
    }
    printf(">\n");
}

