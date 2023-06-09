/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m-boukel <m-boukel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:25:42 by m-boukel          #+#    #+#             */
/*   Updated: 2023/06/07 11:32:43 by m-boukel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct args
{
	long			number_of_philosophers;
	long			time_to_eat;
	long			time_to_die;
	long			time_to_sleep;
	sem_t			*forks;
	sem_t			*print;
}					t_args;

typedef struct philo
{
	long			start_time;
	long			nb_of_eating;
	int				id;
	struct timeval	lastmeal;
	pid_t			pid;
	t_args			*inp;
}					t_philo;

long				to_msec(void);
long				ft_atoi(char *str);
int					check_sign(int ac, char **av);
int					check_cara(int ac, char **av);
int					check_int_range(int ac, char **av);
void				eating_sleeping_time(t_philo *philo, int i);
void				open_s(t_args *args, char **av);
void				is_finish(t_philo *philo, int ac);
void				take_printf(t_philo *philo, char *s);
void				kill_in_case(t_philo *philo, int c, int *v, int i);

#endif