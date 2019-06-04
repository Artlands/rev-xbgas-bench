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
 * double value put from PE 0 to PE 1 to shmem_malloc'ed variable
 * (Intended for runinng on 2 PEs)
 */

#include <stdio.h>
#include <math.h>
#include "test.h"
#include "xbrtime.h"

static const double E = 2.71828182;
static const double PI = 3.14159265;

static const double EPSILON = 0.00000001;

int main(void)
{
    size_t xbgas_sz  = _XBGAS_ALLOC_SIZE_;
    size_t xbgas_nelems = _XBGAS_ALLOC_NELEMS_;
    double local_accesses = 0;
    double remote_accesses = 0;
    double time_init = 0;
	double time_mem = 0;
	double time_start = 0;
	double time_end = 0;

    double *f;
    int me;
    int npes;

    time_start = mysecond();

    xbrtime_init();
    me = xbrtime_mype();
    npes = xbrtime_num_pes();

    f = (double *) xbrtime_malloc(sizeof(*f));

    *f = PI;
    temp_barrier();

    if(me == 0){
		printf("=========================\n");
		printf(" xBGAS Dip Benchmark\n");
		printf("=========================\n");
		printf("Data size       = %d Bytes\n", (int)(xbgas_sz) * (int)(xbgas_nelems) );
		printf("Element #       = %d\n", xbgas_nelems);
		printf("PE #            = %d\n", npes);
	}

    if (me == 0) {
        xbrtime_double_put(f, &E, 1, 0, 1);
    }

    temp_barrier();



    if (me == 1) {
        printf("PE %d            = %f, %s\n",
               me, *f, (fabs(*f - E) < EPSILON) ? "TEST VERIFIED!" : "TEST FAILED");
    }

    temp_barrier();

    if(me == 0){
				time_end = mysecond();
				printf("Time cost       = %f sec\n", time_end - time_start);
				printf("------------------------------------------\n");
    }

    xbrtime_free(f);

    xbrtime_close();

    return 0;
}
