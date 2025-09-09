#include "philo.h"

long elapsed_ms(long start_time)
{
    return get_time_ms() - start_time;
}

long get_time_ms(void)
{
    struct timeval tv;
    long ms;

    gettimeofday(&tv, NULL);
    ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return ms;
}