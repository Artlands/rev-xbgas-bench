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
 */

#include <stdio.h>
#include "test.h"
#include "xbrtime.h"

int main()
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

    short source[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    short *target;
    int i;
    int me;
    int npes;

    xbrtime_init();
    me = xbrtime_mype();
    npes = xbrtime_num_pes();

    target = (short *) xbrtime_malloc(10 * sizeof(*target));

    for (i = 0; i < 10; i += 1) {
        target[i] = 666;
    }

    temp_barrier();

    if(me == 0){
		printf("=========================\n");
		printf(" xBGAS Stride Benchmark\n");
		printf("=========================\n");
		printf("Data size       = %d Bytes\n", (int)(xbgas_sz) * (int)(xbgas_nelems) );
		printf("Element #       = %d\n", xbgas_nelems);
		printf("PE #            = %d\n", npes);
	}

    if (me == 0) {
        xbrtime_short_put(target, source, 5, 2, 1);
    }

    temp_barrier();        /* sync sender and receiver */




    if(me == 0){
				time_end = mysecond();
				printf("Time cost       = %f sec\n", time_end - time_start);
				printf("------------------------------------------\n");
    }
    temp_barrier();

    if (me == 1) {
        for (i = 0; i < 10; i += 1) {
            printf("PE %d: target[%d] = %hd\n", me, i, target[i]);
        }
    }
    xbrtime_free(target);

    xbrtime_close();

    return 0;
}
