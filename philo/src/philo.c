/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:28 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/22 04:06:32 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"
#include <unistd.h>

void	*philo_death_check(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (get_current_time(philo->env_data) >= philo->self_death_time)
	{
		print_action(philo, DEAD);
		return ((void *)ERR_PTR);
	}
	return (NULL);
}

static void	philo_wait_start(t_philo *philo)
{
	set_val_mut(philo->is_ready, false);
	while (get_val_mut(philo->env_data->state) == starting)
		usleep(100);
	set_val_mut(philo->is_ready, true);
}

static void	*even_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo_eat(philo) == (void *)ERR_PTR)
		return ((void *)ERR_PTR);
	if (philo_sleep(philo) == (void *)ERR_PTR)
		return ((void *)ERR_PTR);
	if (philo_death_check(philo) == (void *)ERR_PTR)
		return ((void *)ERR_PTR);
	print_action(philo, THINK);
	return (NULL);
}

static void	*odd_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo_sleep(philo) == (void *)ERR_PTR)
		return ((void *)ERR_PTR);
	if (philo_death_check(philo) == (void *)ERR_PTR)
		return ((void *)ERR_PTR);
	print_action(philo, THINK);
	if (philo_eat(philo) == (void *)ERR_PTR)
		return ((void *)ERR_PTR);
	return (NULL);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->id == philo->env_data->nb_philo)
		set_val_mut(philo->env_data->state, running);
	philo_wait_start(philo);
	while (get_val_mut(philo->env_data->state) == running)
	{
		if (philo->id % 2 == 0)
		{
			if (even_routine(philo) == (void *)ERR_PTR)
				return ((void *)ERR_PTR);
		}
		else
		{
			if (odd_routine(philo) == (void *)ERR_PTR)
				return ((void *)ERR_PTR);
		}
	}
	return (NULL);
}
