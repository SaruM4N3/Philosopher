/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:11 by zsonie            #+#    #+#             */
/*   Updated: 2025/05/16 14:10:28 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	init_fork(t_fork *fork, int id)
{
	fork->id = id;
	fork->is_available = true;
	if (pthread_mutex_init(&fork->mutex, NULL) != 0)
	{
		printf("Fork %d init failed\n", fork->id);
		return (false);
	}
	return (true);
}

static bool	create_philo(t_env *env, int i)
{
	env->philos[i].id = i + 1;
	env->philos[i].meals_eaten = 0;
	if (env->philos[i].id == 3)
		env->philos[i].meals_eaten = 3;
	env->philos[i].last_eat_time = 0;
	env->philos[i].is_eating = false;
	env->philos[i].is_sleeping = false;
	env->philos[i].is_dead = false;
	if (i != 0)
		env->philos[i].left_fork = env->philos[i - 1].right_fork;
	else
		env->philos[i].left_fork = NULL;
	env->philos[i].right_fork = malloc(sizeof(t_fork));
	if (!env->philos[i].right_fork)
		return (false);
	if (!init_fork(env->philos[i].right_fork, env->philos[i].id))
	{
		free(env->philos[i].right_fork);
		return (false);
	}
	if (env->philos[i].id == env->number_of_philosophers)
		env->last_fork = env->philos[i].right_fork;
	return (true);
}

static bool	init_thread(t_philo philo)
{
	pthread_create(&philo.thread, NULL, print_test, &philo);
	if (pthread_mutex_init(&philo.eat_mutex, NULL) != 0)
	{
		printf("eat_mutex %d init failed\n", philo.id);
		return (false);
	}
	if (pthread_mutex_init(&philo.sleep_mutex, NULL) != 0)
	{
		printf("sleep_mutex %d init failed\n", philo.id);
		return (false);
	}
	if (pthread_mutex_init(&philo.dead_mutex, NULL) != 0)
	{
		printf("dead_mutex %d init failed\n", philo.id);
		return (false);
	}
	usleep(100);
	return (true);
}

t_env	init_env(char **av)
{
	t_env	env;

	env.number_of_philosophers = ft_atoi(av[1]);
	env.time_to_die = ft_atoi(av[2]);
	env.time_to_eat = ft_atoi(av[3]);
	env.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		env.number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	return (env);
}

bool	init_philosophers(t_env *env)
{
	int	i;

	env->start_time =
		i = 0;
	env->philos = malloc(sizeof(t_philo) * (env->number_of_philosophers + 1));
	if (!env->philos)
		return (false);
	while (i < env->number_of_philosophers)
	{
		if (!create_philo(env, i))
			return (false);
		i++;
	}
	env->philos[0].left_fork = env->last_fork;
	usleep(150);
	i = 0;
	while (i < env->number_of_philosophers)
	{
		if (!init_thread(env->philos[i]))
			return (false);
		i++;
	}
	i = 0;
	usleep(150);
	while (i < env->number_of_philosophers)
	{
		if (pthread_join(env->philos[i].thread, NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}
