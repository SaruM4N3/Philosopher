/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:34:06 by zsonie            #+#    #+#             */
/*   Updated: 2025/05/10 00:45:01 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <time.h>
#include <stdio.h>

//STRUCT

typedef struct s_fork 
{
	int is_available;
}	t_fork;

typedef struct s_philo
{
	t_fork left_fork;
	t_fork right_fork;
}	t_philo;

typedef struct s_rules
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_rules;

// FUNCTIONS
void	ft_putchar(char c);
void	ft_putstr(char *str);
int		ft_strlen(char *str);

#endif
