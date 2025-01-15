#define BENCHMARK "OSU OpenSHMEM Get Test"

/*
 * For detailed copyright and licensing information, please refer to the
 * copyright file COPYRIGHT in the top level directory.
 */


#include <xbrtime.h>
#include "xbgas_osu_util.h"

int main(int argc, char *argv[])
{
    double t_start = 0, t_end = 0;

    t_start = TIME();

    printf("Start time: %.5f\n", t_start);
    for( int i=0; i<1000; i++ ) {
        // do nothing
    }

    t_end = TIME();

    printf("End time: %.5f\n", t_end);

    return EXIT_SUCCESS;
}

