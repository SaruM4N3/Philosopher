/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:07:30 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/22 04:06:33 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"

void	*philo_sleep(t_philo *philo)
{
	if (philo_death_check(philo) == (void *)ERR_PTR)
		return ((void *)ERR_PTR);
	print_action(philo, SLEEP);
	ft_wait(philo->env_data->time_to_sleep, philo);
	return (NULL);
}

void	*philo_eat(t_philo *philo)
{
	if (philo_death_check(philo) == (void *)ERR_PTR)
		return ((void *)ERR_PTR);
	grab_forks(philo);
	philo->self_death_time = get_current_time(philo->env_data)
		+ philo->env_data->time_to_die;
	print_action(philo, EAT);
	ft_wait(philo->env_data->time_to_eat, philo);
	if (philo->must_eat > 0)
	{
		philo->meals_count++;
		if (philo->meals_count >= philo->must_eat)
		{
			pthread_mutex_lock(&philo->env_data->finished->mutex);
			philo->env_data->finished->value++;
			pthread_mutex_unlock(&philo->env_data->finished->mutex);
			philo->must_eat = -1;
		}
	}
	release_forks(philo);
	return (NULL);
}
