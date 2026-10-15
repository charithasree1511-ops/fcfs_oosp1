#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

int compare(const void *a, const void *b) {
    struct Process *p1 = (struct Process *)a;
    struct Process *p2 = (struct Process *)b;

    if (p1->arrival_time < p2->arrival_time)
        return -1;
    if (p1->arrival_time > p2->arrival_time)
        return 1;

    return p1->pid - p2->pid;
}

int main() {
    int n, current_time = 0;
    float total_waiting_time = 0;
    float total_turnaround_time = 0;
    int total_burst_time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);

        if (p[i].arrival_time < 0 || p[i].burst_time <= 0) {
            printf("Invalid input. Arrival must be >= 0 and burst must be > 0.\n");
            return 1;
        }
    }

    qsort(p, n, sizeof(struct Process), compare);

    printf("\nProcess\tArrival\tBurst\tStart\tCompletion\tWaiting\tTurnaround\n");

    for (int i = 0; i < n; i++) {
        p[i].start_time = (current_time > p[i].arrival_time)
                            ? current_time : p[i].arrival_time;

        p[i].waiting_time = p[i].start_time - p[i].arrival_time;

        p[i].completion_time = p[i].start_time + p[i].burst_time;

        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;

        current_time = p[i].completion_time;

        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
        total_burst_time += p[i].burst_time;

        printf("P%d\t%d\t%d\t%d\t%d\t\t%d\t%d\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].start_time,
               p[i].completion_time,
               p[i].waiting_time,
               p[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n",
           total_waiting_time / n);

    printf("Average Turnaround Time: %.2f\n",
           total_turnaround_time / n);

    printf("Throughput: %.2f processes/unit time\n",
           (float)n / current_time);

    printf("Total CPU Burst Time: %d\n", total_burst_time);

    return 0;
}

