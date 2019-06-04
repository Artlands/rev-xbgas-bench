/*
 * _GATHER_DEMO_C_
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
    int i, my_pe, nelems, *dest_array;
    my_pe = xbrtime_mype();
    nelems = 15;
    dest_array = (int*) xbrtime_malloc(nelems*sizeof(int));
    int src_array[5] = {my_pe, my_pe, my_pe, my_pe, my_pe};

    for(i = 0; i < nelems; i++)
    {
           dest_array[i] = 99;
    }

    int pe_msg_sz[6] = {3, 2, 4, 1, 2, 3};
    int pe_disp[6] = {0, 3, 5, 9, 10, 12};

    printf("Pre-Gather - PE %d src_array = %d %d %d %d %d\n", my_pe, src_array[0], src_array[1], src_array[2], src_array[3], src_array[4]);

    temp_barrier();

    xbrtime_int_gather(dest_array, src_array, pe_msg_sz, pe_disp, nelems, 3);

    temp_barrier();

    printf("Pre-Gather - PE %d dest_array = %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", my_pe, dest_array[0], dest_array[1], dest_array[2], dest_array[3],
                                                                                dest_array[4], dest_array[5], dest_array[6], dest_array[7],
                                                                                dest_array[8], dest_array[9], dest_array[10], dest_array[11],
                                                                                dest_array[12], dest_array[13], dest_array[14]);

    xbrtime_close();

    return 0;
}
