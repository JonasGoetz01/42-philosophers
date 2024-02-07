/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:02:32 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/07 19:50:36 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_init(pthread_mutex_t *mutex, int n)
{
	int	i;

	i = 0;
	while (i++ < n)
		pthread_mutex_init(&mutex[i], NULL);
}
