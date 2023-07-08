/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:58:41 by sashaboulog       #+#    #+#             */
/*   Updated: 2023/07/08 16:33:58 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_the_table(t_param *table)
{
	t_philo	*tmp;
	t_philo	*next;

	tmp = table->philo;
	while (table->nbr_of_philosophers > 0)
	{
		next = tmp->next;
		pthread_mutex_destroy(&(tmp->forks));
		if (tmp && tmp != NULL)
			free(tmp);
		tmp = next;
		table->nbr_of_philosophers--;
	}
}

t_philo	*ft_lstnew(char **argv, int philo_nbr, t_param *tmp)
{
	t_philo	*ncontent;

	ncontent = malloc(sizeof(t_philo));
	if (!ncontent)
		return (NULL);
	if (ncontent)
	{
		ncontent->time_to_eat = ft_atoi(argv[3]);
		if (ncontent->time_to_eat < 1)
			return (NULL);
		ncontent->time_to_sleep = ft_atoi(argv[4]);
		if (ncontent->time_to_sleep < 0)
			return (NULL);
		ncontent->meal = 0;
		ncontent->nbr = philo_nbr;
		ncontent->next = NULL;
		ncontent->last_meal = 0;
		ncontent->general = tmp;
		ncontent->eat_enough = 0;
		ncontent->off = &tmp->on;
		ncontent->time_mutex = &tmp->mutex;
		pthread_mutex_init(&ncontent->forks, NULL);
	}
	return (ncontent);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*i;

	i = *lst;
	if (!i)
	{
		*lst = new;
		return ;
	}
	while (i->next)
		i = i->next;
	i->next = new;
}

int	fill_the_table(t_param *philosophers)
{
	t_philo	*current;
	t_philo	*new;
	int		i;
	int		x;

	i = 0;
	x = 1;
	current = NULL;
	new = NULL;
	while (i < philosophers->nbr_of_philosophers)
	{
		new = ft_lstnew(philosophers->argv, x, philosophers);
		if (new == NULL)
			return (printf("Think to sleep and/or eat a good amount of time\n"));
		ft_lstadd_back(&current, new);
		x++;
		i++;
	}
	new = current;
	while (new->next != NULL)
		new = new->next;
	new->next = current;
	philosophers->philo = current;
	return (0);
}

useconds_t	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	useconds_t	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = (res * 10) + str[i] - '0';
		i++;
	}
	return (res * sign);
}
