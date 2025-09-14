/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:51:42 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/14 03:01:36 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"

void	*monitor_routine(void *env_ptr)
{
	t_env	*env;

	env = (t_env *)env_ptr;
	pthread_mutex_lock(&env->state_mutex);
	while (!env->philosophers[env->number_of_philosophers - 1].started)
		usleep(10);
	env->state = running;
	pthread_mutex_unlock(&env->state_mutex);
	while (env->state == running)
	{
		pthread_mutex_lock(&env->sim_mutex);
		if (env->finished >= env->number_of_philosophers)
			env->state = stoping;
		pthread_mutex_unlock(&env->sim_mutex);
		usleep(1000);
	}
	return (NULL);
}
