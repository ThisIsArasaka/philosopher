/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 06:20:03 by olardeux          #+#    #+#             */
/*   Updated: 2024/07/15 19:43:09 by olardeux         ###   ########.fr       */
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
	if (!init_threads(&data))
		return (0);
	free_all(&data);
}