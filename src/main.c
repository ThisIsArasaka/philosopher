/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 06:20:03 by olardeux          #+#    #+#             */
/*   Updated: 2024/07/25 00:04:01 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_data *data)
{
	data->start = get_time();
	pthread_mutex_lock(&data->forks[0]);
	message(FORK, &data->philo[0]);
	usleep(data->time_to_die * 1000);
	message(DEAD, &data->philo[0]);
	pthread_mutex_unlock(&data->forks[0]);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!check_args(&data, argc, argv))
		return (0);
	if (!init(&data))
		return (0);
	if (data.nb_philo == 1)
		one_philo(&data);
	else
		init_threads(&data);
	free_all(&data);
	// destroy_mutex(&data);
	return (0);
}
