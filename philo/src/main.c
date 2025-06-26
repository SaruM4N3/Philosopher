/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:11 by zsonie            #+#    #+#             */
/*   Updated: 2025/06/25 17:05:32 by zsonie           ###   ########.fr       */
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

static bool	init_simulation(t_env *env, char **av)
{
	*env = init_env(av);
	if (!env->info)
		return (false);
	return (init_philosophers(env));
}

static bool launch_simulation(t_env *env)
{
    int         i;
    pthread_t   monitor_thread;

    if (pthread_create(&monitor_thread, NULL, &monitor_routine, env) != 0)
        return (false);
    i = 0;
    while (i < env->info->number_of_philosophers)
    {
        if (pthread_create(&env->philos[i].thread, NULL, 
            &life, &env->philos[i]) != 0)
        {
            set_simulation_end(env->info);
            break;
        }
        i++;
    }
    if (i < env->info->number_of_philosophers)
    {
        while (--i >= 0)
            pthread_join(env->philos[i].thread, NULL);
        pthread_join(monitor_thread, NULL);
        return (false);
    }
    pthread_join(monitor_thread, NULL);
    i = 0;
    while (i < env->info->number_of_philosophers)
        pthread_join(env->philos[i++].thread, NULL);

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
