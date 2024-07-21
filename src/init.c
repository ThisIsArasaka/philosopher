/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:52:32 by olardeux          #+#    #+#             */
/*   Updated: 2024/07/21 15:13:01 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(struct s_philo) * data->nb_philo);
	data->philo_is_dead = 0;
	data->finished = 0;
	if (!data->philo)
		return (printf(ERR_MALLOC), 0);
	while (i < data->nb_philo)
	{
		data->philo[i].id = i;
		data->philo[i].nb_eat = 0;
		data->philo[i].data_ptr = data;
		i++;
	}
	return (1);
}

static int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (printf(ERR_MALLOC), free(data->philo), 0);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (printf(ERR_MUTEX), free_all(data), 0);
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL))
		return (printf(ERR_MUTEX), free_all(data), 0);
	if (pthread_mutex_init(&data->lock, NULL))
		return (printf(ERR_MUTEX), free_all(data), 0);
	return (1);
}
static void	adress_fork(t_data *data)
{
	int	i;

	i = 1;
	while (i < data->nb_philo)
	{
		data->philo[i].left_fork = &data->forks[i - 1];
		data->philo[i].right_fork = &data->forks[i];
		i++;
	}
	data->philo[0].left_fork = &data->forks[data->nb_philo - 1];
	data->philo[0].right_fork = &data->forks[0];
}

int	init(t_data *data)
{
	if (!init_philo(data))
		return (0);
	if (!init_mutex(data))
		return (0);
	adress_fork(data);
	return (1);
}