
#define _POSIX_C_SOURCE 200809L
#include <time.h>
#include "gettime.h"

double getTime(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + 1.0e-9 * (double)ts.tv_nsec;
}
