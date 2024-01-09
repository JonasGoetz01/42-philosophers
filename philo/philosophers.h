/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:51:59 by jgotz             #+#    #+#             */
/*   Updated: 2024/01/09 17:09:59 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct args_s
{
	int	num_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_eat;
}		args_t;

void	error(char *str);

void	usage(void);

int		ft_atoi(const char *str);

#endif
