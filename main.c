/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashaboulogne <sashaboulogne@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:49:48 by sashaboulog       #+#    #+#             */
/*   Updated: 2023/07/01 18:42:23 by sashaboulog      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int fill_needs(s_philosopher *needs, char **argv)
{
    needs->nbr_of_philosophers=ft_atoi(argv[1]);
    if (needs->nbr_of_philosophers <= 1)
        return (1);
    needs->nbr_of_fork = needs->nbr_of_philosophers;
    needs->time_to_die = ft_atoi(argv[2]);
    if (needs->time_to_die <= 0)
        return (2);
    needs->time_to_eat = ft_atoi(argv[3]);
    if  (needs->time_to_eat <= 0)
        return (3);
    needs->time_to_sleep = ft_atoi(argv[4]);
    if (needs->time_to_sleep <= 0)
        return (4);
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
    if (error_code == 3)
    {
        printf("Not enough Time to Eat\n");
        return (1);
    }
    if (error_code == 4)
    {
        printf("Not enough Time to Sleep, Burnout...\n");
        return (1);
    }
    return (0);
}

int main(int argc, char **argv)
{
    s_philosopher   needs;
    (void)argc;
    (void)argv;
    if (argc == 5)
    {
        if (handle_errors(fill_needs(&needs, argv)) == 1)
            return (1);
        // printf("number of philosophers = %d\n", needs.nbr_of_philosophers);
        // printf("number of Fork = %d\n", needs.nbr_of_fork);
        // printf("time to die = %d\n", needs.time_to_die);
        // printf("time to eat = %d\n", needs.time_to_eat);
        // printf("time to sleep = %d\n", needs.time_to_sleep);
    }
    else
        printf("Not enough informations to survive, or too much !?\n");
    return (0);
}