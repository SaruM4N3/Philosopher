/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:11 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/21 00:48:47 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"
#include <stdlib.h>

bool	init_all(t_env *env)
{
	if (!init_philosophers(env))
		return (false);
	if (!init_forks(env))
		return (false);
	return (true);
}

void	destroy_and_free(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_philo)
	{
		if (env->forks)
			destroy_mut(env->forks[i].is_available);
		if (env->philosophers)
			destroy_mut(env->philosophers[i].is_ready);
		i++;
	}
	destroy_mut(env->state);
	destroy_mut(env->finished);
	destroy_mut(env->can_print);
	free(env->forks);
	free(env->philosophers);
	free(env->threads);
}

static bool	check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (false);
	if (ft_atoi(av[1]) <= 0)
		return (false);
	if (ft_atoi(av[2]) <= 0)
		return (false);
	if (ft_atoi(av[3]) <= 0)
		return (false);
	if (ft_atoi(av[4]) <= 0)
		return (false);
	if (ac == 6 && av[5])
	{
		if (ft_atoi(av[5]) < 0)
			return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_env	env;

	if (!check_args(ac, av))
	{
		print_custom_error(ERR_ARG);
		return (1);
	}
	env = init_env(ac, av);
	if (env.nb_philo == -1 || !init_all(&env) || !init_threads(&env))
	{
		destroy_and_free(&env);
		return (1);
	}
	destroy_and_free(&env);
	return (0);
}
