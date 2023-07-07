/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:49:48 by sashaboulog       #+#    #+#             */
/*   Updated: 2023/07/07 17:30:21 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *routine(void *arg)
{
	t_philo *philo = arg;
	t_philo *next_philo = philo->next;

	while (1)
	{
		pthread_mutex_lock(philo->time_mutex);
		if (philo->off == 0)
		{
			pthread_mutex_unlock(philo->time_mutex);
			return (0);
		}
		pthread_mutex_unlock(philo->time_mutex);
		pthread_mutex_lock(&(philo->forks));
		pthread_mutex_lock((philo->time_mutex));
		printf("%ld %d has taken a fork\n", *philo->time, philo->nbr);
		pthread_mutex_unlock((philo->time_mutex));
		pthread_mutex_lock(&(next_philo->forks));
		pthread_mutex_lock((philo->time_mutex));
		printf("%ld %d has taken a fork\n", *philo->time, philo->nbr);
		pthread_mutex_unlock((philo->time_mutex));
		pthread_mutex_lock((philo->time_mutex));
		printf("%ld %d is eating\n", *philo->time, philo->nbr);
		philo->last_meal = *philo->time;
		pthread_mutex_unlock((philo->time_mutex));
		philo->meal += 1;
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(&(next_philo->forks));
		pthread_mutex_unlock(&(philo->forks));
		pthread_mutex_lock((philo->time_mutex));
		printf("%ld %d is sleeping\n", *philo->time, philo->nbr);
		pthread_mutex_unlock((philo->time_mutex));
		usleep(philo->time_to_sleep * 1000);
		pthread_mutex_lock((philo->time_mutex));
		printf("%ld %d is thinking\n", *philo->time, philo->nbr);
		pthread_mutex_unlock((philo->time_mutex));
	}
	return NULL;
}

void *time_pass(void *arg)
{
	t_param *time = arg;
	struct timeval time_before, time_after;
	long long elapsed_time;

	gettimeofday(&time_before, NULL);
	while (1)
	{
		gettimeofday(&time_after, NULL);
		elapsed_time = (time_after.tv_sec - time_before.tv_sec) * 1000 +
					(time_after.tv_usec - time_before.tv_usec) / 1000;
		pthread_mutex_lock(&(time->mutex));
		time->timestamp = elapsed_time;
		pthread_mutex_unlock(&(time->mutex));
		pthread_mutex_lock(&(time->mutex));
		if (time->on == 0)
		{
			pthread_mutex_unlock(&(time->mutex));
			break;
		}
		time->timestamp = elapsed_time;
		pthread_mutex_unlock(&(time->mutex));
	}
	return NULL;
}

void *die_or_full(void *arg)
{
	t_param *general = arg;

	while (general->philo != NULL)
	{
		pthread_mutex_lock(&(general->mutex));
		printf("%ld \n", general->philo->last_meal);
		if ((general->timestamp - general->philo->last_meal) > general->time_to_die)
		{
			general->on = 0;
			printf("%ld %d died\n", general->timestamp, general->philo->nbr);
			pthread_mutex_unlock(&(general->mutex));
			return NULL;
		}
		general->philo = general->philo->next;
		pthread_mutex_unlock(&(general->mutex));
	}
	return NULL;
}

int fill_arg(t_param *needs, char **argv)
{
	needs->nbr_of_philosophers = ft_atoi(argv[1]);
	if (needs->nbr_of_philosophers <= 1)
	{
		printf("Pas assez de fourchettes pour manger, ou pas assez de philosophes !\n");
		return -1;
	}
	needs->nbr_of_fork = needs->nbr_of_philosophers;
	needs->time_to_die = ft_atoi(argv[2]);
	if (needs->time_to_die <= 0)
	{
		printf("Temps de vie insuffisant\n");
		return -1;
	}
	if (argv[5] != NULL)
	{
		needs->nbr_of_meal = ft_atoi(argv[5]);
		if (needs->nbr_of_meal < 1)
		{
			printf("Pas besoin de manger\n");
			return -1;
		}
	}
	needs->on = 1;
	needs->argv = argv;
	needs->philo = NULL;
	return 0;
}

void launch_philosophie(t_param *philo)
{
	t_philo *first_philo = philo->philo;
	pthread_t	end;
	int i;

	i = 0;
	while (i < philo->nbr_of_philosophers)
	{
		if (philo->philo->nbr % 3 == 2)
			usleep(100);
		if (philo->philo->nbr % 3 == 0)
			usleep(50);
		pthread_create(&(philo->philo->philo), NULL, &routine, philo->philo);
		philo->philo = philo->philo->next;
		i++;
	}
	philo->philo = first_philo;
	pthread_create(&end, NULL, &die_or_full, &philo);
	pthread_join(end, NULL);
	while (i > 0)
	{
		pthread_join(philo->philo->philo, NULL);
		philo->philo = philo->philo->next;
		i--;
	}
	pthread_mutex_lock(&(philo->mutex));
	philo->on = 0;
	pthread_mutex_unlock(&(philo->mutex));
}

int main(int argc, char **argv)
{
	t_param		general;
	pthread_t	time_thread;
	

	if (argc != 5 && argc != 6)
	{
		printf("don't forget any settings\n");
		return -1;
	}
	if (fill_arg(&general, argv) != 0)
		return -1;
	if (fill_the_table(&general) != 0)
		return -1;
	pthread_mutex_init(&(general.mutex), NULL);
	pthread_create(&time_thread, NULL, time_pass, &general);
	pthread_detach(time_thread);
	launch_philosophie(&general);
	
	// sleep(4);
	//pthread_mutex_destroy(&(general.mutex));
	return (0);
}
