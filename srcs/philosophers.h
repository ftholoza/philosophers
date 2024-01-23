/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:02:11 by ftholoza          #+#    #+#             */
/*   Updated: 2024/01/11 15:45:03 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct t_args
{
	pthread_mutex_t	print;
	pthread_mutex_t	death_control;
	pthread_mutex_t	eat;
	pthread_mutex_t	eat2;
	int				nb_philos;
	int				incr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_of_times_they_eat;
	int				*number_of_times_they_ate;
	int				dead_count;
	long			*timetheyeat;
	long			start;
}	t_args;

typedef struct t_philo
{
	long			start;
	int				id;
	int				eat_count;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_t		th;
	pthread_t		*ths;
	t_args			*args;
}	t_philo;

int		ft_isdigit(char *str);
int		ft_atoi(const char *nptr);
long	ft_gettime(long start);
long	ft_get_start(void);
void	*routine(void	*philo);
void	*sroutine(void	*arg);
int		take_r_fork(t_philo *philo);
int		take_l_fork(t_philo *philo);
int		take_l_fork2(t_philo *philo);
int		take_r_fork2(t_philo *philo);
int		eat(t_philo *philo);
int		sleeping(t_philo *philo);
t_philo	*set_philo(t_args *args, pthread_mutex_t *forks, double start, int i);
t_args	*set_args(int argc, char **argv);
int		control(int argc, char **argv);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		thinking(t_philo *philo);
int		check_death(t_args	*args, int i);
void	ft_usleep(t_philo *philo, long time);
void	eat_extention(t_philo *philo, long time);

#endif