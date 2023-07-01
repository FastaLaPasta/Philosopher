/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashaboulogne <sashaboulogne@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:53:05 by sashaboulog       #+#    #+#             */
/*   Updated: 2023/07/01 18:06:08 by sashaboulog      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef     PHILOSOPHER_H
# define    PHILOSOPHER_H
# include   <stdlib.h>
# include    <stdio.h>
# include    <pthread.h>
# include    <unistd.h>

typedef struct s_philosopher
{
    int nbr_of_philosophers;
    int nbr_of_fork;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
}               s_philosopher;

int	ft_atoi(const char *str);

#endif