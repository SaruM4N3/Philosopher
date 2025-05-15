/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:11 by zsonie            #+#    #+#             */
/*   Updated: 2025/05/13 16:30:24 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
bool	init_fork(t_fork *fork, int id)
{
	fork->id = id;
	fork->is_available = false;
	if (pthread_mutex_init(&fork->mutex, NULL) != 0)
	{
		printf("Fork %d init failed\n", fork->id);
		return (false);
	}
	return (true);
}

bool	create_philo(t_env *env, int i)
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
		env->philos[i].left_fork = env->philos[i-1].right_fork;
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
	pthread_create(&env->philos[i].thread, NULL, print_test, &(env->philos[i]));
	if (pthread_mutex_init(&env->philos[i].eat_mutex, NULL) != 0)
	{
		printf("eat_mutex %d init failed\n", env->philos[i].id);
		return (false);
	}
	if (pthread_mutex_init(&env->philos[i].sleep_mutex, NULL) != 0)
	{
		printf("sleep_mutex %d init failed\n",  env->philos[i].id);
		return (false);
	}
	if (pthread_mutex_init(&env->philos[i].dead_mutex, NULL) != 0)
	{
		printf("dead_mutex %d init failed\n",  env->philos[i].id);
		return (false);
	}
	return (true);
}

bool	init_philosophers(t_env *env)
{
	int	i;

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
	print_test_first_philo(&env->philos[0]);
	return (true);
}

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		print_custom_error(ERR_ARG);
		return (1);
	}
	t_env env;
	env = init_env(av);
	if (!init_philosophers(&env))
	{
		return (1);
	}
	return (0);
}
