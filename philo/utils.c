/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:26:15 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/26 11:13:08 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	int				offset;
	int				len;

	if (count == 0 || size == 0)
		return (NULL);
	len = count * size;
	ptr = (unsigned char *)malloc(len);
	if (!ptr)
		return (NULL);
	offset = 0;
	while (offset < len)
		ptr[offset++] = 0;
	return ((void *)ptr);
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
			return (0);
	}
	if (ret > INT_MAX)
		return (0);
	else if (ret < INT_MIN)
		return (0);
	return ((int)ret);
}

int	is_dead(long time, t_philo *ph)
{
	long	last_ate;

	pthread_mutex_lock(&(ph->last_ate_mutex));
	last_ate = ph->t_last_ate;
	pthread_mutex_unlock(&(ph->last_ate_mutex));
	if (time >= last_ate + ph->t_2_die)
	{
		pthread_mutex_lock(&(ph->table->end_mutex));
		ph->table->end_flag = 1;
		pthread_mutex_unlock(&(ph->table->end_mutex));
		return (ph->ph_num);
	}
	return (0);
}

void	*die(t_philo *ph, int to_unlock)
{
	if (to_unlock & UNL_RIGHT)
		pthread_mutex_unlock(ph->fork_r);
	if (to_unlock & UNL_LEFT)
		pthread_mutex_unlock(ph->fork_l);
	if (to_unlock & UNL_END)
		pthread_mutex_unlock(&(ph->table->end_mutex));
	if (to_unlock & UNL_MEAL)
		pthread_mutex_unlock(&(ph->meal_eaten_mutex));
	if (to_unlock & UNL_REM)
		pthread_mutex_unlock(&(ph->table->ft_remain_mutex));
	if (to_unlock & UNL_LAST)
		pthread_mutex_unlock(&(ph->last_ate_mutex));
	pthread_mutex_lock(&(ph->table->ft_remain_mutex));
	ph->table->philos_remaining -= 1;
	pthread_mutex_unlock(&(ph->table->ft_remain_mutex));
	pthread_mutex_lock(&(ph->meal_eaten_mutex));
	ph->meals_eaten = ph->meals_goal + 1;
	pthread_mutex_unlock(&(ph->meal_eaten_mutex));
	return (NULL);
}
