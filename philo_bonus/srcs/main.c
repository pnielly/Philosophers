/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 14:49:30 by pnielly           #+#    #+#             */
/*   Updated: 2021/07/22 14:04:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
** ft_kill_everyone() : One death has been detected.
** Closing the program, all other philosophers stop.
**/

int	ft_stop_everyone(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb)
		kill(data->philos[i].pid, SIGINT);
	return (0);
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
	int		status;

	status = 0;
	i = -1;
	while (++i < data->nb)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid < 0)
			return (NULL);
		if (data->philos[i].pid == 0)
		{
			routine(&data->philos[i]);
			if (data->kia)
				exit(1);
			exit(0);
		}
	}
	while (!status)
		if (waitpid(0, &status, 0) < 0)
			return (NULL);
	if (status)
		ft_stop_everyone(data);
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
		printf("Normal usage :\n\t\t %s./philo_one %s#_of_philosophers%s ",
			CYAN, GREEN, NO_COLOR);
		printf("%stime_to_die %stime_to_eat %stime_to_sleep%s ",
			YELLOW, RED, PURPLE, NO_COLOR);
		printf("%s[#_times_each_philosopher_must_eat]%s",
			WHITE, NO_COLOR);
		return (0);
	}
	if (ft_init(&data, ac, av))
		return (end_clear(&data) && display_error("INIT FAILED"));
	ft_control(&data);
	return (end_clear(&data));
}
