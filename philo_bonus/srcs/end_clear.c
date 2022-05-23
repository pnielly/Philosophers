/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:38:46 by pnielly           #+#    #+#             */
/*   Updated: 2021/07/21 17:54:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	end_clear(t_data *data)
{
	sem_close(data->forks_s);
	sem_close(data->log_s);
	sem_close(data->kia_s);
	sem_unlink(FORKS);
	sem_unlink(LOG);
	sem_unlink(KIA);
	if (data->philos)
		free(data->philos);
	printf("End of the simulation.\n");
	return (0);
}
