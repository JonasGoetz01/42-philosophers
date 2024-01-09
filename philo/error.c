/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:58:20 by jgotz             #+#    #+#             */
/*   Updated: 2024/01/09 12:34:31 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	usage(void)
{
	printf("Wrong number of arguments\n");
	printf("Usage: \n./philo \nnumber_of_philosophers \
	\ntime_to_die time_to_eat \ntime_to_sleep \
	\n[number_of_times_each_philosopher_must_eat]\n");
	exit(1);
}

void	error(char *str)
{
	printf("%s\n", str);
	exit(1);
}