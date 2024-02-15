/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:45:26 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/15 17:22:02 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\a' || c == '\b' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	ret;

	ret = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		++str;
	if (*str == '+' || *str == '-')
		if (*(str++) == '-')
			sign *= -1;
	while (ft_isdigit(*str))
	{
		ret = ret * 10 + sign * (*str++ - '0');
		if (ret > LONG_MAX)
			ft_exit();
	}
	if (ret > INT_MAX)
		ft_exit();
	else if (ret < INT_MIN)
		ft_exit();
	return ((int)ret);
}

void	mutex_init(pthread_mutex_t *mutex, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
}
