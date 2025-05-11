/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:34:06 by zsonie            #+#    #+#             */
/*   Updated: 2025/05/11 19:21:54 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

//STRUCT

typedef struct s_fork 
{
	pthread_mutex_t mutex;
	bool is_available;
}	t_fork;

typedef struct s_philo
{
	pthread_t thread;
	int id;
	int meals_eaten;
	int last_eat_time;
	bool is_eating;
	bool is_sleeping;
	bool is_dead;
	t_fork left_fork;
	t_fork right_fork;
	pthread_mutex_t eat_mutex;
	pthread_mutex_t sleep_mutex;
	pthread_mutex_t dead_mutex;
}	t_philo;

typedef struct s_env
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	int	start_time;
	t_philo	*philos;
}	t_env;

// FUNCTIONS


void	ft_putchar(char c);
void	ft_putstr(char *str);
int		ft_atoi(const char *str);
int		ft_strlen(char *str);

#endif
