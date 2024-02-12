/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:44:54 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/12 14:32:02 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

t_philosopher	**philo_create(t_data *data, pthread_mutex_t *forks)
{
	int				i;
	t_philosopher	**philosophers;

	i = 0;
	philosophers = malloc(sizeof(t_philosopher *) * data->num_philos + 1);
	philosophers[data->num_philos] = NULL;
	while (i < data->num_philos)
	{
		philosophers[i] = malloc(sizeof(t_philosopher));
		philosophers[i]->data = data;
		philosophers[i]->dead = 0;
		philosophers[i]->id = i;
		philosophers[i]->times_eaten = 0;
		if (i == 0)
			philosophers[i]->fork_left = &forks[philosophers[i]->data->num_philos
				- 1];
		else
			philosophers[i]->fork_left = &forks[i - 1];
		philosophers[i]->fork_right = &forks[i];
		i++;
	}
	return (philosophers);
}

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
