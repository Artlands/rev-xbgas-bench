#define BENCHMARK "OSU OpenSHMEM Collect Latency Test"

/*
 * For detailed copyright and licensing information, please refer to the
 * copyright file COPYRIGHT in the top level directory.
 */

#include <xbrtime.h>
#include "xbgas_osu_util.h"

int main(int argc, char *argv[])
{
    int i, numprocs, rank, loop, po_ret;
    unsigned long align_size = 4 * 1024;
    int skip;
    int size = 0;
    static double latency = 0.0;
    double t_start = 0, t_stop = 0, timer = 0;
    static double avg_time = 0.0, max_time = 0.0, min_time = 0.0;
    char *recvbuff, *sendbuff;
    int max_msg_size = 1048576, full = 1, t;
    uint64_t requested_mem_limit = 0;

    xbrtime_init();
    rank = xbrtime_mype();
    numprocs = xbrtime_num_pes();
    max_msg_size = MAX_MESSAGE_SIZE;

    if (numprocs < 2) {
        if (rank == 0) {
            printf("This test requires at least two processes\n");
        }
        return EXIT_FAILURE;
    }

    print_header_pgas(HEADER, rank, full);

    recvbuff =
        (char *)xbrtime_align(align_size, sizeof(char) * max_msg_size * numprocs);

    if (NULL == recvbuff) {
        printf("xbrtime_align failed\n");
        return( EXIT_FAILURE );
    }

    sendbuff = (char *)xbrtime_align(align_size, sizeof(char) * max_msg_size);

    if (NULL == sendbuff) {
        printf("xbrtime_align failed\n");
       return( EXIT_FAILURE );
    }

    memset(recvbuff, 1, max_msg_size * numprocs);
    memset(sendbuff, 0, max_msg_size);

    for (size = 1; size <= max_msg_size / sizeof(uint32_t); size *= 2) {
        if (size > LARGE_MESSAGE_SIZE) {
            skip = OSHM_SKIP_LARGE;
            loop = OSHM_LOOP_LARGE;
        } else {
            skip = OSHM_SKIP_SMALL;
            loop = OSHM_LOOP_SMALL;
        }

        xbrtime_barrier_all();

        timer = 0;
        for (i = 0; i < loop + skip; i++) {
            t_start = TIME();
            xbrtime_char_collect(recvbuff, sendbuff, size);
            t_stop = TIME();

            if (i >= skip) {
                timer += t_stop - t_start;
            }
        }

        xbrtime_barrier_all();
        latency = (double)(timer * 1.0) / loop;

        xbrtime_double_min_reduce(&min_time, &latency, 1);
        xbrtime_double_max_reduce(&max_time, &latency, 1);
        xbrtime_double_sum_reduce(&avg_time, &latency, 1);

        avg_time = avg_time / numprocs;

        print_data_pgas(rank, full, size * sizeof(uint32_t), avg_time, min_time,
                        max_time, loop);
    }

    xbrtime_barrier_all();

    xbrtime_free(recvbuff);
    xbrtime_free(sendbuff);
    xbrtime_close();

    return EXIT_SUCCESS;
}
