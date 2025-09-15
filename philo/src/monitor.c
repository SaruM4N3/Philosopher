/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:51:42 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/15 01:15:11 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"

static int check_philo_state(t_philo *philo)
{
	int philo_state;

	pthread_mutex_lock(&philo->philo_state_mutex);
	philo_state = philo->philo_state;
	pthread_mutex_unlock(&philo->philo_state_mutex);
	return philo_state;
}

void	*monitor_routine(void *env_ptr)
{
	t_env	*env;
	int		cur_env_state;

	env = (t_env *)env_ptr;
	
	while (check_philo_state(&env->philosophers[env->nb_philo -1]) == start)
		usleep(100);
	
	pthread_mutex_lock(&env->state_mutex);
	env->state = running;
	pthread_mutex_unlock(&env->state_mutex);
	cur_env_state = check_env_state(env);
	while (cur_env_state == running)
	{
		cur_env_state = check_env_state(env);
		pthread_mutex_lock(&env->state_mutex);
		if (env->finished >= env->nb_philo)
			env->state = stoping;
		pthread_mutex_unlock(&env->state_mutex);
		usleep(100);
	}
	return (NULL);
}
