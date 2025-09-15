/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 02:49:15 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/14 19:55:14 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"

static bool	check_right_fork(void *philo_ptr, bool r_fork_grabed)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->right_fork->mutex);
	if (philo->right_fork->is_available)
	{
		philo->right_fork->is_available = false;
		print_action(philo, FORK);
		r_fork_grabed = true;
	}
	pthread_mutex_unlock(&philo->right_fork->mutex);
	return (r_fork_grabed);
}

static bool	check_left_fork(void *philo_ptr, bool l_fork_grabed)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->left_fork->mutex);
	if (philo->left_fork->is_available)
	{
		philo->left_fork->is_available = false;
		print_action(philo, FORK);
		l_fork_grabed = true;
	}
	pthread_mutex_unlock(&philo->left_fork->mutex);
	return (l_fork_grabed);
}

void	*grab_forks(t_philo *philo)
{
	bool	r_fork_grabed;
	bool	l_fork_grabed;

	r_fork_grabed = false;
	l_fork_grabed = false;
	while (!r_fork_grabed || !l_fork_grabed)
	{
		r_fork_grabed = check_right_fork(philo, r_fork_grabed);
		if (philo_death_check(philo) == ERR_PTR)
			return (ERR_PTR);
		l_fork_grabed = check_left_fork(philo, l_fork_grabed);
		usleep(100);
	}
	return (NULL);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->right_fork->is_available = true;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->left_fork->is_available = true;
	pthread_mutex_unlock(&philo->left_fork->mutex);
}
