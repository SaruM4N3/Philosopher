/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 02:49:15 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/20 00:36:53 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"

static bool	check_fork(t_philo *philo, t_fork *fork, bool fork_grabed)
{
	if (get_val_mut(philo->env_data->state) != running)
		return (ERR_PTR);
	if (get_val_mut(fork->is_available) == true)
	{
		set_val_mut(fork->is_available, false);
		print_action(philo, FORK);
		fork_grabed = true;
	}
	return (fork_grabed);
}

void	*grab_forks(t_philo *philo)
{
	bool	r_fork_grabed;
	bool	l_fork_grabed;

	r_fork_grabed = false;
	l_fork_grabed = false;
	while (!r_fork_grabed || !l_fork_grabed)
	{
		r_fork_grabed = check_fork(philo, philo->right_fork, r_fork_grabed);
		l_fork_grabed = check_fork(philo, philo->left_fork, l_fork_grabed);
		usleep(100);
	}
	return (NULL);
}

void	release_forks(t_philo *philo)
{
	set_val_mut(philo->right_fork->is_available, true);
	set_val_mut(philo->left_fork->is_available, true);
}
