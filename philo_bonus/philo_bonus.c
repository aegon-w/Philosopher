/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m-boukel <m-boukel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:26:29 by m-boukel          #+#    #+#             */
/*   Updated: 2023/06/08 15:59:02 by m-boukel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_args(int ac, char **av, t_philo *philo)
{
	int		i;
	t_args	*args;

	i = 0;
	args = malloc(sizeof(t_args));
	args->number_of_philosophers = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	open_s(args, av);
	while (i < ft_atoi(av[1]))
	{
		if (ac == 6)
			philo[i].nb_of_eating = ft_atoi(av[5]);
		else
			philo[i].nb_of_eating = -1;
		philo[i].id = i + 1;
		philo[i].inp = args;
		i++;
	}
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		sem_wait(philo->inp->forks);
		take_printf(philo, "take first fork");
		sem_wait(philo->inp->forks);
		take_printf(philo, "take second fork");
		take_printf(philo, "is eating");
		eating_sleeping_time(philo, 1);
		gettimeofday(&philo->lastmeal, NULL);
		if (philo->nb_of_eating != -1)
			philo->nb_of_eating--;
		sem_post(philo->inp->forks);
		sem_post(philo->inp->forks);
		take_printf(philo, "is sleeping");
		eating_sleeping_time(philo, 2);
		take_printf(philo, "is thinking");
		if (philo->nb_of_eating == 0)
			exit(2);
	}
}

void	kill_p(t_philo *philo)
{
	int	status;
	int	i;

	i = 0;
	while (1)
	{
		if (waitpid(-1, &status, 0))
		{
			if (status == 256)
			{
				i = -1;
				while (++i < philo->inp->number_of_philosophers)
					kill(philo[i].pid, 15);
				exit(0);
			}
			i = 0;
			while (++i < philo->inp->number_of_philosophers)
				waitpid(-1, NULL, 0);
			exit(0);
		}
	}
}

int	child(t_philo *philo, int ac, char **av, pthread_t *t)
{
	int	i;

	i = 0;
	philo->start_time = to_msec();
	while (i < atoi(av[1]))
	{
		gettimeofday(&philo[i].lastmeal, NULL);
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			philo[i].start_time = philo->start_time;
			if (pthread_create(&t[i], NULL, &routine, &philo[i]) != 0)
				return (1);
			is_finish(&philo[i], ac);
		}
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
			exit(1);
		}
		if (ft_atoi(av[1]) == 0)
			exit(0);
		philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
		t = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
		init_args(ac, av, philo);
		if (child(philo, ac, av, t) == 1)
		{
			printf("Error\n");
			exit(1);
		}
		kill_p(philo);
	}
	return (0);
}
