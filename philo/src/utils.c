/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:11:38 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/27 02:48:12 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stddef.h>
#include "../includes/philo.h"

static void	ft_check_sign(const char *str, size_t *i, int *sign)
{
	*i = 0;
	while (str[*i] && ((str[*i] == ' ') || (str[*i] >= 9 && str[*i] <= 13)))
		(*i)++;
	*sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	num;
	int		sign;

	num = 0;
	ft_check_sign(str, &i, &sign);
	while (str[i] && !(str[i] < '0' || str[i] > '9'))
	{
		if (LONG_MAX / 10 < num)
		{
			if (sign > 0)
				return (-1);
			return (0);
		}
		num *= 10;
		if (LONG_MAX - (str[i] - 48) < num)
		{
			if (sign > 0)
				return (-1);
			return (0);
		}
		num += str[i] - '0';
		i++;
	}
	return (num * sign);
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
