#include<stdio.h>
#include"oslabs.h"
#include<stdlib.h>

struct RCB handle_request_arrival_fcfs(struct RCB request_queue[QUEUEMAX], int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp)
{
    if(current_request.address == 0 && current_request.arrival_timestamp ==0 && current_request.cylinder==0 &&
        current_request.process_id == 0 && current_request.request_id == 0) //checking if disk is free
    {
        request_queue[*queue_cnt] = new_request;
        *queue_cnt+=1;
        return new_request;
    }
    else  // else adding new request to queue and returning current request
    {
        request_queue[*queue_cnt] = new_request;
        *queue_cnt+=1;
        return current_request;
    }
}


struct RCB handle_request_completion_fcfs(struct RCB request_queue[QUEUEMAX], int *queue_cnt)
{
    struct RCB result = {0,0,0,0,0};
    if(*queue_cnt == 0)  //if queue is empty
        return result;
    int minAT = request_queue[0].arrival_timestamp;
    int minIndex=0;
    for(int i=0; i<*queue_cnt; i++)  //finding request with minimum arrival time
    {
        if(request_queue[i].arrival_timestamp < minAT)
        {
            minIndex = i;
            minAT = request_queue[i].arrival_timestamp;
        }
    }
    result = request_queue[minIndex];
    *queue_cnt -=1;
    for(int i=minIndex; i<*queue_cnt; i++)
    {
        request_queue[i] = request_queue[i+1];
    }
    return result;
}

struct RCB handle_request_arrival_sstf(struct RCB request_queue[QUEUEMAX], int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp)
{
    if(current_request.address == 0 && current_request.arrival_timestamp ==0 && current_request.cylinder==0 &&
        current_request.process_id == 0 && current_request.request_id == 0) //checking if disk is free
    {
        request_queue[*queue_cnt] = new_request;
        *queue_cnt+=1;
        return new_request;
    }
    else  // else adding new request to queue and returning current request
    {
        request_queue[*queue_cnt] = new_request;
        *queue_cnt+=1;
        return current_request;
    }
}


struct RCB handle_request_completion_sstf(struct RCB request_queue[QUEUEMAX], int *queue_cnt, int current_cylinder)
{
    struct RCB result = {0,0,0,0,0};
    if(*queue_cnt == 0)  //if queue is empty
        return result;
    int minAT = request_queue[0].arrival_timestamp;
    int processIndex = 0;
    int diffFromCylinder = current_cylinder - request_queue[0].cylinder;
    if(diffFromCylinder < 0)
        diffFromCylinder *= -1;
    for(int i=0; i< *queue_cnt; i++)  //finding cylinder closest to current cylinder
    {
        int temp = current_cylinder - request_queue[i].cylinder;
        if(temp < 0)
            temp *= -1;
        if(temp < diffFromCylinder)
        {
        processIndex = i;
            minAT = request_queue[i].arrival_timestamp;
            diffFromCylinder = temp;
        }
        else if(temp == diffFromCylinder && minAT > request_queue[i].arrival_timestamp)  //if two requests have same distance form current cylinder
        {
            processIndex = i;
            minAT = request_queue[i].arrival_timestamp;
            diffFromCylinder = temp;
        }
    }
    result = request_queue[processIndex];
    *queue_cnt -=1;
    for(int i=processIndex; i<*queue_cnt; i++)
    {
        request_queue[i] = request_queue[i+1];
    }
    return result;
}


struct RCB handle_request_arrival_look(struct RCB request_queue[QUEUEMAX], int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp)
{
    if(current_request.address == 0 && current_request.arrival_timestamp ==0 && current_request.cylinder==0 &&
        current_request.process_id == 0 && current_request.request_id == 0) //checking if disk is free
    {
        request_queue[*queue_cnt] = new_request;
        *queue_cnt+=1;
        return new_request;
    }
    else  // else adding new request to queue and returning current request
    {
        request_queue[*queue_cnt] = new_request;
        *queue_cnt+=1;
        return current_request;
    }
}


struct RCB handle_request_completion_look(struct RCB request_queue[QUEUEMAX], int *queue_cnt, int current_cylinder, int scan_direction)
{
    struct RCB result = {0,0,0,0,0};
    if(*queue_cnt == 0)  //if queue is empty
        return result;
    int cylNo = current_cylinder;
    int arrTime = __INT_MAX__;
    int processIndex=-1;
    for(int i=0; i< *queue_cnt; i++)  //if cylinder number of request is same as current cylinder
    {
        if(cylNo == request_queue[i].cylinder && arrTime > request_queue[i].arrival_timestamp)
        {
            arrTime = request_queue[i].arrival_timestamp;
            processIndex = i;
        }
    }
    if(processIndex != -1)
    {
        result = request_queue[processIndex];
        *queue_cnt -=1;
        for(int i=processIndex; i<*queue_cnt; i++)
        {
            request_queue[i] = request_queue[i+1];
        }
        return result;
    }
    if(scan_direction == 1)
    {
        processIndex = -1;
        int diffFromCylinder = __INT_MAX__;
        for(int i=0; i< *queue_cnt; i++)  //if scan direction is 1 and there are requests having cylinder number greater than current cylinder number
        {
            if(current_cylinder < request_queue[i].cylinder)
            {
                int temp = current_cylinder - request_queue[i].cylinder;
                if(temp < 0)
                    temp *= -1;
                if(temp < diffFromCylinder)
                {
                    processIndex = i;
                    diffFromCylinder = temp;
                }
            }
        }
        if(processIndex != -1)
        {result = request_queue[processIndex];
            *queue_cnt -=1;
            for(int i=processIndex; i<*queue_cnt; i++)
            {
                request_queue[i] = request_queue[i+1];
            }
            return result;
        }
        else  // if there are no requests haivng cylinder number greater than current cylinder and direction is 1
        {
            for(int i=0; i< *queue_cnt; i++)
            {
                int temp = current_cylinder - request_queue[i].cylinder;
                if(temp < 0)
                    temp *= -1;
                if(temp < diffFromCylinder)
                {
                    processIndex = i;
                    diffFromCylinder = temp;
                }
            }
            result = request_queue[processIndex];
            *queue_cnt -=1;
            for(int i=processIndex; i<*queue_cnt; i++)
            {
                request_queue[i] = request_queue[i+1];
            }
            return result;
        }
    }
    else if (scan_direction == 0)  //if scan direction is 1 and there are requests having cylinder number less than current cylinder number
    {
        processIndex = -1;
        int diffFromCylinder = __INT_MAX__;
        for(int i=0; i< *queue_cnt; i++)
        {
            if(current_cylinder > request_queue[i].cylinder)
            {
                int temp = current_cylinder - request_queue[i].cylinder;
                if(temp < 0)
                    temp *= -1;
                if(temp < diffFromCylinder)
                {
                    processIndex = i;
                    diffFromCylinder = temp;
                }
            }
            }
        if(processIndex != -1)
        {
            result = request_queue[processIndex];
            *queue_cnt -=1;
            for(int i=processIndex; i<*queue_cnt; i++)
            {
                request_queue[i] = request_queue[i+1];
            }
            return result;
        }
        else  // if there are no requests haivng cylinder number less than current cylinder and direction is 0
        {
            for(int i=0; i< *queue_cnt; i++)
            {
                int temp = current_cylinder - request_queue[i].cylinder;
                if(temp < 0)
                    temp *= -1;
                if(temp < diffFromCylinder)
                {
                    processIndex = i;
                    diffFromCylinder = temp;
                }
            }
            result = request_queue[processIndex];
            *queue_cnt -=1;
            for(int i=processIndex; i<*queue_cnt; i++)
            {
                request_queue[i] = request_queue[i+1];
            }
            return result;
        }
    }
    return result;
}   