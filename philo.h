/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:50:44 by nvallin           #+#    #+#             */
/*   Updated: 2024/07/12 14:43:18 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				number;
	int				status;
	int				meals;
	int				full;
	long			last_meal;
	pthread_t		id;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*meal_time;
}			t_philo;

typedef struct s_info
{
	int					philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals;
	int					argc;
	int					status;
	int					full_philos;
	struct timeval		start;
	t_philo				*philo;
	pthread_mutex_t		*fork;
	pthread_mutex_t		*meal_time;
	pthread_mutex_t		print;
	pthread_mutex_t		stat_check;
	pthread_mutex_t		full_check;
	pthread_mutex_t		philo_lock;
	pthread_t			universe;
	pthread_t			waiter;
}			t_info;

void	ft_start(t_info *info);
void	*ft_observe(void *data);
void	*ft_routine(void *args);
void	ft_message(t_info *info, int id, char state);
void	ft_usleep(t_info *info, int milliseconds);
void	ft_eat(t_info *info, t_philo *philo);
void	ft_actions(t_info *info, t_philo *philo);
void	ft_destroy_mutexes(t_info *info);
long	ft_time(struct timeval start);
void	ft_destroy_forks_and_such(t_info *info, int other_mutexes);
void	*ft_meal_check(void *data);
int		ft_death_check(t_info *info, t_philo *philo);
int		ft_init_forks_and_such(t_info *info);
int		ft_init_mutexes(t_info *info);
int		ft_init_struct(t_info *args, int argc, char **argv);
int		ft_init_philos(t_info *info);
int		ft_check_input(int argc, char **argv);
int		ft_atoi(const char *str);
int		ft_isnumber(const char *str);
int		ft_check_status(t_info *info);

#endif
