/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:19:02 by olardeux          #+#    #+#             */
/*   Updated: 2024/08/09 10:27:23 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->lock);
	if (get_time() - philo->last_meal > philo->data_ptr->time_to_die
		&& philo->last_meal != 0)
	{
		if (philo->is_eating)
			return (pthread_mutex_unlock(&philo->data_ptr->lock), 1);
		message(DEAD, philo);
		philo->data_ptr->philo_is_dead = 1;
		pthread_mutex_unlock(&philo->data_ptr->lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data_ptr->lock);
	return (1);
}

int	check_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->lock);
	if (philo->nb_eat == philo->data_ptr->nb_eat && !philo->finished)
	{
		philo->data_ptr->finished++;
		philo->finished = 1;
	}
	if (philo->data_ptr->finished == philo->data_ptr->nb_philo)
		return (pthread_mutex_unlock(&philo->data_ptr->lock), 0);
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
				if (!check_eat(&data->philo[i]))
				{
					message(FINISHED, &data->philo[i]);
					return ;
				}
			}
			i++;
			usleep(10);
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
		if (!philo_check(philo))
			break ;
		message(THINK, philo);
		if (philo->data_ptr->time_to_eat >= philo->data_ptr->time_to_sleep)
			usleep((philo->data_ptr->time_to_eat
					- philo->data_ptr->time_to_sleep + 1) * 1000);
	}
	return (NULL);
}

void	init_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start = get_time();
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &routine,
				&data->philo[i]))
			return (join_threads_error(data, i - 1), (void)printf(ERR_THREAD));
		if ((i + 1) % 2 == 0)
			usleep(100);
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
