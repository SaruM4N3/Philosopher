/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:28 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/24 13:09:59 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool grab_forks(t_philo *p)
{
    // printf("Philo %d trying to grab forks\n", p->id);
    if (p->info->number_of_philosophers == 1)
    {
        pthread_mutex_lock(&p->left_fork->mutex);
        print_action(p, FORK);
        precise_usleep(p->info->time_to_die + 10);
        return (false);
    }
    else if (p->id % 2 == 0)
    {
        pthread_mutex_lock(&p->right_fork->mutex);
        print_action(p, FORK);
        pthread_mutex_lock(&p->left_fork->mutex);
        print_action(p, FORK);
    }
    else
    {
        pthread_mutex_lock(&p->right_fork->mutex);
        print_action(p, FORK);
        pthread_mutex_lock(&p->left_fork->mutex);
        print_action(p, FORK);
    }
    // printf("Philo %d grabbed both forks\n", p->id);
    return (true);
}

void	release_forks(t_philo *philo)
{
    // printf("Philo %d releasing forks\n", philo->id);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
    // printf("Philo %d released both forks\n", philo->id);
}

bool philo_eat(t_philo *philo)
{
    // printf("Philo %d is trying to eat\n", philo->id);
    if (!grab_forks(philo))
        return false;
    else
    {
        pthread_mutex_lock(&philo->eat_mutex);
        philo->last_eat_time = get_current_time(philo->info);
        philo->meals_eaten++;
        print_action(philo, EAT);
        pthread_mutex_unlock(&philo->eat_mutex);
        precise_usleep(philo->info->time_to_eat);
        release_forks(philo);
    }
    return true;
}

void philo_sleep(t_philo *philo)
{
    print_action(philo, SLEEP);
    precise_usleep(philo->info->time_to_sleep); 
}

void	philo_dead(t_philo *p)
{
    pthread_mutex_lock(&p->dead_mutex);
    p->is_dead = true;
    pthread_mutex_unlock(&p->dead_mutex);
}

void *life(void *philo)
{
    t_philo *p = (t_philo *)philo;

    while (!p->info->simulation_ended)
    {
        if (p->is_dead)
        {
            print_bool(p->is_dead);
            set_simulation_end(p->info, true);
            break;
        }
        print_action(p, THINK);
	    usleep(100);
        if (!philo_eat(p))
            break;
        philo_sleep(p);
    }
    return NULL;
}
