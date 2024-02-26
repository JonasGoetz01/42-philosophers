/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:26:21 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/26 11:07:12 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_ate_check(t_table *tbl)
{
	pthread_mutex_lock(&(tbl->ft_remain_mutex));
	if (tbl->philos_remaining < 1)
	{
		pthread_mutex_unlock(&(tbl->ft_remain_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(tbl->ft_remain_mutex));
	return (0);
}

int	is_this_philo_done(t_table *tbl, int i)
{
	pthread_mutex_lock(&(tbl->philos[i].meal_eaten_mutex));
	if (tbl->philos[i].meals_goal != -1
		&& tbl->philos[i].meals_eaten >= tbl->philos[i].meals_goal)
	{
		pthread_mutex_unlock(&(tbl->philos[i].meal_eaten_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(tbl->philos[i].meal_eaten_mutex));
	return (0);
}

void	*waiter_check(t_table *tbl)
{
	int		i;
	long	time;

	i = 0;
	while (i < tbl->philos_amt)
	{
		if (all_ate_check(tbl))
			return (stop_sim(tbl, 0, 0));
		time = get_ms_elapsed(tbl);
		if (is_dead(time, &(tbl->philos[i])))
		{
			return (stop_sim(tbl, time, i + 1));
		}
		i++;
	}
	return ((void *)tbl);
}

void	*waiter_routine(void *arg)
{
	t_table	*tbl;

	tbl = (t_table *)arg;
	pthread_mutex_lock(&(tbl->start_mutex));
	tbl->sim_start = get_ms();
	pthread_mutex_unlock(&(tbl->start_mutex));
	while (1)
	{
		if (waiter_check(tbl) == NULL)
			break ;
	}
	return (NULL);
}
