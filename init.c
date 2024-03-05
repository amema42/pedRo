/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:23:45 by amema             #+#    #+#             */
/*   Updated: 2024/03/04 22:23:20 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = philo_calloc(data->philo_count, sizeof(t_philo));
	if (!philo)
		return (NULL);
	i = -1;
	while (++i < data->philo_count)
	{
		philo[i].time_to_die = data->time_to_die;
		philo[i].time_to_eat = data->time_to_eat;
		philo[i].time_to_sleep = data->time_to_sleep;
		philo[i].meals_count = data->meals_count;
		philo[i].id = i + 1;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->philo_count];
		if (data->philo_count == 1)
			philo[i].right_fork = NULL;
		philo[i].personal_lock = &data->personal_lock[i];
		philo[i].common_lock = data->common_lock;
		philo[i].start = data->start;
		philo[i].stop = data->stop;
		philo[i].philos_full = data->philos_full;
	}
	return (philo);
}

int	allocate_data(t_data *data)
{
	data->forks = philo_calloc(data->philo_count, sizeof(pthread_mutex_t));
	if (!data->forks)
		return (0);
	data->personal_lock = philo_calloc(data->philo_count,
			sizeof(pthread_mutex_t));
	if (!data->personal_lock)
		return (0);
	data->common_lock = philo_calloc(1, sizeof(pthread_mutex_t));
	if (!data->common_lock)
		return (0);
	data->start = philo_calloc(1, sizeof(long int));
	if (!data->start)
		return (0);
	data->stop = philo_calloc(1, sizeof(int));
	if (!data->stop)
		return (0);
	data->philos_full = philo_calloc(1, sizeof(int));
	if (!data->philos_full)
		return (0);
	return (1);
}

t_data	*create_data(char **argv)
{
	t_data	*data;
	int		i;

	i = -1;
	data = philo_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->philo_count = another_atoi(argv[1]);
	data->time_to_die = another_atoi(argv[2]);
	data->time_to_eat = another_atoi(argv[3]);
	data->time_to_sleep = another_atoi(argv[4]);
	if (argv[5])
		data->meals_count = another_atoi(argv[5]);
	if (!allocate_data(data))
		return (free_all(data), NULL);
	while (++i < data->philo_count)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->personal_lock[i], NULL);
	}
	pthread_mutex_init(data->common_lock, NULL);
	return (data);
}

pthread_t	*create_threads(t_philo *philo, t_data *data)
{
	pthread_t	*threads;
	int			i;

	threads = philo_calloc(data->philo_count, sizeof(pthread_t));
	if (!threads)
		return (NULL);
	i = -1;
	*data->start = get_current_time_ms();
	while (++i < data->philo_count)
	{
		if (pthread_create(&threads[i], NULL, &philo_routine, &philo[i]) != 0)
		{
			free(threads);
			return (philo_putstr_fd("thread creation: failed", 2), NULL);
		}
	}
	return (threads);
}
