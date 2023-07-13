/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:21:23 by sboulogn          #+#    #+#             */
/*   Updated: 2023/07/13 11:33:41 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

struct	s_philosopher;

typedef struct s_philosoph
{
	pthread_t				philo;
	long					last_meal;
	int						eat_enough;
	int						*off;
	useconds_t				time_to_eat;
	useconds_t				time_to_sleep;
	pthread_mutex_t			forks;
	pthread_mutex_t			*time_mutex;
	int						nbr;
	int						meal;
	struct s_philosopher	*general;
	struct s_philosoph		*next;
}			t_philo;

typedef struct s_philosopher
{
	int				nbr_of_philosophers;
	int				nbr_of_fork;
	int				nbr_of_meal;
	int				stop_time;
	char			**argv;
	struct timeval	timestamp;
	time_t			tv_sec;		
	suseconds_t		tv_usec;
	useconds_t		time_to_die;
	t_philo			*philo;
	int				on;
	pthread_mutex_t	mutex;
}				t_param;

useconds_t		ft_atoi(const char *str);
void			ft_lstadd_back(t_philo **lst, t_philo *new);
void			*routine(void *arg);
int				fill_the_table(t_param *philosophers);
void			free_the_table(t_param *table);
void			ft_usleep(long int time_in_ms, t_param *time);
long int		time_pass(t_param *time);
int				check_enough_eat(t_param *general);
int				check_death(t_philo *philo, int fork);
int				routine_to_eat(t_philo *philo);
int				routine_to_sleep_and_think(t_philo *philo);
int				routine_all(t_philo *philo);
void			printf_end(t_param *general);
void			ft_putstr(char *str);
void			ft_putnbr(int n);
void			print_actions(int time, int nbr, char *str);

#endif