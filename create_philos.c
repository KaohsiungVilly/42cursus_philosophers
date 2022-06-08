/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:21:45 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/02 20:45:27 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_list	*create_philos(t_data *vars)
{
	t_list	*philo;
	int		nbr;

	nbr = 0;
	philo = new_philo(nbr++, vars);
	while (nbr < vars->nbr_philos)
		ft_lstadd_back(&philo, new_philo(nbr++, vars));
	return (philo);
}

static int	death_checker(t_list *philos)
{
	while (philos)
	{
		pthread_mutex_lock(&philos->vars->mutex_dead);
		if (c_time(philos->vars->time_start)
			- philos->last_dinner > philos->vars->time_die)
		{
			philos->vars->dead = philos->philo;
			pthread_mutex_unlock(&philos->vars->mutex_dead);
			pthread_mutex_lock(&philos->vars->mutex_print);
			printf(RED"[%lu ms] philo %d has died\n",
				c_time(philos->vars->time_start), philos->philo + 1);
			pthread_mutex_unlock(&philos->vars->mutex_print);
			return (1);
		}
		pthread_mutex_unlock(&philos->vars->mutex_dead);
		philos = philos->next;
	}
	return (0);
}

static int	all_ate(t_list *philos)
{
	t_list	*temp;

	temp = philos;
	while (philos)
	{
		pthread_mutex_lock(&philos->mutex_ate);
		if (philos->nbr_ate < philos->vars->nbr_to_fin)
		{
			pthread_mutex_unlock(&philos->mutex_ate);
			return (0);
		}
		pthread_mutex_unlock(&philos->mutex_ate);
		philos = philos->next;
	}
	pthread_mutex_lock(&temp->vars->mutex_dead);
	temp->vars->dead = -2;
	pthread_mutex_unlock(&temp->vars->mutex_dead);
	return (1);
}

void	start_philos(t_list *philos)
{
	t_list	*temp;

	temp = philos;
	philos->vars->time_start = c_time(0);
	while (temp)
	{
		pthread_create(&temp->thread, NULL, &routine, (void *)temp);
		temp = temp->next;
	}
	temp = philos;
	while (1)
	{
		ft_usleep(philos, 1);
		if (death_checker(temp) == 1)
			break ;
		if (temp->vars->nbr_to_fin != -1 && all_ate(temp) == 1)
			break ;
	}
	temp = philos;
	while (temp)
	{
		pthread_join(temp->thread, NULL);
		temp = temp->next;
	}
}
