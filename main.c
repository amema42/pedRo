/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:14:12 by amema             #+#    #+#             */
/*   Updated: 2024/03/04 18:11:42 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	pthread_t	*threads;
	t_philo		*philo;
	t_data		*data;

	if (arg_valid(argc, argv) == -1)
		return (EXIT_FAILURE);
	data = create_data(argv);
	if (!data)
		return (EXIT_FAILURE);
	philo = create_philo(data);
	if (!philo)
		return (free_all(data), EXIT_FAILURE);
	threads = create_threads(philo, data);
	if (!threads)
		return (free(philo), free_all(data), EXIT_FAILURE);
	check_philos(philo, data);
	meal_ctrl(data, philo, threads);
	return (EXIT_SUCCESS);
}
