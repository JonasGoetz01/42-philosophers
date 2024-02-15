/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:45:08 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/15 17:35:32 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	philo_runtime(t_philosopher *p)
{
	if (!p)
		return (1);
	if (p->id == 0)
		p->data->timestamp_init = get_ms();
	p->last_time_eaten = get_ms();
	if (p->id % 2 == 1)
		sleep_ms(5);
	while (has_eaten_enough(p) == 0)
	{
		pthread_mutex_lock(p->fork_left);
		ft_log(*(p->data->log), p->data->timestamp_init, p->id, FORK);
		pthread_mutex_lock(p->fork_right);
		ft_log(*(p->data->log), p->data->timestamp_init, p->id, FORK);
		ft_log(*(p->data->log), p->data->timestamp_init, p->id, EAT);
		sleep_ms(p->data->time_to_eat);
		pthread_mutex_unlock(p->fork_left);
		pthread_mutex_unlock(p->fork_right);
		p->last_time_eaten = get_ms();
		ft_log(*(p->data->log), p->data->timestamp_init, p->id, SLEEP);
		sleep_ms(p->data->time_to_sleep);
		ft_log(*(p->data->log), p->data->timestamp_init, p->id, THINK);
		p->times_eaten++;
	}
	return (0);
}

void	ft_eat(t_philosopher *p)
{
	pthread_mutex_lock(p->fork_left);
	ft_log(*(p->data->log), p->data->timestamp_init, p->id, FORK);
	pthread_mutex_lock(p->fork_right);
	ft_log(*(p->data->log), p->data->timestamp_init, p->id, FORK);
	ft_log(*(p->data->log), p->data->timestamp_init, p->id, EAT);
	sleep_ms(p->data->time_to_eat);
	p->last_time_eaten = get_ms();
	p->times_eaten++;
	pthread_mutex_unlock(p->fork_left);
	pthread_mutex_unlock(p->fork_right);
}

void	ft_sleep(t_philosopher *p)
{
	ft_log(*(p->data->log), p->data->timestamp_init, p->id, SLEEP);
	sleep_ms(p->data->time_to_sleep);
}
