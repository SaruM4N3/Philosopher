/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:28 by zsonie            #+#    #+#             */
/*   Updated: 2025/05/20 16:48:31 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	grab_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left_fork->mutex));
	print_action(philo, FORK);
	if (philo->info->number_of_philosophers == 1)
	{
		usleep(philo->info->time_to_die + 1);
		return ;
	}
	pthread_mutex_lock(&(philo->right_fork->mutex));
	print_action(philo, FORK);
}

void	release_fork(t_philo *philo)
{
	__builtin_printf("release\n");
	if (!philo->left_fork->is_available && !philo->right_fork->is_available)
	{
		philo->left_fork->is_available = true;
		philo->right_fork->is_available = true;
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
	}
}

void	philo_eat(t_philo *philo)
{
	grab_fork(philo);
	philo->is_eating = true;
	pthread_mutex_lock(&philo->eat_mutex);
	philo->left_fork->is_available = false;
	philo->right_fork->is_available = false;
	philo->last_eat_time = timestamp_in_ms();
	philo->meals_eaten++;
	print_action(philo, EAT);
	pthread_mutex_unlock(&philo->eat_mutex);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->sleep_mutex);
	print_action(philo, SLEEP);
}

void	*life(void *philo)
{
	t_philo	*curphilo;

	curphilo = (t_philo *)philo;
	if (curphilo->is_eating || curphilo->is_dead || curphilo->is_sleeping)
	{
		printf("ERROR: already in action\n");
		return NULL;
	}
	if (curphilo->left_fork->is_available && curphilo->right_fork->is_available)
	{
		philo_eat(curphilo);
	}
	else 
		philo_sleep(curphilo);
	print_action(curphilo, THINK);
	pthread_join(curphilo->thread, NULL);
	release_fork(curphilo);
	return (NULL);
}
