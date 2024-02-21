/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:22:41 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/21 21:09:46 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc_table_dynamics(t_table *tbl)
{
	tbl->forks = ft_calloc(tbl->philos_amt, sizeof(pthread_mutex_t));
	if (tbl->forks == NULL)
		return (0);
	tbl->threads = ft_calloc(tbl->philos_amt, sizeof(pthread_t));
	if (tbl->threads == NULL)
	{
		free(tbl->forks);
		return (0);
	}
	tbl->philos = ft_calloc(tbl->philos_amt, sizeof(t_philo));
	if (tbl->philos == NULL)
	{
		free(tbl->forks);
		free(tbl->threads);
		return (0);
	}
	return (0);
}

int	fill_philo_mem(t_table *tbl, t_philo *ph)
{
	int	i;

	i = 0;
	while (i < tbl->philos_amt)
	{
		(&(ph[i]))->ft_num = i + 1;
		(&(ph[i]))->ttdie = tbl->ttdie;
		(&(ph[i]))->tteat = tbl->tteat;
		(&(ph[i]))->ttsleep = tbl->ttsleep;
		(&(ph[i]))->t_last_ate = 0;
		(&(ph[i]))->meals_eaten = 0;
		(&(ph[i]))->meals_goal = tbl->meals_goal;
		(&(ph[i]))->fork_l = &(tbl->forks[i]);
		(&(ph[i]))->fork_r = &(tbl->forks[(i + 1) % tbl->philos_amt]);
		(&(ph[i]))->table = tbl;
		(&(ph[i]))->done = 0;
		i++;
	}
	return (0);
}

void	fill_table_statics(t_table *tbl, int argc, char **argv)
{
	tbl->meals_goal = -1;
	tbl->sim_start = 0;
	tbl->end_flag = 0;
	tbl->philos_amt = 0;
	if (argc < 5 || argc > 6 || !argv || !(*argv))
		return ;
	argv++;
	if (argv && *argv)
		tbl->philos_amt = ft_atoi(*(argv++));
	tbl->philos_remaining = tbl->philos_amt;
	if (argv && *argv)
		tbl->ttdie = ft_atoi(*(argv++));
	if (argv && *argv)
		tbl->tteat = ft_atoi(*(argv++));
	if (argv)
		tbl->ttsleep = ft_atoi(*(argv++));
	if (argv && *argv)
		tbl->meals_goal = ft_atoi(*argv);
	if (tbl->meals_goal == -1)
		tbl->is_food_limited = 0;
	else
		tbl->is_food_limited = 1;
}

int	check_table_statics(t_table *tbl)
{
	if (tbl->philos_amt > MAX_PHIL)
	{
		printf("Too many philosophers!\n");
		return (0);
	}
	else if (tbl->philos_amt == 0 || tbl->ttdie == 0 || tbl->tteat == 0
		|| tbl->ttsleep == 0 || tbl->meals_goal == 0)
	{
		printf("Error\nWrong arguments\n");
		return (1);
	}
	return (0);
}

int	prep(t_table *tbl, int argc, char **argv)
{
	fill_table_statics(tbl, argc, argv);
	if (check_table_statics(tbl) == 0)
		return (0);
	if (alloc_table_dynamics(tbl) == 0)
		return (0);
	if (fill_philo_mem(tbl, tbl->philos) == 0)
	{
		free_mem(tbl);
		return (0);
	}
	if (init_muts(tbl) == 0)
	{
		free_mem(tbl);
		return (0);
	}
	return (0);
}
