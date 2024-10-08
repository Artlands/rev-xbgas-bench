/*
 * atomics_test.c
 */

#include "xbrtime.h"

#define TEST_ATOMIC(_type, _typename, _op, _format)                                                                         \
void test_##_typename##_##_op(_type op_val)                                                                                 \
{                                                                                                                           \
    int my_pe = xbrtime_mype();                                                                                             \
    _type *source_val = (_type*) xbrtime_malloc(sizeof(_type));                                                             \
    *source_val = (_type) ((my_pe+1) * 100);                                                                                           \
    _type ret_val = 999;													\
                                                                                                                            \
    if(my_pe == 0)                                                                                                          \
    {                                                                                                                       \
        printf("RUNNING ATOMIC %s TEST FOR TYPE %s!\n", #_op, #_type);                                                      \
    }                                                                                                                       \
                                                                                                                            \
    xbrtime_barrier();                                                                                                         \
                                                                                                                            \
    printf("Before atomic operation\tPE: %d\tSource value: "_format"\tReturn value: "_format"\tOp value: "_format"\n", my_pe, *source_val, ret_val, op_val);  \
                                                                                                                            \
    xbrtime_barrier();                                                                                                         \
                                                                                                                            \
    if(my_pe == 0)                                                                                                          \
    {                                                                                                                       \
        ret_val = xbrtime_##_typename##_atomic_##_op(source_val, op_val, 1);                                                          \
    }                                                                                                                       \
                                                                                                                            \
    xbrtime_barrier();                                                                                                         \
                                                                                                                            \
    printf("After atomic operation\tPE: %d\tSource value: "_format"\tReturn value: "_format"\tOp value: "_format"\n", my_pe, *source_val, ret_val, op_val);   \
                                                                                                                            \
    xbrtime_barrier();                                                                                                         \
                                                                                                                            \
    if(my_pe == 0)                                                                                                          \
    {                                                                                                                       \
        printf("ATOMIC %s TEST FOR TYPE %s COMPLETED!\n\n", #_op, #_type);                                                  \
    }                                                                                                                       \
    xbrtime_free(source_val);                                                                                               \
}

    TEST_ATOMIC(unsigned int, uint, add, "%u")
    TEST_ATOMIC(unsigned long, ulong, add, "%u")
    TEST_ATOMIC(uint32_t, uint32, add, "%u")
    TEST_ATOMIC(int, int, add, "%d")
    TEST_ATOMIC(long, long, add, "%d")
    TEST_ATOMIC(int32_t, int32, add, "%d")
    TEST_ATOMIC(unsigned long long, ulonglong, add, "%llu")
    TEST_ATOMIC(uint64_t, uint64, add, "%llu")
    TEST_ATOMIC(long long, longlong, add, "%lld")
    TEST_ATOMIC(int64_t, int64, add, "%lld")

    TEST_ATOMIC(unsigned int, uint, bor, "%u")
    TEST_ATOMIC(unsigned long, ulong, bor, "%u")
    TEST_ATOMIC(uint32_t, uint32, bor, "%u")
    TEST_ATOMIC(int, int, bor, "%d")
    TEST_ATOMIC(long, long, bor, "%d")
    TEST_ATOMIC(int32_t, int32, bor, "%d")
    TEST_ATOMIC(unsigned long long, ulonglong, bor, "%llu")
    TEST_ATOMIC(uint64_t, uint64, bor, "%llu")
    TEST_ATOMIC(long long, longlong, bor, "%lld")
    TEST_ATOMIC(int64_t, int64, bor, "%lld")

    TEST_ATOMIC(unsigned int, uint, band, "%u")
    TEST_ATOMIC(unsigned long, ulong, band, "%u")
    TEST_ATOMIC(uint32_t, uint32, band, "%u")
    TEST_ATOMIC(int, int, band, "%d")
    TEST_ATOMIC(long, long, band, "%d")
    TEST_ATOMIC(int32_t, int32, band, "%d")
    TEST_ATOMIC(unsigned long long, ulonglong, band, "%llu")
    TEST_ATOMIC(uint64_t, uint64, band, "%llu")
    TEST_ATOMIC(long long, longlong, band, "%lld")
    TEST_ATOMIC(int64_t, int64, band, "%lld")

    TEST_ATOMIC(unsigned int, uint, bxor, "%u")
    TEST_ATOMIC(unsigned long, ulong, bxor, "%u")
    TEST_ATOMIC(uint32_t, uint32, bxor, "%u")
    TEST_ATOMIC(int, int, bxor, "%d")
    TEST_ATOMIC(long, long, bxor, "%d")
    TEST_ATOMIC(int32_t, int32, bxor, "%d")
    TEST_ATOMIC(unsigned long long, ulonglong, bxor, "%llu")
    TEST_ATOMIC(uint64_t, uint64, bxor, "%llu")
    TEST_ATOMIC(long long, longlong, bxor, "%lld")
    TEST_ATOMIC(int64_t, int64, bxor, "%lld")

    TEST_ATOMIC(unsigned int, uint, min, "%u")
    TEST_ATOMIC(unsigned long, ulong, min, "%u")
    TEST_ATOMIC(uint32_t, uint32, min, "%u")
    //TEST_ATOMIC(int, int, min, "%d")
    //TEST_ATOMIC(long, long, min, "%d")
    //TEST_ATOMIC(int32_t, int32, min, "%d")
    TEST_ATOMIC(unsigned long long, ulonglong, min, "%llu")
    TEST_ATOMIC(uint64_t, uint64, min, "%llu")
    //TEST_ATOMIC(long long, longlong, min, "%lld")
    //TEST_ATOMIC(int64_t, int64, min, "%lld")

    TEST_ATOMIC(unsigned int, uint, max, "%u")
    TEST_ATOMIC(unsigned long, ulong, max, "%u")
    TEST_ATOMIC(uint32_t, uint32, max, "%u")
    //TEST_ATOMIC(int, int, max, "%d")
    //TEST_ATOMIC(long, long, max, "%d")
    //TEST_ATOMIC(int32_t, int32, max, "%d")
    TEST_ATOMIC(unsigned long long, ulonglong, max, "%llu")
    TEST_ATOMIC(uint64_t, uint64, max, "%llu")
    //TEST_ATOMIC(long long, longlong, max, "%lld")
    //TEST_ATOMIC(int64_t, int64, max, "%lld")

    TEST_ATOMIC(unsigned int, uint, compare_swap, "%u")
    TEST_ATOMIC(unsigned long, ulong, compare_swap, "%u")
    TEST_ATOMIC(uint32_t, uint32, compare_swap, "%u")
    TEST_ATOMIC(int, int, compare_swap, "%d")
    TEST_ATOMIC(long, long, compare_swap, "%d")
    TEST_ATOMIC(int32_t, int32, compare_swap, "%d")
    TEST_ATOMIC(unsigned long long, ulonglong, compare_swap, "%llu")
    TEST_ATOMIC(uint64_t, uint64, compare_swap, "%llu")
    TEST_ATOMIC(long long, longlong, compare_swap, "%lld")
    TEST_ATOMIC(int64_t, int64, compare_swap, "%lld")

#undef TEST_ATOMIC

int main(int argc, char **argv)
{
    xbrtime_init();

    test_int_compare_swap(200);

    xbrtime_close();
    return 0;
}
