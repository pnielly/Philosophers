/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 15:02:53 by pnielly           #+#    #+#             */
/*   Updated: 2021/07/16 12:41:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_nb(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if ((s[i] < 48 || s[i] > 57) && s[i] != '+' && s[i] != '-')
			return (0);
	}
	return (1);
}

int	error_parsing(int ac, char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (!is_nb(av[i]))
			return (display_error("Only numbers are allowed."));
	}
	if (ac < 5 || ac > 6)
		return (display_error("There should be 5 or 6 arguments"));
	if (ft_atoi(av[1]) < 1)
		return (display_error("There can't be less than 1 philosopher."));
	if (ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0)
		return (display_error("Negative durations are not allowed."));
	if (ac == 6 && !ft_atoi(av[5]))
		return (display_error("Round 0 : End of the simulation."));
	if (ac == 6 && ft_atoi(av[5]) < 0)
		return (display_error("There can't be less than 0 rounds."));
	return (0);
}

int	display_error(char *error)
{
	printf("%s%s%s\n", RED, error, NO_COLOR);
	return (1);
}
