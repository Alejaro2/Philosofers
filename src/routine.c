#include "philo.h"

void print_status(t_philo *philo, char *status)
{
    long timestamp;

    timestamp = get_time_ms() - philo->data->start_time;
    printf("%ld %d %s\n", timestamp, philo->id, status);
}
void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (!simulation_ended(philo->data))
    {
        print_status(philo, "is thinking");
        usleep(200000);

        // Antes de tomar forks, revisamos si la simulación terminó
        if (simulation_ended(philo->data))
            break;

        pthread_mutex_lock(philo->left_fork);
        if (simulation_ended(philo->data))
        {
            pthread_mutex_unlock(philo->left_fork);
            break;
        }
        print_status(philo, "has taken a fork");

        pthread_mutex_lock(philo->right_fork);
        if (simulation_ended(philo->data))
        {
            pthread_mutex_unlock(philo->left_fork);
            pthread_mutex_unlock(philo->right_fork);
            break;
        }
        print_status(philo, "has taken a fork");

        // Comer
        print_status(philo, "is eating");
        philo->last_meal_time = get_time_ms();
        usleep(philo->data->time_to_eat * 1000);

        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

        // Dormir
        if (simulation_ended(philo->data))
            break;
        print_status(philo, "is sleeping");
        usleep(philo->data->time_to_sleep * 1000);
    }
    return (NULL);
}




