#include "philo.h"

int main(int argc, char **argv)
{
    t_data data;
    t_philo *philos;
    pthread_mutex_t *forks;
    pthread_t monitor;

    memset(&data, 0, sizeof(t_data));
    
    if (validate_args(argc, argv) != 0)
        return (printf("Error: Invalid arguments\n"), 1);
    
    if (init_data(&data) != 0)
        return (printf("Error: Initialization failed\n"), 1);
    
    data.num_philos = ft_atoi_safe(argv[1]);
    data.time_to_die = ft_atoi_safe(argv[2]);
    data.time_to_eat = ft_atoi_safe(argv[3]);
    data.time_to_sleep = ft_atoi_safe(argv[4]);
    
    if (argc == 6)
        data.must_eat_count = ft_atoi_safe(argv[5]);
    else
        data.must_eat_count = -1;
    
    if (data.num_philos <= 0 || data.time_to_die <= 0 ||
        data.time_to_eat <= 0 || data.time_to_sleep <= 0 ||
        (argc == 6 && data.must_eat_count <= 0))
        return (printf("Error: Invalid values\n"), 1);
    
    forks = init_forks_array(data.num_philos);
    if (!forks)
        return (printf("Error: Forks initialization failed\n"), 1);
        
    philos = init_philos_array(&data, forks);
    if (!philos)
        return (free(forks), printf("Error: Philos initialization failed\n"), 1);
    
    
    start_philos(philos, data.num_philos);
    pthread_create(&monitor, NULL, monitor_routine, philos);
    pthread_join(monitor, NULL);
    join_philos(philos, data.num_philos);
    cleanup(philos, forks, &data);
    return 0;
}
