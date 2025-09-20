/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:11 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/20 01:39:52 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"

void	destroy_and_free(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_philo)
	{
		pthread_mutex_destroy(&env->forks[i].is_available->mutex);
		pthread_mutex_destroy(&env->philosophers[i].state->mutex);
		pthread_mutex_destroy(&env->philosophers[i].eating->mutex);
		pthread_mutex_destroy(&env->philosophers[i].meals_count->mutex);
		i++;
	}
	pthread_mutex_destroy(&env->state->mutex);
	pthread_mutex_destroy(&env->finished->mutex);
	pthread_mutex_destroy(&env->can_print->mutex);
	free(env->forks);
	free(env->philosophers);
	free(env->threads);
}

static bool	check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		print_custom_error(ERR_ARG);
		return (false);
	}
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) > 200)
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
	if (!init_all(&env))
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
