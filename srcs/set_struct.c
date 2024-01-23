/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:47:01 by ftholoza          #+#    #+#             */
/*   Updated: 2024/01/10 20:38:04 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	*number_of_times_they_ate(t_args *args)
{
	int	i;
	int	*res;

	i = 0;
	res = malloc(sizeof(int) * args->nb_philos);
	while (i < args->nb_philos)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}

static long	*timetheyeat(t_args *args)
{
	int		i;
	long	*res;

	i = 0;
	res = malloc(sizeof(long) * args->nb_philos);
	while (i < args->nb_philos)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}

static void	set_args2(t_args *res, int argc, char **argv)
{
	int	i;
	int	j;
	int	args[5];

	i = 1;
	j = 0;
	while (i < argc)
	{
		args[j] = ft_atoi(argv[i]);
		i++;
		j++;
	}
	if (argc == 5)
		res->incr = 0;
	else
		res->incr = 1;
	res->nb_philos = args[0];
	res->time_to_die = args[1];
	res->time_to_eat = args[2] * 1000;
	res->time_to_sleep = args[3] * 1000;
	if (argc == 6)
		res->number_of_times_they_eat = args[4];
	else
		res->number_of_times_they_eat = 1;
}

t_args	*set_args(int argc, char **argv)
{
	t_args			*res;
	pthread_mutex_t	print;
	pthread_mutex_t	death_control;
	pthread_mutex_t	eat[2];
	int				i;

	i = 0;
	res = malloc(sizeof(*res) * 1);
	if (!res)
		return (NULL);
	pthread_mutex_init(&print, NULL);
	pthread_mutex_init(&death_control, NULL);
	pthread_mutex_init(&eat[0], NULL);
	pthread_mutex_init(&eat[1], NULL);
	res->eat = eat[0];
	res->eat2 = eat[1];
	res->death_control = death_control;
	res->print = print;
	set_args2(res, argc, argv);
	res->number_of_times_they_ate = number_of_times_they_ate(res);
	res->timetheyeat = timetheyeat(res);
	res->dead_count = 0;
	return (res);
}

t_philo	*set_philo(t_args *args, pthread_mutex_t *forks, double start, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(*philo) * 1);
	philo->eat_count = 0;
	philo->r_fork = &forks[i];
	philo->start = start;
	if (i == 0)
		philo->l_fork = &forks[args->nb_philos - 1];
	else
		philo->l_fork = &forks[i - 1];
	philo->args = args;
	philo->id = i;
	return (philo);
}
