/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:17:38 by nvallin           #+#    #+#             */
/*   Updated: 2024/07/12 15:27:25 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_death_check(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(philo->meal_time);
	if (ft_time(info->start) - philo->last_meal > info->time_to_die)
	{
		pthread_mutex_unlock(philo->meal_time);
		pthread_mutex_lock(&info->stat_check);
		info->status = 0;
		pthread_mutex_unlock(&info->stat_check);
		ft_message(info, philo->number, 'd');
		return (0);
	}
	pthread_mutex_unlock(philo->meal_time);
	return (1);
}

void	*ft_observe(void *data)
{
	t_info	*info;
	int		i;

	info = data;
	i = -1;
	while (ft_check_status(info) == 1)
	{
		while (++i < info->philos)
			if (!ft_death_check(info, &info->philo[i]))
				return (NULL);
		i = -1;
	}
	return (NULL);
}

void	ft_start(t_info *info)
{
	int	i;

	i = 0;
	gettimeofday(&info->start, NULL);
	pthread_create(&info->universe, NULL, ft_observe, info);
	if (info->argc == 6)
		pthread_create(&info->waiter, NULL, ft_meal_check, info);
	while (i < info->philos)
		pthread_create(&info->philo[i++].id, NULL, ft_routine, info);
}

int	main(int argc, char **argv)
{
	int		i;
	t_info	args;

	if (!ft_check_input(argc, argv))
		return (0);
	if (!ft_init_struct(&args, argc, argv))
		return (0);
	if (!ft_init_forks_and_such(&args))
		return (0);
	if (!ft_init_mutexes(&args))
		return (0);
	if (!ft_init_philos(&args))
		return (0);
	ft_start(&args);
	pthread_join(args.universe, NULL);
	if (argc == 6)
		pthread_join(args.waiter, NULL);
	i = 0;
	while (i < args.philos)
		pthread_join(args.philo[i++].id, NULL);
	ft_destroy_mutexes(&args);
	free(args.fork);
	free(args.meal_time);
	free(args.philo);
	return (0);
}
