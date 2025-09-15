/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:11:38 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/15 02:01:57 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <limits.h>
#include <stddef.h>
#include <unistd.h>

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
			if (sign > 0 || num > 2147483647 || num < 0)
				return (-1);
			return (0);
		}
		num *= 10;
		if (LONG_MAX - (str[i] - 48) < num)
		{
			if (sign > 0 || num > 2147483647 || num < 0)
				return (-1);
			return (0);
		}
		num += str[i] - '0';
		i++;
	}
	return (num * sign);
}

static bool	set_can_print(t_philo *philo, bool set)
{
	pthread_mutex_lock(&philo->env_data->print_mutex);
	philo->env_data->can_print = set;
	pthread_mutex_unlock(&philo->env_data->print_mutex);
	return (set);
}
void print_action(t_philo *philo, int action)
{
    pthread_mutex_lock(&philo->env_data->death_printed_mutex);
    if (philo->env_data->death_printed && action != DEAD)
    {
        pthread_mutex_unlock(&philo->env_data->death_printed_mutex);
        return; // Already printed a death, skip any other prints
    }
    if (action == DEAD)
        philo->env_data->death_printed = true; // Mark death printed
    pthread_mutex_unlock(&philo->env_data->death_printed_mutex);

    pthread_mutex_lock(&philo->env_data->state_mutex);
    if (philo->env_data->state == stoping)
    {
        pthread_mutex_unlock(&philo->env_data->state_mutex);
        return;
    }
    pthread_mutex_unlock(&philo->env_data->state_mutex);

    if (!set_can_print(philo, false))
    {
        if (action == FORK)
            printf("%ld %d has taken a fork\n", get_current_time(philo->env_data), philo->id);
        else if (action == EAT)
            printf("%ld %d is eating\n", get_current_time(philo->env_data), philo->id);
        else if (action == SLEEP)
            printf("%ld %d is sleeping\n", get_current_time(philo->env_data), philo->id);
        else if (action == THINK)
            printf("%ld %d is thinking\n", get_current_time(philo->env_data), philo->id);
        else if (action == DEAD)
            printf("%ld %d is dead\n", get_current_time(philo->env_data), philo->id);
        else
            printf("ERROR: UNKNOWN ACTION\n");

        set_can_print(philo, true);
    }
}

