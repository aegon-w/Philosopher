/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m-boukel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:55:25 by m-boukel          #+#    #+#             */
/*   Updated: 2023/06/03 21:51:30 by m-boukel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct args
{
	long			number_of_philosophers;
	long			time_to_eat;
	long			time_to_die;
	long			time_to_sleep;
	pthread_mutex_t	print;
	pthread_mutex_t	var;
	pthread_mutex_t	*mt;
}					t_args;

typedef struct philo
{
	long			start_time;
	long			nb_of_eating;
	int				id;
	long			lastmeal;
	t_args			*inp;
}					t_philo;

long				to_msec(void);
void				eating_time(t_philo *philo);
void				sleeping_time(t_philo *philo);
long				ft_atoi(char *str);
int					check_sign(int ac, char **av);
int					check_cara(int ac, char **av);
int					check_int_range(int ac, char **av);
void				take_printf(t_philo *philo, char *s);
int					is_finish(t_philo *philo, int ac);
void				destroy(t_philo *philo);

#endif