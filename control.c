/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 11:14:19 by amema             #+#    #+#             */
/*   Updated: 2024/03/05 16:35:08 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philosopher_check(t_philo *philo)
{
	pthread_mutex_lock(philo->common_lock);
	if (!*(philo->stop))
		return (pthread_mutex_unlock(philo->common_lock), 1);
	else
		return (pthread_mutex_unlock(philo->common_lock), 0);
}

int	check_buoni_pasto(t_data *data)
{
	pthread_mutex_lock(data->common_lock);
	if (*data->philos_full == data->philo_count)
	{
		printf("every philosopher ate %d times\n", data->meals_count);
		*data->stop = 1;
		return (pthread_mutex_unlock(data->common_lock), 1);
	}
	return (pthread_mutex_unlock(data->common_lock), 0);
}

int	death_status(t_philo *philo, t_data *data, long int start)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_lock(&data->personal_lock[i]);
		if (get_elapsed_time_ms(start) - philo[i].last_eat > data->time_to_die)
		{
			pthread_mutex_unlock(&data->personal_lock[i]);
			pthread_mutex_lock(data->common_lock);
			*data->stop = 1;
			printf("%d\t%d\tdied\n", get_elapsed_time_ms(start), philo[i].id);
			pthread_mutex_unlock(data->common_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->personal_lock[i]);
	}
	return (0);
}

void	check_philos(t_philo *philo, t_data *data)
{
	long int	start;

	start = *philo->start;
	while (1)
	{
		if (death_status(philo, data, start) == 1)
			return ;
		if (data->meals_count && check_buoni_pasto(data) == 1)
			return ;
	}
}

void	meal_ctrl(t_data *data, t_philo *philo, pthread_t *threads)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_join(threads[i], NULL) != 0)
			philo_putstr_fd("thread creation: failed", 2);
	}
	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->personal_lock[i]);
	}
	pthread_mutex_destroy(data->common_lock);
	free_all(data);
	free(threads);
	free(philo);
}
