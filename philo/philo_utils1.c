/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m-boukel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:53:51 by m-boukel          #+#    #+#             */
/*   Updated: 2023/06/04 14:34:16 by m-boukel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	died_philo(t_philo *philo, int i)
{
	if (to_msec() - philo[i % philo->inp->number_of_philosophers].lastmeal
		> philo->inp->time_to_die)
	{
		pthread_mutex_lock(&(philo->inp->print));
		printf("%ld philo %d died\n", to_msec() - philo->start_time, philo->id);
		return (1);
	}
	return (0);
}

int	is_finish(t_philo *philo, int ac)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	while (1)
	{
		j = 0;
		count = 0;
		while (j < philo->inp->number_of_philosophers)
		{
			pthread_mutex_lock(&(philo->inp->var));
			if (ac == 6 && philo[j++].nb_of_eating == 0)
				count++;
			if (ac == 6 && philo->inp->number_of_philosophers == count)
				return (0);
			if (died_philo(philo, i) == 1)
				return (0);
			pthread_mutex_unlock(&(philo->inp->var));
			i++;
			if (i >= philo->inp->number_of_philosophers)
				i = 0;
			usleep(100);
		}
	}
}

void	destroy(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->inp->number_of_philosophers)
		pthread_mutex_destroy(philo[i].inp->mt);
	pthread_mutex_destroy(&philo->inp->print);
	pthread_mutex_destroy(&philo->inp->var);
}
