/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:07:30 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/14 23:04:50 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"

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
	pthread_mutex_lock(&philo->philo_eating_mutex);
	philo->eating = true;
	pthread_mutex_unlock(&philo->philo_eating_mutex);
	philo->self_death_time = get_current_time(philo->env_data)
		+ philo->env_data->time_to_die;
	print_action(philo, EAT);
	philo->meals_count++;
	if (philo->env_data->nb_must_eat > 0)
	{
		if (philo->meals_count == philo->env_data->nb_must_eat)
		{
			pthread_mutex_lock(&philo->env_data->finished_mutex);
			philo->env_data->finished++;
			pthread_mutex_unlock(&philo->env_data->finished_mutex);
		}
	}
	ft_wait(philo->env_data->time_to_eat);
	pthread_mutex_lock(&philo->philo_eating_mutex);
	philo->eating = false;
	pthread_mutex_unlock(&philo->philo_eating_mutex);
	release_forks(philo);
	return (NULL);
}
