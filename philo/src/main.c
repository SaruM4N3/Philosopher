/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:11 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/14 03:01:40 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"

void	destroy_and_free(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->number_of_philosophers)
	{
		pthread_mutex_destroy(&env->forks[i].mutex);
		pthread_mutex_destroy(&env->philosophers[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&env->sim_mutex);
	pthread_mutex_destroy(&env->state_mutex);
	pthread_mutex_destroy(&env->dead_mutex);
	pthread_mutex_destroy(&env->print_mutex);
	free(env->forks);
	free(env->philosophers);
	free(env->threads);
}

static bool	parse_args(int ac)
{
	if (ac < 5 || ac > 6)
	{
		print_custom_error(ERR_ARG);
		return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_env	env;

	if (!parse_args(ac))
		return (1);
	if (!init_all(av, ac, &env))
	{
		destroy_and_free(&env);
		return (1);
	}
	if (!init_threads(&env))
	{
		destroy_and_free(&env);
		return (1);
	}
	destroy_and_free(&env);
	return (0);
}
