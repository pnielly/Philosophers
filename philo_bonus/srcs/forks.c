/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:55:43 by pnielly           #+#    #+#             */
/*   Updated: 2021/07/22 14:05:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
** If the total of philo is odd,
** Then you need to set up 3 lunch services per round
** One for odds, one for even and one for the last philo.
**/

int	take_forks(t_philo *philo)
{
	if (philo->data->nb == 1)
	{
		ft_log(philo, RIGHT_FORK, 0);
		if (do_sleep(philo, philo->data->ttdie))
			return (1);
	}
	sem_wait(philo->data->forks_s);
	philo->data->hold_forks++;
	ft_log(philo, RIGHT_FORK, 0);
	sem_wait(philo->data->forks_s);
	philo->data->hold_forks++;
	ft_log(philo, LEFT_FORK, 0);
	return (0);
}

/**
** Dropping forks (unlocking mutexes)
**/

void	drop_forks(t_philo *philo)
{
	if (philo->data->nb == 1)
		return ;
	sem_post(philo->data->forks_s);
	philo->data->hold_forks--;
	ft_log(philo, LEFT_FORK_DROP, 0);
	sem_post(philo->data->forks_s);
	philo->data->hold_forks--;
	ft_log(philo, RIGHT_FORK_DROP, 0);
}
