/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:21:57 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/21 00:00:47 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"
#include <stdlib.h>
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

static void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*res;

	total = nmemb * size;
	if (size != 0 && total / size != nmemb)
		return (malloc(0));
	res = malloc(total);
	if (!res)
		return (NULL);
	ft_memset(res, 0, total);
	return (res);
}
