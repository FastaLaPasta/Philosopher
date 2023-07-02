/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:58:41 by sashaboulog       #+#    #+#             */
/*   Updated: 2023/07/02 17:12:33 by sboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_the_table(s_philosopher *table)
{
	t_philosoph	*tmp;
	t_philosoph *next;

	tmp = table->philosoph;
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

t_philosoph	*ft_lstnew(char **argv)
{
	t_philosoph	*ncontent;

	ncontent = malloc(sizeof(t_philosoph));
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
		ncontent->next = NULL;
		pthread_mutex_init(&ncontent->forks, NULL);
		pthread_create(&ncontent->philo, NULL, &routine, ncontent);
	}
	return (ncontent);
}

void	ft_lstadd_back(t_philosoph **lst, t_philosoph *new)
{
	t_philosoph	*i;

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

int	fill_the_table(s_philosopher *philosophers)
{
	t_philosoph	*current;
	t_philosoph *new;
	int	i;

	i = 0;
	current = NULL;
	new = NULL;
	while (i < philosophers->nbr_of_philosophers)
	{
		new = ft_lstnew(philosophers->argv);
		if (new == NULL)
			return (printf("Think to sleep and/or eat a good amount of time\n"));
		ft_lstadd_back(&current, new);
		i++;
	}
	new = current;
	while (new->next != NULL)
		new = new->next;
	new->next = current;
	philosophers->philosoph = current;
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