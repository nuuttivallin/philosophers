/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:54:59 by nvallin           #+#    #+#             */
/*   Updated: 2024/07/12 15:21:37 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isnumber(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str != '\0')
	{
		if (*str < 48 || *str > 57)
			return (0);
		str++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	size_t	result;
	int		sign;
	size_t	max;

	result = 0;
	sign = 1;
	max = 0 - 1;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str > 47 && *str < 58)
	{
		if (result > max / 10 - *str - 48 && sign == -1)
			return (0);
		if (result > max / 10 - *str - 48 && sign == 1)
			return (-1);
		result = result * 10 + *str - 48;
		str++;
	}
	return (result * sign);
}

void	ft_message(t_info *info, int id, char state)
{
	char	*str;

	if (state == 'f')
		str = "has taken a fork\n";
	if (state == 'e')
		str = "is eating\n";
	if (state == 's')
		str = "is sleeping\n";
	if (state == 't')
		str = "is thinking\n";
	if (state == 'd')
		str = "died\n";
	pthread_mutex_lock(&info->print);
	if (ft_check_status(info) == 1)
		printf("%ld %d %s", ft_time(info->start), id, str);
	pthread_mutex_unlock(&info->print);
	if (state == 'd')
	{
		usleep(420);
		pthread_mutex_lock(&info->print);
		printf("%ld %d %s", ft_time(info->start), id, str);
		pthread_mutex_unlock(&info->print);
	}
}

long	ft_time(struct timeval start)
{
	struct timeval	now;
	long			milliseconds;

	gettimeofday(&now, NULL);
	milliseconds = (now.tv_sec * 1000) + (now.tv_usec / 1000) - \
		(start.tv_sec * 1000) - (start.tv_usec / 1000);
	return (milliseconds);
}

void	ft_usleep(t_info *info, int milliseconds)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	while (ft_time(start) < milliseconds && ft_check_status(info))
		usleep(500);
}
