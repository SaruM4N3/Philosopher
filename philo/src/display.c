/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:52:21 by zsonie            #+#    #+#             */
/*   Updated: 2025/05/13 16:27:59 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "error.h"

void	*print_test(void *philo)
{
	t_philo *curphilo;
	
	curphilo = (t_philo *)philo;
	pthread_mutex_lock(&curphilo->sleep_mutex);
	printf("\n%sphilosopher stats test %d\n", YELLOW, curphilo->id);
	printf("\n%sphilo ID: %s%d%s\n", RESET, GREEN, curphilo->id, RESET);
	printf("%sphilo meals_eaten: %s%d%s\n", RESET, GREEN, curphilo->meals_eaten, RESET);
	printf("%sphilo last_eat_time: %s%d%s\n", RESET, GREEN, curphilo->last_eat_time, RESET);
	printf("%sphilo is_eating: %s%s%s\n", RESET, GREEN, print_bool(curphilo->is_eating), RESET);
	printf("%sphilo is_sleeping: %s%s%s\n", RESET, GREEN, print_bool(curphilo->is_sleeping), RESET);
	printf("%sphilo is_dead: %s%s%s\n", RESET, GREEN, print_bool(curphilo->is_dead), RESET);
	if (curphilo->left_fork)
		printf("%sphilo left_fork_id: %s%d%s\n", RESET, GREEN, curphilo->left_fork->id, RESET);
	else
		printf("%sphilo left_fork_id: %snihil%s\n", RESET, GREEN, RESET);
	printf("%sphilo right_fork_id: %s%d%s\n", RESET, GREEN, curphilo->right_fork->id, RESET);
	pthread_mutex_unlock(&curphilo->sleep_mutex);
	return (NULL);
}

void	*print_test_first_philo(void *philo)
{
	t_philo *curphilo;
	
	curphilo = (t_philo *)philo;
	pthread_mutex_lock(&curphilo->sleep_mutex);
	printf("\n%sphilosopher stats test %d\n", YELLOW, curphilo->id);
	printf("\n%sphilo ID: %s%d%s\n", RESET, GREEN, curphilo->id, RESET);
	printf("%sphilo meals_eaten: %s%d%s\n", RESET, GREEN, curphilo->meals_eaten, RESET);
	printf("%sphilo last_eat_time: %s%d%s\n", RESET, GREEN, curphilo->last_eat_time, RESET);
	printf("%sphilo is_eating: %s%s%s\n", RESET, GREEN, print_bool(curphilo->is_eating), RESET);
	printf("%sphilo is_sleeping: %s%s%s\n", RESET, GREEN, print_bool(curphilo->is_sleeping), RESET);
	printf("%sphilo is_dead: %s%s%s\n", RESET, GREEN, print_bool(curphilo->is_dead), RESET);
	if (curphilo->left_fork)
		printf("%sphilo left_fork_id: %s%d%s\n", RESET, GREEN, curphilo->left_fork->id, RESET);
	printf("%sphilo right_fork_id: %s%d%s\n", RESET, GREEN, curphilo->right_fork->id, RESET);
	pthread_mutex_unlock(&curphilo->sleep_mutex);
	return (NULL);
}
/* SUBJECT
About the logs of your program:

• Any state change of a philosopher must be formatted as follows:
	◦ timestamp_in_ms X has taken a fork
	◦ timestamp_in_ms X is eating
	◦ timestamp_in_ms X is sleeping
	◦ timestamp_in_ms X is thinking
	◦ timestamp_in_ms X died

• A displayed state message should not be mixed up with another message.

• A message announcing a philosopher died should be displayed no more than 10 ms
after the actual death of the philosopher.

• Again, philosophers should avoid dying!
*/