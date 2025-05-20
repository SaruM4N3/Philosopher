/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:11 by zsonie            #+#    #+#             */
/*   Updated: 2025/05/20 17:13:12 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_free(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->info->number_of_philosophers)
	{
		pthread_mutex_destroy(&env->philos[i].right_fork->mutex);
		free(env->philos[i].right_fork);
		pthread_mutex_destroy(&env->philos[i].eat_mutex);
		pthread_mutex_destroy(&env->philos[i].sleep_mutex);
		pthread_mutex_destroy(&env->philos[i].dead_mutex);
		i++;
	}
	free(env->philos);
}

int	main(int ac, char **av)
{
	t_env	env;
	int		i;

	if (ac < 5 || ac > 6)
	{
		print_custom_error(ERR_ARG);
		return (1);
	}
	env = init_env(av);
	if (!init_philosophers(&env))
	{
		ft_free(&env);
		return (1);
	}
	i = 0;
	while (i < env.info->number_of_philosophers)
	{
		if (!init_thread(env.philos[i]))
			return (false);
		i++;
	}
	i = 0;
	while (i < env.info->number_of_philosophers)
	{
		if (pthread_join(env.philos[i].thread, NULL) != 0)
			return (false);
		i++;
	}
	return (0);
}
