/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:32:13 by alejaro2          #+#    #+#             */
/*   Updated: 2025/09/16 17:37:29 by alejaro2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_philos(t_philo *philos, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		usleep(100);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		monitor;

	memset(&data, 0, sizeof(t_data));
	if (validate_args(argc, argv) != 0 || init_data(&data) != 0)
		return (printf("Error: Invalid arguments\n"), 1);
	if (parse_input(argc, argv, &data) != 0)
		return (1);
	forks = init_forks_array(data.num_philos);
	if (!forks)
		return (printf("Error: Forks initialization failed\n"), 1);
	philos = init_philos_array(&data, forks);
	if (!philos)
		return (free(forks), printf("Error: Philos initialization failed\n"),
			1);
	start_philos(philos, data.num_philos);
	pthread_create(&monitor, NULL, monitor_routine, philos);
	pthread_join(monitor, NULL);
	join_philos(philos, data.num_philos);
	cleanup(philos, forks, &data);
	return (0);
}
