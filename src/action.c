/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:30:53 by olardeux          #+#    #+#             */
/*   Updated: 2024/08/06 17:00:46 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(int MSG, t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->print);
	if (MSG == EAT)
		printf("\033[0;32m%ld\033[0m : \033[0;34m%d\033[0;0m is eating\n",
			get_time() - philo->data_ptr->start, philo->id + 1);
	else if (MSG == SLEEP)
		printf("\033[0;32m%ld\033[0m : \033[0;34m%d\033[0;0m is sleeping\n",
			get_time() - philo->data_ptr->start, philo->id + 1);
	else if (MSG == THINK)
		printf("\033[0;32m%ld\033[0m : \033[0;34m%d\033[0;0m is thinking\n",
			get_time() - philo->data_ptr->start, philo->id + 1);
	else if (MSG == FORK)
		printf("\033[0;32m%ld\033[0m : \033[0;34m%d\033[0;0m has taken a fork\n",
			get_time() - philo->data_ptr->start, philo->id + 1);
	else if (MSG == DEAD)
		printf("\033[0;32m%ld\033[0m : \033[0;34m%d\033[0;0m \033[0;31m died\n\033[0;0m",
			get_time() - philo->data_ptr->start, philo->id + 1);
	else if (MSG == FINISHED)
		printf("\033[0;33m%d philo have eaten %d times\n\033[0;0m",
			philo->data_ptr->nb_philo, philo->data_ptr->nb_eat);
	pthread_mutex_unlock(&philo->data_ptr->print);
}

int	philo_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->lock);
	usleep(10);
	if (philo->data_ptr->philo_is_dead
		|| philo->data_ptr->finished == philo->data_ptr->nb_philo)
	{
		pthread_mutex_unlock(&philo->data_ptr->lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data_ptr->lock);
	return (1);
}

int	lock_fork(t_philo *philo)
{
	if ((philo->id + 1) % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		if (!philo_check(philo))
			return (pthread_mutex_unlock(philo->left_fork), 0);
		message(FORK, philo);
		pthread_mutex_lock(philo->right_fork);
		if (!philo_check(philo))
			return (forks_action(philo, DROP_FORK), 0);
		message(FORK, philo);
		return (1);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (!philo_check(philo))
			return (pthread_mutex_unlock(philo->right_fork), 0);
		message(FORK, philo);
		pthread_mutex_lock(philo->left_fork);
		if (!philo_check(philo))
			return (forks_action(philo, DROP_FORK), 0);
		message(FORK, philo);
		return (1);
	}
}

void	drop_forks(t_philo *philo)
{
	if ((philo->id + 1) % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

int	forks_action(t_philo *philo, int ACTION)
{
	if (ACTION == TAKE_FORK)
	{
		if (!lock_fork(philo))
			return (0);
		pthread_mutex_lock(&philo->data_ptr->lock);
		philo->is_eating = 1;
		pthread_mutex_unlock(&philo->data_ptr->lock);
	}
	else if (ACTION == DROP_FORK)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	return (1);
}
