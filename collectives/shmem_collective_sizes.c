/*
 *
 * Copyright (c) 2016 - 2018
 *   Stony Brook University
 * Copyright (c) 2015 - 2018
 *   Los Alamos National Security, LLC.
 * Copyright (c) 2011 - 2015
 *   University of Houston System and UT-Battelle, LLC.
 * Copyright (c) 2009 - 2015
 *   Silicon Graphics International Corp.  SHMEM is copyrighted
 *   by Silicon Graphics International Corp. (SGI) The OpenSHMEM API
 *   (shmem) is released by Open Source Software Solutions, Inc., under an
 *   agreement with Silicon Graphics International Corp. (SGI).
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * o Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * o Neither the name of the University of Houston System,
 *   UT-Battelle, LLC. nor the names of its contributors may be used to
 *   endorse or promote products derived from this software without specific
 *   prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <shmem.h>
//#include "test.h"
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/perf_event.h>
#include <linux/hw_breakpoint.h>
#include <asm/unistd.h>
#include <sys/types.h>
#include <sys/time.h>

long broadcast_psync[SHMEM_BCAST_SYNC_SIZE];
int reduce_pwrk[25600];
long reduce_psync[SHMEM_REDUCE_SYNC_SIZE];
long collect_psync[SHMEM_COLLECT_SYNC_SIZE];

int
main()
{
 		shmem_init();

 struct perf_event_attr pe1;
 long long count;
 int fd;
 memset(&pe1, 0, sizeof(struct perf_event_attr));
 pe1.type = PERF_TYPE_HARDWARE;
 pe1.size = sizeof(struct perf_event_attr);
 pe1.config = PERF_COUNT_HW_INSTRUCTIONS;
 pe1.disabled = 1;
 pe1.exclude_kernel = 1;
 pe1.exclude_hv = 1;
 pe1.exclude_idle = 1;
 pe1.pinned = 1;

 fd = perf_event_open(&pe1, 0, -1, -1, 0);
 if (fd == -1) {
    fprintf(stderr, "Error opening leader %llx\n", pe1.config);
    exit(EXIT_FAILURE);
 }

    int i;
    int me;
    int numpes = shmem_n_pes();
    me = shmem_my_pe();
    int *long_arr = (int*) shmem_malloc(sizeof(int) * 25600);
    int *small_arr = (int*) shmem_malloc(sizeof(int) * 256);

    for(int i = 0; i < SHMEM_BCAST_SYNC_SIZE; i++)
    {
        broadcast_psync[i] = SHMEM_SYNC_VALUE;
    }

    for(int i = 0; i < SHMEM_REDUCE_SYNC_SIZE; i++)
    {
        reduce_psync[i] = SHMEM_SYNC_VALUE;
    }

    for(int i = 0; i < SHMEM_COLLECT_SYNC_SIZE; i++)
    {
        collect_psync[i] = SHMEM_SYNC_VALUE;
    }

    for(i = 0; i < 256; i++)
    {
        small_arr[i] = me;
    }

    for(i = 0; i < 25600; i++)
    {
        long_arr[i] = me;
    }

    shmem_barrier_all();

 		ioctl(fd, PERF_EVENT_IOC_RESET, 0);
 		ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);

        shmem_broadcast32(small_arr, small_arr, 256, 0, 0, 0, numpes, broadcast_psync);
        //shmem_broadcast32(long_arr, long_arr, 25600, 0, 0, 0, numpes, broadcast_psync);
        //shmem_int_sum_to_all(small_arr, small_arr, 256, 0, 0, numpes, reduce_pwrk, reduce_psync);
        //shmem_int_sum_to_all(long_arr, long_arr, 25600, 0, 0, numpes, reduce_pwrk, reduce_psync);
        //shmem_collect32(small_arr, small_arr, 64, 0, 0, numpes, collect_psync);
        //shmem_collect32(long_arr, long_arr, 6400, 0, 0, numpes, collect_psync);


 		ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);

    shmem_barrier_all();
 	  read(fd, &count, sizeof(long long));
 		printf("Used %lld instructions\n", count);
		//while(1);
    /*if (me == 1) {
        for (i = 0; i < numpes; i += 1) {
            printf("PE %d: target[%d] = %hd, source[%d] = %hd\n",
                   me, i, target[i], i, source[i]);
        } 
    }*/

    shmem_free(long_arr);
    shmem_free(small_arr);



    shmem_finalize();
 		close(fd);

    return 0;
}
