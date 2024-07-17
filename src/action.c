/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:30:53 by olardeux          #+#    #+#             */
/*   Updated: 2024/07/16 09:26:13 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(int MSG, t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->print);
	if (MSG == EAT)
		printf("%ld %d is eating\n", get_time() - philo->data_ptr->start,
			philo->id + 1);
	else if (MSG == SLEEP)
		printf("%ld %d is sleeping\n", get_time() - philo->data_ptr->start,
			philo->id + 1);
	else if (MSG == THINK)
		printf("%ld %d is thinking\n", get_time() - philo->data_ptr->start,
			philo->id + 1);
	else if (MSG == FORK)
		printf("%ld %d has taken a fork\n", get_time() - philo->data_ptr->start,
			philo->id + 1);
	else if (MSG == DEAD)
		printf("%ld %d died\n", get_time() - philo->data_ptr->start, philo->id
			+ 1);
	pthread_mutex_unlock(&philo->data_ptr->print);
}

void	forks_action(t_philo *philo, int ACTION)
{
	if (ACTION == TAKE_FORK)
	{
		pthread_mutex_lock(philo->left_fork);
		message(FORK, philo);
		pthread_mutex_lock(philo->right_fork);
		message(FORK, philo);
	}
	else if (ACTION == DROP_FORK)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

int	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (philo->is_dead || philo->data_ptr->philo_is_dead)
		return (pthread_mutex_unlock(&philo->lock), 0);
	pthread_mutex_unlock(&philo->lock);
	message(SLEEP, philo);
	usleep(philo->data_ptr->time_to_sleep * 1000);
	return (1);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (philo->is_dead)
		return (pthread_mutex_unlock(&philo->lock), 0);
	forks_action(philo, TAKE_FORK);
	message(EAT, philo);
	usleep(philo->data_ptr->time_to_eat * 1000);
	philo->nb_eat++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->lock);
	forks_action(philo, DROP_FORK);
	return (1);
}