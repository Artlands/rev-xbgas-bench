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

/*
 * PORTED FROM OpenSHMEM CODE FOR XBGAS
 * This program shows how to use shmem_put to simulate MPI_Alltoall.
 * Each processor send/rec a different random number to/from other processors.
 * Adopted/ported from source url: http://geco.mines.edu/workshop/class2/examples/mpi/c_ex07.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "xbrtime.h"

/* globals */
int numnodes, myid;

void init_it(int *argc, char ***argv);
void seed_random(int id);
void random_number(float *z);

void init_it(int *argc, char ***argv)
{
    xbrtime_init();
    numnodes = xbrtime_num_pes();
    myid = xbrtime_mype();
}

int main(int argc, char *argv[])
{
    size_t xbgas_sz  = _XBGAS_ALLOC_SIZE_;
    size_t xbgas_nelems = _XBGAS_ALLOC_NELEMS_;
    double local_accesses = 0;
    double remote_accesses = 0;
    double time_init = 0;
    double time_mem = 0;
    double time_start = 0;
    double time_end = 0;

    time_start = mysecond();

    int *scounts, *rcounts;
    int i, node_id;
    float z;

    init_it(&argc, &argv);
    scounts = (int *) xbrtime_malloc(sizeof(int) * numnodes);
    rcounts = (int *) xbrtime_malloc(sizeof(int) * numnodes);

    /*  ! seed the random number generator with a ! different number on each
       processor */
    seed_random(myid);

    /* find data to send */
    for (i = 0; i < numnodes; i++) {
        random_number(&z);
        scounts[i] = myid;
        rcounts[i] = myid;
    }


    if(myid == 0){
		printf("===========================\n");
		printf(" xBGAS Shmem_all Benchmark\n");
		printf("===========================\n");
		printf("Data size       = %d Bytes\n", (int)(xbgas_sz) * (int)(xbgas_nelems) );
		printf("Element #       = %d\n", xbgas_nelems);
		printf("PE #            = %d\n", numnodes);
		printf("------------------------------------------\n");
		}
    temp_barrier();
    printf("myid            = %d, scounts=", myid);
    for (i = 0; i < numnodes; i++) {
        printf("%d ", scounts[i]);
    }
    printf("\n");

    for (node_id = 0; node_id < numnodes; node_id++) {
            xbrtime_int_put(&rcounts[myid], &scounts[node_id], 1, 0, node_id);
    }

    temp_barrier();

    printf("myid            = %d, rcounts=", myid);
    for (i = 0; i < numnodes; i++) {
        printf("%d ", rcounts[i]);
    }
    printf("\n");

		if(myid == 0){
				time_end = mysecond();
				printf("Time cost       = %f sec\n", time_end - time_start);
				printf("------------------------------------------\n");
		}
    xbrtime_free(scounts);
    xbrtime_free(rcounts);
    xbrtime_close();
    return 0;
}

void seed_random(int id)
{
    srand((unsigned int) id);
}

void random_number(float *z)
{
    int i;
    i = rand();
    *z = (float) i / RAND_MAX;
}
