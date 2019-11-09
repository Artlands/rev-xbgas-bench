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

    (*((long long *)(FLAG))) = 1;

    xbrtime_int_broadcast_tree(message, message, nelems, 1, 0);

    (*((long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_close();
}

void large_broadcast()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = 25600;
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

    xbrtime_close();
}

void large_reduce()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = 25600;
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

    xbrtime_close();
}

void large_reduce_all()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = 25600;
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

    xbrtime_close();
}

void large_scatter()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = 25600;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    if(my_pe == 0)
    {
        for(int i = 0; i < nelems; i++)
        {
            message[i] = my_pe;
        }
    }

    int pe_msg_sz[8] = {3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200};
    int pe_disp[8] = {0, 3200, 6400, 9600, 12800, 16000, 19200, 22400};

    xbrtime_barrier();

    (*((long long *)(FLAG))) = 1;

    xbrtime_int_scatter_tree(message, message, pe_msg_sz, pe_disp, nelems, 0);

    (*((long long *)(FLAG))) = 0;

    xbrtime_barrier();

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

    xbrtime_close();
}

void large_gather()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = 25600;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    int pe_msg_sz[8] = {3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200};
    int pe_disp[8] = {0, 3200, 6400, 9600, 12800, 16000, 19200, 22400};

    xbrtime_barrier();

    (*((long long *)(FLAG))) = 1;

    xbrtime_int_gather_tree(message, message, pe_msg_sz, pe_disp, nelems, 0);

    (*((long long *)(FLAG))) = 0;

    xbrtime_barrier();

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

    xbrtime_close();
}

void large_gather_all()
{
    xbrtime_init();
    int my_pe = xbrtime_mype();
    int numpes = xbrtime_num_pes();
    int nelems = 25600;
    int *message = (int*) xbrtime_malloc(sizeof(int) * nelems);

    for(int i = 0; i < nelems; i++)
    {
        message[i] = my_pe;
    }

    int pe_msg_sz[8] = {3200, 3200, 3200, 3200, 3200, 3200, 3200, 3200};
    int pe_disp[8] = {0, 3200, 6400, 9600, 12800, 16000, 19200, 22400};

    xbrtime_barrier();

    (*((long long *)(FLAG))) = 1;

    xbrtime_int_gather_all_ring(message, message, pe_msg_sz, pe_disp, nelems, 0);

    (*((long long *)(FLAG))) = 0;

    xbrtime_barrier();

    xbrtime_close();
}

void main()
{

}
