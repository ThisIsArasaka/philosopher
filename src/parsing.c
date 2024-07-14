/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:15:12 by olardeux          #+#    #+#             */
/*   Updated: 2024/06/28 08:58:02 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	atoi_parting(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9' || res > INT_MAX)
			return (-1);
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

int	check_args(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (printf("Error: Wrong number of arguments\n"), 0);
	if (argc == 6)
	{
		data->nb_eat = atoi_parting(argv[5]);
		if (data->nb_eat < 0)
			return (printf("Error: Invalid Input\n"), 0);
	}
	data->nb_philo = atoi_parting(argv[1]);
	data->time_to_die = atoi_parting(argv[2]);
	data->time_to_eat = atoi_parting(argv[3]);
	data->time_to_sleep = atoi_parting(argv[4]);
	if (data->nb_philo < 1 || data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1)
		return (printf("Error: Invalid Input\n"), 0);
	return (1);
}
