/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:51:42 by zsonie            #+#    #+#             */
/*   Updated: 2025/06/26 17:12:24 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	simulation_should_end(t_info *info)
{
	bool	ended;

	pthread_mutex_lock(&info->sim_mutex);
	ended = info->simulation_ended;
	pthread_mutex_unlock(&info->sim_mutex);
	return (ended);
}

void	set_simulation_end(t_info *info)
{
	pthread_mutex_lock(&info->sim_mutex);
	info->simulation_ended = true;
	pthread_mutex_unlock(&info->sim_mutex);
}

void	*monitor_routine(void *env_ptr)
{
	int		i;
	bool	all_ate_enough;

	precise_usleep(env->info->time_to_eat * 500);
	while (!simulation_should_end(env->info))
	{
		i = 0;
		all_ate_enough = true;
		while (i < env->info->number_of_philosophers)
		{
			pthread_mutex_lock(&env->philos[i].eat_mutex);
			if (get_current_time(env->info)
				- env->philos[i].last_eat_time > env->info->time_to_die)
			{
				print_action(&env->philos[i], DEAD);
				set_simulation_end(env->info);
				pthread_mutex_unlock(&env->philos[i].eat_mutex);
				return (NULL);
			}
			if (env->info->number_of_times_each_philosopher_must_eat > 0 &&
				env->philos[i].meals_eaten < env->info->number_of_times_each_philosopher_must_eat)
			{
				all_ate_enough = false;
			}
			if (get_current_time(env->info)
				- env->philos[i].last_eat_time > env->info->time_to_die)
			{
				print_action(&env->philos[i], DEAD);
				set_simulation_end(env->info);
				pthread_mutex_unlock(&env->philos[i].eat_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&env->philos[i].eat_mutex);
			i++;
		}
		if (env->info->number_of_times_each_philosopher_must_eat > 0
			&& all_ate_enough)
		{
			set_simulation_end(env->info);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
