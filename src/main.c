/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 06:20:03 by olardeux          #+#    #+#             */
/*   Updated: 2024/07/21 14:29:34 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data data;

	if (!check_args(&data, argc, argv))
		return (0);
	if (!init(&data))
		return (0);
	init_threads(&data);
	free_all(&data);
	destroy_mutex(&data);
	return (0);
}