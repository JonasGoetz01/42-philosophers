/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:14:41 by jgotz             #+#    #+#             */
/*   Updated: 2024/02/15 17:11:25 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	long			timestamp_init;
	pthread_mutex_t	*died;
	pthread_mutex_t	*log;
}					t_data;

typedef struct s_philosopher
{
	int				id;
	int				times_eaten;
	long			dead;
	long			last_time_eaten;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_data			*data;
}					t_philosopher;

typedef struct s_vars
{
	pthread_mutex_t	mutex[250];
	pthread_mutex_t	log;
	pthread_mutex_t	died;
	pthread_t		threads[251];
}					t_vars;

void				philo_init(t_philosopher **philosophers,
						pthread_t *threads);
void				threads_detach(pthread_t *threads, t_data *data);
t_philosopher		**philo_create(t_data *data, pthread_mutex_t *forks);
int					philo_runtime(t_philosopher *p);
void				mutex_init(pthread_mutex_t *mutex, int n);
void				philo_checker(t_philosopher **philos);
int					ft_atoi(const char *str);
int					is_space(char c);
void				ft_log(pthread_mutex_t mutex, long timestamp_init, int id,
						char *message);
void				log_death(t_philosopher **philosophers);
long				get_ms(void);
void				sleep_ms(int ms);
void				check_if_dead(t_philosopher *p);
void				ft_eat(t_philosopher *p);
void				ft_sleep(t_philosopher *p);
int					has_eaten_enough(t_philosopher *p);
void				dead_checker(t_philosopher **philos, t_philosopher *p);
int					check_all_eaten(t_philosopher **philosophers);
void				log_death(t_philosopher **philosophers);
int					ft_strlen(char *str);
int					input_check(int argc, char **argv);
int					input_parse(t_data *data, int argc, char **argv);
int					ft_isdigit(int c);
void				ft_exit(void);
#endif