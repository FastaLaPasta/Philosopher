/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:49:48 by sashaboulog       #+#    #+#             */
/*   Updated: 2023/07/13 12:04:15 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->nbr % 2 == 0)
		ft_usleep(philo->time_to_eat, philo->general);
	if (routine_all(philo) == 1)
		return (0);
	return (NULL);
}

void	*die_or_full(void *arg)
{
	t_param	*general;
	int		eat;

	general = arg;
	eat = 0;
	while (1)
	{
		pthread_mutex_lock(&general->mutex);
		eat += check_enough_eat(general);
		if ((time_pass(general) - general->philo->last_meal
				> general->time_to_die || eat == general->nbr_of_philosophers))
		{
			general->on = 0;
			if (eat == general->nbr_of_philosophers)
				printf_end(general);
			else
				printf("%ld %d died\n", time_pass(general), general->philo->nbr);
			pthread_mutex_unlock(&(general->mutex));
			return (NULL);
		}
		general->philo = general->philo->next;
		pthread_mutex_unlock(&general->mutex);
	}
	return (NULL);
}

int	fill_arg(t_param *needs, char **argv)
{
	needs->nbr_of_philosophers = ft_atoi(argv[1]);
	if (needs->nbr_of_philosophers <= 0)
		return (printf("Pas assez de fourchettes pour manger,\
 ou pas assez de philosophes !\n"));
	needs->nbr_of_fork = needs->nbr_of_philosophers;
	needs->time_to_die = ft_atoi(argv[2]);
	if (needs->time_to_die <= 0)
		return (printf("Temps de vie insuffisant\n"));
	if (argv[5] != NULL)
	{
		needs->nbr_of_meal = ft_atoi(argv[5]);
		if (needs->nbr_of_meal < 1)
			return (printf("Pas besoin de manger\n"));
	}
	needs->on = 1;
	needs->stop_time = 1;
	needs->argv = argv;
	needs->philo = NULL;
	return (0);
}

void	launch_philosophie(t_param *philo)
{
	pthread_t	end;
	int			i;

	i = 0;
	while (i < philo->nbr_of_philosophers)
	{
		pthread_create(&(philo->philo->philo), NULL, &routine, philo->philo);
		philo->philo = philo->philo->next;
		i++;
	}
	pthread_create(&end, NULL, &die_or_full, philo);
	pthread_join(end, NULL);
	while (i > 0)
	{
		pthread_join(philo->philo->philo, NULL);
		philo->philo = philo->philo->next;
		i--;
	}
	pthread_mutex_lock(&(philo->mutex));
	philo->stop_time = 0;
	pthread_mutex_unlock(&(philo->mutex));
	ft_usleep(50, philo);
}

int	main(int argc, char **argv)
{
	t_param		general;

	if (argc != 5 && argc != 6)
	{
		printf("don't forget any settings\n");
		return (-1);
	}
	if (fill_arg(&general, argv) != 0)
		return (-1);
	if (fill_the_table(&general) != 0)
		return (-1);
	gettimeofday(&general.timestamp, NULL);
	pthread_mutex_init(&(general.mutex), NULL);
	launch_philosophie(&general);
	free_the_table(&general);
	return (0);
}
