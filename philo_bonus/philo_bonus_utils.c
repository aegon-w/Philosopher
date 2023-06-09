/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m-boukel <m-boukel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:05:00 by m-boukel          #+#    #+#             */
/*   Updated: 2023/06/07 15:26:45 by m-boukel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	to_msec(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	eating_sleeping_time(t_philo *philo, int i)
{
	long	cur_time;

	cur_time = to_msec();
	if (i == 1)
	{
		while (to_msec() < cur_time + philo->inp->time_to_eat)
			usleep(100);
	}
	if (i == 2)
	{
		while (to_msec() < cur_time + philo->inp->time_to_sleep)
			usleep(100);
	}
}

void	open_s(t_args *args, char **av)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	args->forks = sem_open("/forks", O_CREAT | O_EXCL, 0664, ft_atoi(av[1]));
	args->print = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	if (args->forks == SEM_FAILED || args->print == SEM_FAILED)
	{
		printf("Failed to open semphore for empty\n");
		exit(1);
	}
}

void	is_finish(t_philo *philo, int ac)
{
	(void)ac;
	while (1)
	{
		if ((to_msec() - ((philo->lastmeal.tv_sec * 1000)
					+ (philo->lastmeal.tv_usec
						/ 1000))) > philo->inp->time_to_die)
		{
			sem_wait(philo->inp->print);
			printf("%ld philo %d died\n", to_msec() - philo->start_time,
				philo->id);
			exit(1);
		}
		usleep(100);
	}
}

void	take_printf(t_philo *philo, char *s)
{
	sem_wait(philo->inp->print);
	printf("%ld philo %d %s\n", to_msec() - philo->start_time, philo->id, s);
	sem_post(philo->inp->print);
}
