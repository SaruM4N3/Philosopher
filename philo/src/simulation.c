/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:26:18 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/24 13:08:00 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	init_simulation(t_env *env, char **av)
{
	*env = init_env(av);
	if (!env->info)
		return (false);
	return (init_philosophers(env));
}

void	set_simulation_end(t_info *info, bool end)
{
	pthread_mutex_lock(&info->sim_mutex);
	info->simulation_ended = end;
}

bool launch_simulation(t_env *env)
{
    int         i;
    pthread_t   monitor_thread;

    if (pthread_create(&monitor_thread, NULL, &monitor_routine, env) != 0)
        return (false);
    i = 0;
    while (i < env->info->number_of_philosophers)
    {
        if (pthread_create(&env->philos[i].thread, NULL, 
            &life, &env->philos[i]) != 0)
        {
            // set_simulation_end(env->info, true);
            return (false);
        }
        i++;
    }
    if (i < env->info->number_of_philosophers)
    {
        while (--i >= 0)
            pthread_join(env->philos[i].thread, NULL);
        pthread_join(monitor_thread, NULL);
        return (false);
    }
    pthread_join(monitor_thread, NULL);
    i = 0;
    while (i < env->info->number_of_philosophers)
        pthread_join(env->philos[i++].thread, NULL);

    return (true);
}
