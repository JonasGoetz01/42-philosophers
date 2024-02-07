/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:45:02 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/07 21:22:43 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_philosopher **philosophers, pthread_t *threads)
{
	int	i;

	i = 0;
	while (philosophers[i])
	{
		pthread_create(&threads[i], NULL, (void *)philo_runtime,
			philosophers[i]);
		i++;
	}
	pthread_create(&threads[250], NULL, (void *)philo_checker, philosophers);
}

void	threads_detach(pthread_t *threads, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
		pthread_detach(threads[i++]);
	pthread_detach(threads[250]);
}
