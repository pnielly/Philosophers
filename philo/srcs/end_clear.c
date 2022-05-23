/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:38:46 by pnielly           #+#    #+#             */
/*   Updated: 2021/07/19 20:54:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	end_clear(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->m_log);
	pthread_mutex_destroy(&data->m_kia);
	if (data->philos)
		free(data->philos);
	if (data->m_forks)
	{
		i = -1;
		while (++i < data->nb)
			pthread_mutex_destroy(&data->m_forks[i]);
		free(data->m_forks);
	}
	printf("End of the simulation.\n");
	return (0);
}
