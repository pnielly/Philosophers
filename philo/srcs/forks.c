/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:55:43 by pnielly           #+#    #+#             */
/*   Updated: 2021/07/22 16:27:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
** If the total of philo is odd,
** Then you need to set up 3 lunch services per round
** One for odds, one for even and one for the last philo.
**/

void	take_forks_odd_total(t_philo *philo)
{
	if (philo->id != philo->data->nb)
	{
		if ((philo->id % 2) && !philo->rounds)
			usleep(philo->data->tteat * 1000 + 50);
		pthread_mutex_lock(&philo->data->m_forks[philo->id]);
		ft_log(philo, RIGHT_FORK, 0);
		pthread_mutex_lock(&philo->data->m_forks[philo->id - 1]);
		ft_log(philo, LEFT_FORK, 0);
	}
	else
	{
		if (!philo->rounds)
			usleep(philo->data->tteat * 500);
		pthread_mutex_lock(&philo->data->m_forks[0]);
		ft_log(philo, RIGHT_FORK, 0);
		pthread_mutex_lock(&philo->data->m_forks[philo->id - 1]);
		ft_log(philo, LEFT_FORK, 0);
	}
}

/**
** If the total of philo is even,
** Then you just need to set up 2 lunch services per round
**/

void	take_forks_even_total(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->data->m_forks[philo->id]);
		ft_log(philo, RIGHT_FORK, 0);
		pthread_mutex_lock(&philo->data->m_forks[philo->id - 1]);
		ft_log(philo, LEFT_FORK, 0);
	}
	else
	{
		if (!philo->rounds)
			usleep(philo->data->tteat * 999);
		if (philo->id != philo->data->nb)
			pthread_mutex_lock(&philo->data->m_forks[philo->id]);
		else
			pthread_mutex_lock(&philo->data->m_forks[0]);
		ft_log(philo, RIGHT_FORK, 0);
		pthread_mutex_lock(&philo->data->m_forks[philo->id - 1]);
		ft_log(philo, LEFT_FORK, 0);
	}
}

/**
** one_philo() : if there is only one philo
** there is only one fork
** therefore he will die after "data->ttdie" ms.
**/

void	one_philo(t_philo *philo)
{
	ft_log(philo, RIGHT_FORK, 0);
	do_sleep(philo, philo->data->ttdie);
}

/**
** Checks if total nb of philos is even or odd.
** Redirects to right function.
**/

void	take_forks(t_philo *philo)
{
	if (philo->data->nb == 1)
		one_philo(philo);
	else if (philo->data->nb % 2)
		take_forks_odd_total(philo);
	else
		take_forks_even_total(philo);
}

/**
** Dropping forks (unlocking mutexes)
**/

void	drop_forks(t_philo *philo)
{
	if (philo->data->nb == 1)
		return ;
	pthread_mutex_unlock(&philo->data->m_forks[philo->id - 1]);
	ft_log(philo, LEFT_FORK_DROP, 0);
	if (philo->id != philo->data->nb)
		pthread_mutex_unlock(&philo->data->m_forks[philo->id]);
	else
		pthread_mutex_unlock(&philo->data->m_forks[0]);
	ft_log(philo, RIGHT_FORK_DROP, 0);
}
