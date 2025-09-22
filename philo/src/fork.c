/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 02:49:15 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/22 04:06:32 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"
#include <unistd.h>

static bool	check_fork(t_philo *philo, t_fork *fork)
{
	if (get_val_mut(philo->env_data->state) != running)
		return (true);
	pthread_mutex_lock(&fork->is_available->mutex);
	if (fork->is_available->value == true)
	{
		print_action(philo, FORK);
		fork->is_available->value = false;
		pthread_mutex_unlock(&fork->is_available->mutex);
		return (true);
	}
	pthread_mutex_unlock(&fork->is_available->mutex);
	return (false);
}

void	*grab_forks(t_philo *philo)
{
	bool	r_fork_grabbed;
	bool	l_fork_grabbed;

	r_fork_grabbed = false;
	l_fork_grabbed = false;
	while (!r_fork_grabbed || !l_fork_grabbed)
	{
		if (philo_death_check(philo) == (void *)ERR_PTR)
			break ;
		if (!r_fork_grabbed)
			r_fork_grabbed = check_fork(philo, philo->right_fork);
		if (!l_fork_grabbed)
			l_fork_grabbed = check_fork(philo, philo->left_fork);
		usleep(1000);
	}
	return (NULL);
}

void	release_forks(t_philo *philo)
{
	set_val_mut(philo->right_fork->is_available, true);
	set_val_mut(philo->left_fork->is_available, true);
}
