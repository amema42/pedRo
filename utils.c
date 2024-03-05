/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 11:14:56 by amema             #+#    #+#             */
/*   Updated: 2024/03/04 18:12:35 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	locked_print(char *action, long int start, t_philo *philo)
{
	pthread_mutex_lock(philo->common_lock);
	if (!*philo->stop)
		printf("%d\t%d\t%s\n", get_elapsed_time_ms(start), philo->id, action);
	pthread_mutex_unlock(philo->common_lock);
}

int	another_atoi(char *c)
{
	long int	n;

	n = 0;
	while (*c)
	{
		if (*c < '0' || *c > '9')
			return (0);
		n *= 10;
		n += (*c - '0');
		if (n > 2147483647)
			return (0);
		c++;
	}
	return (n);
}

void	philo_putstr_fd(char *str, int fd)
{
	while (str && *str)
		write(fd, str++, 1);
}

// void	*p_calloc(int count, int size)
// {
// 	int		i;
// 	char	*ptr;

// 	i = 0;
// 	ptr = malloc(count * size);
// 	if (!ptr)
// 		return (philo_putstr_fd(ALLOC_ERROR, 2), NULL);
// 	while (i < count * size)
// 		ptr[i++] = 0;
// 	return ((void *)ptr);
// }

void	*philo_calloc(int i, int size)
{
	void	*ptr;

	if (i <= 0 || size <= 0 || i > (INT_MAX / size))
		return (NULL);
	ptr = malloc(i * size);
	if (!ptr)
	{
		philo_putstr_fd("allocation failed", 2);
		return (NULL);
	}
	memset(ptr, 0, i * size);
	return (ptr);
}

void	free_all(t_data *data)
{
	if (data && data->forks)
		free(data->forks);
	if (data && data->personal_lock)
		free(data->personal_lock);
	if (data && data->common_lock)
		free(data->common_lock);
	if (data && data->start)
		free(data->start);
	if (data && data->stop)
		free(data->stop);
	if (data && data->philos_full)
		free(data->philos_full);
	if (data)
		free(data);
}
