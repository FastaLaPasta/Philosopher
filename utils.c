/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:17:15 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/09 15:02:58 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long int	time_pass(t_param *time)
{
	struct timeval	time_after;

	gettimeofday(&time_after, NULL);
	return ((time_after.tv_sec - time->timestamp.tv_sec) * 1000
		+ (time_after.tv_usec - time->timestamp.tv_usec) / 1000);
}

void	ft_usleep(long int time_in_ms, t_param *time)
{
	long int	start_time;
	long int	time_to_wait;

	start_time = 0;
	time_to_wait = time_in_ms / 10;
	start_time = time_pass(time);
	while ((time_pass(time) - start_time) < time_in_ms)
		usleep(time_to_wait);
}

int	check_enough_eat(t_param *general)
{
	int	eat;

	eat = 0;
	if (general->philo->meal >= general->nbr_of_meal
		&& general->philo->eat_enough == 0)
	{
		eat += 1;
		general->philo->eat_enough = 1;
		return (1);
	}
	return (0);
}

int	check_death(t_philo *philo, int fork)
{
	if (*philo->off == 0)
	{
		if (fork == 1)
			pthread_mutex_unlock(&philo->forks);
		else if (fork == 2)
		{
			pthread_mutex_unlock(&philo->forks);
			pthread_mutex_unlock(&philo->next->forks);
		}
		pthread_mutex_unlock(philo->time_mutex);
		return (1);
	}
	return (0);
}

void	printf_end(t_param *general)
{
	printf("================FINISH at %ld================",
		time_pass(general));
}
