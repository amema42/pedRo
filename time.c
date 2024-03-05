/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 11:14:22 by amema             #+#    #+#             */
/*   Updated: 2024/03/05 16:39:47 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//in timeval sono ottenuti sec e millisec, converto e return tempo tot
long int	get_current_time_ms(void)
{
	struct timeval	current;

	if (gettimeofday(&current, NULL) != 0)
	{
		return (-1);
	}
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

int	get_elapsed_time_ms(int start)
{
	return ((int)(get_current_time_ms() - start));
}

//checkin using timeToSleep

void	msleep(int ms)
{
	long int	sleep_start;

	sleep_start = get_current_time_ms();
	while (get_elapsed_time_ms(sleep_start) < ms)
		usleep(100);
}
