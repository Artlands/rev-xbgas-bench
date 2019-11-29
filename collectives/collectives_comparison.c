#include <stdint.h>

//#define TEST_XBGAS
//#define TEST_SHMEM
//#define TEST_MPI

#define SMALL_NELEMS 256
#define LARGE_NELEMS 25600

#ifdef TEST_XBGAS

#include <xbrtime.h>

#define FLAG 0xC000000000000000ull

void xbgas_small_broadcast_tree_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = SMALL_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    if(my_pe == 0)
    {
        for(int i = 0; i < nelems; i++)
        {
            message[i] = my_pe;
        }
    }

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_broadcast_tree(message, message, nelems, 1, 0);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_large_broadcast_tree_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = LARGE_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    if(my_pe == 0)
    {
        for(int i = 0; i < nelems; i++)
        {
            message[i] = my_pe;
        }
    }

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_broadcast_tree(message, message, nelems, 1, 0);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_small_broadcast_vdg_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = SMALL_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    if(my_pe == 0)
    {
        for(int i = 0; i < nelems; i++)
        {
            message[i] = my_pe;
        }
    }

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_broadcast_van_de_geijn(message, message, nelems, 1, 0);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_large_broadcast_vdg_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = LARGE_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    if(my_pe == 0)
    {
        for(int i = 0; i < nelems; i++)
        {
            message[i] = my_pe;
        }
    }

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_broadcast_van_de_geijn(message, message, nelems, 1, 0);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_small_reduce_tree_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = SMALL_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_reduce_sum_tree(message, message, nelems, 1, 0);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_large_reduce_tree_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = LARGE_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_reduce_sum_tree(message, message, nelems, 1, 0);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_small_reduce_rabenseifner_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = SMALL_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_reduce_sum_rabenseifner(message, message, nelems, 1, 0);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_large_reduce_rabenseifner_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = LARGE_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_reduce_sum_rabenseifner(message, message, nelems, 1, 0);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_small_reduce_all_rd_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = SMALL_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_reduce_all_sum_recursive_doubling(message, message, nelems, 1);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_large_reduce_all_rd_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = LARGE_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_reduce_all_sum_recursive_doubling(message, message, nelems, 1);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_small_reduce_all_rabenseifner_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = SMALL_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_reduce_all_sum_rabenseifner(message, message, nelems, 1);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_large_reduce_all_rabenseifner_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = LARGE_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_reduce_all_sum_rabenseifner(message, message, nelems, 1);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_small_scatter_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = SMALL_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    if(my_pe == 0)
    {
        for(int i = 0; i < nelems; i++)
        {
            message[i] = my_pe;
        }
    }

    int pe_msg_sz[8] = {64, 64, 64, 64};
    int pe_disp[8] = {0, 64, 128, 192};

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_scatter_tree(message, message, pe_msg_sz, pe_disp, nelems, 0);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_large_scatter_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = LARGE_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    if(my_pe == 0)
    {
        for(int i = 0; i < nelems; i++)
        {
            message[i] = my_pe;
        }
    }

    int pe_msg_sz[8] = {6400, 6400, 6400, 6400};
    int pe_disp[8] = {0, 6400, 12800, 19200};

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_scatter_tree(message, message, pe_msg_sz, pe_disp, nelems, 0);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_small_gather_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = SMALL_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    int pe_msg_sz[8] = {64, 64, 64, 64};
    int pe_disp[8] = {0, 64, 128, 192};

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_gather_tree(message, message, pe_msg_sz, pe_disp, nelems, 0);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_large_gather_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = LARGE_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    int pe_msg_sz[8] = {6400, 6400, 6400, 6400};
    int pe_disp[8] = {0, 6400, 12800, 19200};

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_gather_tree(message, message, pe_msg_sz, pe_disp, nelems, 0);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_small_gather_all_bruck_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = SMALL_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    int pe_msg_sz[8] = {64, 64, 64, 64};
    int pe_disp[8] = {0, 64, 128, 192};

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_gather_all_bruck_concat(message, message, pe_msg_sz, pe_disp, nelems);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_large_gather_all_bruck_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = LARGE_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    int pe_msg_sz[8] = {6400, 6400, 6400, 6400};
    int pe_disp[8] = {0, 6400, 12800, 19200};

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_gather_all_bruck_concat(message, message, pe_msg_sz, pe_disp, nelems);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_small_gather_all_ring_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = SMALL_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    int pe_msg_sz[8] = {64, 64, 64, 64};
    int pe_disp[8] = {0, 64, 128, 192};

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_gather_all_ring(message, message, pe_msg_sz, pe_disp, nelems);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_large_gather_all_ring_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = LARGE_NELEMS;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    int pe_msg_sz[8] = {6400, 6400, 6400, 6400};
    int pe_disp[8] = {0, 6400, 12800, 19200};

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_gather_all_ring(message, message, pe_msg_sz, pe_disp, nelems);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_small_alltoall_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = SMALL_NELEMS/numpes;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems * numpes);

    for(int i = 0; i < nelems*numpes; i++)
    {
        message[i] = my_pe;
    }

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_all_to_all_shift_exchange(message, message, 1, 1, nelems);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void xbgas_large_alltoall_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = LARGE_NELEMS/numpes;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems * numpes);

    for(int i = 0; i < nelems*numpes; i++)
    {
        message[i] = my_pe;
    }

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    xbrtime_int_all_to_all_shift_exchange(message, message, 1, 1, nelems);

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void main()
{
    //xbgas_small_broadcast_tree_test();
    //xbgas_large_broadcast_tree_test();
    //xbgas_small_broadcast_vdg_test();
    //xbgas_large_broadcast_vdg_test();
    //xbgas_small_reduce_tree_test();
    //xbgas_large_reduce_tree_test();
    //xbgas_small_reduce_rabenseifner_test();
    //xbgas_large_reduce_rabenseifner_test();
    //xbgas_small_reduce_all_rd_test();
    //xbgas_large_reduce_all_rd_test();
    //xbgas_small_reduce_all_rabenseifner_test();
    //xbgas_large_reduce_all_rabenseifner_test();
    //xbgas_small_scatter_test();
    //xbgas_large_scatter_test();
    //xbgas_small_gather_test();
    //xbgas_large_gather_test();
    //xbgas_small_gather_all_bruck_test();
    //xbgas_large_gather_all_bruck_test();
    //xbgas_small_gather_all_ring_test();
    //xbgas_large_gather_all_ring_test();
    //xbgas_small_alltoall_test();
    //xbgas_large_alltoall_test();
}

#undef TEST_XBGAS
#endif

#ifdef TEST_SHMEM

#include <shmem.h>
#include "test.h"

long broadcast_psync[SHMEM_BCAST_SYNC_SIZE];
int reduce_pwrk[25600];
long reduce_psync[SHMEM_REDUCE_SYNC_SIZE];
long collect_psync[SHMEM_COLLECT_SYNC_SIZE];
long alltoalls_psync[SHMEM_ALLTOALLS_SYNC_SIZE];

void main()
{
    shmem_init();
    perf_init();
    int i, my_pe, numpes;
    numpes = shmem_n_pes();
    my_pe = shmem_my_pe();
    int *large_arr = (int*) shmem_malloc(sizeof(int) * LARGE_NELEMS);
    int *small_arr = (int*) shmem_malloc(sizeof(int) * SMALL_NELEMS);

    for(i = 0; i < SHMEM_BCAST_SYNC_SIZE; i++)
    {
        broadcast_psync[i] = SHMEM_SYNC_VALUE;
    }

    for(i = 0; i < SHMEM_REDUCE_SYNC_SIZE; i++)
    {
        reduce_psync[i] = SHMEM_SYNC_VALUE;
    }

    for(i = 0; i < SHMEM_COLLECT_SYNC_SIZE; i++)
    {
        collect_psync[i] = SHMEM_SYNC_VALUE;
    }

    for(i = 0; i < SMALL_NELEMS; i++)
    {
        small_arr[i] = my_pe;
    }

    for(i = 0; i < LARGE_NELEMS; i++)
    {
        large_arr[i] = my_pe;
    }

    for(i = 0; i < SHMEM_ALLTOALLS_SYNC_SIZE; i++)
    {
        alltoalls_psync[i] = SHMEM_SYNC_VALUE;
    }

    shmem_barrier_all();
    test_start();

    //shmem_broadcast32(small_arr, small_arr, SMALL_NELEMS, 0, 0, 0, numpes, broadcast_psync);
    //shmem_broadcast32(long_arr, long_arr, LARGE_NELEMS, 0, 0, 0, numpes, broadcast_psync);
    //shmem_int_sum_to_all(small_arr, small_arr, SMALL_NELEMS, 0, 0, numpes, reduce_pwrk, reduce_psync);
    //shmem_int_sum_to_all(long_arr, long_arr, LARGE_NELEMS, 0, 0, numpes, reduce_pwrk, reduce_psync);
    //shmem_collect32(small_arr, small_arr, SMALL_NELEMS/numpes, 0, 0, numpes, collect_psync);
    //shmem_collect32(long_arr, long_arr, LARGE_NELEMS/numpes, 0, 0, numpes, collect_psync);
    //shmem_alltoalls32(dest, source, 1, 1, size_t SMALL_NELEMS/numpes, 0, 0, numpes, alltoalls_psync);
    //shmem_alltoalls32(dest, source, 1, 1, size_t LARGE_NELEMS/numpes, 0, 0, numpes, alltoalls_psync)

    test_end();
    shmem_barrier_all();

    shmem_free(long_arr);
    shmem_free(small_arr);
    perf_end();
    shmem_finalize();
}

#undef TEST_SHMEM
#endif

#ifdef TEST_MPI

#include <mpi.h>
#include "test.h"

void main()
{
    MPI_Init(NULL, NULL);
    perf_init();
    int i, my_pe, numpes;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe);
    MPI_Comm_size(MPI_COMM_WORLD, &numpes);
    int small_arr[SMALL_NELEMS], large_arr[LARGE_NELEMS];
    int small_counts = {64, 64, 64, 64};
    int small_disp = {0, 64, 128, 192};
    int large_counts = {6400, 6400, 6400, 6400};
    int large_disp = {0, 6400, 12800, 19200};

    for(i = 0; i < SMALL_NELEMS; i++)
    {
        small_arr[i] = my_pe;
    }

    for(i = 0; i < LARGE_NELEMS; i++)
    {
        large_arr[i] = my_pe;
    }

    MPI_Barrier(MPI_COMM_WORLD);

    test_start();
    //MPI_Bcast(&small_arr, SMALL_NELEMS, MPI_INT, 0, MPI_COMM_WORLD);
    //MPI_Bcast(&large_arr, LARGE_NELEMS, MPI_INT, 0, MPI_COMM_WORLD);
    //MPI_Reduce(&small_arr, &small_arr, SMALL_NELEMS, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    //MPI_Reduce(&large_arr, &large_arr, LARGE_NELEMS, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    //MPI_Allreduce(&small_arr, &small_arr, SMALL_NELEMS, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    //MPI_Allreduce(&large_arr, &large_arr, LARGE_NELEMS, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    //MPI_Scatterv(&small_arr, &small_counts, &small_disp, MPI_INT, &small_arr, SMALL_NELEMS/numpes, MPI_INT, 0, MPI_COMM_WORLD);
    //MPI_Scatterv(&large_arr, &large_counts, &large_disp, MPI_INT, &large_arr, LARGE_NELEMS/numpes, MPI_INT, 0, MPI_COMM_WORLD);
    //MPI_Gatherv(&small_arr, SMALL_NELEMS/numpes, MPI_INT, &small_arr, &small_counts, &small_disp, MPI_INT, 0, MPI_COMM_WORLD);
    //MPI_Gatherv(&large_arr, LARGE_NELEMS/numpes, MPI_INT, &large_arr, &large_counts, &large_disp, MPI_INT, 0, MPI_COMM_WORLD);
    //MPI_Allgatherv(&small_arr, SMALL_NELEMS/numpes, MPI_INT, &small_arr, &small_counts, &small_disp, MPI_INT, MPI_COMM_WORLD);
    //MPI_Allgatherv(&large_arr, LARGE_NELEMS/numpes, MPI_INT, &large_arr, &large_counts, &large_disp, MPI_INT, MPI_COMM_WORLD);
    //MPI_Alltoall(&small_arr, SMALL_NELEMS/numpes, MPI_INT, &small_arr, SMALL_NELEMS/numpes, MPI_INT, MPI_COMM_WORLD);
    //MPI_Alltoall(&large_arr, LARGE_NELEMS/numpes, MPI_INT, &large_arr, LARGE_NELEMS/numpes, MPI_INT, MPI_COMM_WORLD);
    test_end();

    MPI_Barrier(MPI_COMM_WORLD);
    perf_end();
    MPI_Finalize();
}

#undef TEST_MPI
#endif
