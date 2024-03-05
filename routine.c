/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:14:22 by amema             #+#    #+#             */
/*   Updated: 2024/03/05 14:13:07 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
//prendere una posata, se questa e null il philo muore e torna 0
//se il philo e' vivo prende la posata e torna 1, else non e piu vivo
int	lock_fork(t_philo *philo, pthread_mutex_t *fork, long int start)
{
	if (!fork)
		return (msleep(philo->time_to_die + 100), 0);
	// if (philosopher_check(philo))
	// {
	// 	pthread_mutex_lock(fork);
	// 	locked_print("has taken a fork", start, philo);
	// 	return (1);
	// }
	// else
	// 	return (0);

	pthread_mutex_lock(fork);
	locked_print("has taken a fork", start, philo);
	return (1);
}
//if fork sx e else if fork dx --> mangia
//acquisizione del mutex_personale, blocca una risorsa contemporaneamente
//di base, nella seconda funzione else if se non puo' acquisire anche la fork
//sx, esce dalla funz.

void	eating_process(t_philo *philo, long int start)
{
	if (!lock_fork(philo, philo->left_fork, start))
		return ;
	else if (!lock_fork(philo, philo->right_fork, start))
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	if (philosopher_check(philo))
	{
		pthread_mutex_lock(philo->personal_lock);
		philo->last_eat = get_elapsed_time_ms(start);
		locked_print("is eating", start, philo);
		pthread_mutex_unlock(philo->personal_lock);
		if (philo->meals_count && ++philo->n_of_meals == philo->meals_count)
		{
			pthread_mutex_lock(philo->common_lock);
			*philo->philos_full += 1;
			pthread_mutex_unlock(philo->common_lock);
		}
		msleep(philo->time_to_eat);
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	relax(t_philo *philo, long int start)
{
	locked_print("is sleeping", start, philo);
	msleep(philo->time_to_sleep);
	locked_print("is thinking", *philo->start, philo);
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		locked_print("is thinking", *philo->start, philo);
	if (philo->id % 2 == 0)
		msleep(100);
	while (philosopher_check(philo))
	{
		if (philosopher_check(philo))
			eating_process(philo, *philo->start);
		if (philosopher_check(philo))
			relax(philo, *philo->start);
	}
	return (NULL);
}
