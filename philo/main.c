/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:11 by zsonie            #+#    #+#             */
/*   Updated: 2025/05/11 19:32:23 by zsonie           ###   ########.fr       */
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
	env.number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	return (env);
}
void	setup_philo(t_env *env, int i)
{
	pthread_create(env->philos[i].thread, NULL, NULL, NULL);
	env->philos[i].id = i;
	env->philos[i].meals_eaten = 0;
	env->philos[i].last_eat_time = 0;
	env->philos[i].is_eating = false;
	env->philos[i].is_sleeping = false;
	env->philos[i].is_dead = false;
	
}

bool	init_philosophers(t_env *env)
{
	int	i;

	i = 0;
	env->philos = malloc(sizeof(t_philo) * (env->number_of_philosophers + 1));
	if (!env->philos)
		return (false);
	while (i < env->number_of_philosophers)
		setup_philo(env, i);
	return (true);
}

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		ft_putstr("Wrong nbr of arguments\n");
		return (1);
	}
	t_env env;
	env = init_env(av);
	if (!init_philosophers(&env))
		return (1);

	return (0);
}