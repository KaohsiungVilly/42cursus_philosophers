/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:38:10 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/02 20:47:32 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_list	*new_philo(int nbr, t_data *vars)
{
	t_list	*philo;

	philo = malloc(sizeof(t_list));
	if (!philo)
		return (NULL);
	philo->philo = nbr;
	if (nbr == 0)
		philo->left = vars->nbr_philos - 1;
	else
		philo->left = nbr - 1;
	philo->nbr_ate = 0;
	philo->vars = vars;
	pthread_mutex_init(&philo->mutex_ate, NULL);
	philo->next = NULL;
	return (philo);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!new)
		return ;
	last = ft_lstlast(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}

void	ft_lstclear(t_list *philos)
{
	t_list	*temp;

	temp = philos;
	while (temp)
	{
		philos = temp;
		temp = temp->next;
		pthread_mutex_destroy(&philos->mutex_ate);
		free(philos);
	}
}
