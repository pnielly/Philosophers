/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <pnielly@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 21:51:12 by user42            #+#    #+#             */
/*   Updated: 2021/07/20 16:50:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
** Log : Displays <timestamp_in_ms> <who> <action>.
** Also checks if a philo is dead.
**/

int	ft_log(t_philo *philo, char *action, int duration)
{
	(void)duration;
	pthread_mutex_lock(&philo->data->m_log);
	if (philo->data->kia || !philo->data->philo_done)
	{
		pthread_mutex_unlock(&philo->data->m_log);
		return (1);
	}
	if (action)
	{
		printf("%s%lld%s ", YELLOW, get_time() - philo->start_time, NO_COLOR);
		printf("%s%d %s%s%s.\n",
			CYAN, philo->id, GREEN, action, NO_COLOR);
	}
	pthread_mutex_unlock(&philo->data->m_log);
	return (0);
}
