/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:18:23 by pnielly           #+#    #+#             */
/*   Updated: 2021/07/22 11:43:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
** Init sem : 
**/

int	ft_init_sem(t_data *data)
{
	sem_unlink(FORKS);
	data->forks_s = sem_open(FORKS, O_CREAT, 0644, data->nb);
	sem_unlink(LOG);
	data->log_s = sem_open(LOG, O_CREAT, 0644, 1);
	sem_unlink(KIA);
	data->kia_s = sem_open(KIA, O_CREAT, 0644, 1);
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
	data->hold_forks = 0;
	if (ac == 6)
		data->rounds = ft_atoi(av[5]);
	else
		data->rounds = -1;
	data->philo_done = data->nb;
	data->philos = (t_philo *)malloc(sizeof(*(data->philos)) * (data->nb));
	if (!(data->philos))
		return (display_error("Malloc failed. See ft_init() (in main.c)"));
	return (ft_init_philos(data) + ft_init_sem(data));
}
