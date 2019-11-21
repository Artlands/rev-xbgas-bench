// Debug code for unrolled get/put


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "xbrtime.h"

#define TEST_LEN 517
#define PE_SRC 1
#define PE_DEST 1

int main(int argc, char** argv)
{
    xbrtime_init();
    int my_pe, num_pes, i;
    my_pe = xbrtime_mype();
    num_pes = xbrtime_num_pes();

    int32_t* int32_vals = (int32_t*) xbrtime_malloc(sizeof(int32_t) * TEST_LEN);
//    int64_t* int64_vals = (int64_t*) xbrtime_malloc(sizeof(int64_t) * TEST_LEN);

    for(i = 0; i < TEST_LEN; i++)
    {
        int32_vals[i] = my_pe;
   //     int64_vals[i] = my_pe;
    }

    printf("PE %d of %d _XBRTIME_MIN_UNR_THRESHOLD_: %d _XBRTIME_UNROLL_FACTOR_: %d\n\n", my_pe, num_pes, _XBRTIME_MIN_UNR_THRESHOLD_, _XBRTIME_UNROLL_FACTOR_);
    fflush(stdout);
    xbrtime_barrier();
    
    printf("PE %d of %d initialized! int32_vals addr (pe relative): %ld\nint64_vals addr: %ld\n\n", my_pe, num_pes, __xbrtime_ltor((uint64_t)(int32_vals),my_pe));// int64_vals);

    fflush(stdout);
    xbrtime_barrier();

    if(my_pe == 0)
    	printf("Performing get of %d 4-byte words. Source PE: %d My PE: %d\n\n", TEST_LEN, PE_SRC, my_pe);
    
    fflush(stdout);
    xbrtime_barrier();

    if(my_pe == 0)
    	xbrtime_int_get(int32_vals, int32_vals, TEST_LEN, 1, PE_SRC);

    xbrtime_barrier();
   /* 
    if(my_pe == 0)
    	printf("Performing get of %d 8-byte words. Source PE: %d My PE: %d\n\n", TEST_LEN, PE_SRC, my_pe);
    
    fflush(stdout);
    xbrtime_barrier();

    if(my_pe == 0)
    	xbrtime_int64_get(int64_vals, int64_vals, TEST_LEN, 1, PE_SRC);

    xbrtime_barrier();

    
    if(my_pe == 0)
    	printf("Performing put of %d 4-byte words. My PE: %d Dest PE: %d\n\n", TEST_LEN, my_pe , PE_DEST);
    
    fflush(stdout);
    xbrtime_barrier();

    xbrtime_uint32_put(int32_vals, int32_vals, TEST_LEN, 1, PE_DEST);

    if(my_pe == 0)
    	printf("Performing put of %d 8-byte words. My PE: %d Dest PE: %d\n\n", TEST_LEN, my_pe, PE_DEST);
    
    fflush(stdout);
    xbrtime_barrier();

    xbrtime_uint64_put(int64_vals, int64_vals, TEST_LEN, 1, PE_DEST);

    xbrtime_barrier();
    */

    printf("PE %d of %d completed tests!\n\n", my_pe, num_pes);
    fflush(stdout);
    xbrtime_barrier();

    xbrtime_close();

    return 0;
}
