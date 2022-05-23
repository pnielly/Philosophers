/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 21:58:44 by pnielly           #+#    #+#             */
/*   Updated: 2021/07/21 19:09:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

/**
** Actions
**/

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define LEFT_FORK "has taken a fork"
# define RIGHT_FORK "has taken a fork"
# define LEFT_FORK_DROP "has dropped a fork"
# define RIGHT_FORK_DROP "has dropped a fork"

/**
** Colors
**/

# define BLACK "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"
# define NO_COLOR "\033[0;37m"

typedef struct s_philo
{
	pthread_t		thread_philo;
	int				id;
	long long int	last_meal;
	long long int	start_time;
	int				rounds;
	long long int	died_ago;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				nb;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				rounds;
	int				philo_done;
	int				kia;
	t_philo			*philos;
	pthread_t		thread_death;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_log;
	pthread_mutex_t	m_kia;
}					t_data;

int				ft_atoi(const char *str);
int				error_parsing(int ac, char **av);
int				display_error(char *error);
void			display_philo(t_philo *philo);
void			*routine(void *philo_v);
void			routine_done(t_philo *philo);
long long int	get_time(void);
int				ft_init(t_data *data, int ac, char **av);
int				end_clear(t_data *data);
int				ft_log(t_philo *philo, char *action, int duration);
void			take_forks(t_philo *philo);
void			drop_forks(t_philo *philo);
int				ft_abs(int a);
int				ft_strcmp(const char *s1, const char *s2);
void			do_sleep(t_philo *philo, long long int duration);

#endif
