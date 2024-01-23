/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:01:35 by ftholoza          #+#    #+#             */
/*   Updated: 2024/01/09 15:33:31 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	end_room(pthread_mutex_t *forks,
	pthread_t *th, t_args *args, pthread_t *sth)
{
	int	i;

	i = 0;
	pthread_join(sth[0], NULL);
	while (i < args->nb_philos)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	i = 0;
	while (i < args->nb_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&args->eat);
	pthread_mutex_destroy(&args->print);
	pthread_mutex_destroy(&args->death_control);
	free(args->number_of_times_they_ate);
	free(args->timetheyeat);
	free(forks);
	free(sth);
	free(args);
	free(th);
	return ;
}

void	cphilos(t_args *args, long start, pthread_t *th, pthread_t *sth)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * args->nb_philos);
	while (i < args->nb_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	pthread_create(&sth[0], NULL, sroutine, args);
	while (i < args->nb_philos)
	{
		philo = set_philo(args, forks, start, i);
		pthread_create(&th[i], NULL, routine, philo);
		i++;
	}
	end_room(forks, th, args, sth);
	return ;
}

int	main(int argc, char **argv)
{
	t_args			*args;
	pthread_t		*th;
	pthread_t		*sth;
	int				i;
	long			start;

	i = 0;
	start = ft_get_start();
	if (!control(argc, argv))
		return (0);
	args = set_args(argc, argv);
	args->start = start;
	th = malloc(sizeof(unsigned long) * (args->nb_philos));
	if (!th)
		return (0);
	sth = malloc(sizeof(pthread_t) * 1);
	if (!sth)
	{
		free(th);
		return (0);
	}
	i = 0;
	cphilos(args, start, th, sth);
	return (0);
}
