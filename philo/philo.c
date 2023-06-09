/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m-boukel <m-boukel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:56:42 by m-boukel          #+#    #+#             */
/*   Updated: 2023/06/08 15:58:32 by m-boukel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(int ac, char **av, t_philo *philo)
{
	int		i;
	t_args	*args;

	i = 0;
	args = malloc(sizeof(t_args));
	pthread_mutex_init(&(args->print), NULL);
	pthread_mutex_init(&(args->var), NULL);
	args->number_of_philosophers = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->mt = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	while (i < ft_atoi(av[1]))
	{
		if (ac == 6)
			philo[i].nb_of_eating = ft_atoi(av[5]);
		else
			philo->nb_of_eating = -1;
		philo[i].lastmeal = to_msec();
		philo[i].id = i + 1;
		philo[i].inp = args;
		pthread_mutex_init(&(philo[i].inp->mt[i]), NULL);
		i++;
	}
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		pthread_mutex_lock(&(philo->inp->mt[philo->id - 1]));
		take_printf(philo, "take first fork");
		pthread_mutex_lock(&(philo->inp->mt[philo->id
				% philo->inp->number_of_philosophers]));
		take_printf(philo, "take second fork");
		take_printf(philo, "is eating");
		eating_time(philo);
		pthread_mutex_lock(&(philo->inp->var));
		philo->lastmeal = to_msec();
		if (philo->nb_of_eating != -1)
			philo->nb_of_eating--;
		pthread_mutex_unlock(&(philo->inp->var));
		pthread_mutex_unlock(&(philo->inp->mt[philo->id - 1]));
		pthread_mutex_unlock(&(philo->inp->mt[philo->id
				% philo->inp->number_of_philosophers]));
		take_printf(philo, "is sleeping");
		sleeping_time(philo);
		take_printf(philo, "is thinking");
	}
	return (NULL);
}

int	threads_creat(char **av, t_philo *philo, pthread_t *t)
{
	int	i;

	i = 0;
	while (i < atoi(av[1]))
	{
		philo[i].start_time = to_msec();
		if (pthread_create(&t[i], NULL, &routine, &philo[i]) != 0)
			return (1);
		usleep(100);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t	*t;
	t_philo		*philo;

	if (ac == 5 || ac == 6)
	{
		if (check_sign(ac, av) || check_cara(ac, av) || check_int_range(ac, av))
		{
			printf("Error\n");
			return (0);
		}
		if (ft_atoi(av[1]) == 0)
			return (0);
		philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
		t = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
		init_args(ac, av, philo);
		if (threads_creat(av, philo, t) == 1)
		{
			printf("Error\n");
			return (0);
		}
		if (is_finish(philo, ac) == 0)
			return (0);
		destroy(philo);
	}
	return (0);
}
