#define BENCHMARK "OSU OpenSHMEM Atomic Operation Rate Test"

/*
 * For detailed copyright and licensing information, please refer to the
 * copyright file COPYRIGHT in the top level directory.
 */

#include <xbrtime.h>
#include "xbgas_osu_util.h"

struct pe_vars {
    int me;
    int npes;
    int pairs;
    int nxtpe;
};

union data_types {
    int int_type;
    long long_type;
    long long longlong_type;
    float float_type;
    double double_type;
};

struct pe_vars init_xbrtime(void)
{
    struct pe_vars v;

    xbrtime_init();
    v.me = xbrtime_mype();
    v.npes = xbrtime_num_pes();

    v.pairs = v.npes / 2;
    v.nxtpe = v.me < v.pairs ? v.me + v.pairs : v.me - v.pairs;

    return v;
}

void check_usage(int me, int npes, int argc, char *argv[])
{
    if (2 > npes) {
        if (0 == me) {
            printf("This test requires at least two processes\n");
        }

        exit(EXIT_FAILURE);
    }
}

void print_header_local(int myid)
{
    if (myid == 0) {
        printf(HEADER);
        printf("%-*s%*s%*s\n", 20, "# Operation", FIELD_WIDTH,
                "Million ops/s", FIELD_WIDTH, "Latency (us)");
    }
}

union data_types *allocate_memory(int me)
{
    union data_types *msg_buffer;

    msg_buffer = (union data_types *)xbrtime_malloc(
                  sizeof(union data_types[OSHM_LOOP_ATOMIC]));

    if (NULL == msg_buffer) {
        printf("Failed to xbrtime_malloc (pe: %d)\n", me);
        exit(EXIT_FAILURE);
    }

    return msg_buffer;
}

void print_operation_rate(int myid, char *operation, double rate, double lat)
{
    if (myid == 0) {
        printf("%-*s%*.*f%*.*f\n", 20, operation, FIELD_WIDTH,
               FLOAT_PRECISION, rate, FIELD_WIDTH, FLOAT_PRECISION, lat);
    }
}

double benchmark_atomic_fetch_add(struct pe_vars v, union data_types *buffer,
                                  unsigned long iterations)
{
    double begin, end;
    int i;
    static double rate = 0, sum_rate = 0, lat = 0, sum_lat = 0;

    /*
     * Touch memory
     */
    memset(buffer, CHAR_MAX * 0.5,
           sizeof(union data_types[OSHM_LOOP_ATOMIC]));

    xbrtime_barrier_all();

    if (v.me < v.pairs) {
        int value = 1;
        int old_value;

        begin = TIME();
        for (i = 0; i < iterations; i++) {
            old_value = xbrtime_int_atomic_fetch_add(&(buffer[i].int_type), value, v.nxtpe);
        }
        end = TIME();

        rate = ((double)iterations * 1e6) / (end - begin);
        lat = (end - begin) / (double)iterations;
    }

    xbrtime_double_sum_reduce(&sum_rate, &rate, 1);
    xbrtime_double_sum_reduce(&sum_lat, &lat, 1);
    print_operation_rate(v.me, "xbrtime_int_atomic_fetch_add", sum_rate / 1e6,
                         sum_lat / v.pairs);

    return 0;
}

double benchmark_atomic_fetch_add_longlong(struct pe_vars v, union data_types *buffer,
                               unsigned long iterations)
{
    double begin, end;
    int i;
    static double rate = 0, sum_rate = 0, lat = 0, sum_lat = 0;

    /*
     * Touch memory
     */
    memset(buffer, CHAR_MAX * 0.5,
           sizeof(union data_types[OSHM_LOOP_ATOMIC]));

    xbrtime_barrier_all();

    if (v.me < v.pairs) {
        long long value = 1;
        long long old_value;

        begin = TIME();
        for (i = 0; i < iterations; i++) {
            old_value =
                xbrtime_longlong_atomic_fetch_add(&(buffer[i].longlong_type), value, v.nxtpe);
        }
        end = TIME();

        rate = ((double)iterations * 1e6) / (end - begin);
        lat = (end - begin) / (double)iterations;
    }

    xbrtime_double_sum_reduce(&sum_rate, &rate, 1);
    xbrtime_double_sum_reduce(&sum_lat, &lat, 1);
    print_operation_rate(v.me, "xbrtime_longlong_atomic_fetch_add", sum_rate / 1e6,
                         sum_lat / v.pairs);
    return 0;
}

double benchmark_atomic_fetch_inc(struct pe_vars v, union data_types *buffer,
                      unsigned long iterations)
{
    double begin, end;
    int i;
    static double rate = 0, sum_rate = 0, lat = 0, sum_lat = 0;

    /*
     * Touch memory
     */
    memset(buffer, CHAR_MAX * 0.5,
           sizeof(union data_types[OSHM_LOOP_ATOMIC]));

    xbrtime_barrier_all();

    if (v.me < v.pairs) {
        int old_value;

        begin = TIME();
        for (i = 0; i < iterations; i++) {
            old_value = xbrtime_int_atomic_fetch_inc(&(buffer[i].int_type), v.nxtpe);
        }
        end = TIME();

        rate = ((double)iterations * 1e6) / (end - begin);
        lat = (end - begin) / (double)iterations;
    }

    xbrtime_double_sum_reduce(&sum_rate, &rate, 1);
    xbrtime_double_sum_reduce(&sum_lat, &lat, 1);
    print_operation_rate(v.me, "xbrtime_int_atomic_fetch_inc", sum_rate / 1e6,
                         sum_lat / v.pairs);

    return 0;
}

double benchmark_atomic_fetch_inc_longlong(struct pe_vars v, union data_types *buffer,
                      unsigned long iterations)
{
    double begin, end;
    int i;
    static double rate = 0, sum_rate = 0, lat = 0, sum_lat = 0;

    /*
     * Touch memory
     */
    memset(buffer, CHAR_MAX * 0.5,
           sizeof(union data_types[OSHM_LOOP_ATOMIC]));

    xbrtime_barrier_all();

    if (v.me < v.pairs) {
        int old_value;

        begin = TIME();
        for (i = 0; i < iterations; i++) {
            old_value = xbrtime_longlong_atomic_fetch_inc(&(buffer[i].longlong_type), v.nxtpe);
        }
        end = TIME();

        rate = ((double)iterations * 1e6) / (end - begin);
        lat = (end - begin) / (double)iterations;
    }

    xbrtime_double_sum_reduce(&sum_rate, &rate, 1);
    xbrtime_double_sum_reduce(&sum_lat, &lat, 1);
    print_operation_rate(v.me, "xbrtime_int_atomic_fetch_inc", sum_rate / 1e6,
                         sum_lat / v.pairs);

    return 0;
}

double benchmark_atomic_add(struct pe_vars v, union data_types *buffer,
                     unsigned long iterations)
{
    double begin, end;
    int i;
    static double rate = 0, sum_rate = 0, lat = 0, sum_lat = 0;

    /*
     * Touch memory
     */
    memset(buffer, CHAR_MAX * 0.5,
           sizeof(union data_types[OSHM_LOOP_ATOMIC]));

    xbrtime_barrier_all();

    if (v.me < v.pairs) {
        int value = INT_MAX * 0.5;

        begin = TIME();
        for (i = 0; i < iterations; i++) {
            xbrtime_int_atomic_add(&(buffer[i].int_type), value, v.nxtpe);
        }
        end = TIME();

        rate = ((double)iterations * 1e6) / (end - begin);
        lat = (end - begin) / (double)iterations;
    }

    xbrtime_double_sum_reduce(&sum_rate, &rate, 1);
    xbrtime_double_sum_reduce(&sum_lat, &lat, 1);
    print_operation_rate(v.me, "xbrtime_int_atomic_add", sum_rate / 1e6,
                         sum_lat / v.pairs);

    return 0;
}

double benchmark_atomic_add_longlong(struct pe_vars v, union data_types *buffer,
                              unsigned long iterations)
{
    double begin, end;
    int i;
    static double rate = 0, sum_rate = 0, lat = 0, sum_lat = 0;

    /*
     * Touch memory
     */
    memset(buffer, CHAR_MAX * 0.5,
           sizeof(union data_types[OSHM_LOOP_ATOMIC]));

    xbrtime_barrier_all();

    if (v.me < v.pairs) {
        long long value = INT_MAX * 0.5;

        begin = TIME();
        for (i = 0; i < iterations; i++) {
            xbrtime_longlong_atomic_add(&(buffer[i].longlong_type), value, v.nxtpe);
        }
        end = TIME();

        rate = ((double)iterations * 1e6) / (end - begin);
        lat = (end - begin) / (double)iterations;
    }

    xbrtime_double_sum_reduce(&sum_rate, &rate, 1);
    xbrtime_double_sum_reduce(&sum_lat, &lat, 1);
    print_operation_rate(v.me, "xbrtime_longlong_atomic_add", sum_rate / 1e6,
                         sum_lat / v.pairs);

    return 0;
}

double benchmark_atomic_inc(struct pe_vars v, union data_types *buffer,
                     unsigned long iterations)
{
    double begin, end;
    int i;
    static double rate = 0, sum_rate = 0, lat = 0, sum_lat = 0;

    /*
     * Touch memory
     */
    memset(buffer, CHAR_MAX * 0.5,
           sizeof(union data_types[OSHM_LOOP_ATOMIC]));

    xbrtime_barrier_all();

    if (v.me < v.pairs) {
        begin = TIME();
        for (i = 0; i < iterations; i++) {
            xbrtime_int_atomic_inc(&(buffer[i].int_type), v.nxtpe);
        }
        end = TIME();

        rate = ((double)iterations * 1e6) / (end - begin);
        lat = (end - begin) / (double)iterations;
    }

    xbrtime_double_sum_reduce(&sum_rate, &rate, 1);
    xbrtime_double_sum_reduce(&sum_lat, &lat, 1);
    print_operation_rate(v.me, "xbrtime_int_atomic_inc", sum_rate / 1e6,
                         sum_lat / v.pairs);

    return 0;
}

double benchmark_atomic_inc_longlong(struct pe_vars v, union data_types *buffer,
                              unsigned long iterations)
{
    double begin, end;
    int i;
    static double rate = 0, sum_rate = 0, lat = 0, sum_lat = 0;

    /*
     * Touch memory
     */
    memset(buffer, CHAR_MAX * 0.5,
           sizeof(union data_types[OSHM_LOOP_ATOMIC]));

    xbrtime_barrier_all();

    if (v.me < v.pairs) {
        begin = TIME();
        for (i = 0; i < iterations; i++) {
            xbrtime_longlong_atomic_inc(&(buffer[i].longlong_type), v.nxtpe);
        }
        end = TIME();

        rate = ((double)iterations * 1e6) / (end - begin);
        lat = (end - begin) / (double)iterations;
    }

    xbrtime_double_sum_reduce(&sum_rate, &rate, 1);
    xbrtime_double_sum_reduce(&sum_lat, &lat, 1);
    print_operation_rate(v.me, "xbrtime_longlong_atomic_inc", sum_rate / 1e6,
                         sum_lat / v.pairs);

    return 0;
}

double benchmark_atomic_swap(struct pe_vars v, union data_types *buffer,
                      unsigned long iterations)
{
    double begin, end;
    int i;
    static double rate = 0, sum_rate = 0, lat = 0, sum_lat = 0;

    /*
     * Touch memory
     */
    memset(buffer, CHAR_MAX * 0.5,
           sizeof(union data_types[OSHM_LOOP_ATOMIC]));

    xbrtime_barrier_all();

    if (v.me < v.pairs) {
        int value = INT_MAX * 0.5;
        int old_value;

        begin = TIME();
        for (i = 0; i < iterations; i++) {
            old_value = xbrtime_int_atomic_swap(&(buffer[i].int_type), value, v.nxtpe);
        }
        end = TIME();

        rate = ((double)iterations * 1e6) / (end - begin);
        lat = (end - begin) / (double)iterations;
    }

    xbrtime_double_sum_reduce(&sum_rate, &rate, 1);
    xbrtime_double_sum_reduce(&sum_lat, &lat, 1);
    print_operation_rate(v.me, "xbrtime_int_atomic_swap", sum_rate / 1e6,
                         sum_lat / v.pairs);

    return 0;
}

double benchmark_atomic_swap_longlong(struct pe_vars v, union data_types *buffer,
                               unsigned long iterations)
{
    double begin, end;
    int i;
    static double rate = 0, sum_rate = 0, lat = 0, sum_lat = 0;

    /*
     * Touch memory
     */
    memset(buffer, CHAR_MAX * 0.5,
           sizeof(union data_types[OSHM_LOOP_ATOMIC]));

    xbrtime_barrier_all();

    if (v.me < v.pairs) {
        long long value = INT_MAX * 0.5;
        long long old_value;

        begin = TIME();
        for (i = 0; i < iterations; i++) {
            old_value =
                xbrtime_longlong_atomic_swap(&(buffer[i].longlong_type), value, v.nxtpe);
        }
        end = TIME();

        rate = ((double)iterations * 1e6) / (end - begin);
        lat = (end - begin) / (double)iterations;
    }

    xbrtime_double_sum_reduce(&sum_rate, &rate, 1);
    xbrtime_double_sum_reduce(&sum_lat, &lat, 1);
    print_operation_rate(v.me, "xbrtime_longlong_atomic_swap", sum_rate / 1e6,
                         sum_lat / v.pairs);

    return 0;
}

double benchmark_atomic_compare_swap(struct pe_vars v, union data_types *buffer,
                       unsigned long iterations)
{
    double begin, end;
    int i;
    static double rate = 0, sum_rate = 0, lat = 0, sum_lat = 0;

    /*
     * Touch memory
     */
    for (i = 0; i < OSHM_LOOP_ATOMIC; i++) {
        buffer[i].int_type = v.me;
    }

    xbrtime_barrier_all();

    if (v.me < v.pairs) {
        int cond = v.nxtpe;
        int value = INT_MAX * 0.5;
        int old_value;

        begin = TIME();
        for (i = 0; i < iterations; i++) {
            old_value =
                xbrtime_int_atomic_compare_swap(&(buffer[i].int_type), cond, value, v.nxtpe);
        }
        end = TIME();

        rate = ((double)iterations * 1e6) / (end - begin);
        lat = (end - begin) / (double)iterations;
    }

    xbrtime_double_sum_reduce(&sum_rate, &rate, 1);
    xbrtime_double_sum_reduce(&sum_lat, &lat, 1);
    print_operation_rate(v.me, "xbrtime_int_atomic_compare_swap", sum_rate / 1e6,
                         sum_lat / v.pairs);

    return 0;
}

double benchmark_atomic_compare_swap_longlong(struct pe_vars v, union data_types *buffer,
                                unsigned long iterations)
{
    double begin, end;
    int i;
    static double rate = 0, sum_rate = 0, lat = 0, sum_lat = 0;

    /*
     * Touch memory
     */
    for (i = 0; i < OSHM_LOOP_ATOMIC; i++) {
        buffer[i].int_type = v.me;
    }

    xbrtime_barrier_all();

    if (v.me < v.pairs) {
        long long cond = v.nxtpe;
        long long value = INT_MAX * 0.5;
        long long old_value;

        begin = TIME();
        for (i = 0; i < iterations; i++) {
            old_value = xbrtime_longlong_atomic_compare_swap(&(buffer[i].longlong_type), cond,
                                             value, v.nxtpe);
        }
        end = TIME();

        rate = ((double)iterations * 1e6) / (end - begin);
        lat = (end - begin) / (double)iterations;
    }

    xbrtime_double_sum_reduce(&sum_rate, &rate, 1);
    xbrtime_double_sum_reduce(&sum_lat, &lat, 1);
    print_operation_rate(v.me, "xbrtime_longlong_atomic_compare_swap", sum_rate / 1e6,
                         sum_lat / v.pairs);

    return 0;
}

double benchmark_atomic_fetch(struct pe_vars v, union data_types *buffer,
                       unsigned long iterations)
{
    double begin, end;
    int i;
    static double rate = 0, sum_rate = 0, lat = 0, sum_lat = 0;

    /*
     * Touch memory
     */
    memset(buffer, CHAR_MAX * 0.5,
           sizeof(union data_types[OSHM_LOOP_ATOMIC]));

    xbrtime_barrier_all();

    if (v.me < v.pairs) {
        begin = TIME();
        for (i = 0; i < iterations; i++) {
            xbrtime_int_atomic_fetch(&buffer[i].int_type, v.nxtpe);
        }
        end = TIME();

        rate = ((double)iterations * 1e6) / (end - begin);
        lat = (end - begin) / (double)iterations;
    }

    xbrtime_double_sum_reduce(&sum_rate, &rate, 1);
    xbrtime_double_sum_reduce(&sum_lat, &lat, 1);
    print_operation_rate(v.me, "xbrtime_int_atomic_fetch", sum_rate / 1e6,
                         sum_lat / v.pairs);

    return 0;
}

double benchmark_atomic_fetch_longlong(struct pe_vars v, union data_types *buffer,
                                unsigned long iterations)
{
    double begin, end;
    int i;
    static double rate = 0, sum_rate = 0, lat = 0, sum_lat = 0;

    /*
     * Touch memory
     */
    memset(buffer, CHAR_MAX * 0.5,
           sizeof(union data_types[OSHM_LOOP_ATOMIC]));

    xbrtime_barrier_all();

    if (v.me < v.pairs) {
        begin = TIME();
        for (i = 0; i < iterations; i++) {
            int res = xbrtime_longlong_atomic_fetch(&(buffer[i].longlong_type), v.nxtpe);
        }
        end = TIME();

        rate = ((double)iterations * 1e6) / (end - begin);
        lat = (end - begin) / (double)iterations;
    }

    xbrtime_double_sum_reduce(&sum_rate, &rate, 1);
    xbrtime_double_sum_reduce(&sum_lat, &lat, 1);
    print_operation_rate(v.me, "xbrtime_longlong_atomic_fetch", sum_rate / 1e6,
                         sum_lat / v.pairs);

    return 0;
}

double benchmark_atomic_set(struct pe_vars v, union data_types *buffer,
                     unsigned long iterations)
{
    double begin, end;
    int i;
    static double rate = 0, sum_rate = 0, lat = 0, sum_lat = 0;

    /*
     * Touch memory
     */
    memset(buffer, CHAR_MAX * 0.5,
           sizeof(union data_types[OSHM_LOOP_ATOMIC]));

    xbrtime_barrier_all();

    if (v.me < v.pairs) {
        int value = 1;

        begin = TIME();
        for (i = 0; i < iterations; i++) {
            xbrtime_int_atomic_set(&(buffer[i].int_type), value, v.nxtpe);
        }
        end = TIME();

        rate = ((double)iterations * 1e6) / (end - begin);
        lat = (end - begin) / (double)iterations;
    }

    xbrtime_double_sum_reduce(&sum_rate, &rate, 1);
    xbrtime_double_sum_reduce(&sum_lat, &lat, 1);
    print_operation_rate(v.me, "xbrtime_int_atomic_set", sum_rate / 1e6,
                         sum_lat / v.pairs);

    return 0;
}

double benchmark_atomic_set_longlong(struct pe_vars v, union data_types *buffer,
                              unsigned long iterations)
{
    double begin, end;
    int i;
    static double rate = 0, sum_rate = 0, lat = 0, sum_lat = 0;

    /*
     * Touch memory
     */
    memset(buffer, CHAR_MAX * 0.5,
           sizeof(union data_types[OSHM_LOOP_ATOMIC]));

    xbrtime_barrier_all();

    if (v.me < v.pairs) {
        long long value = 1;

        begin = TIME();
        for (i = 0; i < iterations; i++) {
            xbrtime_longlong_atomic_set(&(buffer[i].longlong_type), value, v.nxtpe);
        }
        end = TIME();

        rate = ((double)iterations * 1e6) / (end - begin);
        lat = (end - begin) / (double)iterations;
    }

    xbrtime_double_sum_reduce(&sum_rate, &rate, 1);
    xbrtime_double_sum_reduce(&sum_lat, &lat, 1);
    print_operation_rate(v.me, "xbrtime_longlong_atomic_set", sum_rate / 1e6,
                         sum_lat / v.pairs);
    return 0;
}

void benchmark(struct pe_vars v, union data_types *msg_buffer)
{
    /*
     * Warmup with puts
     */
    if (v.me < v.pairs) {
        unsigned long i;

        for (i = 0; i < OSHM_LOOP_ATOMIC; i++) {
            xbrtime_int_put(&msg_buffer[i].int_type, &msg_buffer[i].int_type,
                            sizeof(int), v.nxtpe);
        }
    }

    /*
     * Performance with atomics
     */
    benchmark_atomic_fetch_add(v, msg_buffer, OSHM_LOOP_ATOMIC);
    benchmark_atomic_fetch_inc(v, msg_buffer, OSHM_LOOP_ATOMIC);
    benchmark_atomic_add(v, msg_buffer, OSHM_LOOP_ATOMIC);
    benchmark_atomic_inc(v, msg_buffer, OSHM_LOOP_ATOMIC);
    benchmark_atomic_compare_swap(v, msg_buffer, OSHM_LOOP_ATOMIC);
    benchmark_atomic_swap(v, msg_buffer, OSHM_LOOP_ATOMIC);
    benchmark_atomic_set(v, msg_buffer, OSHM_LOOP_ATOMIC);
    benchmark_atomic_fetch(v, msg_buffer, OSHM_LOOP_ATOMIC);

    benchmark_atomic_fetch_add_longlong(v, msg_buffer, OSHM_LOOP_ATOMIC);
    benchmark_atomic_fetch_inc_longlong(v, msg_buffer, OSHM_LOOP_ATOMIC);
    benchmark_atomic_add_longlong(v, msg_buffer, OSHM_LOOP_ATOMIC);
    benchmark_atomic_inc_longlong(v, msg_buffer, OSHM_LOOP_ATOMIC);
    benchmark_atomic_compare_swap_longlong(v, msg_buffer, OSHM_LOOP_ATOMIC);
    benchmark_atomic_swap_longlong(v, msg_buffer, OSHM_LOOP_ATOMIC);
    benchmark_atomic_set_longlong(v, msg_buffer, OSHM_LOOP_ATOMIC);
    benchmark_atomic_fetch_longlong(v, msg_buffer, OSHM_LOOP_ATOMIC);
}

int main(int argc, char *argv[])
{
    int i;
    struct pe_vars v;
    union data_types *msg_buffer;

    /*
     * Initialize
     */
    v = init_xbrtime();
    check_usage(v.me, v.npes, argc, argv);

    xbrtime_barrier_all();

    print_header_local(v.me);

    /*
     * Allocate Memory
     */
    msg_buffer = allocate_memory(v.me);
    memset(msg_buffer, 0, sizeof(union data_types[OSHM_LOOP_ATOMIC]));

    /*
     * Time Atomic Message Rate
     */
    benchmark(v, msg_buffer);

    /*
     * Finalize
     */
    xbrtime_free(msg_buffer);

    xbrtime_close();

    return EXIT_SUCCESS;
}
