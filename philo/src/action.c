/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:07:30 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/14 03:00:44 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "error.h"

void	*philo_sleep(t_philo *philo)
{
	if (philo_death_check(philo) == ERR_PTR)
		return (ERR_PTR);
	print_action(philo, SLEEP);
	ft_wait(philo->env_data->time_to_sleep);
	return (NULL);
}

void	*philo_eat(t_philo *philo)
{
	if (philo_death_check(philo) == ERR_PTR)
		return (ERR_PTR);
	grab_forks(philo);
	pthread_mutex_lock(&philo->mutex);
	philo->eating = true;
	philo->self_death_time = get_current_time(philo->env_data)
		+ philo->env_data->time_to_die;
	print_action(philo, EAT);
	philo->meals_count++;
	if (philo->env_data->number_of_times_each_philosopher_must_eat > 0)
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
	return (NULL);
}
