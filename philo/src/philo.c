/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:28 by zsonie            #+#    #+#             */
/*   Updated: 2025/05/19 18:16:37 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	grab_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left_fork->mutex));
	print_action(philo,FORK);
	if (philo->info->number_of_philosophers == 1)
	{
		usleep(philo->info->time_to_die + 1);
		return;
	}
	pthread_mutex_lock(&(philo->right_fork->mutex));
	print_action(philo,FORK);
}

void	eat(t_philo *philo)
{
	if (philo->is_eating || philo->is_dead || philo->is_sleeping)
	{
		printf("ERROR: already in action\n");
		return;
	}
	if (philo->left_fork->is_available && philo->right_fork->is_available)
	{
		grab_fork(philo);
		philo->is_eating = true;
		pthread_mutex_lock(&philo->eat_mutex);
		philo->left_fork->is_available = false;
		philo->right_fork->is_available = false;
		print_action(philo, EAT);
		philo->last_eat_time = timestamp_in_ms();
		philo->meals_eaten++;
		philo->left_fork->is_available = true;
		philo->right_fork->is_available = true;
		pthread_mutex_unlock(&(philo->left_fork->mutex));
		pthread_mutex_unlock(&(philo->right_fork->mutex));
	}
	else
		print_test((void *) philo);
	pthread_mutex_unlock(&philo->eat_mutex);
}

void	*life(void *philo)
{
	t_philo	*curphilo = (t_philo *)philo;
	eat(curphilo);
	print_action(curphilo, THINK);
	return NULL;
}
