/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:22:41 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/21 18:23:52 by jgotz            ###   ########.fr       */
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
	pthread_create(&(tbl->waiter), NULL, waiter_routine, tbl);
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
		return (EXIT_FAILURE);
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
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_muts_tbl(t_table *tbl)
{
	if (pthread_mutex_init(&(tbl->start_mutex), NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(tbl->end_mutex), NULL) != 0)
	{
		pthread_mutex_destroy(&(tbl->start_mutex));
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&(tbl->ph_remain_mutex), NULL) != 0)
	{
		pthread_mutex_destroy(&(tbl->start_mutex));
		pthread_mutex_destroy(&(tbl->end_mutex));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_muts(t_table *tbl)
{
	if (init_muts_tbl(tbl) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_muts_ph(tbl) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
