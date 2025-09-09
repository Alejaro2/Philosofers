#include "philo.h"

int is_number(char *str)
{
    int i;

    if (!str)
        return 0;
    i = 0;
    if (str[i] == '\0')
        return 0;
    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

int ft_atoi_safe(char *str)
{
    long result;
    int i;

    result = 0;
    i = 0;
    while (str[i] != '\0')
    {
        result = result * 10 + (str[i] - '0');
        if (result > 2147483647)
            return -1;
        i++;
    }
    return (int)result;
}

int parse_args(int argc, char **argv, t_data *data)
{
    int i;

    if (argc < 5 || argc > 6)
        return 1;
    i = 1;
    while (i < argc)
    {
        if (!is_number(argv[i]))
            return 1;
        i++;
    }
    data->num_philos = ft_atoi_safe(argv[1]);
    data->time_to_die = ft_atoi_safe(argv[2]);
    data->time_to_eat = ft_atoi_safe(argv[3]);
    data->time_to_sleep = ft_atoi_safe(argv[4]);
    if (argc == 6)
        data->must_eat_count= ft_atoi_safe(argv[5]);
    else
        data->must_eat_count = -1;
    if (data->num_philos <= 0 || data->time_to_die <= 0 ||
        data->time_to_eat <= 0 || data->time_to_sleep <= 0 ||
        (argc == 6 && data->must_eat_count <= 0))
        return 1;
    return 0;
}
