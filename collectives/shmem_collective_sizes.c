#include "test.h"
#include <shmem.h>

long broadcast_psync[SHMEM_BCAST_SYNC_SIZE];
int reduce_pwrk[25600];
long reduce_psync[SHMEM_REDUCE_SYNC_SIZE];
long collect_psync[SHMEM_COLLECT_SYNC_SIZE];

void main()
{
    shmem_init();
    perf_init();
    int i, me, numpes;
    numpes = shmem_n_pes();
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
    test_start();

    //shmem_broadcast32(small_arr, small_arr, 256, 0, 0, 0, numpes, broadcast_psync);
    //shmem_broadcast32(long_arr, long_arr, 25600, 0, 0, 0, numpes, broadcast_psync);
    //shmem_int_sum_to_all(small_arr, small_arr, 256, 0, 0, numpes, reduce_pwrk, reduce_psync);
    //shmem_int_sum_to_all(long_arr, long_arr, 25600, 0, 0, numpes, reduce_pwrk, reduce_psync);
    //shmem_collect32(small_arr, small_arr, 64, 0, 0, numpes, collect_psync);
    //shmem_collect32(long_arr, long_arr, 6400, 0, 0, numpes, collect_psync);

    test_end();
    shmem_barrier_all();

    shmem_free(long_arr);
    shmem_free(small_arr);
    perf_end();
    shmem_finalize();
}
