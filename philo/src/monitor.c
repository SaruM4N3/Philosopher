/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:51:42 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/27 03:45:52 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/error.h"

void	*monitor_routine(void *env_ptr)
{
	t_env *env = (t_env *)env_ptr;
	pthread_mutex_lock(&env->start_mutex);
	while (!env->philosophers[env->number_of_philosophers-1].started)
		usleep(10);
	env->start_sim = true;
	pthread_mutex_unlock(&env->start_mutex);
	while (env->dead == false)
	{
		pthread_mutex_lock(&env->sim_mutex);
		if (env->finished >= env->number_of_philosophers)
			env->dead = true;
		pthread_mutex_unlock(&env->sim_mutex);
	}
	return (NULL);
}
