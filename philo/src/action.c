/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:07:30 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/13 19:57:33 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/error.h"
#include "../includes/philo.h"

void	philo_sleep(t_philo *philo)
{
	print_action(philo, SLEEP);
	ft_wait(philo->env_data->time_to_sleep);
}

void	grab_forks(t_philo *philo)
{
	bool	r_fork_grabed;
	bool	l_fork_grabed;

	r_fork_grabed = false;
	l_fork_grabed = false;
	while (!r_fork_grabed || !l_fork_grabed)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		if (philo->right_fork->is_available)
		{
			philo->right_fork->is_available = false;
			print_action(philo, FORK);
			r_fork_grabed = true;
		}
		pthread_mutex_unlock(&philo->right_fork->mutex);
		pthread_mutex_lock(&philo->left_fork->mutex);
		if (philo->left_fork->is_available)
		{
			philo->left_fork->is_available = false;
			print_action(philo, FORK);
			l_fork_grabed = true;
		}
		pthread_mutex_unlock(&philo->left_fork->mutex);
		usleep(100);
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->left_fork->is_available = true;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->right_fork->is_available = true;
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

void	philo_eat(t_philo *philo)
{
	grab_forks(philo);
	pthread_mutex_lock(&philo->mutex);
	philo->eating = true;
	philo->self_death_time = get_current_time(philo->env_data) + philo->env_data->time_to_die;
	print_action(philo, EAT);
	philo->meals_count++;
	if (philo->env_data->number_of_times_each_philosopher_must_eat  > 0)
	{
		if (philo->meals_count == philo->env_data->number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_lock(&philo->env_data->sim_mutex);
			philo->env_data->finished++;
			pthread_mutex_unlock(&philo->env_data->sim_mutex);
		}	
	}
	ft_wait(philo->env_data->time_to_eat);
	philo->eating = false;
	pthread_mutex_unlock(&philo->mutex);
	release_forks(philo);
}
