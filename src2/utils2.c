/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:21:57 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/25 14:05:59 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/error.h"
#include <sys/time.h>

static long long timestamp_in_ms(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
        return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	precise_usleep(long long milliseconds)
{
	long long	start;

	start = timestamp_in_ms();
	while (timestamp_in_ms() - start < milliseconds)
		usleep(100);
}

bool validate_input(t_env *env_data, char **av)
{
    if (env_data->number_of_philosophers <= 0 ||
        env_data->time_to_die <= 0 ||
        env_data->time_to_eat <= 0 ||
        env_data->time_to_sleep <= 0)
    {
        print_custom_error(ERR_ARG);
        return false;
    }
    if (av[5] && env_data->number_of_times_each_philosopher_must_eat <= 0)
    {
        print_custom_error(ERR_ARG);
        return false;
    }
    return true;
}

long long	get_current_time(t_env *env_data)
{
	return (timestamp_in_ms() - env_data->start_time);
}
