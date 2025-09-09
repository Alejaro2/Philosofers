#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>


typedef struct s_data
{
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat_count;
    long start_time;
    int someone_died;
    pthread_mutex_t print_mutex;
    pthread_mutex_t state_mutex;
}   t_data;

typedef struct s_philo
{
    int id;
    int meals_eaten;
    long last_meal_time;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data *data;
}   t_philo;

// parse.c
int     parse_args(int argc, char **argv, t_data *data);
int     ft_atoi_safe(char *str);
int     is_number(char *str);
void join_philos(t_philo *philos, int num_philos);

// init.c
pthread_mutex_t *init_forks_array(int num_philos);
t_philo *init_philos_array(t_data *data, pthread_mutex_t *forks);
int init_data(t_data *data);
void start_philos(t_philo *philos, int num_philos);

//time.c
long get_time_ms(void);
long elapsed_ms(long start_time);

//routine.c 
void *philo_routine(void *arg);

//monitor.c 
void *monitor_routine(void *arg);
int	simulation_ended(t_data *data);

//clean.c
void cleanup(t_philo *philos, pthread_mutex_t *forks, t_data *data);
#endif
