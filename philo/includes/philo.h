/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:31:15 by alejaro2          #+#    #+#             */
/*   Updated: 2025/09/16 17:31:23 by alejaro2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long			start_time;
	int				someone_died;
	int				philos_done_eating;

	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	done_eating_mutex;

	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}					t_philo;

// parse.c
int					validate_args(int argc, char **argv);
int					ft_atoi_safe(char *str);
int					is_number(char *str);
int					parse_input(int argc, char **argv, t_data *data);

// init.c
int					init_data(t_data *data);
pthread_mutex_t		*init_forks_array(int num_philos);
t_philo				*init_philos_array(t_data *data, pthread_mutex_t *forks);
void				start_philos(t_philo *philos, int num_philos);
void				join_philos(t_philo *philos, int num_philos);
void				print_status(t_philo *philo, char *status);

// time.c
long				get_time_ms(void);
long				elapsed_ms(long start_time);

// routine.c
void				*philo_routine(void *arg);

// monitor.c
void				*monitor_routine(void *arg);
int					simulation_ended(t_data *data);

// clean.c
void				cleanup(t_philo *philos, pthread_mutex_t *forks,
						t_data *data);

#endif