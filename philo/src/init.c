/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:11 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/22 04:02:42 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"
#include <stdlib.h>

t_env	init_env(int ac, char **av)
{
	t_env	env;

	env.threads = NULL;
	env.nb_philo = ft_atoi(av[1]);
	env.time_to_die = ft_atoi(av[2]);
	env.time_to_eat = ft_atoi(av[3]);
	env.time_to_sleep = ft_atoi(av[4]);
	env.start_time = 0;
	if (ac == 6)
		env.nb_must_eat = ft_atoi(av[5]);
	else
		env.nb_must_eat = -1;
	env.state = init_mut(starting);
	env.can_print = init_mut(true);
	env.finished = init_mut(0);
	if (!env.state || !env.can_print || !env.finished)
		env.nb_philo = -1;
	env.philosophers = NULL;
	env.forks = NULL;
	return (env);
}

bool	init_philosophers(t_env *env)
{
	int	i;

	env->philosophers = ft_calloc(env->nb_philo, sizeof(t_philo));
	if (!env->philosophers)
		return (false);
	i = 0;
	while (i < env->nb_philo)
	{
		env->philosophers[i].env_data = env;
		env->philosophers[i].id = i + 1;
		env->philosophers[i].must_eat = env->nb_must_eat;
		env->philosophers[i].self_death_time = env->time_to_die;
		env->philosophers[i].is_ready = init_mut(false);
		if (!env->philosophers[i].is_ready)
			return (false);
		env->philosophers[i].meals_count = 0;
		i++;
	}
	return (true);
}

bool	init_forks(t_env *env)
{
	int	i;

	env->forks = ft_calloc(env->nb_philo, sizeof(t_fork));
	if (!env->forks)
		return (false);
	i = -1;
	while (++i < env->nb_philo)
	{
		env->forks[i].is_available = init_mut(true);
		if (!env->forks[i].is_available)
			return (false);
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

int	secure_thread(t_env *env)
{
	int		i;
	bool	ret;

	ret = true;
	i = 0;
	while (i < env->nb_philo)
	{
		if (pthread_create(&env->threads[i], NULL, &philo_routine,
				&env->philosophers[i]) != 0)
		{
			set_val_mut(env->state, stopped);
			print_custom_error(ERR_PTHREAD_CREATE);
			ret = false;
			break ;
		}
		i++;
	}
	while (i > 0)
		pthread_join(env->threads[--i], NULL);
	return (ret);
}

bool	init_threads(t_env *env)
{
	bool		ret;
	pthread_t	monitor_thread;

	env->threads = malloc(sizeof(pthread_t) * env->nb_philo);
	if (!env->threads)
		return (false);
	if (pthread_create(&monitor_thread, NULL, &monitor_routine, env) != 0)
	{
		print_custom_error(ERR_PTHREAD_CREATE);
		return (false);
	}
	env->start_time = timestamp_in_ms();
	ret = secure_thread(env);
	pthread_join(monitor_thread, NULL);
	return (ret);
}
