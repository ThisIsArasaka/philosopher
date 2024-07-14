/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 06:20:03 by olardeux          #+#    #+#             */
/*   Updated: 2024/06/28 11:47:09 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data data;

	if (!check_args(&data, argc, argv))
		return (0);
	printf("%d\n%d\n%d\n%d\n", data.nb_philo, data.time_to_die,
		data.time_to_eat, data.time_to_sleep);
	if (argc == 6)
		printf("%d\n", data.nb_eat);
}