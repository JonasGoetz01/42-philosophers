/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:22:20 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/21 21:11:32 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

long	get_elapsed(t_table *tbl)
{
	long			curtime;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	curtime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (curtime - tbl->sim_start);
}

int	sleep_ms(t_table *tbl, long time_ms)
{
	long	tmp;

	tmp = get_ms();
	while (get_ms() - tmp < time_ms)
	{
		usleep(50);
		pthread_mutex_lock(&(tbl->end_mutex));
		if (tbl->end_flag)
		{
			pthread_mutex_unlock(&(tbl->end_mutex));
			return (1);
		}
		pthread_mutex_unlock(&(tbl->end_mutex));
	}
	return (0);
}
