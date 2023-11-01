#include <stdio.h>

struct Process {
    int process_id;
    int burst_time;
    int arrival_time;
    int remaining_time;
};

void round_robin_scheduler(struct Process processes[], int n, int time_quantum) {
    int current_time = 0;
    int total_waiting_time = 0;
    int front = 0, rear = 0;
    int queue[n];

    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    while (1) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                found = 1;
                if (processes[i].remaining_time > time_quantum) {
                    current_time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                } else {
                    current_time += processes[i].remaining_time;
                    total_waiting_time += current_time - processes[i].arrival_time - processes[i].burst_time;
                    processes[i].remaining_time = 0;
                }
                queue[rear] = i;
                rear = (rear + 1) % n;
            }
        }

        if (!found)
            current_time++;

        int next_process = queue[front];
        if (processes[next_process].remaining_time == 0) {
            front = (front + 1) % n;
        }

        int all_done = 1;
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                all_done = 0;
                break;
            }
        }

        if (all_done)
            break;
    }

    printf("Total waiting time for all processes: %d\n", total_waiting_time);
}

int main() {
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        processes[i].process_id = i + 1;
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    round_robin_scheduler(processes, n, time_quantum);
    return 0;
}
