#include "xbrtime.h"

#define FLAG 0xC000000000000000ull

void small_broadcast()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = 256;
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

void large_broadcast()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = 2600;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    if(my_pe == 0)
    {
        for(int i = 0; i < nelems; i++)
        {
            message[i] = my_pe;
        }
    }

    xbrtime_barrier();

    (*((long long *)(FLAG))) = 1;

    xbrtime_int_broadcast_van_de_geijn(message, message, nelems, 1, 0);

    (*((long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void small_reduce()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = 256;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    xbrtime_barrier();

    (*((long long *)(FLAG))) = 1;

    xbrtime_int_reduce_sum_tree(message, message, nelems, 1, 0);

    (*((long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void large_reduce()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = 2560;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    xbrtime_barrier();

    (*((long long *)(FLAG))) = 1;

    xbrtime_int_reduce_sum_rabenseifner(message, message, nelems, 1, 0);

    (*((long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void small_reduce_all()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = 256;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    if(my_pe == 0)
    {
        for(int i = 0; i < nelems; i++)
        {
            message[i] = my_pe;
        }
    }

    xbrtime_barrier();

    (*((long long *)(FLAG))) = 1;

    xbrtime_int_reduce_all_sum_recursive_doubling(message, message, nelems, 1);

    (*((long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void large_reduce_all()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = 2560;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    xbrtime_barrier();

    (*((long long *)(FLAG))) = 1;

    xbrtime_int_reduce_all_sum_rabenseifner(message, message, nelems, 1);

    (*((long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void small_scatter()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = 256;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    if(my_pe == 0)
    {
        for(int i = 0; i < nelems; i++)
        {
            message[i] = my_pe;
        }
    }

    int pe_msg_sz[8] = {32, 32, 32, 32, 32, 32, 32, 32};
    int pe_disp[8] = {0, 32, 64, 96, 128, 160, 192, 224};

    xbrtime_barrier();

    (*((long long *)(FLAG))) = 1;

    xbrtime_int_scatter_tree(message, message, pe_msg_sz, pe_disp, nelems, 0);

    (*((long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void large_scatter()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = 2560;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    if(my_pe == 0)
    {
        for(int i = 0; i < nelems; i++)
        {
            message[i] = my_pe;
        }
    }

    int pe_msg_sz[8] = {320, 320, 320, 320, 320, 320, 320, 320};
    int pe_disp[8] = {0, 320, 640, 960, 1280, 1600, 1920, 2240};

    xbrtime_barrier();

    (*((long long *)(FLAG))) = 1;

    xbrtime_int_scatter_tree(message, message, pe_msg_sz, pe_disp, nelems, 0);

    (*((long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void small_gather()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = 256;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    int pe_msg_sz[8] = {32, 32, 32, 32, 32, 32, 32, 32};
    int pe_disp[8] = {0, 32, 64, 96, 128, 160, 192, 224};

    xbrtime_barrier();

    (*((long long *)(FLAG))) = 1;

    xbrtime_int_gather_tree(message, message, pe_msg_sz, pe_disp, nelems, 0);

    (*((long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void large_gather()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = 2560;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    int pe_msg_sz[8] = {320, 320, 320, 320, 320, 320, 320, 320};
    int pe_disp[8] = {0, 320, 640, 960, 1280, 1600, 1920, 2240};

    xbrtime_barrier();

    (*((long long *)(FLAG))) = 1;

    xbrtime_int_gather_tree(message, message, pe_msg_sz, pe_disp, nelems, 0);

    (*((long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void small_gather_all()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = 256;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    int pe_msg_sz[8] = {32, 32, 32, 32, 32, 32, 32, 32};
    int pe_disp[8] = {0, 32, 64, 96, 128, 160, 192, 224};

    xbrtime_barrier();

    (*((long long *)(FLAG))) = 1;

    xbrtime_int_gather_all_bruck_concat(message, message, pe_msg_sz, pe_disp, nelems);

    (*((long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void large_gather_all()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = 2560;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    int pe_msg_sz[8] = {320, 320, 320, 320, 320, 320, 320, 320};
    int pe_disp[8] = {0, 320, 640, 960, 1280, 1600, 1920, 2240};

    xbrtime_barrier();

    (*((long long *)(FLAG))) = 1;

    xbrtime_int_gather_all_ring(message, message, pe_msg_sz, pe_disp, nelems);

    (*((long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_free(message);

    xbrtime_close();
}

void main()
{
	//small_broadcast();
    //large_broadcast();
    //small_reduce();
    //large_reduce();
    //small_reduce_all();
    //large_reduce_all();
    //small_scatter();
    //large_scatter();
    //small_gather();
    //larger_gather();
    //small_gather_all();
    //large_gather_all();
}
