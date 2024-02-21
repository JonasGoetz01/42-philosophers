/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:20:40 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/21 20:20:52 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;

	if (prep(&table, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (table.philos_amt == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(ft_atoi(argv[2]) * 1000);
		printf("%d 1 died\n", ft_atoi(argv[2]));
	}
	else
	{
		start_sim(&table);
		i = 0;
		while (i < table.philos_amt)
			pthread_join(table.threads[i++], NULL);
		pthread_join(table.waiter, NULL);
	}
	destroy_muts(&table);
	free_mem(&table);
	return (0);
}
