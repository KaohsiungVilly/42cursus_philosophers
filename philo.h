/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:52:27 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/08 14:19:03 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define RESET				"\x1b[0m"
# define WHITE				"\x1b[1m"
# define GRAY				"\x1b[2m"
# define BLACK				"\x1b[30m"
# define RED				"\x1b[31m"
# define GREEN				"\x1b[32m"
# define YELLOW				"\x1b[33m"
# define BLUE				"\x1b[34m"
# define PURPLE				"\x1b[35m"
# define CYAN				"\x1b[36m"

typedef struct s_data {
	unsigned long int	time_start;
	unsigned long int	time_eat;
	unsigned long int	time_die;
	pthread_mutex_t		mutex_dead;
	unsigned long int	time_sleep;
	pthread_mutex_t		mutex_print;
	int					nbr_philos;
	char				*forks;
	pthread_mutex_t		mutex_fork[250];
	int					nbr_to_fin;
	int					dead;
}						t_data;

typedef struct s_list {
	pthread_t			thread;
	pthread_mutex_t		mutex_ate;
	int					philo;
	int					left;
	int					nbr_ate;
	unsigned long int	last_dinner;
	struct s_data		*vars;
	struct s_list		*next;
}						t_list;

unsigned long int	c_time(unsigned long int time_start);
unsigned long int	ft_atouli(char const *str);
void				*ft_memset(void *str, int c, size_t len);
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *str);
t_list				*new_philo(int nbr, t_data *vars);
t_list				*create_philos(t_data *vars);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				*routine(void *s);
void				start_philos(t_list *philos);
int					ft_usleep(t_list *philos, unsigned long int time);
int					check_dead(t_list *philos);
int					death_cheker(t_list *philos);
int					print_status(t_list *philos, char *action, char *color);
void				ft_lstclear(t_list *philos);
#endif