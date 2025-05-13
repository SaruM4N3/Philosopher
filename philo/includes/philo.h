/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:34:06 by zsonie            #+#    #+#             */
/*   Updated: 2025/05/13 16:29:21 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "error.h"

//Colors
#define	RED	"\e[31m"
#define	GREEN  "\e[32m"
#define	YELLOW "\e[33m"
#define	RESET  "\e[0m"

//Error
#define	ERR_ARG 1001

//STRUCT

typedef struct s_fork 
{
	int				id;
	bool			is_available;
	pthread_mutex_t mutex;
}	t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	int				last_eat_time;
	bool			is_eating;
	bool			is_sleeping;
	bool			is_dead;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	sleep_mutex;
	pthread_mutex_t	dead_mutex;
}	t_philo;

typedef struct s_env
{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
	int		start_time;
	t_philo	*philos;
	t_fork	*last_fork;
}	t_env;

// FUNCTIONS

//display.c
void	*print_test(void *philo);
void	*print_test_first_philo(void *philo);

//ft_atoi.c
int		ft_atoi(const char *str);

//utils.c
void	ft_putchar(char c);
void	ft_putstr(char *str);
int		ft_strlen(char *str);

#endif
