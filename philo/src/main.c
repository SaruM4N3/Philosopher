/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:11 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/27 01:52:31 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/error.h"

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
		return (1);
	destroy_and_free(&env);
	return (0);
}
