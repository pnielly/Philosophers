/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <pnielly@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 14:54:13 by user42            #+#    #+#             */
/*   Updated: 2021/07/23 14:35:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long int	ft_min(long long int a, long long int b)
{
	if (a > b)
		return (b);
	return (a);
}

/**
** death_checker: self explanatory.
** if someone dies: kia = 1 and display message
** Note : KIA = KILLED IN ACTION
**/

int	death_checker(t_data *data, int i)
{
	long long int	is_dead;

	while (++i < data->nb)
	{
		is_dead = data->ttdie - (get_time() - data->philos[i].last_meal);
		pthread_mutex_lock(&data->m_kia);
		pthread_mutex_lock(&data->m_log);
		if (is_dead <= 0 && !data->kia)
		{
			printf("%s%lld%s: ", YELLOW,
				get_time() - data->philos[i].start_time, NO_COLOR);
			printf("%sPhilo %d is dead %lld ms ago.%s\n", CYAN,
				data->philos[i].id, -is_dead, NO_COLOR);
			data->kia = 1;
			pthread_mutex_unlock(&data->m_kia);
			pthread_mutex_unlock(&data->m_log);
			return (1);
		}
		pthread_mutex_unlock(&data->m_kia);
		pthread_mutex_unlock(&data->m_log);
		if (data->kia)
			return (1);
	}
	return (0);
}

/**
** remain_sleep() : computes the remaining time to sleep
**/

long long int	remain_sleep(long long int duration, long long int start_time)
{
	return (duration - (get_time() - start_time));
}

/**
** do_sleep() : makes the philo sleep during 5 ms max
** then checks if anyone died, then makes him sleep again, etc.
**/

void	do_sleep(t_philo *philo, long long int duration)
{
	int				micro_nap;
	long long int	start_time;

	start_time = get_time();
	while (!death_checker(philo->data, -1)
		&& remain_sleep(duration, start_time) > 0)
	{
		micro_nap = ft_min(5000, remain_sleep(duration, start_time));
		usleep(micro_nap);
	}
}
