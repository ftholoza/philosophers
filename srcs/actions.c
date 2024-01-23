/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:59:04 by ftholoza          #+#    #+#             */
/*   Updated: 2024/01/11 19:37:40 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_r_fork(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(philo->r_fork);
	time = ft_gettime(philo->start);
	pthread_mutex_lock(&philo->args->print);
	pthread_mutex_lock(&philo->args->death_control);
	if (philo->args->dead_count == 0)
	{
		pthread_mutex_unlock(&philo->args->death_control);
		printf("%ld %d has taken a fork\n", (long)time, philo->id + 1);
		pthread_mutex_unlock(&philo->args->print);
	}
	else
	{
		pthread_mutex_unlock(&philo->args->death_control);
		pthread_mutex_unlock(&philo->args->print);
		pthread_mutex_unlock(philo->r_fork);
		free(philo);
		return (0);
	}
	return (1);
}

int	take_l_fork(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(philo->l_fork);
	time = ft_gettime(philo->start);
	pthread_mutex_lock(&philo->args->print);
	pthread_mutex_lock(&philo->args->death_control);
	if (philo->args->dead_count == 0)
	{
		pthread_mutex_unlock(&philo->args->death_control);
		printf("%ld %d has taken a fork\n", (long)time, philo->id + 1);
		pthread_mutex_unlock(&philo->args->print);
	}
	else
	{
		pthread_mutex_unlock(&philo->args->death_control);
		pthread_mutex_unlock(&philo->args->print);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		free(philo);
		return (0);
	}
	return (1);
}

int	eat(t_philo *philo)
{
	long	time;

	time = ft_gettime(philo->start);
	pthread_mutex_lock(&philo->args->print);
	pthread_mutex_lock(&philo->args->death_control);
	if (philo->args->dead_count == 0)
	{
		pthread_mutex_unlock(&philo->args->death_control);
		printf("%ld %d is eating\n", (long)time, philo->id + 1);
		pthread_mutex_unlock(&philo->args->print);
	}
	else
	{
		pthread_mutex_unlock(&philo->args->death_control);
		pthread_mutex_unlock(&philo->args->print);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		free(philo);
		return (0);
	}
	eat_extention(philo, time);
	return (1);
}

int	sleeping(t_philo *philo)
{
	long	time;

	time = ft_gettime(philo->start);
	pthread_mutex_lock(&philo->args->print);
	pthread_mutex_lock(&philo->args->death_control);
	if (philo->args->dead_count == 0)
	{
		pthread_mutex_unlock(&philo->args->death_control);
		printf("%ld %d is sleeping\n", (long)time, philo->id + 1);
		pthread_mutex_unlock(&philo->args->print);
	}
	else
	{
		pthread_mutex_unlock(&philo->args->death_control);
		pthread_mutex_unlock(&philo->args->print);
		free(philo);
		return (0);
	}
	usleep(philo->args->time_to_sleep);
	return (1);
}

int	thinking(t_philo *philo)
{
	long	time;

	time = ft_gettime(philo->start);
	pthread_mutex_lock(&philo->args->print);
	pthread_mutex_lock(&philo->args->death_control);
	if (philo->args->dead_count == 0)
	{
		pthread_mutex_unlock(&philo->args->death_control);
		printf("%ld %d is thinking\n", (long)time, philo->id + 1);
		pthread_mutex_unlock(&philo->args->print);
	}
	else
	{
		pthread_mutex_unlock(&philo->args->death_control);
		pthread_mutex_unlock(&philo->args->print);
		free(philo);
		return (0);
	}
	return (1);
}
