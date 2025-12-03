#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "oslabs.h"

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id)
{
    struct MEMORY_BLOCK temp_memory_block, allocated_memory;
    allocated_memory.end_address = 0;
    allocated_memory.start_address = 0;
    allocated_memory.process_id = 0;
    allocated_memory.segment_size = 0;

    if (request_size == 0)
    {
        return allocated_memory;
    }

    bool match = false;
    int memory_map_index = 0, best_fit_segment = 0;

    for (int i = 0; i <= *map_cnt; i++)
    {
        if ((memory_map[i].segment_size >= request_size) &&
            (memory_map[i].process_id == 0))
        {
            if (match == false)
            {
                memory_map_index = i;
                best_fit_segment = memory_map[i].segment_size;
                match = true;
            }
            else if (memory_map[i].segment_size < best_fit_segment)
            {
                memory_map_index = i;
                best_fit_segment = memory_map[i].segment_size;
            }
        }
    }

    if (match == true)
    {
        if (request_size < memory_map[memory_map_index].segment_size)
        {
            temp_memory_block = memory_map[memory_map_index];
            allocated_memory.start_address =
                memory_map[memory_map_index].start_address;
            allocated_memory.end_address =
                memory_map[memory_map_index].start_address + request_size - 1;
            allocated_memory.process_id = process_id;
            allocated_memory.segment_size = request_size;

            *map_cnt = *map_cnt + 1;

            struct MEMORY_BLOCK temp_memory_block_2;
            for (int i = memory_map_index; i <= *map_cnt; i++)
            {
                temp_memory_block_2 = memory_map[i + 1];
                memory_map[i + 1] = temp_memory_block;
                temp_memory_block = temp_memory_block_2;
                memory_map[memory_map_index + 1].start_address =
                    allocated_memory.end_address + 1;
                memory_map[memory_map_index + 1].end_address =
                    memory_map[memory_map_index].end_address;
                memory_map[memory_map_index].segment_size - allocated_memory.segment_size;
            }
            memory_map[memory_map_index + 1].process_id = 0;
            memory_map[memory_map_index + 1].segment_size =
                memory_map[memory_map_index] = allocated_memory;
            else
            {
                allocated_memory.start_address =
                    memory_map[memory_map_index].start_address;
                allocated_memory.end_address =
                    memory_map[memory_map_index].start_address + request_size - 1;
struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK
            }
            allocated_memory.process_id = process _id;
            allocated_memory.segment_size = request_size;
            memory_map[memory_map_index] = allocated_memory;
            return allocated_memory;
memory_map[MAPMAX],int *map_cnt, int process_id)
{
    struct MEMORY_BLOCK temp_memory_block, allocated_memory;
    allocated_memory.end_address = Q;
    allocated_memory.start_address = Q;
    allocated_memory.process_id = Q0;
    allocated_memory.segment_size = 0;
    if (request_size == 0)
    {
        return allocated_memory;
        bool match = false;
        int memory_map_index = 0, best_fit_segment = Q;

        for (int i = 0; i < x = *map_cnt; i++)
        {
            if ((memory_map[i].segment_size >= request_size) &&
                (memory_map[i].process_id == 0))
            {
                if (match == false)
                {
                    memory_map_index = i;
                    best_fit_segment = memory_map[i].segment_size;
                    match = true;
                    break;
                }
                else if (memory_map[i].segment_size < best_fit_segment)
                {
                    memory_map_index = i;
                    best_fit_segment = memory_map[i].segment_size;
                }
            }
        }

        if (match == true)
        {
            if (request_size < memory_map[memory_map_index].segment_size)
            {
                temp_memory_block = memory_map[memory_map_index];
                allocated_memory.start_address =
                    memory_map[memory_map_index].start_address;
                allocated_memory.end_address =
                    memory_map[memory_map_index].start_address + request_size - 1;
                allocated_memory.process_id = process_id;
                allocated_memory.segment_size = request_size;

                *map_cnt = *map_cnt + 1;
                struct MEMORY_BLOCK temp_memory_block_2;

                for (int i = memory_map_index; i <= *map_cnt; i++)
                {
                    temp_memory_block_2 = memory_map[i + 1];
                    memory_map[i + 1] = temp_memory_block;
                    temp_memory_block = temp_memory_block_2;
                }

                memory_map[memory_map_index + 1].start_address =
                    allocated_memory.end_address + 1;
                memory_map[memory_map_index + 1].end_address =
                    memory_map[memory_map_index].end_address;
                memory_map[memory_map_index + 1].process_id = Q;
                memory_map[memory_map_index + 1].segment_size =
                    memory_map[memory_map_index].segment_size - allocated_memory.segment_size;

                memory_map[memory_map_index] = allocated_memory;
            }
            else
            {
                allocated_memory.start_address =
                    memory_map[memory_map_index].start_address;

                allocated_memory.end_address =
                    memory_map[memory_map_index].start_address + request_size - 1;
                allocated_memory.process_id = process_id;
                allocated_memory.segment_size = request_size;

                memory_map[memory_map_index] = allocated_memory;
            }
        }
        return allocated_memory;
    }

    struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id)
    {
        struct MEMORY_BLOCK temp_memory_block, allocated_memory;
        allocated_memory.end_address = Q;
        allocated_memory.start_address = 0;
        allocated_memory.process_id = 0;
        allocated_memory.segment_size = Q;

        if (request_size == 0)
        {
            return allocated_memory;
        }

        bool match = false;
        int memory_map_index = 0, best_fit_segment = 0;

        for (int i = 0; i <= *map_cnt; i++)
        {
            if ((memory_map[i].segment_size >= request_size) &&
                (memory_map[i].process_id == 0))
            {
                if (match == false)
                {
                    memory_map_index = i;
                    best_fit_segment = memory_map[i].segment_size;
                    match = true;
                }
                else if (memory_map[i].segment_size > best_fit_segment)
                {
                    memory_map_index = i;
                    best_fit_segment = memory_map[i].segment_size;
                }
            }
        }

        if (match == true)
        {
            if (request_size < memory_map[memory_map_index].segment_size)
            {
            https:

                allocated_memory.start_address =
                    memory_map[memory_map_index].start_address;
                allocated_memory.end_address =
                    memory_map[memory_map_index].start_address + request_size - 1;
                allocated_memory.process_id = process_id;
                allocated_memory.segment_size = request_size;

                *map_cnt = *map_cnt + 1;
                struct MEMORY_BLOCK temp_memory_block_2;

                for (int i = memory_map_index; i <= *map_cnt; i++)
                {
                    temp_memory_block_2 = memory_map[i + 1];
                    memory_map[i + 1] = temp_memory_block;
                    temp_memory_block = temp_memory_block_2;
                }

                memory_map[memory_map_index + 1].start_address =
                    allocated_memory.end_address + 1;
                memory_map[memory_map_index + 1].end_address =
                    memory_map[memory_map_index].end_address;
                memory_map[memory_map_index + 1].process_id = 9;
                memory_map[memory_map_index + 1].segment_size =
                    memory_map[memory_map_index].segment_size - allocated_memory.segment_size;

                memory_map[memory_map_index] = allocated_memory;
            }
            else
            {
                allocated_memory.start_address =
                    memory_map[memory_map_index].start_address;
                allocated_memory.end_address =
                    memory_map[memory_map_index].start_address + request_size - 1;
                allocated_memory.process_id = process_id;
                allocated_memory.segment_size = request_size;

                memory_map[memory_map_index] = allocated_memory;
            }
        }
        return allocated_memory;
    }

    struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id, int last_address)
    {

        struct MEMORY_BLOCK temp_memory_block, allocated_memory;
        allocated_memory.end_address = 0;
        allocated_memory.start_address = Q;

        allocated_memory.process_id = 9;
        allocated_memory.segment_size =
            if (request_size == 9)
        {
            return allocated_memory;
            bool match = false;
int memory_map_index = 0 , best
for (int i = 0; i<x=*map_cnt; i+
if ((memory_map[i].segment_
(memory_map[i].process_id == 0) &&
last_address)) {
                            if (match == false)
                            {
                                memory_map_index =
                                    best_fit_segment =
                                        match = true;
                                break;
                            }
else if (memory_map[i].
memory_map_index =
best_fit_segment =
if (match == true) {
                                if (request_size < memory_map[memory_map_index].segment_size)
                                {
temp_memory_block = mem
allocated_memory.start_
memory_map[memory_map_index].start_
allocated_memory.end_ad
memory_map[memory_map_index].start_.
allocated_memory.proces
allocated_memory.segmen
*map_cnt = *map_cnt + 1

)
;
_fit_segment = 0;
+)
{
size >= request_size) &&
(memory_map[i].start_address >=
i;
memory_map[i].segment_size;
segment_size < best_fit_segment)
{
    i;
    memory_map[i].segment_size;
    ory_map[memory_map_index];
    address =
        address;
    dress =
        address + request_size - 1;
    S_id = process_id;
    t_size = request_size;
)
struct MEMORY_BLOCK temp_memory_block_2;
for (int i = memory_map
temp_memory_block_2
memory_map[i+1] = t
temp_memory_block =
memory_map[memory_map_i
allocated_memory.end_address + 1;
index; i <= *map_cnt; i++)
{
    = memory_map[i + 1];
    emp_memory_block;
    temp_memory_block_2;
ndex+1].start_address =

 memory_map[memory_map_index+1].end_address =
memory_map[memory_map_index].end_address;
memory_map[memory_map_index + 1].process_id = Q;
memory_map[memory_map_index + 1].segment_size =
    memory_map[memory_map_index].segment_size - allocated_memory.segment_size;

memory_map[memory_map_index] = allocated_memory;
}
else
{
    allocated_memory.start_address =
        memory_map[memory_map_index].start_address;
    allocated_memory.end_address =
        memory_map[memory_map_index].start_address + request_size - 1;
    allocated_memory.process_id = process _id;
    allocated_memory.segment_size = request_size;

    memory_map[memory_map_index] = allocated_memory;
}
}
return allocated_memory;
}

void release_memory(struct MEMORY _BLOCK freed_block, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt)
{
    bool flag = false;
    if ((*map_cnt == 1) && (memory_map[0].end_address == 0) &&
        (memory_map[0].start_address == 0) && (memory_map[0].process_id == 0) &&
        (memory_map[0].segment_size == 0))
        return;
    else
    {
        for (int i = 0; i < *map_cnt; i++)
        {
            if ((freed_block.start_address == memory_map[i].start_address) &&
                (freed_block.end_address == memory_map[i].end_address) &&
                (freed_block.process_id == memory_map[i].process_id))
            {
                memory_map[i].process_id = 0;
                if (i > 0)
                {
                    if (memory_map[i - 1].process_id == 0)
                    {
                        memory_map[i - 1].end_address = freed_block.end_address;
                        memory_map[i - 1].segment_size = memory_map[i - 1].segment_size +
                                                         freed_block.segment_size;
                        for (int index = i; index <= *map_cnt; index++)
                        {

                            memory_map[index] = memory_map[index + 1];
                        }
                        *map_cnt = *map_cnt - 1;
                        flag = true;
                    }
                }
                if (i < *map_cnt - 1)
                {
                    if (flag == false)
                    {
                        i = i + 1;
                    }
                    if (memory_map[i].process_id == 0)
                    {
                        memory_map[i].start_address = memory_map[i - 1].start_address;
                        memory_map[i].segment_size = memory_map[i].end_address -
                                                     memory_map[i].start_address + 1;
                        for (int index = i; index <= *map_cnt; index++)
                        {
                            memory_map[index - 1] = memory_map[index];
                        }
                        *map_cnt = *map_cnt - 1;
                    }
                }
                break;
            }
        }
    }
}
