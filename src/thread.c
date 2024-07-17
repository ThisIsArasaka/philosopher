/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:19:02 by olardeux          #+#    #+#             */
/*   Updated: 2024/07/16 09:29:12 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (get_time() - philo->last_meal > philo->data_ptr->time_to_die)
	{
		pthread_mutex_lock(&philo->data_ptr->lock);
		philo->data_ptr->philo_is_dead = 1;
		pthread_mutex_unlock(&philo->data_ptr->lock);
		philo->is_dead = 1;
		message(DEAD, philo);
		pthread_mutex_unlock(&philo->lock);
		return (0);
	}
	if (philo->nb_eat == philo->data_ptr->nb_eat)
	{
		philo->is_dead = 1;
		pthread_mutex_unlock(&philo->lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->lock);
	return (1);
}

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (is_dead(philo))
	{
		if (philo->is_dead)
			break ;
		pthread_mutex_lock(&philo->data_ptr->lock);
		if (philo->data_ptr->philo_is_dead)
		{
			pthread_mutex_lock(&philo->lock);
			philo->is_dead = 1;
			pthread_mutex_unlock(&philo->lock);
			pthread_mutex_unlock(&philo->data_ptr->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data_ptr->lock);
		usleep(100);
	}
	printf("Thread %d is dead\n", philo->id);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time();
	if (pthread_create(&philo->thread, NULL, &monitor, philo))
		return (printf("Error: Thread creation failed\n"), NULL);
	while (1)
	{
		if (!philo_eat(philo))
			break ;
		if (!philo_sleep(philo))
			break ;
		if (philo->nb_eat == philo->data_ptr->nb_eat)
			break ;
		message(THINK, philo);
	}
	pthread_join(philo->thread, NULL);
	printf("Thread %d joined\n", philo->id);
	return (NULL);
}

int	init_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start = get_time();
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &routine,
				&data->philo[i]))
			return (printf("Error: Thread creation failed\n"), free_all(data),
				0);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (printf("Error: %d Thread join failed\n", i), free_all(data),
				0);
		i++;
	}
	return (1);
}
