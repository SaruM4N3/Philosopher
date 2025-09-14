/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:21:57 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/14 03:00:16 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "error.h"
#include <sys/time.h>

time_t	timestamp_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, (struct timezone *)0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
time_t	get_current_time(t_env *env_data)
{
	return (timestamp_in_ms() - env_data->start_time);
}

int	ft_wait(unsigned int milliseconds)
{
	time_t	start;

	start = timestamp_in_ms();
	while ((timestamp_in_ms() - start) < milliseconds)
		usleep(100);
	return (0);
}

bool	validate_input(t_env *env_data, char **av, int ac)
{
	(void)av;
	if (env_data->number_of_philosophers <= 0 || env_data->time_to_die <= 0
		|| env_data->time_to_eat <= 0 || env_data->time_to_sleep <= 0)
	{
		print_custom_error(ERR_ARG);
		return (false);
	}
	if (ac == 6 && env_data->number_of_times_each_philosopher_must_eat < 0)
	{
		print_custom_error(ERR_ARG);
		return (false);
	}
	return (true);
}
