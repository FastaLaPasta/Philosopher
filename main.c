/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:49:48 by sashaboulog       #+#    #+#             */
/*   Updated: 2023/07/05 17:12:52 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*routine(void *arg)
{
	t_philo		*current;

	current = arg;
	while (1)
	{
		pthread_mutex_lock(&current->forks);
		printf("%ld %d has taken a fork \n", *current->time, current->nbr);
		pthread_mutex_lock(&current->next->forks);
		printf("%ld %d has taken a fork \n", *current->time, current->nbr);
		printf("%ld %d is eating\n", *current->time, current->nbr);
		usleep(current->time_to_eat * 1000);
		pthread_mutex_unlock(&current->forks);
		pthread_mutex_unlock(&current->next->forks);
		printf("%ld %d is sleeping\n", *current->time, current->nbr);
		usleep(current->time_to_sleep * 1000);
		printf("%ld %d is thinking\n", *current->time, current->nbr);
	}
	return (0);
}

int	fill_arg(t_param *needs, char **argv)
{
	needs->nbr_of_philosophers = ft_atoi(argv[1]);
	if (needs->nbr_of_philosophers <= 1)
		return (printf("Not enough Fork to eat, or not enough... ALIVE!?\n"));
	needs->nbr_of_fork = needs->nbr_of_philosophers;
	needs->time_to_die = ft_atoi(argv[2]);
	if (needs->time_to_die <= 0)
		return (printf("Not enough Time to Live\n"));
	if (argv[5] != NULL)
	{
		needs->nbr_of_meal = ft_atoi(argv[5]);
		if (needs->nbr_of_meal < 1)
			return (printf("No need to eat\n"));
	}
	needs->argv = argv;
	needs->philo = NULL;
	return (0);
}

void	*time_pass(void *arg)
{
	struct timeval	time_after;
	struct timeval	time_before;
	time_t			second;
	suseconds_t		milli_second;
	t_param			*time;

	time = arg;
	gettimeofday(&time_before, NULL);
	time->tv_sec = time_before.tv_sec;
	time->tv_usec = time_before.tv_usec;
	while (1)
	{
		if (time->philo == NULL)
			return (0);
		gettimeofday(&time_after, NULL);
		second = time_after.tv_sec - time->tv_sec;
		milli_second = time_after.tv_usec - time->tv_usec;
		if (milli_second < 0)
			milli_second += 1000;
		time->timestamp = (second * 1000) + (milli_second / 1000);
	}
	return (0);
}

void	launch_the_philosophi(int tmp, t_param *needs)
{
	while (tmp > 0)
	{
		if (needs->philo->nbr % 3 == 1)
			pthread_create(&needs->philo->philo, NULL, &routine, needs->philo);
		else if (needs->philo->nbr % 3 == 2)
		{
			usleep(20);
			pthread_create(&needs->philo->philo, NULL, &routine, needs->philo);
		}
		else if (needs->philo->nbr % 3 == 0)
		{
			usleep(40);
			pthread_create(&needs->philo->philo, NULL, &routine, needs->philo);
		}
		needs->philo = needs->philo->next;
		tmp--;
	}
	tmp = needs->nbr_of_philosophers;
	while (tmp > 0)
	{
		pthread_join(needs->philo->philo, NULL);
		needs->philo = needs->philo->next;
		tmp--;
	}
}

int	main(int argc, char **argv)
{
	t_param		needs;
	pthread_t	time;
	int			tmp;

	if (argc == 5 || argc == 6)
	{
	
		if (fill_arg(&needs, argv) > 0)
			return (1);
		if (fill_the_table(&needs) != 0)
			return (2);
		pthread_create(&time, NULL, time_pass, &needs);
		pthread_detach(time);
		tmp = needs.nbr_of_philosophers;
		launch_the_philosophi(tmp, &needs);
	}
	else
		printf("Not enough informations to survive, or too much !?\n");
	free_the_table(&needs);
	return (0);
}
