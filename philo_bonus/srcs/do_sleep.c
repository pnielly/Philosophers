/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <pnielly@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 14:54:13 by user42            #+#    #+#             */
/*   Updated: 2021/07/22 11:45:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
** death_checker: self explanatory.
** if someone dies: kia = 1 and display message
** Note : KIA = KILLED IN ACTION
**/

int	death_checker(t_data *data, t_philo *philo)
{
	long long int	is_dead;

	is_dead = data->ttdie - (get_time() - philo->last_meal);
	sem_wait(data->kia_s);
	sem_wait(data->log_s);
	if (is_dead < 0)
	{
		usleep(1000);
		printf("%s%lld%s: ", YELLOW,
			get_time() - philo->start_time, NO_COLOR);
		printf("%sPhilo %d is dead %lld ms ago.%s\n", CYAN,
			philo->id, -is_dead, NO_COLOR);
		sem_post(data->log_s);
		sem_post(data->kia_s);
		return (1);
	}
	sem_post(data->log_s);
	sem_post(data->kia_s);
	return (0);
}

/**
** do_sleep() : makes the philo sleep during 5 ms max
** then checks if anyone died, then makes him sleep again, etc.
**/

int	do_sleep(t_philo *philo, long long int duration)
{
	int		will_die;
	int		nap;
	t_data	*data;

	data = philo->data;
	will_die = data->ttdie - (get_time() - philo->last_meal) - duration;
	if (will_die < 0)
		nap = duration + will_die + 5;
	else
		nap = duration;
	usleep(nap * 1000);
	data->kia = death_checker(data, philo);
	return (data->kia);
}
