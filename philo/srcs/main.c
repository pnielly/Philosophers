/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 14:49:30 by pnielly           #+#    #+#             */
/*   Updated: 2021/07/20 17:01:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
** Displays message that eveyone ate the right number of times
** before closing the simulation.
**/

void	*everyone_ate(t_data *data)
{
	printf("%s%lld%s: ", YELLOW,
		get_time() - data->philos[0].start_time, NO_COLOR);
	printf("%sEveyone ate %d times.%s\n", WHITE,
		data->rounds, NO_COLOR);
	return (NULL);
}

/**
** This function will launch each philo's thread (called routine)
** and join them.
** If everyone ate the required amount of rounds, it displays 
** a relevant message.
**/

void	*ft_control(t_data *data)
{
	int		i;
	void	*philo_v;

	i = -1;
	while (++i < data->nb)
	{
		philo_v = (void *)(&data->philos[i]);
		if (pthread_create(&data->philos[i].thread_philo,
				NULL, routine, philo_v))
			return (NULL);
	}
	i = -1;
	while (++i < data->nb)
	{
		if (pthread_join(data->philos[i].thread_philo, NULL))
			return (NULL);
	}
	if (!data->kia)
		everyone_ate(data);
	return (NULL);
}

/**
** MAIN : Error parsing then init then start threads (with ft_control())
**/

int	main(int ac, char **av)
{
	t_data		data;

	if (error_parsing(ac, av))
	{
		printf("Normal usage :\n\t\t %s./[binary] %s#_of_philosophers%s ",
			CYAN, GREEN, NO_COLOR);
		printf("%stime_to_die %stime_to_eat %stime_to_sleep%s ",
			YELLOW, RED, PURPLE, NO_COLOR);
		printf("%s[#_times_each_philosopher_must_eat]%s\n",
			WHITE, NO_COLOR);
		return (0);
	}
	if (ft_init(&data, ac, av))
		return (end_clear(&data) && display_error("INIT FAILED"));
	ft_control(&data);
	return (end_clear(&data));
}
