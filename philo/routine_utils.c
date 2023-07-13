/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:45:10 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/13 12:26:52 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	routine_to_eat(t_philo *philo)
{
	pthread_mutex_lock((philo->time_mutex));
	if (check_death(philo, 2) == 1)
		return (1);
	printf("%ld %d has taken a fork\n",
		time_pass(philo->general), philo->nbr);
	pthread_mutex_unlock((philo->time_mutex));
	pthread_mutex_lock((philo->time_mutex));
	if (check_death(philo, 2) == 1)
		return (1);
	printf("%ld %d is eating\n", time_pass(philo->general), philo->nbr);
	philo->last_meal = time_pass(philo->general);
	philo->meal += 1;
	pthread_mutex_unlock((philo->time_mutex));
	ft_usleep(philo->time_to_eat, philo->general);
	return (0);
}

int	routine_to_sleep_and_think(t_philo *philo)
{
	pthread_mutex_lock((philo->time_mutex));
	if (check_death(philo, 0) == 1)
		return (1);
	printf("%ld %d is sleeping\n", time_pass(philo->general), philo->nbr);
	pthread_mutex_unlock((philo->time_mutex));
	ft_usleep(philo->time_to_sleep, philo->general);
	pthread_mutex_lock((philo->time_mutex));
	if (check_death(philo, 0) == 1)
		return (1);
	printf("%ld %d is thinking\n", time_pass(philo->general), philo->nbr);
	pthread_mutex_unlock((philo->time_mutex));
	return (0);
}

int	routine_all(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->time_mutex);
		if (check_death(philo, 0) == 1)
			return (1);
		pthread_mutex_unlock(philo->time_mutex);
		pthread_mutex_lock(&(philo->forks));
		pthread_mutex_lock((philo->time_mutex));
		if (check_death(philo, 1) == 1)
			return (1);
		printf("%ld %d has taken a fork\n", time_pass(philo->general),
			philo->nbr);
		pthread_mutex_unlock((philo->time_mutex));
		if (philo->general->nbr_of_philosophers > 1)
		{
			pthread_mutex_lock(&(philo->next->forks));
			if (routine_to_eat(philo) == 1)
				return (1);
			pthread_mutex_unlock(&(philo->next->forks));
		}
		pthread_mutex_unlock(&(philo->forks));
		if (routine_to_sleep_and_think(philo) == 1)
			return (1);
	}
	return (0);
}
