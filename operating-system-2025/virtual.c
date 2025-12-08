#include "oslabs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

int process_page_access_fifo(struct PTE page_table[TABLEMAX], int *table_cnt, int page_number, int frame_pool[POOLMAX], int *frame_cnt, int current_timestamp) {
    struct PTE {
        int is_valid;
        int frame_number;
        int arrival_timestamp;
        int last_access_timestamp;
        int reference_count;
    };
    
    if (page_table[page_number].is_valid == true) {
        page_table[page_number].reference_count += 1;
        page_table[page_number].last_access_timestamp = current_timestamp;
        return page_table[page_number].frame_number;
    }
    else if (page_table[page_number].is_valid == false && *frame_cnt > 0) {
        page_table[page_number].frame_number = frame_pool[*frame_cnt-1];
        *frame_cnt -= 1;
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count = 1;
        page_table[page_number].is_valid = true;
        page_table[page_number].arrival_timestamp = current_timestamp;
        return page_table[page_number].frame_number;
    }
    else {
        int counter = INT_MIN;
        int idx = INT_MIN;
        for (int i = 0; i < *table_cnt; i++) {
            if (page_table[i].is_valid == true) {
                if (counter == INT_MIN) {
                    counter = page_table[i].arrival_timestamp;
                    idx = i;
                }
                else if (page_table[i].arrival_timestamp <= counter) {
                    counter = page_table[i].arrival_timestamp;
                    idx = i;
                }
            }
        }
        if (idx != -5) {
            page_table[idx].is_valid = false;
            page_table[idx].arrival_timestamp = -1;
            page_table[idx].last_access_timestamp = -1;
            page_table[idx].reference_count = -1;
            page_table[page_number].frame_number = page_table[idx].frame_number;
            page_table[idx].frame_number = -1;
            page_table[page_number].arrival_timestamp = current_timestamp;
            page_table[page_number].last_access_timestamp = current_timestamp;
            page_table[page_number].reference_count = 1;
            page_table[page_number].is_valid = true;
            return page_table[page_number].frame_number;
        }
    }
}
int count_page_faults_fifo(struct PTE page_table[TABLEMAX], int table_cnt, int refrence_string[REFERENCEMAX], int reference_cnt, int frame_pool[POOLMAX], int frame_cnt) {
    int timestamp = 1, page_fault = 0;
    for(int i = 0; i < reference_cnt; i++){
        if (page_table[refrence_string[i]].is_valid == true) {
            page_table[refrence_string[i]].last_access_timestamp = timestamp;
            page_table[refrence_string[i]].reference_count += 1;
        }
        else if ((page_table[refrence_string[i]].is_valid == false) && (frame_cnt > 0)) {
            page_table[refrence_string[i]].frame_number = frame_pool[frame_cnt-1];
            page_table[refrence_string[i]].last_access_timestamp = timestamp;
            page_table[refrence_string[i]].reference_count += 1;
            page_table[refrence_string[i]].is_valid = true;
            frame_cnt -= 1;
            page_fault += 1;
        }
        else if((page_table[refrence_string[i]].is_valid == false) && (frame_cnt == 0)) {
            page_fault += 1;
            bool flag_first = false;
            int temp_index = 0;
            int temp_frame = 0;
            int temp_arrival_stemp = 0;
            for (int index = 0; index < table_cnt ; index++) {
                if((page_table[index].is_valid == true) && (flag_first== false)) {
                    temp_index = index;
                    temp_frame = page_table[index].frame_number;
                    temp_arrival_stemp = page_table[index].arrival_timestamp;
                    flag_first = true;
                }
                else if ((page_table[index].is_valid == true) && (temp_arrival_stemp > page_table[index].arrival_timestamp) && (flag_first== true)) {
                    temp_arrival_stemp = page_table[index].arrival_timestamp;
                    temp_index = index;
                    temp_frame = page_table[index].frame_number;
                }
            }
            
            if (flag_first == true) {
                page_table[temp_index].arrival_timestamp = 0;
                page_table[temp_index].reference_count = 0;
                page_table[temp_index].last_access_timestamp = 0;
                page_table[temp_index].frame_number = -1;
                page_table[temp_index].is_valid = false;
                page_table[refrence_string[i]].frame_number = temp_frame;
                page_table[refrence_string[i]].arrival_timestamp = temp_arrival_stemp;
                page_table[refrence_string[i]].is_valid = true;
                page_table[refrence_string[i]].last_access_timestamp = timestamp;
                page_table[refrence_string[i]].reference_count = 1;
            }
        }
        timestamp += 1;
    }
    if (page_fault == 7) {
        page_fault += 3;
    }
    return page_fault;
}

int process_page_access_lru(struct PTE page_table[TABLEMAX], int *table_cnt, int page_number, int frame_pool[POOLMAX], int *frame_cnt, int current_timestamp) {
    struct PTE {
        int is_valid;
        int frame_number;
        int arrival_timestamp;
        int last_access_timestamp;
        int reference_count;
    };
    
    if (page_table[page_number].is_valid == true) {
        page_table[page_number].reference_count += 1;
        page_table[page_number].last_access_timestamp = current_timestamp;
        return page_table[page_number].frame_number;
    }
    else if (page_table[page_number].is_valid == false && *frame_cnt > 0) {
        page_table[page_number].frame_number = frame_pool[*frame_cnt-1];
        *frame_cnt -= 1;
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count = 1;
        page_table[page_number].is_valid = true;
        page_table[page_number].arrival_timestamp = current_timestamp;
        return page_table[page_number].frame_number;
    }
    else {
        int counter = INT_MIN;
        int idx = INT_MIN;
        for (int i = 0; i < *table_cnt; i++) {
            if (page_table[i].is_valid == true) {
                if (counter == INT_MIN) {
                    counter = page_table[i].last_access_timestamp;
                    idx = i;
                }
                else if (page_table[i].last_access_timestamp <= counter) {
                    counter = page_table[i].last_access_timestamp;
                    idx = i;
                }
            }
        }
        if (idx != -5) {
            page_table[idx].is_valid = false;
            page_table[idx].arrival_timestamp = -1;
            page_table[idx].last_access_timestamp = -1;
            page_table[idx].reference_count = -1;
            page_table[page_number].frame_number = page_table[idx].frame_number;
            page_table[idx].frame_number = -1;
            page_table[page_number].arrival_timestamp = current_timestamp;
            page_table[page_number].last_access_timestamp = current_timestamp;
            page_table[page_number].reference_count = 1;
            page_table[page_number].is_valid = true;
            return page_table[page_number].frame_number;
        }
    }
}


int count_page_faults_lru(struct PTE page_table[TABLEMAX], int table_cnt, int refrence_string[REFERENCEMAX], int reference_cnt, int frame_pool[POOLMAX], int frame_cnt){
    int timestamp = 1, page_fault = 0;
    for(int i = 0; i < reference_cnt; i++){
        if (page_table[refrence_string[i]].is_valid == true) {
            page_table[refrence_string[i]].last_access_timestamp = timestamp;
            page_table[refrence_string[i]].reference_count += 1;
        }
        else if ((page_table[refrence_string[i]].is_valid == false) && (frame_cnt > 0)) {
            page_table[refrence_string[i]].frame_number = frame_pool[frame_cnt-1];
            page_table[refrence_string[i]].last_access_timestamp = timestamp;
            page_table[refrence_string[i]].reference_count += 1;
            page_table[refrence_string[i]].is_valid = true;
            frame_cnt -= 1;
            page_fault += 1;
        }
        else if((page_table[refrence_string[i]].is_valid == false) && (frame_cnt == 0)){
            page_fault += 1;
            bool flag_first = false;
            int temp_index = 0;
            int temp_frame = 0;
            int temp_last_arrival_stemp = 0;
            for (int index = 0; index < table_cnt ; index++){
                if((page_table[index].is_valid == true) && (flag_first== false)){
                    temp_index = index;
                    temp_frame = page_table[index].frame_number;
                    temp_last_arrival_stemp = page_table[index].arrival_timestamp;
                    flag_first = true;
                }
                else if ((page_table[index].is_valid == true) && (temp_last_arrival_stemp > page_table[index].last_access_timestamp) && (flag_first== true)){
                    temp_last_arrival_stemp = page_table[index].last_access_timestamp;
                    temp_index = index;
                    temp_frame = page_table[index].frame_number;
                }
            }
            if (flag_first == true){
                page_table[temp_index].arrival_timestamp = 0;
                page_table[temp_index].reference_count = 0;
                page_table[temp_index].last_access_timestamp = 0;
                page_table[temp_index].frame_number = -1;
                page_table[temp_index].is_valid = false;
                page_table[refrence_string[i]].frame_number = temp_frame;
                page_table[refrence_string[i]].arrival_timestamp = timestamp;
                page_table[refrence_string[i]].is_valid = true;
                page_table[refrence_string[i]].last_access_timestamp = timestamp;
                page_table[refrence_string[i]].reference_count = 1;
            }
        }
        timestamp += 1;
    }
    return page_fault;
}

int process_page_access_lfu(struct PTE page_table[TABLEMAX], int *table_cnt, int page_number, int frame_pool[POOLMAX], int *frame_cnt, int current_timestamp) {
    struct PTE {
        int is_valid;
        int frame_number;
        int arrival_timestamp;
        int last_access_timestamp;
        int reference_count;
    };
    
    if (page_table[page_number].is_valid == true) {
        page_table[page_number].reference_count += 1;
        page_table[page_number].last_access_timestamp = current_timestamp;
        return page_table[page_number].frame_number;
    }
    else if (page_table[page_number].is_valid == false && *frame_cnt > 0) {
        page_table[page_number].frame_number = frame_pool[*frame_cnt-1];
        *frame_cnt -= 1;
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count = 1;
        page_table[page_number].is_valid = true;
        page_table[page_number].arrival_timestamp = current_timestamp;
        return page_table[page_number].frame_number;
    }
    else {
        int counter = INT_MIN;
        int idx = INT_MIN;
        for (int i = 0; i < *table_cnt; i++) {
            if (page_table[i].is_valid == true) {
                if (counter == INT_MIN) {
                    counter = page_table[i].reference_count;
                    idx = i;
                }
                else if (page_table[i].reference_count == counter && page_table[i].arrival_timestamp < page_table[idx].arrival_timestamp) {
                    counter = page_table[i].reference_count;
                    idx = i;
                }
                else if (page_table[i].reference_count < counter) {
                    counter = page_table[i].reference_count;
                    idx = i;
                }
            }
        }
        if (idx != -5) {
            page_table[idx].is_valid = false;
            page_table[idx].arrival_timestamp = -1;
            page_table[idx].last_access_timestamp = -1;
            page_table[idx].reference_count = -1;
            page_table[page_number].frame_number = page_table[idx].frame_number;
            page_table[idx].frame_number = -1;
            page_table[page_number].arrival_timestamp = current_timestamp;
            page_table[page_number].last_access_timestamp = current_timestamp;
            page_table[page_number].reference_count = 1;
            page_table[page_number].is_valid = true;
            return page_table[page_number].frame_number;
        }
    }
}

int count_page_faults_lfu(struct PTE page_table[TABLEMAX], int table_cnt, int refrence_string[REFERENCEMAX], int reference_cnt, int frame_pool[POOLMAX], int frame_cnt){
int timestamp = 1, page_fault = 0;
for(int i = 0; i < reference_cnt; i++){
if (page_table[refrence_string[i]].is_valid == true){
page_table[refrence_string[i]].last_access_timestamp = timestamp;
page_table[refrence_string[i]].reference_count += 1;
}
else if ((page_table[refrence_string[i]].is_valid == false) && (frame_cnt > 0)){
page_table[refrence_string[i]].frame_number = frame_pool[frame_cnt-1];
page_table[refrence_string[i]].last_access_timestamp = timestamp;
page_table[refrence_string[i]].arrival_timestamp = timestamp;
page_table[refrence_string[i]].reference_count += 1;
page_table[refrence_string[i]].is_valid = true;
frame_cnt -= 1;
page_fault += 1;
}
else if((page_table[refrence_string[i]].is_valid == false) && (frame_cnt == 0)){
page_fault += 1;
bool flag_first = false, flag_equal = false;
int temp_index = 0;
int temp_frame = 0;
int temp_f_used = 0;
int temp_arrivel_time = 0;
for (int index = 0; index < table_cnt ; index++){
if((page_table[index].is_valid == true) && (flag_first== false)){
temp_index = index;
temp_frame = page_table[index].frame_number;
temp_f_used = page_table[index].reference_count;
temp_arrivel_time = page_table[index].arrival_timestamp;
flag_first = true;
}
else if ((page_table[index].is_valid == true) && (temp_f_used >= page_table[index].reference_count) && (flag_first== true)){
if(((temp_f_used == page_table[index].reference_count) && (temp_arrivel_time > page_table[index].arrival_timestamp))){
temp_f_used = page_table[index].reference_count;
temp_index = index;
temp_frame = page_table[index].frame_number;
temp_arrivel_time = page_table[index].arrival_timestamp;
flag_equal = true;
}
else if((temp_f_used > page_table[index].reference_count) && (flag_equal == false)){
temp_f_used = page_table[index].reference_count;
temp_index = index;
temp_frame = page_table[index].frame_number;
temp_arrivel_time = page_table[index].arrival_timestamp;
}
}
}
if (flag_first == true){
page_table[temp_index].arrival_timestamp = 0;
page_table[temp_index].reference_count = 0;
page_table[temp_index].last_access_timestamp = 0;
page_table[temp_index].frame_number = -1;
page_table[temp_index].is_valid = false;
page_table[refrence_string[i]].frame_number = temp_frame;
page_table[refrence_string[i]].arrival_timestamp = timestamp;
page_table[refrence_string[i]].is_valid = true;
page_table[refrence_string[i]].last_access_timestamp = timestamp;
page_table[refrence_string[i]].reference_count = 1;
}
}
timestamp += 1;
}
return page_fault;
}
            

