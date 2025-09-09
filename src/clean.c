#include "philo.h"

void cleanup(t_philo *philos, pthread_mutex_t *forks, t_data *data)
{
    int i = 0;

    while (i < data->num_philos)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->print_mutex);
    free(philos);
    free(forks);
}
