#include "philo.h"

int init_data(t_data *data)
{
    data->someone_died = 0;
    if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
        return 1;
    data->start_time = get_time_ms();
    pthread_mutex_init(&data->state_mutex, NULL);
    return 0;
}

pthread_mutex_t *init_forks_array(int num_philos)
{
    pthread_mutex_t *forks;
    int i;

    forks = malloc(sizeof(pthread_mutex_t) * num_philos);
    if (!forks)
        return NULL;
    i = 0;
    while (i < num_philos)
    {
        if (pthread_mutex_init(&forks[i], NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&forks[i]);
            free(forks);
            return NULL;
        }
        i++;
    }
    return forks;
}


t_philo *init_philos_array(t_data *data, pthread_mutex_t *forks)
{
    t_philo *philos;
    int i;

    philos = malloc(sizeof(t_philo) * data->num_philos);
    if (!philos)
        return NULL;
    i = 0;
    while (i < data->num_philos)
    {
        philos[i].id = i + 1;
        philos[i].meals_eaten = 0;
        philos[i].last_meal_time = data->start_time;
        philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + 1) % data->num_philos];
        philos[i].data = data;
        i++;
    }
    return philos;
}

void start_philos(t_philo *philos, int num_philos)
{
    int i = 0;

    while (i < num_philos)
    {
        pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
        i++;
    }
}

void join_philos(t_philo *philos, int num_philos)
{
    int i = 0;

    while (i < num_philos)
    {
        pthread_join(philos[i].thread, NULL);
        i++;
    }
}
