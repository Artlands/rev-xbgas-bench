/*
 * _REDUCTION_DEMO_C_
 *
 * Copyright (C) 2017-2019 Tactical Computing Laboratories, LLC
 * All Rights Reserved
 * contact@tactcomplabs.com
 *
 * This file is a part of the XBGAS-RUNTIME package.  For license
 * information, see the LICENSE file in the top level directory
 * of the distribution.
 *
 */

 #include "xbrtime.h"

int main()
{
    xbrtime_init();
	int i, my_pe, *r_val;
	my_pe = xbrtime_mype();
	r_val = (int*) xbrtime_malloc(10 * sizeof(int));

    for(i = 0; i < 10; i++)
    {
        r_val[i] = my_pe;
    }

	printf("Pre-Reduction - PE:%d R_Val: %d %d %d %d %d %d %d %d %d %d\n", \
            my_pe, r_val[0], r_val[1], r_val[2], r_val[3], r_val[4], r_val[5], r_val[6], r_val[7], r_val[8], r_val[9]);

	temp_barrier();

	xbrtime_int_reduce_sum(r_val, r_val, 5, 2, 0);

	temp_barrier();

	printf("Post-Reduction - PE:%d R_Val: %d %d %d %d %d %d %d %d %d %d\n", \
            my_pe, r_val[0], r_val[1], r_val[2], r_val[3], r_val[4], r_val[5], r_val[6], r_val[7], r_val[8], r_val[9]);

	xbrtime_close();

    return 0;
}
