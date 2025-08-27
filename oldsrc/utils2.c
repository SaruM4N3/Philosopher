/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:21:57 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/21 13:27:50 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	precise_usleep(long long milliseconds)
{
	long long	start;

	start = timestamp_in_ms();
	while (timestamp_in_ms() - start < milliseconds)
		usleep(100);
}

bool validate_input(t_info *info, char **av)
{
    if (info->number_of_philosophers <= 0 ||
        info->time_to_die <= 0 ||
        info->time_to_eat <= 0 ||
        info->time_to_sleep <= 0)
    {
        print_custom_error(ERR_ARG);
        return false;
    }
    if (av[5] && info->number_of_times_each_philosopher_must_eat <= 0)
    {
        print_custom_error(ERR_ARG);
        return false;
    }
    return true;
}

long long	get_current_time(t_info *info)
{
	return (timestamp_in_ms() - info->start_time);
}
