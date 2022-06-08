/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atouli.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:59:46 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/01 17:15:14 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long int	ft_atouli(char const *str)
{
	unsigned long long int	ans;

	ans = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str > 47 && *str < 58)
	{
		ans = ans * 10 + (*str - 48);
		str++;
	}
	return ((unsigned long int)ans);
}
