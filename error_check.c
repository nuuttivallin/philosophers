/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:02:42 by nvallin           #+#    #+#             */
/*   Updated: 2024/07/11 18:06:43 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_input(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		write(2, "Error! Invalid amout of arguments. (4 or 5 expected)\n", 53);
		return (0);
	}
	while (++i < argc)
	{
		if (!ft_isnumber(argv[i]) || ft_atoi(argv[i]) < 1)
		{
			write(2, "Invalid argument(s)\n", 20);
			return (0);
		}
	}
	if (ft_atoi(argv[1]) > 300)
	{
		write(2, "Not enough seats at the table\n", 30);
		return (0);
	}
	return (1);
}

void	ft_destroy_mutexes(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philos)
	{
		pthread_mutex_destroy(&info->fork[i]);
		pthread_mutex_destroy(&info->meal_time[i++]);
	}
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->stat_check);
	pthread_mutex_destroy(&info->full_check);
	pthread_mutex_destroy(&info->philo_lock);
}
