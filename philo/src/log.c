/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:15:21 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/07 19:15:23 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_log(pthread_mutex_t mutex, long timestamp_init, int id,
		char *message)
{
	pthread_mutex_lock(&mutex);
	printf("%ld %i %s\n", get_current_time_ms() - timestamp_init, id + 1,
		message);
	pthread_mutex_unlock(&mutex);
}

void	log_death(t_philosopher **philosophers)
{
	int	i;

	i = 0;
	while (philosophers[i])
	{
		if (philosophers[i]->dead)
		{
			printf("%ld %i died\n", philosophers[i]->dead, i + 1);
			exit(0);
		}
		i++;
	}
}
