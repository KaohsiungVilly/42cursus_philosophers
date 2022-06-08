/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:39:45 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/02 20:27:21 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long int	c_time(unsigned long int time_start)
{
	struct timeval		time;
	unsigned long int	ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000) - time_start;
	return (ms);
}

int	ft_usleep(t_list *philos, unsigned long int time)
{
	unsigned long int	slept;

	slept = c_time(philos->vars->time_start);
	while (c_time(philos->vars->time_start) - slept < time)
	{
		usleep(50);
		if (check_dead(philos) == 1)
			return (0);
	}
	return (0);
}

void	*ft_memset(void *str, int c, size_t len)
{
	unsigned char	*p;

	p = str;
	while (len--)
		*p++ = (char)c;
	return (str);
}

int	ft_atoi(const char *str)
{
	unsigned long long int	ans;
	int						sign;

	ans = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == 45)
	{
		sign *= -1;
		str++;
	}
	else if (*str == 43)
		str++;
	while (*str > 47 && *str < 58)
	{
		ans = ans * 10 + (*str - 48);
		str++;
	}
	if (ans > 9223372036854775807 && sign < 0)
		return (0);
	else if (ans > 9223372036854775807 && sign > 0)
		return (-1);
	return ((int)(ans * sign));
}

size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}
