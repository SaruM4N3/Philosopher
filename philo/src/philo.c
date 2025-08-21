/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:28 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/21 13:30:27 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool grab_forks(t_philo *p)
{
    if (p->info->number_of_philosophers == 1)
    {
        pthread_mutex_lock(&p->left_fork->mutex);
        print_action(p, FORK);
        precise_usleep(p->info->time_to_die + 10);
        return (false);
    }
    if (p->id % 2 == 0)
    {
        pthread_mutex_lock(&p->right_fork->mutex);
        print_action(p, FORK);
        pthread_mutex_lock(&p->left_fork->mutex);
        print_action(p, FORK);
    }
    else
    {
        pthread_mutex_lock(&p->left_fork->mutex);
        print_action(p, FORK);
        pthread_mutex_lock(&p->right_fork->mutex);
        print_action(p, FORK);
    }
    return (true);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

bool philo_eat(t_philo *philo)
{
    if (!grab_forks(philo))
        return false;

    pthread_mutex_lock(&philo->eat_mutex);
    philo->last_eat_time = get_current_time(philo->info); // Use simulation-relative time
    philo->meals_eaten++;
    print_action(philo, EAT);
    pthread_mutex_unlock(&philo->eat_mutex);

    precise_usleep(philo->info->time_to_eat * 1000); // Convert ms to μs
    
    release_forks(philo);
    return true;
}

void philo_sleep(t_philo *philo)
{
    print_action(philo, SLEEP);
    precise_usleep(philo->info->time_to_sleep * 1000); // Convert ms to μs
}

void	philo_think(t_philo *p)
{
	print_action(p, THINK);
	usleep(100 * (p->id % 5 + 1));
}

void *life(void *philo)
{
    t_philo *p = (t_philo *)philo;
    
    // Stagger start times more effectively
    if (p->id % 2 == 0)
        precise_usleep(p->info->time_to_eat * 1000 / 2);
    
    while (!simulation_should_end(p->info))
    {
        philo_think(p);
        if (!philo_eat(p))
            break;
        if (simulation_should_end(p->info))
            break;
        philo_sleep(p);
    }
    return NULL;
}
