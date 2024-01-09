/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgotz <jgotz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:51:15 by jgotz             #+#    #+#             */
/*   Updated: 2024/01/09 17:50:48 by jgotz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <time.h>
#define NUM_THREADS 2

int mails = 0;
pthread_mutex_t mutex;

void	*routine(void *arg)
{
	(void)arg;
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

void input_parsing(int argc, char **argv)
{
	t_args	args;

	if (argc < 5 || argc > 6)
		usage();
	args.num_philo = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args.num_eat = ft_atoi(argv[5]);
	else
		args.num_eat = -1;
}

int	main(int argc, char **argv)
{
	args_t		args;
	clock_t		start_time;
	clock_t		end_time;
	double		cpu_time_used;
	pthread_t	th[NUM_THREADS];

	input_parsing(argc, argv, );
    start_time = clock();
	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < NUM_THREADS; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			error("Error creating thread");
	}

	for (int i = 0; i < NUM_THREADS; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			error("Error joining thread");
	}

	pthread_mutex_destroy(&mutex);
	printf("mails: %d\n", mails);
	end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("CPU time used: %f seconds\n", cpu_time_used);
}
