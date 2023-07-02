/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:49:48 by sashaboulog       #+#    #+#             */
/*   Updated: 2023/07/02 16:43:05 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*routine(void *arg)
{
	t_philosoph	*philo;

	philo = arg;
	printf("time to die == %u\n", philo->time_to_sleep);
	return (0);
}

int fill_arg(s_philosopher *needs, char **argv)
{
    needs->nbr_of_philosophers=ft_atoi(argv[1]);
    if (needs->nbr_of_philosophers <= 1)
        return (1);
    needs->nbr_of_fork = needs->nbr_of_philosophers;
    needs->time_to_die = ft_atoi(argv[2]);
    if (needs->time_to_die <= 0)
        return (2);
	if (argv[5] != NULL)
	{
		needs->nbr_of_meal = ft_atoi(argv[5]);
		if (needs->nbr_of_meal < 1)
			return (5);
	}
	needs->argv = argv;
	needs->philosoph = NULL;
    return (0);
}

int handle_errors(int   error_code)
{
    if (error_code == 1)
    {
        printf("Not enough Fork to eat, or are they all already... DEAD!?\n");
        return (1);
    }
    if (error_code == 2)
    {
        printf("Not enough Time to Live\n");
        return (1);
    }
	if (error_code == 5)
		return (printf("No need to eat\n"));
    return (0);
}

int main(int argc, char **argv)
{
    s_philosopher   needs;
	struct timeval	time_before;
	struct timeval	time_after;
	int				tmp;

	printf("le temps == %d\n", gettimeofday(&time_before, NULL));
    if (argc == 5 || argc == 6)
    {
        if (handle_errors(fill_arg(&needs, argv)) > 0)
            return (1);
		if (fill_the_table(&needs) != 0)
			return (2);
		gettimeofday(&time_before, NULL);
        // printf("number of philosophers = %d\n", needs.nbr_of_philosophers);
        // printf("number of Fork = %d\n", needs.nbr_of_fork);
        // printf("time to die = %d\n", needs.time_to_die);
		gettimeofday(&time_after, NULL);
		tmp = needs.nbr_of_philosophers;
		while (tmp > 0)
		{
			pthread_join(needs.philosoph->philo, NULL);
			needs.philosoph = needs.philosoph->next;
			tmp--;
		}
    }
    else
        printf("Not enough informations to survive, or too much !?\n");
	// printf("temps en us: %d us\n", (time_after.tv_usec - time_before.tv_usec) / 1000);
	free_the_table(&needs);
    return (0);
}