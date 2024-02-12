/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:45:26 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/12 17:38:37 by jgotz            ###   ########.fr       */
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
		ret = ret * 10 + sign * (*str++ - '0');
	if (ret > 2147483647)
		return (-1);
	else if (ret < -2147483648)
		return (0);
	return ((int)ret);
}

void	mutex_init(pthread_mutex_t *mutex, int n)
{
	int	i;

	i = 0;
	while (i++ < n)
		pthread_mutex_init(&mutex[i], NULL);
}
