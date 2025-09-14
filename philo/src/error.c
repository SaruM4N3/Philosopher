/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:06:52 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/14 03:01:29 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"

void	print_custom_error(int err)
{
	if (err == ERR_ARG)
	{
		printf(ERR_MESSAGE ARG_MESSAGE, RED, YELLOW, GREEN, RESET);
	}
	else if (err == ERR_TIME)
	{
		printf(ERR_MESSAGE ERR_TIME_MESSAGE, RED, RESET);
	}
	else
		printf(ERR_MESSAGE "%sUnknown error\n%s", RED, RESET);
}

char	*colored_bool(bool b)
{
	if (!b)
		return (RED);
	else
		return (GREEN);
}

char	*print_bool(bool b)
{
	if (b == 1)
		return ("true");
	else
		return ("false");
}

// message exemple "%sphilo is_eating: %s%s%s\n"
void	print_custom_bool(char *message, bool b)
{
	printf(message, RESET, colored_bool(b), print_bool(b), RESET);
}

int	error_exit(int err, t_env *env)
{
	print_custom_error(err);
	if (env)
		destroy_and_free(env);
	return (1);
}