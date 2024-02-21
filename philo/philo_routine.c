/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:25:35 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/21 21:11:10 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_eat(t_philo *ph, pthread_mutex_t *r, pthread_mutex_t *l)
{
	pthread_mutex_lock(l);
	pthread_mutex_lock(&(ph->table->end_mutex));
	if (ph->table->end_flag)
		return (die(ph, UNL_END | UNL_LEFT));
	printf("%ld %d has taken a fork\n", get_elapsed(ph->table), ph->ft_num);
	pthread_mutex_unlock(&(ph->table->end_mutex));
	pthread_mutex_lock(r);
	pthread_mutex_lock(&(ph->table->end_mutex));
	if (ph->table->end_flag)
		return (die(ph, UNL_END | UNL_LEFT | UNL_RIGHT));
	printf("%ld %d has taken a fork\n", get_elapsed(ph->table), ph->ft_num);
	pthread_mutex_unlock(&(ph->table->end_mutex));
	pthread_mutex_lock(&(ph->last_ate_mutex));
	ph->t_last_ate = get_elapsed(ph->table);
	pthread_mutex_unlock(&(ph->last_ate_mutex));
	pthread_mutex_lock(&(ph->table->end_mutex));
	if (ph->table->end_flag)
		return (die(ph, UNL_END | UNL_LEFT | UNL_RIGHT));
	printf("%ld %d is eating\n", ph->t_last_ate, ph->ft_num);
	pthread_mutex_unlock(&(ph->table->end_mutex));
	sleep_ms(ph->table, ph->tteat);
	pthread_mutex_unlock(r);
	pthread_mutex_unlock(l);
	return (NULL);
}

void	*ft_sleep(t_philo *ph)
{
	pthread_mutex_lock(&(ph->table->end_mutex));
	if (ph->table->end_flag)
		return (die(ph, UNL_END));
	printf("%ld %d is sleeping\n", get_elapsed(ph->table), ph->ft_num);
	pthread_mutex_unlock(&(ph->table->end_mutex));
	sleep_ms(ph->table, ph->ttsleep);
	pthread_mutex_lock(&(ph->table->end_mutex));
	if (!ph->table->end_flag)
		printf("%ld %d is thinking\n", get_elapsed(ph->table), ph->ft_num);
	else
		return (die(ph, UNL_END));
	pthread_mutex_unlock(&(ph->table->end_mutex));
	return (NULL);
}

int	logmeal(t_philo *ph)
{
	pthread_mutex_lock(&(ph->meal_eaten_mutex));
	if (ph->meals_eaten >= ph->meals_goal)
	{
		pthread_mutex_unlock(&(ph->meal_eaten_mutex));
		return (0);
	}
	ph->meals_eaten++;
	if (ph->meals_eaten == ph->meals_goal)
	{
		pthread_mutex_lock(&(ph->table->remain_mutex));
		ph->table->philos_remaining -= 1;
		pthread_mutex_unlock(&(ph->table->remain_mutex));
		ph->meals_eaten = ph->meals_goal + 1;
	}
	pthread_mutex_unlock(&(ph->meal_eaten_mutex));
	return (0);
}

void	*philo_live(t_philo *ph)
{
	while (1)
	{
		pthread_mutex_lock(&(ph->table->end_mutex));
		if (ph->table->end_flag)
			return (die(ph, UNL_END));
		pthread_mutex_unlock(&(ph->table->end_mutex));
		ft_eat(ph, ph->fork_r, ph->fork_l);
		logmeal(ph);
		pthread_mutex_lock(&(ph->table->end_mutex));
		if (ph->table->end_flag)
			return (die(ph, UNL_END));
		pthread_mutex_unlock(&(ph->table->end_mutex));
		pthread_mutex_lock(&(ph->meal_eaten_mutex));
		pthread_mutex_unlock(&(ph->meal_eaten_mutex));
		pthread_mutex_lock(&(ph->table->end_mutex));
		if (ph->table->end_flag)
			return (die(ph, UNL_END));
		pthread_mutex_unlock(&(ph->table->end_mutex));
		ft_sleep(ph);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (1)
	{
		if (ph->ft_num % 2 == 0)
			usleep(100);
		pthread_mutex_lock(&(ph->table->start_mutex));
		if (ph->table->sim_start)
		{
			pthread_mutex_unlock(&(ph->table->start_mutex));
			break ;
		}
		pthread_mutex_unlock(&(ph->table->start_mutex));
	}
	if (ph->ft_num % 2 == 1)
		sleep_ms(ph->table, ph->ttsleep / 2);
	return (philo_live(ph));
}
