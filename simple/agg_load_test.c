#include <stdio.h>
#include <stdint.h>
#include "xbrtime.h"

//#define ASM_INLINE_TEST
//#define ASM_FUNC_TEST
//#define RUNTIME_TEST

#define SMALL_NELEMS 256
#define MEDIUM_NELEMS 2560
#define LARGE_NELEMS 25600

uint32_t xbrtime_decode_pe(int pe);
uint64_t __xbrtime_ltor(uint64_t remote,int pe);
void __xbrtime_get_s4_agg(uint64_t base_src, uint64_t base_dest, uint32_t pe, uint32_t nelems, uint32_t stride);

int main(int argc, char **argv )
{
    xbrtime_init();
    int i, j;
    int my_pe = xbrtime_mype();
    int num_pes = xbrtime_num_pes();
    int *small_array = (int*) xbrtime_malloc(sizeof(int) * SMALL_NELEMS);
    int *medium_array = (int*) xbrtime_malloc(sizeof(int) * MEDIUM_NELEMS);
    int *large_array = (int*) xbrtime_malloc(sizeof(int) * LARGE_NELEMS);
    uint64_t reg_x10 = 123lu;
    uint64_t reg_x11 = 456lu;
    uint64_t reg_x12 = 789lu;
    uint64_t reg_x13 = 666lu;
    uint64_t reg_x30 = 777lu;
    uint64_t reg_x31 = 888lu;
    uint64_t reg_e10 = 999lu;

    for(i = 0; i < SMALL_NELEMS; i++)
        small_array[i] = my_pe;

    for(i = 0; i < MEDIUM_NELEMS; i++)
        medium_array[i] = my_pe;

    for(i = 0; i < LARGE_NELEMS; i++)
        large_array[i] = my_pe;

    printf("PE %d allocations complete.\nsmall_array addr = %lx\nmedium_array addr = %lx\nlarge_array addr = %lx\n\n", \
           my_pe, small_array, medium_array, large_array);
    fflush(stdout);
    xbrtime_barrier();

    /* Test aggregated store of SMALL_NELEMS */
    printf("PE %d beginning aggregated store of %d elements trial.\nTotal data size = %d bytes.\n\n", my_pe, SMALL_NELEMS, SMALL_NELEMS*sizeof(int));
    fflush(stdout);
    xbrtime_barrier();

    if(my_pe == 0)
    {
    #ifdef ASM_INLINE_TEST
        reg_x10 = (uint64_t) __xbrtime_ltor((uint64_t)(small_array), 1);
        reg_x11 = (uint64_t) small_array;
        reg_x12 = (uint64_t) xbrtime_decode_pe(1);
        reg_x13 = (uint64_t) SMALL_NELEMS;

        printf("PE %d calling 'eaddie e10 = %d, x12 = %d, 0' ->\n'eag x31 = %d, x13 = %d, x11 = %lx' ->\n'elw x30 = %d, 0(x10 = %lx)'\n\n", \
                my_pe, reg_e10, reg_x12, reg_x31, reg_x13, reg_x11, reg_x30, reg_x10);
        fflush(stdout);

        /* EAG/ESW */
        asm volatile
        (
	        " eaddie e10, %[h], 0\n\t"
            " eag %[x], %[y], %[z]\n\t"
            " elw %[a], 0(%[b])\n\t"
            : [e10] "=r" (reg_e10), [x] "=r" (reg_x31)
            : [h] "r" (reg_x12), [y] "r" (reg_x13), [z] "r" (reg_x11), [a] "r" (reg_x30), [b] "r" (reg_x10)
        );

        printf("PE %d completed 'eaddie e10 = %d, x12 = %d, 0' ->\n'eag x31 = %d, x13 = %d, x11 = %lx' ->\n'elw x30 = %d, 0(x10 = %lx)'\n\n", \
                my_pe, reg_e10, reg_x12, reg_x31, reg_x13, reg_x11, reg_x30, reg_x10);
        fflush(stdout);
    #endif

    #ifdef ASM_FUNC_TEST
        __xbrtime_get_s4_agg(__xbrtime_ltor((uint64_t) (small_array),1),
                             (uint64_t) (small_array),
                             xbrtime_decode_pe(1),
                             (uint64_t) SMALL_NELEMS,
                             1);
    #endif

    #ifdef RUNTIME_TEST
        xbrtime_int_get(small_array, small_array, SMALL_NELEMS, 1, 1);
    #endif
    }

    xbrtime_barrier();
    printf("PE %d completed aggregated store of %d elements trial.\n\n", my_pe, SMALL_NELEMS);
    fflush(stdout);
    xbrtime_barrier();

    /* Test aggregated store of MEDIUM_NELEMS */
    printf("PE %d beginning aggregated store of %d elements trial.\nTotal data size = %d bytes.\n\n", my_pe, MEDIUM_NELEMS, MEDIUM_NELEMS*sizeof(int));
    fflush(stdout);
    xbrtime_barrier();

    if(my_pe == 0)
    {
    #ifdef ASM_INLINE_TEST
        reg_x10 = (uint64_t) __xbrtime_ltor((uint64_t)(medium_array), 1);
        reg_x11 = (uint64_t) medium_array;
        reg_x12 = (uint64_t) xbrtime_decode_pe(1);
        reg_x13 = (uint64_t) MEDIUM_NELEMS;

        printf("PE %d calling 'eaddie e10 = %d, x12 = %d, 0' ->\n'eag x31 = %d, x13 = %d, x11 = %lx' ->\n'elw x30 = %d, 0(x10 = %lx)'\n\n", \
                my_pe, reg_e10, reg_x12, reg_x31, reg_x13, reg_x11, reg_x30, reg_x10);
        fflush(stdout);

        /* EAG/ESW */
        asm volatile
        (
	        " eaddie e10, %[h], 0\n\t"
            " eag %[x], %[y], %[z]\n\t"
            " elw %[a], 0(%[b])\n\t"
            : [e10] "=r" (reg_e10), [x] "=r" (reg_x31)
            : [h] "r" (reg_x12), [y] "r" (reg_x13), [z] "r" (reg_x11), [a] "r" (reg_x30), [b] "r" (reg_x10)
        );

        printf("PE %d completed 'eaddie e10 = %d, x12 = %d, 0' ->\n'eag x31 = %d, x13 = %d, x11 = %lx' ->\n'elw x30 = %d, 0(x10 = %lx)'\n\n", \
                my_pe, reg_e10, reg_x12, reg_x31, reg_x13, reg_x11, reg_x30, reg_x10);
        fflush(stdout);
    #endif

    #ifdef ASM_FUNC_TEST
        __xbrtime_get_s4_agg(__xbrtime_ltor((uint64_t) (medium_array),1),
                             (uint64_t) (medium_array),
                             xbrtime_decode_pe(1),
                             (uint64_t) MEDIUM_NELEMS,
                             1);
    #endif

    #ifdef RUNTIME_TEST
        xbrtime_int_get(medium_array, medium_array, MEDIUM_NELEMS, 1, 1);
    #endif
    }

    xbrtime_barrier();
    printf("PE %d completed aggregated store of %d elements trial.\n\n", my_pe, MEDIUM_NELEMS);
    fflush(stdout);
    xbrtime_barrier();

    /* Test aggregated store of LARGE_NELEMS */
    printf("PE %d beginning aggregated store of %d elements trial.\nTotal data size = %d bytes.\n\n", my_pe, LARGE_NELEMS, LARGE_NELEMS*sizeof(int));
    fflush(stdout);
    xbrtime_barrier();

    if(my_pe == 0)
    {
    #ifdef ASM_INLINE_TEST
        reg_x10 = (uint64_t) __xbrtime_ltor((uint64_t)(large_array), 1);
        reg_x11 = (uint64_t) large_array;
        reg_x12 = (uint64_t) xbrtime_decode_pe(1);
        reg_x13 = (uint64_t) LARGE_NELEMS;

        printf("PE %d calling 'eaddie e10 = %d, x12 = %d, 0' ->\n'eag x31 = %d, x13 = %d, x11 = %lx' ->\n'elw x30 = %d, 0(x10 = %lx)'\n\n", \
                my_pe, reg_e10, reg_x12, reg_x31, reg_x13, reg_x11, reg_x30, reg_x10);
        fflush(stdout);

        /* EAG/ESW */
        asm volatile
        (
	        " eaddie e10, %[h], 0\n\t"
            " eag %[x], %[y], %[z]\n\t"
            " elw %[a], 0(%[b])\n\t"
            : [e10] "=r" (reg_e10), [x] "=r" (reg_x31)
            : [h] "r" (reg_x12), [y] "r" (reg_x13), [z] "r" (reg_x11), [a] "r" (reg_x30), [b] "r" (reg_x10)
        );

        printf("PE %d completed 'eaddie e10 = %d, x12 = %d, 0' ->\n'eag x31 = %d, x13 = %d, x11 = %lx' ->\n'elw x30 = %d, 0(x10 = %lx)'\n\n", \
                my_pe, reg_e10, reg_x12, reg_x31, reg_x13, reg_x11, reg_x30, reg_x10);
        fflush(stdout);
    #endif

    #ifdef ASM_FUNC_TEST
        __xbrtime_get_s4_agg(__xbrtime_ltor((uint64_t) (large_array),1),
                             (uint64_t) (large_array),
                             xbrtime_decode_pe(1),
                             (uint64_t) LARGE_NELEMS,
                             1);
    #endif

    #ifdef RUNTIME_TEST
        xbrtime_int_get(large_array, large_array, LARGE_NELEMS, 1, 1);
    #endif
    }

    xbrtime_barrier();
    printf("PE %d completed aggregated store of %d elements trial.\n\n", my_pe, LARGE_NELEMS);
    fflush(stdout);
    xbrtime_barrier();

    printf("PE %d completed all trials.\n\n", my_pe);
    fflush(stdout);
    xbrtime_barrier();

    for(i = 0; i < num_pes; i++)
    {
        if(my_pe == i)
        {
            printf("PE %d Verification Values\n", my_pe);
            printf("small_array[0] = %d small_array[1] = %d small_array[2] = %d\n", \
                   small_array[0], small_array[1], small_array[2]);
            printf("small_array[SMALL_NELEMS-1] = %d small_array[SMALL_NELEMS-2] = %d small_array[SMALL_NELEMS-3] = %d\n", \
                   small_array[SMALL_NELEMS-1], small_array[SMALL_NELEMS-2], small_array[SMALL_NELEMS-3]);
            printf("medium_array[0] = %d medium_array[1] = %d medium_array[2] = %d\n", \
                   medium_array[0], medium_array[1], medium_array[2]);
            printf("medium_array[MEDIUM_NELEMS-1] = %d medium_array[MEDIUM_NELEMS-2] = %d medium_array[MEDIUM_NELEMS-3] = %d\n", \
                   medium_array[MEDIUM_NELEMS-1], medium_array[MEDIUM_NELEMS-2], medium_array[MEDIUM_NELEMS-3]);
            printf("large_array[0] = %d large_array[1] = %d large_array[2] = %d\n", \
                   large_array[0], large_array[1], large_array[2]);
            printf("large_array[LARGE_NELEMS-1] = %d large_array[LARGE_NELEMS-2] = %d large_array[LARGE_NELEMS-3] = %d\n\n", \
                   large_array[LARGE_NELEMS-1], large_array[LARGE_NELEMS-2], large_array[LARGE_NELEMS-3]);
        }
        fflush(stdout);
        xbrtime_barrier();
    }
    xbrtime_barrier();

    xbrtime_free(small_array);
    xbrtime_free(medium_array);
    xbrtime_free(large_array);

    xbrtime_close();
    return 0;
}
