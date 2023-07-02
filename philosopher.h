/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:53:05 by sashaboulog       #+#    #+#             */
/*   Updated: 2023/07/02 16:31:17 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		PHILOSOPHER_H
# define	PHILOSOPHER_H
# include	<stdlib.h>
# include	<stdio.h>
# include	<pthread.h>
# include	<unistd.h>
# include	<sys/time.h>

typedef struct s_philosoph
{
	pthread_t			philo;
	useconds_t			last_meal;
	useconds_t			time_to_eat;
    useconds_t			time_to_sleep;
	pthread_mutex_t		forks;
	int					philo_nbr;
	int					meal;
	struct s_philosoph	*next;
}			t_philosoph;

typedef struct s_philosopher
{
    int 		nbr_of_philosophers;
    int			nbr_of_fork;
	int			nbr_of_meal;
	char		**argv;
    useconds_t	time_to_die;
	t_philosoph	*philosoph;
}               s_philosopher;

useconds_t		ft_atoi(const char *str);
void			ft_lstadd_back(t_philosoph **lst, t_philosoph *new);
void			*routine(void *arg);
int				fill_the_table(s_philosopher *philosophers);
void			free_the_table(s_philosopher *table);

#endif