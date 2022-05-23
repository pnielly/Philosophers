/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_more.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <pnielly@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 21:51:12 by user42            #+#    #+#             */
/*   Updated: 2021/07/21 12:45:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
** will_die() : checks if the philo will die during next activity
** and informs next death time.
**/

static int	will_die(t_philo *philo, int duration, char *action)
{
	long long int	time;
	long long int	will_die;
	int				rounds;

	rounds = philo->rounds;
	if (!ft_strcmp(action, LEFT_FORK_DROP)
		|| !ft_strcmp(action, RIGHT_FORK_DROP))
		rounds++;
	time = get_time();
	will_die = philo->data->ttdie - (time - philo->last_meal) - duration;
	printf("Philo %s%d%s will die in %s%lld%s ms.",
		CYAN, philo->id, NO_COLOR, RED, will_die, NO_COLOR);
	printf(" Has eaten %d time(s) already.\n", rounds);
	return (0);
}

/**
** Log : Displays <timestamp_in_ms> <who> <action>.
** Also checks if a philo is dead.
**/

int	ft_log(t_philo *philo, char *action, int duration)
{
	pthread_mutex_lock(&philo->data->m_log);
	if (philo->data->kia || !philo->data->philo_done)
	{
		usleep(1500);
		pthread_mutex_unlock(&philo->data->m_log);
		return (1);
	}
	if (action)
	{
		printf("%s%lld%s: ", YELLOW, get_time() - philo->start_time, NO_COLOR);
		printf("Philo %s#%d %s%s%s.\n",
			CYAN, philo->id, GREEN, action, NO_COLOR);
	}
	if (will_die(philo, duration, action))
		return (1);
	pthread_mutex_unlock(&philo->data->m_log);
	return (0);
}
