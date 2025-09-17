/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:32:34 by alejaro2          #+#    #+#             */
/*   Updated: 2025/09/17 18:55:11 by alejaro2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi_safe(char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] != '\0')
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	return ((int)result);
}

int	validate_args(int argc, char **argv)
{
	int		i;

	if (argc < 5 || argc > 6)
		return (1);
	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int	parse_input(int argc, char **argv, t_data *data)
{
	data->num_philos = ft_atoi_safe(argv[1]);
	data->time_to_die = ft_atoi_safe(argv[2]);
	data->time_to_eat = ft_atoi_safe(argv[3]);
	data->time_to_sleep = ft_atoi_safe(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atoi_safe(argv[5]);
	else
		data->must_eat_count = -1;
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (1);
	if (argc == 6 && data->must_eat_count < 0)
		return (1);
	if (argc == 6 && data->must_eat_count == 0)
	{
		printf("All philosophers have already eaten 0 times.\n");
		exit(0);
	}
	return (0);
}
