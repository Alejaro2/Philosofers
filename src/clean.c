#include "philo.h"

void cleanup(t_philo *philos, pthread_mutex_t *forks, t_data *data)
{
    int i;
    
    if (forks)
    {
        i = 0;
        while (i < data->num_philos)
        {
            pthread_mutex_destroy(&forks[i]);
            i++;
        }
        free(forks);
    }
    
    if (philos)
        free(philos);
    
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->state_mutex);
    pthread_mutex_destroy(&data->meal_mutex);
    pthread_mutex_destroy(&data->done_eating_mutex);
}
