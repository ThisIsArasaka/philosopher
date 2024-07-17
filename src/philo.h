/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 06:33:08 by olardeux          #+#    #+#             */
/*   Updated: 2024/07/16 08:49:28 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK 3
# define DEAD 4

# define TAKE_FORK 0
# define DROP_FORK 1

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	struct s_data	*data_ptr;
	pthread_t		thread;
	pthread_mutex_t	lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long int		last_meal;
	int				is_dead;
	int				id;
	int				nb_eat;
}					t_philo;

typedef struct s_data
{
	struct s_philo	*philo;
	pthread_t		thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	lock;
	long int		start;
	int				philo_is_dead;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
}					t_data;

int					check_args(t_data *data, int argc, char **argv);
int					init(t_data *data);
int					init_threads(t_data *data);
void				free_all(t_data *data);
void				message(int MSG, t_philo *philo);
long int			get_time(void);
int					philo_eat(t_philo *philo);
int					philo_sleep(t_philo *philo);

#endif