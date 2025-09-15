#include "philo.h"

int simulation_ended(t_data *data)
{
    int ended;
    pthread_mutex_lock(&data->state_mutex);
    ended = data->someone_died;
    pthread_mutex_unlock(&data->state_mutex);
    return ended;
}

static int check_death(t_philo *philo)
{
    long current_time;
    long since_meal;

    current_time = get_time_ms();
    
    pthread_mutex_lock(&philo->data->meal_mutex);
    since_meal = get_time_ms() - philo->last_meal_time;
    pthread_mutex_unlock(&philo->data->meal_mutex);

    if (since_meal > philo->data->time_to_die - 5)
    {
        usleep(10);
        
        current_time = get_time_ms();
        pthread_mutex_lock(&philo->data->meal_mutex);
        since_meal = current_time - philo->last_meal_time;
        pthread_mutex_unlock(&philo->data->meal_mutex);
        
        if (since_meal > philo->data->time_to_die)
        {
            pthread_mutex_lock(&philo->data->print_mutex);
            if (!philo->data->someone_died)
            {
                printf("%ld %d died\n", current_time - philo->data->start_time, philo->id);
                pthread_mutex_lock(&philo->data->state_mutex);
                philo->data->someone_died = 1;
                pthread_mutex_unlock(&philo->data->state_mutex);
            }
            pthread_mutex_unlock(&philo->data->print_mutex);
            return (1);
        }
    }
    return (0);
}

void *monitor_routine(void *arg)
{
    t_philo *philos = (t_philo *)arg;
    t_data *data = philos[0].data;
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
        usleep(50);
    }
    return (NULL);
}
