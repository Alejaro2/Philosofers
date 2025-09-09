#include "philo.h"

int	simulation_ended(t_data *data)
{
    int ended;

    pthread_mutex_lock(&data->state_mutex);
    ended = data->someone_died;
    pthread_mutex_unlock(&data->state_mutex);
    return (ended);
}

static int	check_death(t_philo *philo)
{
    if (get_time_ms() - philo->last_meal_time > philo->data->time_to_die)
    {
        pthread_mutex_lock(&philo->data->print_mutex);
        if (!simulation_ended(philo->data)) // evitar doble impresión
            printf("%ld %d died\n",
                get_time_ms() - philo->data->start_time, philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);

        pthread_mutex_lock(&philo->data->state_mutex);
        philo->data->someone_died = 1;
        pthread_mutex_unlock(&philo->data->state_mutex);

        return (1);
    }
    return (0);
}

static int	check_meals(t_philo *philos, t_data *data)
{
    int i;

    if (data->must_eat_count == -1)
        return (0);
    i = 0;
    while (i < data->num_philos)
    {
        if (philos[i].meals_eaten < data->must_eat_count)
            return (0);
        i++;
    }
    pthread_mutex_lock(&data->state_mutex);
    data->someone_died = 1;
    pthread_mutex_unlock(&data->state_mutex);
    return (1);
}

void	*monitor_routine(void *arg)
{
    t_philo *philos = (t_philo *)arg;
    t_data  *data = philos[0].data;
    int i;

    while (!simulation_ended(data))
    {
        i = 0;
        while (i < data->num_philos && !simulation_ended(data))
        {
            if (check_death(&philos[i]))
                return (NULL);
            i++;
        }
        if (check_meals(philos, data))
            return (NULL);
        usleep(1000); 
    }
    return (NULL);
}




