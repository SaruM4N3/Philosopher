/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 23:57:50 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/20 00:56:17 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <error.h>
#include <philo.h>

t_mut	*init_mut(int value)
{
	t_mut	*mut;

	mut = malloc(sizeof(t_mut) * 1);
	if (!mut)
		return (NULL);
	mut->value = value;
	pthread_mutex_init(&mut->mutex, NULL);
	return (mut);
}

void	set_val_mut(t_mut *mut, int new_val)
{
	pthread_mutex_lock(&mut->mutex);
	mut->value = new_val;
	pthread_mutex_unlock(&mut->mutex);
}

int	get_val_mut(t_mut *mut)
{
	int val;

	pthread_mutex_lock(&mut->mutex);
	val = mut->value;
	pthread_mutex_unlock(&mut->mutex);
	return (val);
}
