/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:28 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/20 01:36:12 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"

void	*philo_death_check(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (get_current_time(philo->env_data) >= philo->self_death_time)
	{
		set_val_mut(philo->state, dead);		
		print_action(philo, DEAD);
		set_val_mut(philo->env_data->state,stoping);
		return (ERR_PTR);
	}
	return (NULL);
}

static void	philo_wait_start(t_philo *philo)
{
	set_val_mut(philo->state,ready);
	while (get_val_mut(philo->env_data->state) == starting)
		usleep(100);
	set_val_mut(philo->state,alive);
}

static void	*even_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo_eat(philo) == ERR_PTR)
		return (ERR_PTR);
	if (philo_sleep(philo) == ERR_PTR)
		return (ERR_PTR);
	if (philo_death_check(philo) == ERR_PTR)
		return (ERR_PTR);
	print_action(philo, THINK);
	return (NULL);
}

static void	*odd_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo_sleep(philo) == ERR_PTR)
		return (ERR_PTR);
	if (philo_death_check(philo) == ERR_PTR)
		return (ERR_PTR);
	print_action(philo, THINK);
	if (philo_eat(philo) == ERR_PTR)
		return (ERR_PTR);
	return (NULL);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;
	philo = (t_philo *)philo_ptr;
	philo_wait_start(philo);
	while (get_val_mut(philo->env_data->state) == running)
	{
		if (philo->id % 2 == 0)
		{
			if (even_routine(philo) == ERR_PTR)
				return (ERR_PTR);
		}
		else
		{
			if (odd_routine(philo) == ERR_PTR)
				return (ERR_PTR);
		}
	}
	return (NULL);
}
