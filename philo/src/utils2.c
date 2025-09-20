/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:21:57 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/20 01:09:22 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

time_t	timestamp_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

time_t	get_current_time(t_env *env_data)
{
	return (timestamp_in_ms() - env_data->start_time);
}

int	ft_wait(unsigned int milliseconds, t_philo *philo)
{
	time_t	start;

	start = timestamp_in_ms();
	while ((timestamp_in_ms() - start) < milliseconds
		&& get_val_mut(philo->env_data->state) == running
		&& philo_death_check(philo) != ERR_PTR)
		usleep(100);
	return (0);
}
