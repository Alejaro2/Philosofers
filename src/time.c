#include "philo.h"

long get_time_ms(void)
{
    struct timeval tv;
    long ms;

    gettimeofday(&tv, NULL);
    ms = (tv.tv_sec * 1000L) + (tv.tv_usec / 1000L);
    return ms;
}

long elapsed_ms(long start_time)
{
    return get_time_ms() - start_time;
}