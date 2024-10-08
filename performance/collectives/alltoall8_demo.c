/*
 * _ALLTOALL_DEMO_C_
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
    int i, my_pe, *my_array;
    my_pe = xbrtime_mype();
    my_array = (int*) xbrtime_malloc(8 * sizeof(int));

    for(i = 0; i < 8; i++)
    {
        my_array[i] = my_pe;
    }

    printf("Pre-AlltoAll - PE:%d my_array: %d %d %d %d %d %d %d %d\n", my_pe, my_array[0], my_array[1], my_array[2],
                                                                    my_array[3], my_array[4], my_array[5], my_array[6], my_array[7]);

    xbrtime_barrier();

    xbrtime_int_alltoall(my_array, my_array, 1, 1, 1);

    xbrtime_barrier();

    printf("Post-AlltoAll - PE:%d my_array: %d %d %d %d %d %d %d %d\n", my_pe, my_array[0], my_array[1], my_array[2],
                                                                    my_array[3], my_array[4], my_array[5], my_array[6], my_array[7]);

    xbrtime_close();

    return 0;
}
