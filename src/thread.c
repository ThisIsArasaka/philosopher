/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:19:02 by olardeux          #+#    #+#             */
/*   Updated: 2024/07/21 15:20:55 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->lock);
	usleep(10);
	if (philo->last_meal + philo->data_ptr->time_to_die < get_time())
	{
		printf("%d died with %ld\n", philo->id, get_time() - philo->last_meal);
		message(DEAD, philo);
		philo->data_ptr->philo_is_dead = 1;
		pthread_mutex_unlock(&philo->data_ptr->lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data_ptr->lock);
	return (1);
}

void	monitor(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (!is_dead(&data->philo[i]))
				return ;
			if (data->nb_eat > 0)
			{
				pthread_mutex_lock(&data->lock);
				usleep(10);
				if (data->philo[i].nb_eat == data->nb_eat)
					data->finished++;
				if (data->finished == data->nb_philo)
				{
					message(FINISHED, &data->philo[i]);
					pthread_mutex_unlock(&data->lock);
					return ;
				}
				pthread_mutex_unlock(&data->lock);
			}
			i++;
		}
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data_ptr->lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data_ptr->lock);
	while (1)
	{
		if (!philo_eat(philo))
			break ;
		if (!philo_sleep(philo))
			break ;
		pthread_mutex_lock(&philo->data_ptr->lock);
		usleep(10);
		if (philo->data_ptr->philo_is_dead
			|| philo->data_ptr->finished == philo->data_ptr->nb_philo)
		{
			pthread_mutex_unlock(&philo->data_ptr->lock);
			break ;
		}
		message(THINK, philo);
		pthread_mutex_unlock(&philo->data_ptr->lock);
	}
	return (NULL);
}

void	init_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start = get_time();
	printf("number of philo: %d\ntime to die: %d\ntime to eat: %d\n",
		data->nb_philo, data->time_to_die, data->time_to_eat);
	printf("time to sleep: %d\nnumber of eat: %d\n", data->time_to_sleep,
		data->nb_eat);
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &routine,
				&data->philo[i]))
			return ((void)printf(ERR_THREAD));
		i++;
	}
	if (pthread_create(&data->monitor, NULL, (void *)monitor, data))
		return ((void)printf(ERR_THREAD));
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return ((void)printf(ERR_JOIN));
		i++;
	}
	if (pthread_join(data->monitor, NULL))
		return ((void)printf(ERR_JOIN));
}
