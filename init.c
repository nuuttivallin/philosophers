/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:49:19 by nvallin           #+#    #+#             */
/*   Updated: 2024/07/10 19:50:16 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_forks_and_such(t_info *info, int other_mutexes)
{
	int	i;

	i = 0;
	while (i < info->philos)
		pthread_mutex_destroy(&info->fork[i++]);
	if (other_mutexes > 0)
		pthread_mutex_destroy(&info->print);
	if (other_mutexes > 1)
		pthread_mutex_destroy(&info->stat_check);
	if (other_mutexes > 2)
	{
		i = 0;
		while (i < info->philos)
			pthread_mutex_destroy(&info->meal_time[i++]);
	}
	if (other_mutexes > 3)
		pthread_mutex_destroy(&info->full_check);
	if (other_mutexes > 4)
		pthread_mutex_destroy(&info->philo_lock);
	write(2, "Mutex initialization failed\n", 28);
}

int	ft_init_forks_and_such(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philos)
	{
		if (pthread_mutex_init(&info->fork[i], NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&info->fork[--i]);
			return (0);
		}
	}
	if (pthread_mutex_init(&info->print, NULL) != 0)
	{
		ft_destroy_forks_and_such(info, 0);
		return (0);
	}
	if (pthread_mutex_init(&info->stat_check, NULL) != 0)
	{
		ft_destroy_forks_and_such(info, 1);
		return (0);
	}
	return (1);
}	

int	ft_init_mutexes(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philos)
	{
		if (pthread_mutex_init(&info->meal_time[i], NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&info->meal_time[--i]);
			ft_destroy_forks_and_such(info, 2);
			return (0);
		}
	}
	if (pthread_mutex_init(&info->full_check, NULL) != 0)
	{
		ft_destroy_forks_and_such(info, 3);
		return (0);
	}
	if (pthread_mutex_init(&info->philo_lock, NULL) != 0)
	{
		ft_destroy_forks_and_such(info, 4);
		return (0);
	}
	return (1);
}

int	ft_init_struct(t_info *args, int argc, char **argv)
{
	args->philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->meals = ft_atoi(argv[5]);
	else
		args->meals = 0;
	args->argc = argc;
	args->status = 1;
	args->full_philos = 0;
	args->fork = malloc(args->philos * sizeof(pthread_mutex_t));
	if (!args->fork)
	{
		write(2, "Malloc failed in ft_init_struct\n", 32);
		return (0);
	}
	args->meal_time = malloc(args->philos * sizeof(pthread_mutex_t));
	gettimeofday(&args->start, NULL);
	return (1);
}

int	ft_init_philos(t_info *info)
{
	int	i;

	i = -1;
	info->philo = malloc(info->philos * sizeof(t_philo));
	if (!info->philo)
	{
		write(2, "Malloc failed in ft_init_philos\n", 32);
		return (0);
	}
	while (++i < info->philos)
	{
		info->philo[i].number = i + 1;
		info->philo[i].last_meal = 0;
		info->philo[i].status = 2;
		info->philo[i].meals = 0;
		info->philo[i].full = 0;
		info->philo[i].r_fork = &info->fork[i];
		if (i == 0)
			info->philo[i].l_fork = &info->fork[info->philos - 1];
		else
			info->philo[i].l_fork = &info->fork[i - 1];
		info->philo[i].meal_time = &info->meal_time[i];
	}
	return (1);
}
