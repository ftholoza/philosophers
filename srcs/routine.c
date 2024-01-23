/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:49:14 by ftholoza          #+#    #+#             */
/*   Updated: 2024/01/11 19:37:28 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat_extention(t_philo *philo, long time)
{
	pthread_mutex_lock(&philo->args->eat);
	philo->args->timetheyeat[philo->id] = time;
	pthread_mutex_unlock(&philo->args->eat);
	usleep(philo->args->time_to_eat);
	philo->eat_count += philo->args->incr;
	pthread_mutex_lock(&philo->args->eat2);
	philo->args->number_of_times_they_ate[philo->id] = philo->eat_count;
	pthread_mutex_unlock(&philo->args->eat2);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

int	check_death(t_args	*args, int i)
{
	pthread_mutex_lock(&args->eat2);
	if (args->number_of_times_they_ate[i] == args->number_of_times_they_eat)
	{
		pthread_mutex_unlock(&args->eat2);
		return (1);
	}
	pthread_mutex_unlock(&args->eat2);
	pthread_mutex_lock(&args->eat);
	if (ft_gettime(args->start) - args->timetheyeat[i]
		> args->time_to_die)
	{
		pthread_mutex_unlock(&args->eat);
		pthread_mutex_lock(&args->print);
		pthread_mutex_lock(&args->death_control);
		args->dead_count = 1;
		pthread_mutex_unlock(&args->death_control);
		pthread_mutex_unlock(&args->print);
		printf("%ld %d died\n", ft_gettime(args->start), i + 1);
		return (0);
	}
	pthread_mutex_unlock(&args->eat);
	return (1);
}

int	check_eat(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philos)
	{
		pthread_mutex_lock(&args->eat2);
		if (args->number_of_times_they_ate[i] < args->number_of_times_they_eat)
		{
			pthread_mutex_unlock(&args->eat2);
			return (1);
		}
		pthread_mutex_unlock(&args->eat2);
		i++;
	}
	return (0);
}

void	*sroutine(void	*arg)
{
	t_args	*args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	args = ((t_args *)arg);
	while (check_eat(args))
	{
		while (i < args->nb_philos)
		{
			if (!check_death(args, i))
				return (NULL);
			i++;
			if (!check_eat(args))
				return (NULL);
		}
		i = 0;
	}
	return (NULL);
}

void	*routine(void *philo)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = ((t_philo *)philo);
	philos->th = pthread_self();
	if ((philos->id + 1) % 2 != 0)
		usleep(philos->args->time_to_eat / 2);
	while (philos->eat_count < philos->args->number_of_times_they_eat)
	{
		if (!take_r_fork(philos))
			return (NULL);
		if (!take_l_fork(philos))
			return (NULL);
		if (!eat(philos))
			return (NULL);
		if (!sleeping(philos))
			return (NULL);
		if (!thinking(philos))
			return (NULL);
	}
	return (NULL);
}
