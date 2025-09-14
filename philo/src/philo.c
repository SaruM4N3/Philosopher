/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:28 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/14 03:00:16 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "error.h"

static int	philo_check_env_state(void *philo_ptr)
{
	t_philo	*philo;
	int		state_stamp;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->env_data->state_mutex);
	state_stamp = philo->env_data->state;
	pthread_mutex_unlock(&philo->env_data->state_mutex);
	return (state_stamp);
}

void	*philo_death_check(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (get_current_time(philo->env_data) >= philo->self_death_time)
	{
		philo->philo_state = dead;
		print_action(philo, DEAD);
		pthread_mutex_lock(&philo->env_data->state_mutex);
		philo->env_data->state = stoping;
		pthread_mutex_unlock(&philo->env_data->state_mutex);
		return (ERR_PTR);
	}
	return (NULL);
}

static void	philo_wait_start(void *philo_ptr)
{
	t_philo	*philo;
	int		cur_state;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->mutex);
	philo->started = true;
	pthread_mutex_unlock(&philo->mutex);
	cur_state = philo_check_env_state(philo);
	while (cur_state == starting)
	{
		cur_state = philo_check_env_state(philo);
		usleep(1);
	}
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

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	philo_wait_start(philo);
	while (philo->env_data->state == running)
	{
		if (philo_death_check(philo) == ERR_PTR)
			return (ERR_PTR);
		if (philo->id % 2 == 0)
		{
			if (even_routine(philo) == ERR_PTR)
				return (NULL);
		}
		else
		{
			if (philo_sleep(philo) == ERR_PTR)
				return (ERR_PTR);
			if (philo_death_check(philo) == ERR_PTR)
				return (ERR_PTR);
			print_action(philo, THINK);
			if (philo_eat(philo) == ERR_PTR)
				return (ERR_PTR);
		}
	}
	return (NULL);
}
