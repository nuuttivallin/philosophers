/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:26:27 by nvallin           #+#    #+#             */
/*   Updated: 2024/07/12 15:27:23 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_meal_check(void *data)
{
	t_info	*info;

	info = data;
	while (ft_check_status(info) == 1)
	{
		pthread_mutex_lock(&info->full_check);
		if (info->full_philos == info->philos)
		{
			pthread_mutex_unlock(&info->full_check);
			pthread_mutex_lock(&info->stat_check);
			info->status = 2;
			pthread_mutex_unlock(&info->stat_check);
		}
		else
			pthread_mutex_unlock(&info->full_check);
	}
	return (NULL);
}

void	ft_eat(t_info *info, t_philo *philo)
{
	if (philo->number % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		ft_message(info, philo->number, 'f');
	}
	pthread_mutex_lock(philo->l_fork);
	ft_message(info, philo->number, 'f');
	if (philo->number % 2 != 0)
	{
		if (info->philos == 1)
			return ;
		pthread_mutex_lock(philo->r_fork);
		ft_message(info, philo->number, 'f');
	}
	pthread_mutex_lock(philo->meal_time);
	philo->last_meal = ft_time(info->start);
	pthread_mutex_unlock(philo->meal_time);
	ft_message(info, philo->number, 'e');
	ft_usleep(info, info->time_to_eat);
	if (++philo->meals == info->meals && info->argc == 6)
	{
		pthread_mutex_lock(&info->full_check);
		info->full_philos++;
		pthread_mutex_unlock(&info->full_check);
	}
}	

void	ft_actions(t_info *info, t_philo *philo)
{
	if (philo->status == 3)
	{
		philo->status = 1;
		ft_eat(info, philo);
		if (info->philos == 1)
		{
			philo->status = 0;
			pthread_mutex_unlock(philo->l_fork);
			return ;
		}
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else if (philo->status == 1)
	{
		philo->status = 2;
		ft_message(info, philo->number, 's');
		ft_usleep(info, info->time_to_sleep);
	}
	else if (philo->status == 2)
	{
		philo->status = 3;
		ft_message(info, philo->number, 't');
	}
}

int	ft_check_status(t_info *info)
{
	int	status;

	pthread_mutex_lock(&info->stat_check);
	status = info->status;
	pthread_mutex_unlock(&info->stat_check);
	return (status);
}

void	*ft_routine(void *data)
{
	static int	i = 0;
	t_info		*info;
	t_philo		*philo;

	info = data;
	pthread_mutex_lock(&info->philo_lock);
	philo = &info->philo[i++];
	pthread_mutex_unlock(&info->philo_lock);
	while (ft_check_status(info) == 1)
	{
		if (philo->status == 0)
			return (NULL);
		ft_actions(info, philo);
	}
	return (NULL);
}
