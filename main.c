/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:15:57 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/08 14:18:55 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_data	*init_vars(char **argv)
{
	t_data	*vars;
	int		n;

	n = -1;
	vars = malloc(sizeof(t_data));
	vars->time_start = 0;
	vars->nbr_philos = ft_atoi(argv[1]);
	vars->time_die = ft_atouli(argv[2]);
	vars->time_eat = ft_atouli(argv[3]);
	vars->time_sleep = ft_atouli(argv[4]);
	if (argv[5])
		vars->nbr_to_fin = ft_atoi(argv[5]);
	else
		vars->nbr_to_fin = -1;
	vars->forks = malloc(sizeof(char) * vars->nbr_philos + 1);
	ft_memset(vars->forks, '1', vars->nbr_philos);
	vars->forks[vars->nbr_philos] = 0;
	vars->dead = -1;
	pthread_mutex_init(&vars->mutex_dead, NULL);
	pthread_mutex_init(&vars->mutex_print, NULL);
	while (++n < vars->nbr_philos)
		pthread_mutex_init(&vars->mutex_fork[n], NULL);
	return (vars);
}

static int	ft_isdigit(int nbr)
{
	if (nbr > 47 && nbr < 58)
		return (1);
	else
		return (0);
}

static int	check_digits(char *s)
{
	while (*s)
	{
		if (ft_isdigit(*s++) == 0)
			return (-1);
	}
	return (0);
}

static int	check_args(char *argv[])
{
	int	i;

	i = 0;
	if (ft_atoi(argv[1]) > 200)
		return (-1);
	while (argv[++i])
	{
		if (ft_strlen(argv[i]) >= 11)
			return (-1);
		else if (check_digits(argv[i]) == -1)
			return (-1);
		else if (ft_atouli(argv[i]) > (unsigned long int) INT_MAX)
			return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*vars;
	t_list	*philos;
	t_list	*temp;
	int		n;

	n = -1;
	if (argc != 5 && argc != 6)
		return (1);
	else if (argv[5] && ft_atoi(argv[5]) == 0)
		return (0);
	else if (check_args(argv) == -1)
		return (1);
	vars = init_vars(argv);
	philos = create_philos(vars);
	start_philos(philos);
	pthread_mutex_destroy(&vars->mutex_dead);
	pthread_mutex_destroy(&vars->mutex_print);
	temp = philos;
	while (++n < vars->nbr_philos)
		pthread_mutex_destroy(&vars->mutex_fork[n]);
	free(vars->forks);
	free(vars);
	ft_lstclear(philos);
	return (0);
}
