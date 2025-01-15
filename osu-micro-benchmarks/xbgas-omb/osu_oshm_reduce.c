#define BENCHMARK "OSU OpenSHMEM Reduce Latency Test"

/*
 * For detailed copyright and licensing information, please refer to the
 * copyright file COPYRIGHT in the top level directory.
 */

#include <xbrtime.h>
#include "xbgas_osu_util.h"

int main(int argc, char *argv[])
{
    int i, numprocs, rank, size = 0, iterations;
    unsigned long align_size = 4 * 1024;
    int skip, loop;
    static double latency = 0.0;
    double t_start = 0, t_stop = 0, timer = 0;
    static double avg_time = 0.0, max_time = 0.0, min_time = 0.0;
    float *sendbuff, *recvbuff;
    int max_msg_size = 1048576, full = 1, t;
    int po_ret;

    xbrtime_init();
    rank = xbrtime_mype();
    numprocs = xbrtime_num_pes();


    if (numprocs < 2) {
        if (rank == 0) {
            printf("This test requires at least two processes\n");
        }
        return EXIT_FAILURE;
    }

    int nreduce = max_msg_size / sizeof(float);

    max_msg_size = MAX_MESSAGE_SIZE;

    recvbuff = (float *)xbrtime_align(align_size, max_msg_size);

    if (NULL == recvbuff) {
        printf("xbrtime_align failed\n");
        return EXIT_FAILURE;
    }
    sendbuff = (float *)xbrtime_align(align_size, max_msg_size);

    if (NULL == sendbuff) {
        printf("xbrtime_align failed\n");
        return EXIT_FAILURE;
    }

    memset(sendbuff, 1, max_msg_size);
    memset(recvbuff, 0, max_msg_size);

    for (size = 1; size * sizeof(float) <= max_msg_size; size *= 2) {
        if (size > LARGE_MESSAGE_SIZE) {
            skip = OSHM_SKIP_LARGE;
            loop = OSHM_LOOP_LARGE;
        } else {
            skip = OSHM_SKIP_SMALL;
            loop = OSHM_LOOP_SMALL;
        }

        xbrtime_barrier_all();

        timer = 0;
        for (i = 0; i < iterations + skip; i++) {
            t_start = TIME();
            xbrtime_float_sum_reduce(recvbuff, sendbuff, size);
            t_stop = TIME();

            if (i >= skip) {
                timer += t_stop - t_start;
            }
            xbrtime_barrier_all();
        }

        latency = (double)(timer * 1.0) / iterations;

        xbrtime_double_min_reduce(&min_time, &latency, 1);
        xbrtime_double_max_reduce(&max_time, &latency, 1);
        xbrtime_double_sum_reduce(&avg_time, &latency, 1);

        avg_time = avg_time / numprocs;

        print_data_pgas(rank, full, sizeof(float) * size, avg_time, min_time,
                        max_time, iterations);
        xbrtime_barrier_all();
    }

    xbrtime_barrier_all();
    
    xbrtime_free(recvbuff);
    xbrtime_free(sendbuff);
    xbrtime_close();

    return EXIT_SUCCESS;
}

/* vi: set sw=4 sts=4 tw=80: */
