#include "philo.h"

int main(int argc, char **argv)
{
    t_data data;
    t_philo *philos;
    pthread_mutex_t *forks;
    pthread_t monitor;

    if (parse_args(argc, argv, &data) || init_data(&data))
        return 1;
    forks = init_forks_array(data.num_philos);
    philos = init_philos_array(&data, forks);
    if (!forks || !philos)
        return 1;

    start_philos(philos, data.num_philos);
    pthread_create(&monitor, NULL, monitor_routine, philos);
    pthread_join(monitor, NULL);
    join_philos(philos, data.num_philos);
    cleanup(philos, forks, &data);
    return 0;
}


