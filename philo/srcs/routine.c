/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <pnielly@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 13:08:45 by user42            #+#    #+#             */
/*   Updated: 2021/07/23 14:35:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
** Routine done : unlock the forks mutex
** If optional nb of rounds reached : print "Philo X is done eating".
**/

void	routine_done(t_philo *philo)
{
	philo->data->philo_done--;
	pthread_mutex_lock(&philo->data->m_kia);
	if (!philo->data->kia)
	{
		printf("%s%lld%s: ", YELLOW, get_time() - philo->start_time, NO_COLOR);
		printf("%sPhilo %d is done eating !%s\n", CYAN, philo->id, NO_COLOR);
	}
	pthread_mutex_unlock(&philo->data->m_kia);
	return ;
}

/**
** Routine : The philosopher eats, then sleeps, then thinks.
** Note : If there is no max round, the while loop is an infinite loop
** (because data->rounds is initialized at -1 and philo->rounds goes increasing)
**/

void	*routine(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	while (philo->rounds != philo->data->rounds && !philo->data->kia)
	{
		if (philo->rounds > 0)
		{
			ft_log(philo, SLEEP, philo->data->ttsleep);
			do_sleep(philo, philo->data->ttsleep);
			ft_log(philo, THINK, 0);
		}
		take_forks(philo);
		pthread_mutex_lock(&philo->data->m_kia);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->data->m_kia);
		ft_log(philo, EAT, philo->data->tteat);
		do_sleep(philo, philo->data->tteat);
		drop_forks(philo);
		philo->rounds++;
	}
	routine_done(philo);
	return (NULL);
}
