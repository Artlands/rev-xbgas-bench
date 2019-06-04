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
 * get from right neighbor, with wrap-around
 */

#include <stdio.h>
#include "test.h"
#include "xbrtime.h"

int main(int argc, char **argv)
{
    size_t xbgas_sz  = _XBGAS_ALLOC_SIZE_;
    size_t xbgas_nelems = _XBGAS_ALLOC_NELEMS_;
    double local_accesses = 0;
    double remote_accesses = 0;
    double time_init = 0;
	double time_mem = 0;
	double time_start = 0;
	double time_end = 0;
		int i = 0;

    time_start = mysecond();

    long *src;
    long dest;
    int nextpe;
    int me, npes;

    xbrtime_init();
    me = xbrtime_mype();
    npes = xbrtime_num_pes();

    src = (long *) xbrtime_malloc(sizeof(*src));

    *src = me;

    nextpe = (me + 1) % npes;

    temp_barrier();

    if(me == 0){
		printf("=========================\n");
		printf(" xBGAS RotGet Benchmark\n");
		printf("=========================\n");
		printf("Data size       = %d Bytes\n", (int)(xbgas_sz) * (int)(xbgas_nelems) );
		printf("Element #       = %d\n", xbgas_nelems);
		printf("PE #            = %d\n", npes);
	}

    xbrtime_long_get(&dest, src, 1, 0, nextpe);

    if(me == 0){
				time_end = mysecond();
				printf("Time cost       = %f sec\n", time_end - time_start);
				printf("------------------------------------------\n");
    		printf("Before:\n");
				for( i = 0; i < npes; i++)
					printf("PE = %d : Shared_var = %d\n", i, i);
    		printf("After:\n");
    }
    temp_barrier();


    printf("PE = %d : Shared_var = %ld\n", me, dest);
    temp_barrier();

		if(me == 0)
				printf("------------------------------------------\n");

    xbrtime_free(src);
    xbrtime_close();

    return 0;
}
