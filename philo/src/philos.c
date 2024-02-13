/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:45:13 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/13 15:50:06 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_vars			vars;
	t_philosopher	**philosophers;
	int				i;

	if (input_parse(&data, argc, argv))
	{
		printf("Error\nWrong arguments\n");
		return (1);
	}
	mutex_init(vars.mutex, data.num_philos);
	pthread_mutex_init(&(vars.log), NULL);
	data.log = &(vars.log);
	data.died = &(vars.died);
	philosophers = philo_create(&data, vars.mutex);
	philo_init(philosophers, vars.threads);
	while (pthread_mutex_lock(&(vars.died)))
		printf("");
	threads_detach(vars.threads, &data);
	log_death(philosophers);
	return (0);
}
