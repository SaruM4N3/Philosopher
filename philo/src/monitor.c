/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:51:42 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/20 01:22:36 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"

void	*monitor_routine(void *env_ptr)
{
	t_env	*env;

	env = (t_env *)env_ptr;
	while (get_val_mut(env->philosophers[env->nb_philo - 1].state) == start)
		usleep(100);
	set_val_mut(env->state, running);
	// printf("eh ze parti \n");
	while (get_val_mut(env->state) == running)
	{
		// printf("run \n");
		if (get_val_mut(env->finished) >= env->nb_philo)
		{
			set_val_mut(env->state, stoping);
			// printf("stop this shit \n");
		}
		usleep(100);
	}
	return (NULL);
}
