/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:22:41 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/26 11:05:46 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc_table(t_table *tbl)
{
	tbl->forks = ft_calloc(tbl->philos_amt, sizeof(pthread_mutex_t));
	if (tbl->forks == NULL)
		return (EXIT_FAILURE);
	tbl->threads = ft_calloc(tbl->philos_amt, sizeof(pthread_t));
	if (tbl->threads == NULL)
	{
		free(tbl->forks);
		return (EXIT_FAILURE);
	}
	tbl->philos = ft_calloc(tbl->philos_amt, sizeof(t_philo));
	if (tbl->philos == NULL)
	{
		free(tbl->forks);
		free(tbl->threads);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_philo(t_table *tbl, t_philo *ph)
{
	int	i;

	i = 0;
	while (i < tbl->philos_amt)
	{
		(&(ph[i]))->ph_num = i + 1;
		(&(ph[i]))->t_2_die = tbl->t_2_die;
		(&(ph[i]))->t_2_eat = tbl->t_2_eat;
		(&(ph[i]))->t_2_sleep = tbl->t_2_sleep;
		(&(ph[i]))->t_last_ate = 0;
		(&(ph[i]))->meals_eaten = 0;
		(&(ph[i]))->meals_goal = tbl->meals_goal;
		(&(ph[i]))->fork_l = &(tbl->forks[i]);
		(&(ph[i]))->fork_r = &(tbl->forks[(i + 1) % tbl->philos_amt]);
		(&(ph[i]))->table = tbl;
		(&(ph[i]))->done = 0;
		i++;
	}
	return (EXIT_SUCCESS);
}

void	init_table(t_table *tbl, int argc, char **argv)
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
		tbl->t_2_die = ft_atoi(*(argv++));
	if (argv && *argv)
		tbl->t_2_eat = ft_atoi(*(argv++));
	if (argv)
		tbl->t_2_sleep = ft_atoi(*(argv++));
	if (argv && *argv)
		tbl->meals_goal = ft_atoi(*argv);
	if (tbl->meals_goal == -1)
		tbl->is_meals_goal = 0;
	else
		tbl->is_meals_goal = 1;
}

int	check_table_statics(t_table *tbl)
{
	if (tbl->philos_amt > MAX_PHIL)
	{
		printf("Too many philosophers!\n");
		return (EXIT_FAILURE);
	}
	else if (tbl->philos_amt == 0 || tbl->t_2_die == 0 || tbl->t_2_eat == 0
		|| tbl->t_2_sleep == 0 || tbl->meals_goal == 0)
	{
		printf("Input error!\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	prep(t_table *tbl, int argc, char **argv)
{
	init_table(tbl, argc, argv);
	if (check_table_statics(tbl) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (alloc_table(tbl) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_philo(tbl, tbl->philos) == EXIT_FAILURE)
	{
		free_mem(tbl);
		return (EXIT_FAILURE);
	}
	if (init_muts(tbl) == EXIT_FAILURE)
	{
		free_mem(tbl);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
