/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:55:52 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/08 14:19:19 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_list *philos)
{
	pthread_mutex_lock(&philos->vars->mutex_dead);
	if (philos->vars->dead != -1)
	{
		pthread_mutex_unlock(&philos->vars->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(&philos->vars->mutex_dead);
	return (0);
}

int	print_status(t_list *philos, char *action, char *color)
{
	pthread_mutex_lock(&philos->vars->mutex_print);
	if (check_dead(philos) == 1)
	{
		pthread_mutex_unlock(&philos->vars->mutex_print);
		return (1);
	}
	printf("%s[%lu ms] philo %d ", color,
		c_time(philos->vars->time_start), philos->philo + 1);
	printf("%s\n"RESET, action);
	pthread_mutex_unlock(&philos->vars->mutex_print);
	return (0);
}

void	ft_eat(t_list *philos)
{
	pthread_mutex_lock(&philos->vars->mutex_dead);
	philos->last_dinner = c_time(philos->vars->time_start);
	pthread_mutex_unlock(&philos->vars->mutex_dead);
	pthread_mutex_lock(&philos->mutex_ate);
	philos->nbr_ate++;
	pthread_mutex_unlock(&philos->mutex_ate);
	ft_usleep(philos, philos->vars->time_eat);
	pthread_mutex_unlock(&philos->vars->mutex_fork[philos->philo]);
	pthread_mutex_unlock(&philos->vars->mutex_fork[philos->left]);
}

int	start_eating(t_list	*philos)
{
	pthread_mutex_lock(&philos->vars->mutex_fork[philos->left]);
	if (print_status(philos, "has taken a fork", RESET) == 1
		|| ft_strlen(philos->vars->forks) == 1)
	{
		pthread_mutex_unlock(&philos->vars->mutex_fork[philos->left]);
		return (1);
	}
	pthread_mutex_lock(&philos->vars->mutex_fork[philos->philo]);
	if (print_status(philos, "has taken a fork", RESET) == 1)
	{
		pthread_mutex_unlock(&philos->vars->mutex_fork[philos->philo]);
		pthread_mutex_unlock(&philos->vars->mutex_fork[philos->left]);
		return (1);
	}
	if (print_status(philos, "is eating", GREEN) == 1)
	{
		pthread_mutex_unlock(&philos->vars->mutex_fork[philos->philo]);
		pthread_mutex_unlock(&philos->vars->mutex_fork[philos->left]);
		return (1);
	}
	ft_eat(philos);
	return (0);
}

void	*routine(void *s)
{
	t_list	*philos;

	philos = (t_list *)s;
	pthread_mutex_lock(&philos->vars->mutex_dead);
	philos->last_dinner = c_time(philos->vars->time_start);
	pthread_mutex_unlock(&philos->vars->mutex_dead);
	if (philos->philo % 2 != 0)
		ft_usleep(philos, 20);
	while (1)
	{
		if (start_eating(philos) == 1)
			return (0);
		if (print_status(philos, "is sleeping", BLUE) == 1)
			return (0);
		ft_usleep(philos, philos->vars->time_sleep);
		if (print_status(philos, "is thinking", PURPLE) == 1)
			return (0);
	}
}
