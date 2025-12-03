#!/bin/bash

# Create a temporary C file to test the function
cat <<EOF > test_handle_process_arrival_pp.c
#include <stdio.h>
#include "oslabs.h"

void print_ready_queue(struct PCB ready_queue[], int queue_cnt) {
    for (int i = 0; i < queue_cnt; i++) {
        printf("[PID:%d, AT:%d, TBT:%d, EST:%d, EET:%d, RBT:%d, Priority:%d]\\n",
               ready_queue[i].process_id,
               ready_queue[i].arrival_timestamp,
               ready_queue[i].total_bursttime,
               ready_queue[i].execution_starttime,
               ready_queue[i].execution_endtime,
               ready_queue[i].remaining_bursttime,
               ready_queue[i].process_priority);
    }
}

int main() {
    struct PCB ready_queue[QUEUEMAX] = {
        {1, 1, 4, 0, 0, 4, 23},
        {2, 1, 4, 0, 0, 4, 22},
        {3, 1, 4, 0, 0, 4, 24}
    };
    int queue_cnt = 3;
    int timestamp = 2;

    struct PCB current_process = ready_queue[1]; // PID:2
    struct PCB new_process = {0}; // No new process in this test case

    struct PCB result = handle_process_arrival_pp(ready_queue, &queue_cnt, current_process, new_process, timestamp);

    printf("Updated Ready Queue:\\n");
    print_ready_queue(ready_queue, queue_cnt);

    printf("Updated Queue Count: %d\\n", queue_cnt);

    printf("Returned PCB: [PID:%d, AT:%d, TBT:%d, EST:%d, EET:%d, RBT:%d, Priority:%d]\\n",
           result.process_id,
           result.arrival_timestamp,
           result.total_bursttime,
           result.execution_starttime,
           result.execution_endtime,
           result.remaining_bursttime,
           result.process_priority);

    return 0;
}
EOF

# Compile the test file with the cpu.c implementation
gcc -o test_handle_process_arrival_pp test_handle_process_arrival_pp.c cpu.c -I.

# Run the test
./test_handle_process_arrival_pp

# Clean up
rm test_handle_process_arrival_pp test_handle_process_arrival_pp.c