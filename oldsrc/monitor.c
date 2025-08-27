/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:51:42 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/24 13:10:44 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitor_routine(void *env_ptr)
{
	int		i;
	bool	everyone_ate_enough;
	t_env	*env = (t_env *) env_ptr;

	everyone_ate_enough = false;
	precise_usleep(env->info->time_to_eat);
	while (!env->info->simulation_ended)
	{
		i = 0;
		while (i < env->info->number_of_philosophers)
		{
			pthread_mutex_lock(&env->philos[i].eat_mutex);
			if (get_current_time(env->info)
				- env->philos[i].last_eat_time > env->info->time_to_die)
			{
				philo_dead(&env->philos[i]);
				print_action(&env->philos[i], DEAD);
				set_simulation_end(env->info, true);
				return (NULL);
			}
			if (env->info->number_of_times_each_philosopher_must_eat > 0 &&
				env->philos[i].meals_eaten < env->info->number_of_times_each_philosopher_must_eat)
			{
				everyone_ate_enough = false;
			}
			pthread_mutex_unlock(&env->philos[i].eat_mutex);
			i++;
		}
		if (env->info->number_of_times_each_philosopher_must_eat > 0
			&& everyone_ate_enough)
		{
			set_simulation_end(env->info, true);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
