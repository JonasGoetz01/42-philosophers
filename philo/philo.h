/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:13:58 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/26 11:13:58 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# define MAX_PHIL 200
# define MAX_TIME 1000000000

# define ft_FREE_NON 1
# define ft_FREE_ALL 2

# define UNL_NONE 0
# define UNL_LEFT 1
# define UNL_RIGHT 2
# define UNL_END 4
# define UNL_MEAL 8
# define UNL_REM 16
# define UNL_LAST 32

# include <limits.h>
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct s_table;

typedef struct s_philo
{
	int ph_num;
	int t_2_die;
	int t_2_eat;
	int t_2_sleep;
	long t_last_ate;
	int meals_eaten;
	int meals_goal;
	pthread_mutex_t last_ate_mutex;
	pthread_mutex_t meal_eaten_mutex;
	pthread_mutex_t *fork_l;
	pthread_mutex_t *fork_r;
	struct s_table *table;
	int done;
	int eating;
} t_philo;

typedef struct s_table
{
	int meals_goal;
	char end_flag;
	long sim_start;
	int philos_amt;
	int philos_remaining;
	int t_2_die;
	int t_2_eat;
	int t_2_sleep;
	int is_meals_goal;
	pthread_mutex_t start_mutex;
	pthread_mutex_t end_mutex;
	pthread_mutex_t ft_remain_mutex;
	pthread_mutex_t *forks;
	t_philo *philos;
	pthread_t *threads;
	pthread_t waiter;
} t_table;

void	*ft_calloc(size_t count, size_t size);

int	ft_atoi(const char *str);

int	alloc_table(t_table *tbl);

int	init_philo(t_table *tbl, t_philo *ph);

int	prep(t_table *tbl, int argc, char **argv);

void	*ft_eat(t_philo *ph, pthread_mutex_t *r, pthread_mutex_t *l);

void	*ft_sleep(t_philo *ph);

void	ft_think(t_philo *ph);

void	*philo_loop(t_philo *ph);

long	get_ms(void);

long	get_ms_elapsed(t_table *tbl);

int	sleep_ms(t_table *tbl, long time_ms);

void	*waiter_routine(void *arg);

void	*philo_routine(void *arg);

int	is_dead(long time, t_philo *ph);

void	free_mem(t_table *tbl);

int	init_muts(t_table *tbl);

int	init_muts_tbl(t_table *tbl);

int	init_muts_ph(t_table *tbl);

void	destroy_muts(t_table *tbl);

void	start_sim(t_table *tbl);

void	stop_sim(t_table *tbl, long time, int who);

void	*die(t_philo *ph, int to_unlock);

void	*waiter_check(t_table *tbl);

void	swap_forks(t_philo *ph, int i);

#endif