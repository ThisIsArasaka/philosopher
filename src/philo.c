/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:22:30 by olardeux          #+#    #+#             */
/*   Updated: 2024/08/08 15:20:54 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleep(t_philo *philo)
{
	if (!philo_check(philo))
		return (0);
	message(SLEEP, philo);
	usleep(philo->data_ptr->time_to_sleep * 1000);
	return (1);
}

int	philo_eat(t_philo *philo)
{
	if (!philo_check(philo))
		return (0);
	if (!forks_action(philo, TAKE_FORK))
		return (0);
	message(EAT, philo);
	pthread_mutex_lock(&philo->data_ptr->lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data_ptr->lock);
	usleep(philo->data_ptr->time_to_eat * 1000);
	pthread_mutex_lock(&philo->data_ptr->lock);
	philo->is_eating = 0;
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->data_ptr->lock);
	forks_action(philo, DROP_FORK);
	return (1);
}
