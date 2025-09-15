/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:11 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/15 01:34:32 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"

t_env	init_env(char **av, int ac)
{
	t_env	env;

	env.threads = NULL;
	env.nb_philo = ft_atoi(av[1]);
	env.finished = 0;
	env.can_print = 0;
	env.death_printed = false;
	env.time_to_die = ft_atoi(av[2]);
	env.time_to_eat = ft_atoi(av[3]);
	env.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		env.nb_must_eat = ft_atoi(av[5]);
	else
		env.nb_must_eat = -1;
	env.start_time = 0;
	env.state = starting;
	env.philosophers = NULL;
	env.forks = NULL;
	return (env);
}

bool	init_philosophers(t_env *env)
{
	int	i;

	env->philosophers = malloc(sizeof(t_philo) * env->nb_philo);
	if (!env->philosophers)
		return (false);
	i = 0;
	while (i < env->nb_philo)
	{
		env->philosophers[i].env_data = env;
		env->philosophers[i].id = i + 1;
		env->philosophers[i].meals_count = 0;
		env->philosophers[i].philo_state = start;
		env->philosophers[i].self_death_time = env->time_to_die;
		env->philosophers[i].eating = false;
		pthread_mutex_init(&env->philosophers[i].mutex, NULL);
		pthread_mutex_init(&env->philosophers[i].philo_eating_mutex, NULL);
		pthread_mutex_init(&env->philosophers[i].philo_state_mutex, NULL);
		i++;
	}
	return (true);
}

bool	init_forks(t_env *env)
{
	int	i;

	env->forks = malloc(sizeof(t_fork) * env->nb_philo);
	if (!env->forks)
		return (false);
	i = -1;
	while (++i < env->nb_philo)
	{
		env->forks[i].id = i;
		env->forks[i].is_available = true;
		pthread_mutex_init(&env->forks[i].mutex, NULL);
	}
	i = -1;
	while (++i < env->nb_philo)
	{
		env->philosophers[i].right_fork = &env->forks[i];
		if (i != 0)
			env->philosophers[i].left_fork = &env->forks[i - 1];
		else
			env->philosophers[i].left_fork = &env->forks[env->nb_philo - 1];
	}
	return (true);
}

bool	init_threads(t_env *env)
{
	int			i;
	pthread_t	monitor_thread;

	env->threads = malloc(sizeof(pthread_t) * env->nb_philo);
	if (!env->threads)
		return (false);
	env->start_time = timestamp_in_ms();
	if (pthread_create(&monitor_thread, NULL, &monitor_routine, env) != 0)
		return (error_exit(ERR_TIME, env));
	i = -1;
	while (++i < env->nb_philo)
	{
		if (pthread_create(&env->threads[i], NULL, &philo_routine,
				&env->philosophers[i]) != 0)
			return (error_exit(ERR_TIME, env));
	}
	i = -1;
	if (pthread_join(monitor_thread, NULL) != 0)
		return (error_exit(ERR_TIME, env));
	while (++i < env->nb_philo)
	{
		if (pthread_join(env->threads[i], NULL) != 0)
			return (error_exit(ERR_TIME, env));
	}
	return (true);
}

bool	init_all(char **av, int ac, t_env *env)
{
	*env = init_env(av, ac);
	pthread_mutex_init(&env->death_printed_mutex, NULL);
	pthread_mutex_init(&env->finished_mutex, NULL);
	pthread_mutex_init(&env->state_mutex, NULL);
	pthread_mutex_init(&env->print_mutex, NULL);
	if (!validate_input(env, ac))
		return (false);
	if (!init_philosophers(env))
		return (false);
	if (!init_forks(env))
		return (false);
	return (true);
}