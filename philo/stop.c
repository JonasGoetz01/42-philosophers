/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:25:58 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/26 10:58:03 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mem(t_table *tbl)
{
	free(tbl->philos);
	free(tbl->forks);
	free(tbl->threads);
}

void	destroy_muts(t_table *tbl)
{
	int	i;

	i = 0;
	while (i < tbl->philos_amt)
	{
		pthread_mutex_destroy(&(tbl->forks[i]));
		pthread_mutex_destroy(&(tbl->philos[i].meal_eaten_mutex));
		pthread_mutex_destroy(&(tbl->philos[i].last_ate_mutex));
		i++;
	}
	pthread_mutex_destroy(&(tbl->end_mutex));
	pthread_mutex_destroy(&(tbl->start_mutex));
	pthread_mutex_destroy(&(tbl->ft_remain_mutex));
}

void	*stop_sim(t_table *tbl, long time, int who)
{
	pthread_mutex_lock(&(tbl->end_mutex));
	tbl->end_flag = 1;
	if (time && who)
		printf("%ld %d died\n", time, who);
	pthread_mutex_unlock(&(tbl->end_mutex));
	return (NULL);
}
