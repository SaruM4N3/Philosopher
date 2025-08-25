/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:11 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/25 17:42:49 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/error.h"

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
	env.dead = false;
	env.finished = false;
	
	env.philosophers = NULL;
	env.forks = NULL;
	//not sure if i need to secure mutexes initialization (ask timeo or david!!!)
    pthread_mutex_init(&env.sim_mutex, NULL);
    pthread_mutex_init(&env.print_mutex, NULL);
    return env;
}

bool	init_philosophers(t_env *env)
{
	int	i;

	env->philosophers = malloc(sizeof(t_philo) * env->number_of_philosophers);
	if (!env->philosophers)
	return (false);
	i = -1;
	while (++i < env->number_of_philosophers)
	{
		env->philosophers[i].env_data = env;
		env->philosophers[i].id = i + 1;
		env->philosophers[i].meals_count = 0;
		env->philosophers[i].current_state = THINK;
		env->philosophers[i].last_eat_time = 0;
		env->philosophers[i].self_death_time = env->time_to_die;
		env->philosophers[i].is_eating = false;
		//not sure if i need to secure mutexes initialization (ask timeo or david!!!)
		if (pthread_mutex_init(&env->philosophers[i].mutex, NULL) != 0)
		{
			printf("Philosopher %d mutex init failed\n", env->philosophers[i].id);
			return (false);
		}
	}
	return true;
}

bool	init_forks(t_env *env)
{
	int i;

	env->forks = malloc(sizeof(pthread_mutex_t) * env->number_of_philosophers);
	if (!env->forks)
		return (false);
	i = -1;
	while (++i < env->number_of_philosophers)
	{
		env->forks->id = i;
		if (pthread_mutex_init(&env->forks->mutex, NULL) != 0)
		{
			printf("Fork %d init failed\n", env->forks->id);
			return (false);
		}
	}
	i = -1;
	while (++i < env->number_of_philosophers)
	{
		env->philosophers[i].right_fork = &env->forks[i];
		if (i != 0)
			env->philosophers[i].left_fork = &env->forks[i - 1];
		else
			env->philosophers[i].left_fork = &env->forks[env->number_of_philosophers - 1];
	}
	return (true);
}

bool	init_threads(t_env *env)
{
	int i;
	pthread_t monitor_thread;
	
	env->thread = malloc(sizeof(pthread_t) * env->number_of_philosophers);
	if (!env->thread)
		return (false);
	env->start_time = get_current_time(env);
	if (pthread_create(&monitor_thread, NULL, &monitor_routine, env) != 0)
		return (false);
	i = -1;
	while (++i < env->number_of_philosophers)
	{
		if (pthread_create(&env->thread[i], NULL, &philo_routine, &env->philosophers[i]) != 0)
			return (error_exit(ERR_TIME, env));
		precise_usleep(10);
	}
	i = -1;
	while (++i < env->number_of_philosophers)
	{
		if (pthread_join(env->thread[i], NULL) != 0)
			return (false);
	}
	return (true);
}

int init_all(char **av, int ac, t_env *env)
{
	*env = init_env(av, ac);
	if (!init_philosophers(env))
		return (1);
	if (!init_forks(env))
		return (1);
	if (!init_threads(env))
		return (1);
	return (0);
}