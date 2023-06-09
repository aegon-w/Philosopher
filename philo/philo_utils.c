/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m-boukel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:11:38 by m-boukel          #+#    #+#             */
/*   Updated: 2023/06/01 17:08:16 by m-boukel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	to_msec(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	eating_time(t_philo *philo)
{
	long	cur_time;

	cur_time = to_msec();
	while (to_msec() < cur_time + philo->inp->time_to_eat)
		usleep(100);
}

void	sleeping_time(t_philo *philo)
{
	long	cur_time;

	cur_time = to_msec();
	while (to_msec() < cur_time + philo->inp->time_to_sleep)
		usleep(100);
}

void	take_printf(t_philo *philo, char *s)
{
	pthread_mutex_lock(&(philo->inp->print));
	printf("%ld philo %d %s\n", to_msec() - philo->start_time, philo->id, s);
	pthread_mutex_unlock(&(philo->inp->print));
}
