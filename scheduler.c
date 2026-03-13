#include <stdio.h>
#include <stdbool.h>

typedef enum { READY, RUNNING, TERMINATED } State;

typedef struct {
    char name[10];
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    State state;
    // 模拟内存隔离的变量
    int num; 
} PCB;

int main() {
    PCB processes[4] = {
        {"P1", 1, 0, 13, 13, 1, READY, 30},
        {"P2", 2, 5, 7, 7, 2, READY, 30},
        {"P3", 3, 10, 5, 5 ,4, READY, 30},
         {"P4", 4, 15, 11, 11, 3, READY, 30},
    };

    int currentTime = 0;
    int finished = 0;
    int TurnaroundTime = 0;
    //公式：$TAT = \text{Finish Time} - \text{Arrival Time}$ 
    int WaitTime = 0;
    //公式：$WT = TAT - \text{Burst Time}$ 
    int TotalWaitTime = 0;

    while (finished < 4) {
        int best_idx = -1;
        int higest_priority = -1;

        for (int i = 0; i < 4; i++) {
            if (processes[i].arrival_time <= currentTime && processes[i].state != TERMINATED) {
                if (processes[i].priority> higest_priority) {
                    higest_priority = processes[i].priority;
                    best_idx = i;
                }
            }
        }
        if (best_idx != -1) {
            printf("Time %d: %s starts running\n", currentTime, processes[best_idx].name);
            processes[best_idx].remaining_time--;
            currentTime++;
            if (processes[best_idx].remaining_time == 0) {
                processes[best_idx].state = TERMINATED;
                finished++;
                TurnaroundTime = currentTime - processes[best_idx].arrival_time;
                WaitTime = TurnaroundTime - processes[best_idx].burst_time;
                TotalWaitTime += WaitTime;
            }
        } else {
            currentTime++;
        }
    }
    printf("Average Waiting time: %f\n", (float)TotalWaitTime/finished);
    
}   