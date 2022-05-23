/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <pnielly@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 13:08:45 by user42            #+#    #+#             */
/*   Updated: 2021/07/22 14:34:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
** separating_philos() : 
** even philos go first
** then odd philos
** then in case the total nb of philos is odd, the last one (alone)
**/

int	separating_philos(t_philo *philo, t_data *data)
{
	float	delay;

	if (philo->id == data->nb && !philo->rounds && (data->nb % 2)
		&& data->nb != 1)
		delay = 2;
	else if ((philo->id % 2) && !philo->rounds)
		delay = 0.9;
	else
		delay = 0;
	if (do_sleep(philo, data->tteat * delay))
		return (1);
	return (0);
}

/**
** sleep_n_think() : only for rounds > 0 so that
** I can put it in the beginning of the loop
** so that when last meal is eaten, loop is left directly.
**/

int	sleep_n_think(t_philo *philo, t_data *data)
{
	int	ret;

	if (philo->rounds > 0)
	{
		ft_log(philo, SLEEP, data->ttsleep);
		if (do_sleep(philo, data->ttsleep))
			return (1);
		ft_log(philo, THINK, 0);
		if (data->nb % 2)
			ret = do_sleep(philo,
					ft_abs(data->tteat - data->ttsleep) + data->tteat);
		else
			ret = do_sleep(philo,
					ft_max(ft_abs(data->tteat - data->ttsleep), 0));
		if (ret)
			return (ret);
	}
	return (0);
}

/**
** Routine done : unlock the forks mutex
** If optional nb of rounds reached : print "Philo X is done eating".
**/

void	routine_done(t_philo *philo)
{
	int	i;

	philo->data->philo_done--;
	i = -1;
	while (++i < philo->data->hold_forks)
		sem_post(philo->data->forks_s);
	sem_wait(philo->data->kia_s);
	sem_wait(philo->data->log_s);
	if (!philo->data->kia)
	{
		printf("%s%lld%s: ", YELLOW, get_time() - philo->start_time, NO_COLOR);
		printf("%sPhilo %d is done eating !%s\n", CYAN, philo->id, NO_COLOR);
	}
	sem_post(philo->data->log_s);
	sem_post(philo->data->kia_s);
	return ;
}

/**
** Routine : The philosopher eats, then sleeps, then thinks.
** Note : If there is no max round, the while loop is an infinite loop
** (because data->rounds is initialized at -1 and philo->rounds goes increasing)
**/

void	*routine(t_philo *philo)
{
	while (philo->rounds != philo->data->rounds && !philo->data->kia)
	{
		if (sleep_n_think(philo, philo->data))
			break ;
		if (separating_philos(philo, philo->data))
			break ;
		if (take_forks(philo))
			break ;
		sem_wait(philo->data->kia_s);
		philo->last_meal = get_time();
		sem_post(philo->data->kia_s);
		ft_log(philo, EAT, philo->data->tteat);
		if (do_sleep(philo, philo->data->tteat))
			break ;
		drop_forks(philo);
		philo->rounds++;
	}
	routine_done(philo);
	return (NULL);
}
