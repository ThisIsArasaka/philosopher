/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 06:33:08 by olardeux          #+#    #+#             */
/*   Updated: 2024/08/08 15:33:19 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// message actions
# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK 3
# define DEAD 4
# define FINISHED 5

// fork actions
# define TAKE_FORK 0
# define DROP_FORK 1

// error messages
# define ERR_ARGS "Error: Wrong number of arguments\n"
# define ERR_INPUT "Error: Invalid Input\n"
# define ERR_MALLOC "Error: Malloc failed\n"
# define ERR_MUTEX "Error: Mutex init failed\n"
# define ERR_THREAD "Error: Thread init failed\n"
# define ERR_JOIN "Error: Thread join failed\n"
# define ERR_DESTROY "Error: Mutex destroy failed\n"

# define EAT_MSG "\033[0;32m%ld : \033[0;34m%d\033[0;0m is eating\n"
# define SLEEP_MSG "\033[0;32m%ld : \033[0;34m%d\033[0;0m is sleeping\n"
# define THINK_MSG "\033[0;32m%ld : \033[0;34m%d\033[0;0m is thinking\n"
# define FORK_MSG "\033[0;32m%ld : \033[0;34m%d\033[0;0m has taken a fork\n"
# define DEAD_MSG "\033[0;32m%ld : \033[0;34m%d\033[0;31m died\n\033[0;0m"
# define FINISHED_MSG "\033[0;33m%d philo have eaten %d times\n\033[0;0m"

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
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long int		last_meal;
	int				is_eating;
	int				id;
	int				nb_eat;
	int				finished;
}					t_philo;

typedef struct s_data
{
	struct s_philo	*philo;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	lock;
	long int		start;
	int				philo_is_dead;
	int				nb_philo;
	int				finished;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
}					t_data;

int					check_args(t_data *data, int argc, char **argv);
int					init(t_data *data);
void				init_threads(t_data *data);
void				free_all(t_data *data);
void				message(int MSG, t_philo *philo);
int					philo_eat(t_philo *philo);
int					philo_sleep(t_philo *philo);
int					philo_check(t_philo *philo);
void				destroy_mutex(t_data *data);
long				get_time(void);
int					philo_eat(t_philo *philo);
int					philo_sleep(t_philo *philo);
int					forks_action(t_philo *philo, int ACTION);
void				join_threads_error(t_data *data, int i);

#endif