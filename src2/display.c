/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:52:21 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/25 16:05:52 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/error.h"

void	*print_test(void *philo)
{
	t_philo *curphilo;
	
	curphilo = (t_philo *)philo;
	printf("\n%sphilosopher number %d stats:\n", YELLOW, curphilo->id);
	printf("\n%sthread number: %s%ld\n", RESET, CYAN, curphilo->thread);
	printf("%sID: %s%d%s\n", RESET, GREEN, curphilo->id, RESET);
	printf("%smeals_eaten: %s%d%s\n", RESET, GREEN, curphilo->meals_count, RESET);
	printf("%slast_eat_time: %s%d%s\n", RESET, GREEN, curphilo->last_eat_time, RESET);
	printf("%sleft_fork.id: %s%d%s\n", RESET, GREEN, curphilo->left_fork->id, RESET);
	printf("%sright_fork.id: %s%d%s\n", RESET, GREEN, curphilo->right_fork->id, RESET);
	usleep(150);
	return (NULL);
}

void print_action(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->env_data->print_mutex);
	printf("%lld ", timestamp_in_ms());
	if(action == FORK)
		printf("%d has taken a fork\n", philo->id);
	else if(action == EAT)
		printf("%d is eating\n", philo->id);
	else if(action == SLEEP)
		printf("%d is sleeping\n", philo->id);
	else if(action == THINK)
		printf("%d is thinking\n", philo->id);
	else if (action == DEAD)
		printf("%d is dead\n", philo->id);
	else
		printf("ERROR: UNKNOW ACTION");
	pthread_mutex_unlock(&philo->env_data->print_mutex);
}
