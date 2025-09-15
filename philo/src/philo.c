/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:28 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/15 02:04:57 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"

int	check_env_state(t_env *env)
{
	int		state_stamp;

	pthread_mutex_lock(&env->state_mutex);
	state_stamp = env->state;
	pthread_mutex_unlock(&env->state_mutex);
	return (state_stamp);
}

void	*philo_death_check(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (get_current_time(philo->env_data) >= philo->self_death_time)
	{
		pthread_mutex_lock(&philo->philo_state_mutex);
		philo->philo_state = dead;
		pthread_mutex_unlock(&philo->philo_state_mutex);
		
		print_action(philo, DEAD);
		pthread_mutex_lock(&philo->env_data->state_mutex);
		philo->env_data->state = stoping;
		pthread_mutex_unlock(&philo->env_data->state_mutex);

		return (ERR_PTR);
	}
	return (NULL);
}

static void	philo_wait_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_state_mutex);
	philo->philo_state = ready;
	pthread_mutex_unlock(&philo->philo_state_mutex);
	
	while (check_env_state(philo->env_data) == starting)
		usleep(100);
	pthread_mutex_lock(&philo->philo_state_mutex);
	philo->philo_state = alive;
	pthread_mutex_unlock(&philo->philo_state_mutex);
}

static void	*even_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo_death_check(philo) == ERR_PTR)
		return (ERR_PTR);
	if (philo_eat(philo) == ERR_PTR)
		return (ERR_PTR);
	if (philo_death_check(philo) == ERR_PTR)
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
	if (philo_death_check(philo) == ERR_PTR)
		return (ERR_PTR);
	if (philo_sleep(philo) == ERR_PTR)
		return (ERR_PTR);
	if (philo_death_check(philo) == ERR_PTR)
		return (ERR_PTR);
	print_action(philo, THINK);
	if (philo_death_check(philo) == ERR_PTR)
		return (ERR_PTR);
	if (philo_eat(philo) == ERR_PTR)
		return (ERR_PTR);
	return (NULL);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;
	
	philo = (t_philo *)philo_ptr;
	philo_wait_start(philo);
	while (check_env_state(philo->env_data) == running)
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
