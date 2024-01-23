/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:49:31 by ftholoza          #+#    #+#             */
/*   Updated: 2024/01/09 00:30:50 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	control2(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) == 10)
		{
			if (ft_strncmp(argv[i], "2147483647", 10) > 0)
				return (0);
			printf("ok\n");
		}
		if (ft_strlen(argv[i]) == 11)
		{
			if (argv[i][0] != '-')
				return (0);
			if (ft_strncmp(argv[i], "-2147483648", 11) > 0)
				return (0);
			printf("ok\n");
		}
		if (ft_strlen(argv[i]) > 11)
			return (0);
		i++;
	}
	return (1);
}

static	int	control3(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	if (ft_atoi(argv[1]) == 1)
	{
		printf("%s 1 died\n", argv[2]);
		return (0);
	}
	return (1);
}

int	control(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("ERROR !\n");
		printf("./philos nb_philos time_to_die time_to_eat time_to_sleep");
		printf(" (OPTION) number_of_times_they_eat\n");
		return (0);
	}
	while (i < argc)
	{
		if (ft_isdigit(argv[i]))
			i++;
		else
		{
			printf("ERROR!\nbad arguments\n");
			return (0);
		}
	}
	if (!control2(argc, argv))
		return (0);
	if (!control3(argc, argv))
		return (0);
	return (1);
}
