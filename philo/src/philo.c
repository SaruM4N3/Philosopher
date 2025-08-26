/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:28 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/26 17:50:08 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void grab_forks(t_philo *philo)
{
    pthread_mutex_lock(&philo->right_fork->mutex);
    print_action(philo, FORK);
    pthread_mutex_lock(&philo->left_fork->mutex);
    print_action(philo, FORK);
}

void release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
    print_action(philo, SLEEP);
    precise_usleep(philo->env_data->time_to_sleep);
}

void philo_eat(t_philo *philo)
{
    grab_forks(philo);
    pthread_mutex_lock(&philo->mutex);
    philo->eating = true;
    philo->self_death_time = timestamp_in_ms() + philo->env_data->time_to_die;
    print_action(philo, EAT);
    philo->meals_count++;
    precise_usleep(philo->env_data->time_to_eat);
    printf("Philo %d has eaten %d times\n", philo->id, philo->meals_count);
    philo->eating = false;
    pthread_mutex_unlock(&philo->mutex);
    release_forks(philo);
}
