#include "philo.h"

int simulation_ended(t_data *data)
{
    int ended;

    pthread_mutex_lock(&data->state_mutex);
    ended = data->someone_died;
    pthread_mutex_unlock(&data->state_mutex);
    return (ended);
}

static int check_meals(t_philo *philos)
{
    int i;
    int all_have_eaten;

    if (philos[0].data->must_eat_count <= 0)
        return (0);
    i = 0;
    all_have_eaten = 1;
    while (i < philos[0].data->num_philos)
    {
        pthread_mutex_lock(&philos[i].data->meal_mutex);
        if (philos[i].meals_eaten < philos[i].data->must_eat_count)
            all_have_eaten = 0;
        pthread_mutex_unlock(&philos[i].data->meal_mutex);
        if (!all_have_eaten)
            break ;
        i++;
    }
    if (all_have_eaten)
    {
        pthread_mutex_lock(&philos[0].data->state_mutex);
        philos[0].data->someone_died = 1;
        pthread_mutex_unlock(&philos[0].data->state_mutex);
        return (1);
    }
    return (0);
}

static int process_death(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->meal_mutex);
    if (get_time_ms() - philo->last_meal_time > philo->data->time_to_die)
    {
        pthread_mutex_lock(&philo->data->state_mutex);
        if (!philo->data->someone_died)
        {
            philo->data->someone_died = 1;
            pthread_mutex_lock(&philo->data->print_mutex);
            printf("%ld %d died\n", get_time_ms() - philo->data->start_time,
                philo->id);
            pthread_mutex_unlock(&philo->data->print_mutex);
        }
        pthread_mutex_unlock(&philo->data->state_mutex);
        pthread_mutex_unlock(&philo->data->meal_mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->meal_mutex);
    return (0);
}

void *monitor_routine(void *arg)
{
    t_philo *philos;
    int i;

    philos = (t_philo *)arg;
    while (1)
    {
        i = 0;
        while (i < philos[0].data->num_philos)
        {
            if (process_death(&philos[i]))
                return (NULL);
            i++;
        }
        if (check_meals(philos))
            return (NULL);
        usleep(1000);
    }
    return (NULL);
}