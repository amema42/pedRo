/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:23:59 by amema             #+#    #+#             */
/*   Updated: 2024/03/04 18:36:07 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	arg_valid(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (philo_putstr_fd("error: wrong nbr. of args", 2), -1);
	i = 1;
	while (i < argc)
	{
		if (!positive_int(argv[i]))
			return (philo_putstr_fd("error: need positive int args", 2), -1);
		i++;
	}
	return (0);
}

int	positive_int(char *c)
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
	if (n > 0)
		return (1);
	else
		return (0);
}
