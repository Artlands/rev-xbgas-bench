/*
 * atomics_test.c
 */

#include "xbrtime.h"

#define TEST_ATOMIC(_type, _typename, _op, _format)                                                                         \
void test_##_typename##_##_op(_type op_val)                                                                                 \
{                                                                                                                           \
    int my_pe = xbrtime_mype();                                                                                             \
    _type *source_val = (_type*) xbrtime_malloc(sizeof(_type));                                                             \
    *source_val = (_type) my_pe;                                                                                            \
                                                                                                                            \
    if(my_pe == 0)                                                                                                          \
    {                                                                                                                       \
        printf("RUNNING ATOMIC %s TEST FOR TYPE %s!\n", #_op, #_type);                                                      \
    }                                                                                                                       \
                                                                                                                            \
    temp_barrier();                                                                                                         \
                                                                                                                            \
    printf("Before atomic operation\tPE: %d\tSource value: "_format"\tOp value: "_format"\n", my_pe, *source_val, op_val);  \
                                                                                                                            \
    temp_barrier();                                                                                                         \
                                                                                                                            \
    if(my_pe == 0)                                                                                                          \
    {                                                                                                                       \
        xbrtime_##_typename##_atomic_##_op(source_val, op_val, 1);                                                          \
    }                                                                                                                       \
                                                                                                                            \
    temp_barrier();                                                                                                         \
                                                                                                                            \
    printf("After atomic operation\tPE: %d\tSource value: "_format"\tOp value: "_format"\n", my_pe, *source_val, op_val);   \
                                                                                                                            \
    temp_barrier();                                                                                                         \
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

    TEST_ATOMIC(unsigned int, uint, lor, "%u")
    TEST_ATOMIC(unsigned long, ulong, lor, "%u")
    TEST_ATOMIC(uint32_t, uint32, lor, "%u")
    TEST_ATOMIC(int, int, lor, "%d")
    TEST_ATOMIC(long, long, lor, "%d")
    TEST_ATOMIC(int32_t, int32, lor, "%d")
    TEST_ATOMIC(unsigned long long, ulonglong, lor, "%llu")
    TEST_ATOMIC(uint64_t, uint64, lor, "%llu")
    TEST_ATOMIC(long long, longlong, lor, "%lld")
    TEST_ATOMIC(int64_t, int64, lor, "%lld")

    TEST_ATOMIC(unsigned int, uint, land, "%u")
    TEST_ATOMIC(unsigned long, ulong, land, "%u")
    TEST_ATOMIC(uint32_t, uint32, land, "%u")
    TEST_ATOMIC(int, int, land, "%d")
    TEST_ATOMIC(long, long, land, "%d")
    TEST_ATOMIC(int32_t, int32, land, "%d")
    TEST_ATOMIC(unsigned long long, ulonglong, land, "%llu")
    TEST_ATOMIC(uint64_t, uint64, land, "%llu")
    TEST_ATOMIC(long long, longlong, land, "%lld")
    TEST_ATOMIC(int64_t, int64, land, "%lld")

    TEST_ATOMIC(unsigned int, uint, lxor, "%u")
    TEST_ATOMIC(unsigned long, ulong, lxor, "%u")
    TEST_ATOMIC(uint32_t, uint32, lxor, "%u")
    TEST_ATOMIC(int, int, lxor, "%d")
    TEST_ATOMIC(long, long, lxor, "%d")
    TEST_ATOMIC(int32_t, int32, lxor, "%d")
    TEST_ATOMIC(unsigned long long, ulonglong, lxor, "%llu")
    TEST_ATOMIC(uint64_t, uint64, lxor, "%llu")
    TEST_ATOMIC(long long, longlong, lxor, "%lld")
    TEST_ATOMIC(int64_t, int64, lxor, "%lld")

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

    test_uint_compare_swap(1);
    test_ulong_compare_swap(0);
    test_uint32_compare_swap(0);
    test_int_compare_swap(0);
    test_long_compare_swap(0);
    test_int32_compare_swap(1);
    test_ulonglong_compare_swap(1);
    test_uint64_compare_swap(0);
    test_longlong_compare_swap(0);
    test_int64_compare_swap(1);

    xbrtime_close();
    return 0;
}
