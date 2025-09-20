/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:07:30 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/20 01:41:36 by zsonie           ###   ########lyon.fr   */
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
	set_val_mut(philo->eating, true);
	philo->self_death_time = get_current_time(philo->env_data)
		+ philo->env_data->time_to_die;
	print_action(philo, EAT);
	set_val_mut(philo->meals_count, philo->meals_count->value + 1);
	if (philo->must_eat > 0)
	{
		if (get_val_mut(philo->meals_count) >= philo->must_eat)
		{
			set_val_mut(philo->env_data->finished,
				philo->env_data->finished->value + 1);
		}
	}
	ft_wait(philo->env_data->time_to_eat);
	set_val_mut(philo->eating, false);
	release_forks(philo);
	return (NULL);
}
