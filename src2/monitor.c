/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:51:42 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/25 16:05:18 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitor_routine(void *env_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) env_ptr;
	pthread_mutex_lock(&philo->env_data->print_mutex);
	print_custom_bool("Philo death =",philo->env_data->dead);
	pthread_mutex_unlock(&philo->env_data->print_mutex);
	while (philo->env_data->dead == false)
	{
		pthread_mutex_lock(&philo->mutex);
		if (philo->env_data->finished >= philo->env_data->number_of_philosophers)
			philo->env_data->dead = true;
		pthread_mutex_unlock(&philo->env_data->sim_mutex);
	}
	return (NULL);
}

void	*monitor_checker(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (philo->env_data->dead == false)
	{
		pthread_mutex_lock(&philo->mutex);
		if (timestamp_in_ms() >= philo->self_death_time && philo->is_eating == false)
			print_action(philo, DEAD);
		if (philo->meals_count == philo->env_data->number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_lock(&philo->env_data->sim_mutex);
			philo->env_data->finished++;
			philo->meals_count++;
			pthread_mutex_unlock(&philo->env_data->sim_mutex);
		}
		pthread_mutex_unlock(&philo->env_data->sim_mutex);
	}
	return (NULL);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	philo->self_death_time = philo->env_data->time_to_die + get_current_time(philo->env_data);
	if (pthread_create(&philo->thread, NULL, &monitor_checker, philo))
		return (ERR_PTR);
	while (philo->env_data->dead == false)
	{
		philo_eat(philo);
		print_action(THINK, philo);
	}
	if (pthread_join(philo->thread, NULL))
		return (ERR_PTR);
	return (NULL);
}