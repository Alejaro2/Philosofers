#include "philo.h"

int is_number(char *str)
{
    int i;

    if (!str || !str[0])
        return 0;
    i = 0;
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
        if (result > INT_MAX)
            return -1;
        i++;
    }
    return (int)result;
}

int validate_args(int argc, char **argv)
{
    int i;
    long value;

    if (argc < 5 || argc > 6)
        return 1;
    
    i = 1;
    while (i < argc)
    {
        if (!is_number(argv[i]))
            return 1;
        
        value = ft_atoi_safe(argv[i]);
        if (value <= 0)
            return 1;
        i++;
    }
    return 0;
}