/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:21:23 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/06 14:34:38 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philosoph
{
	pthread_t			philo;
	long				last_meal;
	useconds_t			time_to_eat;
	useconds_t			time_to_sleep;
	pthread_mutex_t		forks;
	long				*time;
	int					nbr;
	int					meal;
	struct s_philosoph	*next;
}			t_philo;

typedef struct s_philosopher
{
	int				nbr_of_philosophers;
	int				nbr_of_fork;
	int				nbr_of_meal;
	char			**argv;
	long			timestamp;
	time_t			tv_sec;		
	suseconds_t		tv_usec;
	useconds_t		time_to_die;
	t_philo			*philo;
}				t_param;

useconds_t		ft_atoi(const char *str);
void			ft_lstadd_back(t_philo **lst, t_philo *new);
void			*routine(void *arg);
int				fill_the_table(t_param *philosophers);
void			free_the_table(t_param *table);

#endif