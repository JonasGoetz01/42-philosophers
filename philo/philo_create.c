/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:22:41 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/21 20:48:21 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_sim(t_table *tbl)
{
	int	i;

	i = 0;
	while (i < tbl->philos_amt)
	{
		pthread_create(&(tbl->threads[i]), NULL, philo_routine,
			&(tbl->philos[i]));
		i++;
	}
	pthread_create(&(tbl->supervisor), NULL, supervisor_routine, tbl);
}

int	init_muts_ph(t_table *tbl)
{
	int	i;

	i = 0;
	while (i < tbl->philos_amt)
		if (pthread_mutex_init(&(tbl->forks[i++]), NULL) != 0)
			break ;
	if (i < tbl->philos_amt)
	{
		while (i >= 0)
			pthread_mutex_destroy(&(tbl->forks[i--]));
		return (0);
	}
	i = 0;
	while (i < tbl->philos_amt)
		if (pthread_mutex_init(&(tbl->philos[i++].meal_eaten_mutex), NULL) != 0)
			break ;
	if (i < tbl->philos_amt)
	{
		while (i >= 0)
			pthread_mutex_destroy(&(tbl->philos[i--].meal_eaten_mutex));
		while (++i < tbl->philos_amt)
			pthread_mutex_destroy(&(tbl->forks[i]));
		return (0);
	}
	return (0);
}

int	init_muts_tbl(t_table *tbl)
{
	if (pthread_mutex_init(&(tbl->start_mutex), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(tbl->end_mutex), NULL) != 0)
	{
		pthread_mutex_destroy(&(tbl->start_mutex));
		return (0);
	}
	if (pthread_mutex_init(&(tbl->remain_mutex), NULL) != 0)
	{
		pthread_mutex_destroy(&(tbl->start_mutex));
		pthread_mutex_destroy(&(tbl->end_mutex));
		return (0);
	}
	return (0);
}

int	init_muts(t_table *tbl)
{
	if (init_muts_tbl(tbl) == 0)
		return (0);
	if (init_muts_ph(tbl) == 0)
		return (0);
	return (0);
}
