/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:11 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/21 13:30:50 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_free(t_env *env)
{
	int	i;

	if (!env || !env->info || !env->philos)
		return;
		
	i = 0;
	while (i < env->info->number_of_philosophers)
	{
		if (env->philos[i].right_fork)
		{
			pthread_mutex_destroy(&env->philos[i].right_fork->mutex);
			free(env->philos[i].right_fork);
		}
		pthread_mutex_destroy(&env->philos[i].eat_mutex);
		pthread_mutex_destroy(&env->philos[i].sleep_mutex);
		pthread_mutex_destroy(&env->philos[i].dead_mutex);
		i++;
	}
	free(env->philos);
	if (env->info)
	{
		pthread_mutex_destroy(&env->info->sim_mutex);
		free(env->info);
	}
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
	t_env	env = {0};

	if (!parse_args(ac))
		return (1);
	__builtin_printf("Philosophers simulation started with %d philosophers.\n", ft_atoi(av[1]));
	if (!init_simulation(&env, av) || !launch_simulation(&env))
	{
		ft_free(&env);
		return (1);
	}
	
	ft_free(&env);
	return (0);
}
