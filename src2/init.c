/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:11 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/25 14:55:52 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_env init_env(char **av, int ac)
{
    t_env env;
    
	env.thread = NULL;
    env.number_of_philosophers = ft_atoi(av[1]);
    env.time_to_die = ft_atoi(av[2]);
    env.time_to_eat = ft_atoi(av[3]);
    env.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
    	env.number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		env.number_of_times_each_philosopher_must_eat = -1;

	env.start_time = 0;
	env.dead = 0;
	env.finished = 0;
	
	env.philosophers = NULL;
	env.forks = NULL;

    pthread_mutex_init(&env.sim_mutex, NULL);
    pthread_mutex_init(&env.print_mutex, NULL);
    return env;
}

bool	init_philosophers(t_env *env)
{
	int	i;

	i = 0;
	env->philosophers = malloc(sizeof(t_philo) * (env->number_of_philosophers
				+ 1));
	if (!env->philosophers)
		return (false);
	env->start_time = timestamp_in_ms();
	for (int i = 0; i < env->number_of_philosophers; i++)
	env->start_time = timestamp_in_ms();
	while (i < env->number_of_philosophers)
	{
		if (!create_philo(env, i))
			return (false);
		i++;
	}
	return true;
}

static bool	init_fork(t_env *env)
{
	int i;

	i = 0;
	while (i < env->number_of_philosophers)
	{
		env->forks->id = i;
		if (pthread_mutex_init(&env->forks->mutex, NULL) != 0)
		{
			printf("Fork %d init failed\n", env->forks->id);
			return (false);
		}
		i++;		
	}
	i = 0;
	while (env->forks[i].id < env->number_of_philosophers)
	{
		env->philosophers[i].right_fork = &env->forks[i];
		if (i != 0)
			env->philosophers[i].left_fork = &env->forks[i - 1];
		else
			env->philosophers[i].left_fork = &env->forks[env->number_of_philosophers - 1];
		i++;
	}
	return (true);
}

bool	init_thread(t_philo *philo)
{
	return (true);
}



