/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:52:21 by zsonie            #+#    #+#             */
/*   Updated: 2025/05/19 14:52:27 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "error.h"
#include <sys/time.h>

void	*print_test(void *philo)
{
	t_philo *curphilo;
	
	curphilo = (t_philo *)philo;
	pthread_mutex_lock(&curphilo->sleep_mutex);
	curphilo->is_sleeping = true;
	printf("\n%sphilosopher number %d stats:\n", YELLOW, curphilo->id);
	printf("\n%sthread number: %s%ld\n", RESET, CYAN, curphilo->thread);
	printf("%sID: %s%d%s\n", RESET, GREEN, curphilo->id, RESET);
	printf("%smeals_eaten: %s%d%s\n", RESET, GREEN, curphilo->meals_eaten, RESET);
	printf("%slast_eat_time: %s%d%s\n", RESET, GREEN, curphilo->last_eat_time, RESET);
	print_custom_bool("%sis_eating: %s%s%s\n", curphilo->is_eating);
	print_custom_bool("%sis_sleeping: %s%s%s\n", curphilo->is_sleeping);
	print_custom_bool("%sis_dead: %s%s%s\n", curphilo->is_dead);
	printf("%sleft_fork.id: %s%d%s\n", RESET, GREEN, curphilo->left_fork->id, RESET);
	print_custom_bool("%sleft_fork.is_available: %s%s%s\n", curphilo->left_fork->is_available);
	printf("%sright_fork.id: %s%d%s\n", RESET, GREEN, curphilo->right_fork->id, RESET);
	print_custom_bool("%sright_fork.is_available: %s%s%s\n", curphilo->right_fork->is_available);
	printf("%seat_mutex: %s%p%s\n", RESET, CYAN, &curphilo->eat_mutex, RESET);
	printf("%ssleep_mutex: %s%p%s\n", RESET, CYAN, &curphilo->sleep_mutex, RESET);
	printf("%sdead_mutex: %s%p%s\n", RESET, CYAN, &curphilo->dead_mutex, RESET);
	usleep(150);
	pthread_mutex_unlock(&curphilo->sleep_mutex);
	curphilo->is_sleeping = false;
	return (NULL);
}

long long timestamp_in_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void print_action(t_philo *philo, int action)
{
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