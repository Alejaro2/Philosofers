#include "philo.h"

static void take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork");
    }
}

static void update_meal_status(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->meal_mutex);
    philo->meals_eaten++;
    
    if (philo->data->must_eat_count > 0 && 
        philo->meals_eaten >= philo->data->must_eat_count)
    {
        pthread_mutex_lock(&philo->data->done_eating_mutex);
        philo->data->philos_done_eating++;
        if (philo->data->philos_done_eating == philo->data->num_philos)
        {
            pthread_mutex_lock(&philo->data->state_mutex);
            philo->data->someone_died = 1;
            pthread_mutex_unlock(&philo->data->state_mutex);
        }
        pthread_mutex_unlock(&philo->data->done_eating_mutex);
    }
    pthread_mutex_unlock(&philo->data->meal_mutex);
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->data->num_philos == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
        usleep(philo->data->time_to_die * 1000);
        pthread_mutex_unlock(philo->left_fork);
        return (NULL);
    }

    if (philo->id % 2 == 0)
        usleep(philo->data->time_to_eat * 1000);

    pthread_mutex_lock(&philo->data->meal_mutex);
    philo->last_meal_time = get_time_ms();
    pthread_mutex_unlock(&philo->data->meal_mutex);

    while (!philo->data->someone_died)
    {
        take_forks(philo);
        
        pthread_mutex_lock(&philo->data->meal_mutex);
        philo->last_meal_time = get_time_ms();
        pthread_mutex_unlock(&philo->data->meal_mutex);
        
        print_status(philo, "is eating");
        usleep(philo->data->time_to_eat * 1000);
        
        update_meal_status(philo);
        
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        
        if (philo->data->someone_died)
            break;
            
        print_status(philo, "is sleeping");
        usleep(philo->data->time_to_sleep * 1000);
        
        print_status(philo, "is thinking");
        
        usleep(100);
    }
    return (NULL);
}