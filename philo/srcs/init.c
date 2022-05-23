/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:18:23 by pnielly           #+#    #+#             */
/*   Updated: 2021/07/20 23:29:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
** Init mutex : 
** m_log aims at letting log messages get displayed 
** one after another (not at the same time).
** m_kia (Killed In Action) aims at stopping
** the simulation as soon as one philo dies.
** m_forks aims at preventing cutlery (here forks) duplication. 
**/

int	ft_init_mutex(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->m_log, NULL);
	pthread_mutex_init(&data->m_kia, NULL);
	data->m_forks = (pthread_mutex_t *)malloc(
			sizeof(*(data->m_forks)) * data->nb);
	if (!(data->m_forks))
		return (display_error("MALLOC FAILED in ft_mutex_init (init.c)."));
	i = 0;
	while (i < data->nb)
		pthread_mutex_init(&data->m_forks[i++], NULL);
	return (0);
}

/**
** Init philos
**/

int	ft_init_philos(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal = get_time();
		data->philos[i].rounds = 0;
		data->philos[i].data = data;
		data->philos[i].start_time = get_time();
		data->philos[i].died_ago = 0;
	}
	return (0);
}

/**
** Init data
** When philo_done == 0 : means that all philos
** ate required amount of time
**/

int	ft_init(t_data *data, int ac, char **av)
{
	data->nb = ft_atoi(av[1]);
	data->ttdie = ft_atoi(av[2]);
	data->tteat = ft_atoi(av[3]);
	data->ttsleep = ft_atoi(av[4]);
	data->kia = 0;
	if (ac == 6)
		data->rounds = ft_atoi(av[5]);
	else
		data->rounds = -1;
	data->philo_done = data->nb;
	data->philos = (t_philo *)malloc(sizeof(*(data->philos)) * data->nb);
	if (!(data->philos))
		return (display_error("Malloc failed. See ft_init() (in main.c)"));
	return (ft_init_philos(data) + ft_init_mutex(data));
}
