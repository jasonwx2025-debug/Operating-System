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
    while (finished < 4) {
        int best_idx = -1;
        int min_burst = 999;

        for (int i = 0; i < 4; i++) {
            if (processes[i].arrival_time <= currentTime && processes[i].state == READY) {
                if (processes[i].burst_time < min_burst) {
                    min_burst = processes[i].burst_time;
                    best_idx = i;
                }
            }
        }
        if (best_idx != -1) {
            // 2. 模拟非抢占执行：直接跳到执行结束的时间
            printf("Time %d: %s starts running\n", currentTime, processes[best_idx].name);
            
            currentTime = currentTime + processes[best_idx].burst_time;
            processes[best_idx].state = TERMINATED;
            
            finished++;
        } else {
           
            currentTime++;
        }
    }
    
}   
