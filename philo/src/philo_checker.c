/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:03:33 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/12 14:32:02 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	philo_checker(t_philosopher **philos)
{
	int	i;

	while (1)
	{
		i = 0;
		while (philos[i])
			check_if_dead_checker(philos, philos[i++]);
		check_if_everyone_has_eaten(philos);
	}
}

void	check_if_dead_checker(t_philosopher **philos, t_philosopher *p)
{
	if (get_ms() - p->last_time_eaten > p->data->time_to_die)
	{
		if (check_if_everyone_has_eaten(philos) == 0)
			p->dead = get_ms() - p->data->timestamp_init;
		pthread_mutex_init(p->data->died, NULL);
	}
}

int	check_if_everyone_has_eaten(t_philosopher **philosophers)
{
	int	i;
	int	times_must_eat;

	i = 0;
	times_must_eat = philosophers[i]->data->num_must_eat;
	while (philosophers[i])
	{
		if (times_must_eat == -1
			|| times_must_eat > philosophers[i]->times_eaten)
			return (0);
		i++;
	}
	pthread_mutex_init(philosophers[0]->data->died, NULL);
	return (1);
}

int	has_eaten_enough(t_philosopher *p)
{
	int	times_must_eat;

	times_must_eat = p->data->num_must_eat;
	if (times_must_eat == -1 || times_must_eat > p->times_eaten)
		return (0);
	return (1);
}
