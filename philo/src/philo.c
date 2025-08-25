/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:28 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/25 17:54:35 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void grab_forks(t_philo *p)
{
    pthread_mutex_lock(&p->right_fork->mutex);
    print_action(p, FORK);
    pthread_mutex_lock(&p->left_fork->mutex);
    print_action(p, FORK);
}

void release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
    print_action(philo, SLEEP);
    precise_usleep((__useconds_t)philo->env_data->time_to_sleep);
}

void philo_eat(t_philo *philo)
{
    grab_forks(philo);
    pthread_mutex_lock(&philo->mutex);
    philo->is_eating = true;
    philo->self_death_time = timestamp_in_ms() + philo->env_data->time_to_die;
    print_action(philo, EAT);
    philo->meals_count++;
    precise_usleep(philo->env_data->time_to_eat);
    philo->is_eating = false;
    pthread_mutex_unlock(&philo->mutex);
    release_forks(philo);
}
