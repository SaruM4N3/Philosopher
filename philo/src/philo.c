/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:08:28 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/13 19:59:07 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/error.h"
#include "../includes/philo.h"
static void philo_wait_start(void *philo_ptr)
{
    t_philo *philo = (t_philo *)philo_ptr;

    pthread_mutex_lock(&philo->mutex);
    philo->started = true;
    pthread_mutex_unlock(&philo->mutex);

    pthread_mutex_lock(&philo->env_data->start_mutex);
    while (philo->env_data->state == starting)
    {
        pthread_mutex_unlock(&philo->env_data->start_mutex);
        usleep(100);
        pthread_mutex_lock(&philo->env_data->start_mutex);
    }
    pthread_mutex_unlock(&philo->env_data->start_mutex);
}

static void	*philo_death_check(void *philo_ptr)
{
	t_philo *philo;
	
	philo = (t_philo *)philo_ptr;
	if (get_current_time(philo->env_data) >= philo->self_death_time)
	{
		philo->philo_state = dead;
		print_action(philo, DEAD);
		philo->env_data->state = stoping;
		return (ERR_PTR);
	}
	return NULL;
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	philo_wait_start(philo);
	while (philo->env_data->state == running)
	{
		if (philo_death_check(philo) == ERR_PTR)
			return (ERR_PTR);
		if (philo->id % 2 == 0)
		{
			philo_eat(philo);
			philo_sleep(philo);
			print_action(philo, THINK);
		}
		else
		{
			philo_sleep(philo);
			print_action(philo, THINK);
			philo_eat(philo);
		}
	}
	if (pthread_join(philo->philo_thread, NULL))
		return (ERR_PTR);
	return (NULL);
}
