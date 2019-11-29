#include <stdint.h>

//#define TEST_XBGAS
//#define TEST_SHMEM
//#define TEST_MPI

#ifdef TEST_XBGAS

#include <xbrtime.h>

#define FLAG 0xC000000000000000ull

void xbrtime_atomic_add_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int64_t ret;
    int64_t* value = (int64_t*) xbrtime_malloc(sizeof(int64_t));
    *value = my_pe;

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    if(my_pe == 0)
    {
        ret = xbrtime_int64_atomic_add(value, 1000000000, 1);
    }

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();
    xbrtime_free(value);
    xbrtime_close();
}

void xbrtime_atomic_inc_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int64_t ret;
    int64_t* value = (int64_t*) xbrtime_malloc(sizeof(int64_t));
    *value = my_pe;

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    if(my_pe == 0)
    {
        ret = xbrtime_int64_atomic_add(value, 1, 1);
    }

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();
    xbrtime_free(value);
    xbrtime_close();
}

void xbrtime_atomic_compare_swap_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int64_t ret;
    int64_t* value = (int64_t*) xbrtime_malloc(sizeof(int64_t));
    *value = my_pe;

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    if(my_pe == 0)
    {
        ret = xbrtime_int64_atomic_compare_swap(value, 1, 1);
    }

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();
    xbrtime_free(value);
    xbrtime_close();
}

void xbrtime_atomic_band_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int64_t ret;
    int64_t* value = (int64_t*) xbrtime_malloc(sizeof(int64_t));
    *value = my_pe;

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    if(my_pe == 0)
    {
        ret = xbrtime_int64_atomic_band(value, *value, 1);
    }

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();
    xbrtime_free(value);
    xbrtime_close();
}

void xbrtime_atomic_bor_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int64_t ret;
    int64_t* value = (int64_t*) xbrtime_malloc(sizeof(int64_t));
    *value = my_pe;

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    if(my_pe == 0)
    {
        ret = xbrtime_int64_atomic_bor(value, *value, 1);
    }

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();
    xbrtime_free(value);
    xbrtime_close();
}

void xbrtime_atomic_bxor_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int64_t ret;
    int64_t* value = (int64_t*) xbrtime_malloc(sizeof(int64_t));
    *value = my_pe;

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    if(my_pe == 0)
    {
        ret = xbrtime_int64_atomic_bxor(value, *value, 1);
    }

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();
    xbrtime_free(value);
    xbrtime_close();
}

void xbrtime_atomic_min_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int64_t ret;
    uint64_t* value = (uint64_t*) xbrtime_malloc(sizeof(uint64_t));
    *value = my_pe;

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    if(my_pe == 0)
    {
        ret = xbrtime_uint64_atomic_min(value, *value, 1);
    }

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();
    xbrtime_free(value);
    xbrtime_close();
}

void xbrtime_atomic_max_test()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int64_t ret;
    uint64_t* value = (uint64_t*) xbrtime_malloc(sizeof(uint64_t));
    *value = my_pe;

    xbrtime_barrier();

    (*((unsigned long long *)(FLAG))) = 1;

    if(my_pe == 0)
    {
        ret = xbrtime_uint64_atomic_max(value, *value, 1);
    }

    (*((unsigned long long *)(FLAG))) = 0;

    xbrtime_barrier();
    xbrtime_free(value);
    xbrtime_close();
}

#undef TEST_XBGAS
#endif

#ifdef TEST_SHMEM

#include <shmem.h>
#include "test.h"

// SHMEM tests use long long type because OSHMEM (OpenMPI OpenSHMEM) doesn't like the int64 typename in atomic calls

void shmem_atomic_add_test()
{
    shmem_init();
    perf_init();
    int my_pe = shmem_my_pe();
    int numpes = shmem_n_pes();
    long long ret;
    long long* value = (long long*) shmem_malloc(sizeof(long long));
    *value = my_pe;

    shmem_barrier_all();

    if(my_pe == 0)
    {
        test_start();
        ret = shmem_longlong_atomic_fetch_add(value, 1000000000, 1);
        test_end();
    }

    shmem_barrier_all();
    shmem_free(value);
    perf_end();
    shmem_finalize();
}

void shmem_atomic_inc_test()
{
    shmem_init();
    perf_init();
    int my_pe = shmem_my_pe();
    int numpes = shmem_n_pes();
    long long ret;
    long long* value = (long long*) shmem_malloc(sizeof(long long));
    *value = my_pe;

    shmem_barrier_all();

    if(my_pe == 0)
    {
        test_start();
        ret = shmem_longlong_atomic_fetch_inc(value, 1);
        test_end();
    }

    shmem_barrier_all();
    shmem_free(value);
    perf_end();
    shmem_finalize();
}

void shmem_atomic_compare_swap_test()
{
    shmem_init();
    perf_init();
    int my_pe = shmem_my_pe();
    int numpes = shmem_n_pes();
    long long ret;
    long long* value = (long long*) shmem_malloc(sizeof(long long));
    *value = my_pe;

    shmem_barrier_all();

    if(my_pe == 0)
    {
        test_start();
        ret = shmem_longlong_atomic_compare_swap(value, 1, *value, 1);
        test_end();
    }

    shmem_barrier_all();
    shmem_free(value);
    perf_end();
    shmem_finalize();
}

void shmem_atomic_band_test()
{
    shmem_init();
    perf_init();
    int my_pe = shmem_my_pe();
    int numpes = shmem_n_pes();
    long long ret;
    long long* value = (long long*) shmem_malloc(sizeof(long long));
    *value = my_pe;

    shmem_barrier_all();

    if(my_pe == 0)
    {
        test_start();
        ret = shmem_longlong_atomic_fetch_and(value, *value, 1);
        test_end();
    }

    shmem_barrier_all();
    shmem_free(value);
    perf_end();
    shmem_finalize();
}

void shmem_atomic_bor_test()
{
    shmem_init();
    perf_init();
    int my_pe = shmem_my_pe();
    int numpes = shmem_n_pes();
    long long ret;
    long long* value = (long long*) shmem_malloc(sizeof(long long));
    *value = my_pe;

    shmem_barrier_all();

    if(my_pe == 0)
    {
        test_start();
        ret = shmem_longlong_atomic_fetch_or(value, *value, 1);
        test_end();
    }

    shmem_barrier_all();
    shmem_free(value);
    perf_end();
    shmem_finalize();
}

void shmem_atomic_bxor_test()
{
    shmem_init();
    perf_init();
    int my_pe = shmem_my_pe();
    int numpes = shmem_n_pes();
    long long ret;
    long long* value = (long long*) shmem_malloc(sizeof(long long));
    *value = my_pe;

    shmem_barrier_all();

    if(my_pe == 0)
    {
        test_start();
        ret = shmem_longlong_atomic_fetch_xor(value, *value, 1);
        test_end();
    }

    shmem_barrier_all();
    shmem_free(value);
    perf_end();
    shmem_finalize();
}

#undef TEST_SHMEM
#endif

#ifdef TEST_MPI

#include <mpi.h>
#include "test.h"

void mpi_atomic_add_test()
{
    MPI_Init(NULL, NULL);
    perf_init();
    int my_pe, numpes;
    MPI_Win window;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe);
    MPI_Comm_size(MPI_COMM_WORLD, &numpes);
    int64_t result, value;

    if(my_pe == 1)
    {
        value = 1;
    }
    else
    {
        value = 1000000000;
    }

    MPI_Win_create(&value, sizeof(int64_t), sizeof(int64_t), MPI_INFO_NULL, MPI_COMM_WORLD, &window);

    MPI_Barrier(MPI_COMM_WORLD);

    if(my_pe == 0)
    {
        MPI_Win_lock_all(0, window);
        test_start();
        MPI_Fetch_and_op(&value, &result, MPI_INT64_T, 1, 0, MPI_SUM, window);
        test_end();
        MPI_Win_flush_all(window);
        MPI_Win_unlock_all(window);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Win_free(&window);
    perf_end();
    MPI_Finalize();
}

void mpi_atomic_inc_test()
{
    MPI_Init(NULL, NULL);
    perf_init();
    int my_pe, numpes;
    MPI_Win window;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe);
    MPI_Comm_size(MPI_COMM_WORLD, &numpes);
    int64_t result, value;
    value = 1;

    MPI_Win_create(&value, sizeof(int64_t), sizeof(int64_t), MPI_INFO_NULL, MPI_COMM_WORLD, &window);

    MPI_Barrier(MPI_COMM_WORLD);

    if(my_pe == 0)
    {
        MPI_Win_lock_all(0, window);
        test_start();
        MPI_Fetch_and_op(&value, &result, MPI_INT64_T, 1, 0, MPI_SUM, window);
        test_end();
        MPI_Win_flush_all(window);
        MPI_Win_unlock_all(window);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Win_free(&window);
    perf_end();
    MPI_Finalize();
}

void mpi_atomic_compare_swap_test()
{
    MPI_Init(NULL, NULL);
    perf_init();
    int my_pe, numpes;
    MPI_Win window;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe);
    MPI_Comm_size(MPI_COMM_WORLD, &numpes);
    int64_t result, value, compare;
    value = my_pe;
    compare = 1;

    MPI_Win_create(&value, sizeof(int64_t), sizeof(int64_t), MPI_INFO_NULL, MPI_COMM_WORLD, &window);

    MPI_Barrier(MPI_COMM_WORLD);

    if(my_pe == 0)
    {
        MPI_Win_lock_all(0, window);
        test_start();
        MPI_Compare_and_swap(&value, &compare, &result, MPI_INT64_T, 1, 0, window);
        test_end();
        MPI_Win_flush_all(window);
        MPI_Win_unlock_all(window);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Win_free(&window);
    perf_end();
    MPI_Finalize();
}

void mpi_atomic_band_test()
{
    MPI_Init(NULL, NULL);
    perf_init();
    int my_pe, numpes;
    MPI_Win window;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe);
    MPI_Comm_size(MPI_COMM_WORLD, &numpes);
    int64_t result, value;
    value = my_pe;

    MPI_Win_create(&value, sizeof(int64_t), sizeof(int64_t), MPI_INFO_NULL, MPI_COMM_WORLD, &window);

    MPI_Barrier(MPI_COMM_WORLD);

    if(my_pe == 0)
    {
        MPI_Win_lock_all(0, window);
        test_start();
        MPI_Fetch_and_op(&value, &result, MPI_INT64_T, 1, 0, MPI_BAND, window);
        test_end();
        MPI_Win_flush_all(window);
        MPI_Win_unlock_all(window);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Win_free(&window);
    perf_end();
    MPI_Finalize();
}

void mpi_atomic_bor_test()
{
    MPI_Init(NULL, NULL);
    perf_init();
    int my_pe, numpes;
    MPI_Win window;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe);
    MPI_Comm_size(MPI_COMM_WORLD, &numpes);
    int64_t result, value;
    value = my_pe;

    MPI_Win_create(&value, sizeof(int64_t), sizeof(int64_t), MPI_INFO_NULL, MPI_COMM_WORLD, &window);

    MPI_Barrier(MPI_COMM_WORLD);

    if(my_pe == 0)
    {
        MPI_Win_lock_all(0, window);
        test_start();
        MPI_Fetch_and_op(&value, &result, MPI_INT64_T, 1, 0, MPI_BOR, window);
        test_end();
        MPI_Win_flush_all(window);
        MPI_Win_unlock_all(window);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Win_free(&window);
    perf_end();
    MPI_Finalize();
}

void mpi_atomic_bxor_test()
{
    MPI_Init(NULL, NULL);
    perf_init();
    int my_pe, numpes;
    MPI_Win window;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe);
    MPI_Comm_size(MPI_COMM_WORLD, &numpes);
    int64_t result, value;
    value = my_pe;

    MPI_Win_create(&value, sizeof(int64_t), sizeof(int64_t), MPI_INFO_NULL, MPI_COMM_WORLD, &window);

    MPI_Barrier(MPI_COMM_WORLD);

    if(my_pe == 0)
    {
        MPI_Win_lock_all(0, window);
        test_start();
        MPI_Fetch_and_op(&value, &result, MPI_INT64_T, 1, 0, MPI_BXOR, window);
        test_end();
        MPI_Win_flush_all(window);
        MPI_Win_unlock_all(window);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Win_free(&window);
    perf_end();
    MPI_Finalize();
}

void mpi_atomic_min_test()
{
    MPI_Init(NULL, NULL);
    perf_init();
    int my_pe, numpes;
    MPI_Win window;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe);
    MPI_Comm_size(MPI_COMM_WORLD, &numpes);
    int64_t result, value;
    value = my_pe;

    MPI_Win_create(&value, sizeof(int64_t), sizeof(int64_t), MPI_INFO_NULL, MPI_COMM_WORLD, &window);

    MPI_Barrier(MPI_COMM_WORLD);

    if(my_pe == 0)
    {
        MPI_Win_lock_all(0, window);
        test_start();
        MPI_Fetch_and_op(&value, &result, MPI_INT64_T, 1, 0, MPI_MIN, window);
        test_end();
        MPI_Win_flush_all(window);
        MPI_Win_unlock_all(window);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Win_free(&window);
    perf_end();
    MPI_Finalize();
}

void mpi_atomic_max_test()
{
    MPI_Init(NULL, NULL);
    perf_init();
    int my_pe, numpes;
    MPI_Win window;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe);
    MPI_Comm_size(MPI_COMM_WORLD, &numpes);
    int64_t result, value;
    value = my_pe;

    MPI_Win_create(&value, sizeof(int64_t), sizeof(int64_t), MPI_INFO_NULL, MPI_COMM_WORLD, &window);

    MPI_Barrier(MPI_COMM_WORLD);

    if(my_pe == 0)
    {
        MPI_Win_lock_all(0, window);
        test_start();
        MPI_Fetch_and_op(&value, &result, MPI_INT64_T, 1, 0, MPI_MAX, window);
        test_end();
        MPI_Win_flush_all(window);
        MPI_Win_unlock_all(window);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Win_free(&window);
    perf_end();
    MPI_Finalize();
}

#undef TEST_MPI
#endif

void main()
{
    //xbrtime_atomic_add_test();
    //xbrtime_atomic_inc_test();
    //xbrtime_atomic_compare_swap_test();
    //xbrtime_atomic_band_test();
    //xbrtime_atomic_bor_test();
    //xbrtime_atomic_bxor_test();
    //xbrtime_atomic_min_test();
    //xbrtime_atomic_max_test();
    //shmem_atomic_add_test();
    //shmem_atomic_inc_test();
    //shmem_atomic_compare_swap_test();
    //shmem_atomic_band_test();
    //shmem_atomic_bor_test();
    //shmem_atomic_bxor_test();
    //mpi_atomic_add_test();
    //mpi_atomic_inc_test();
    //mpi_atomic_compare_swap_test();
    //mpi_atomic_band_test();
    //mpi_atomic_bor_test();
    //mpi_atomic_bxor_test();
    //mpi_atomic_min_test();
    //mpi_atomic_max_test();
}
