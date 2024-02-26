/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:22:41 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/26 10:58:03 by jgotz            ###   ########.fr       */
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
		pthread_mutex_init(&(tbl->forks[i++]), NULL);
	i = 0;
	while (i < tbl->philos_amt)
		pthread_mutex_init(&(tbl->philos[i++].meal_eaten_mutex), NULL);
	return (EXIT_SUCCESS);
}

int	init_muts_tbl(t_table *tbl)
{
	pthread_mutex_init(&(tbl->start_mutex), NULL);
	pthread_mutex_init(&(tbl->end_mutex), NULL);
	pthread_mutex_init(&(tbl->ft_remain_mutex), NULL);
	return (EXIT_SUCCESS);
}

int	init_muts(t_table *tbl)
{
	init_muts_tbl(tbl);
	init_muts_ph(tbl);
	return (EXIT_SUCCESS);
}
