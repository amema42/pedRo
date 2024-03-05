/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amema <amema@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:27:57 by amema             #+#    #+#             */
/*   Updated: 2024/03/04 21:06:41 by amema            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo
{
	long int		*start;
	int				*stop;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long int		last_eat;
	int				id;
	int				n_of_meals;
	int				meals_count;
	int				*philos_full;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*common_lock;
	pthread_mutex_t	*personal_lock;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*common_lock;
	pthread_mutex_t	*personal_lock;
	long int		*start;
	int				*stop;
	int				*philos_full;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_count;
	int				meals_count;
}	t_data;

void		msleep(int ms);
long int	get_current_time_ms(void);
int			get_elapsed_time_ms(int start);

void		eating_process(t_philo *philo, long int start);
void		relax(t_philo *philo, long int start);
void		*philo_routine(void *arg);
int			lock_fork(t_philo *philo, pthread_mutex_t *fork, long int start);

int			arg_valid(int argc, char **argv);
int			positive_int(char *c);

t_philo		*create_philo(t_data *data);
t_data		*create_data(char **argv);
pthread_t	*create_threads(t_philo *philo, t_data *data);

void		check_philos(t_philo *philo, t_data *data);
int			death_status(t_philo *philo, t_data *data, long int start);
int			check_buoni_pasto(t_data *data);
int			philosopher_check(t_philo *philo);
void		meal_ctrl(t_data *data, t_philo *philo, pthread_t *threads);

void		locked_print(char *action, long int start, t_philo *philo);
int			another_atoi(char *c);
void		philo_putstr_fd(char *str, int fd);
void		*philo_calloc(int count, int size);
void		free_all(t_data *data);

#endif
