/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:06:52 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/22 04:00:56 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <stdio.h>

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
	else if (err == ERR_PTHREAD_CREATE)
	{
		printf(ERR_MESSAGE ERR_PCREATE_MESSAGE, RED, RESET);
	}
	else if (err == ERR_PTHREAD_JOIN)
	{
		printf(ERR_MESSAGE ERR_PJOIN_MESSAGE, RED, RESET);
	}
	else
		printf(ERR_MESSAGE "%sUnknown error\n%s", RED, RESET);
}

int	error_handler(int err, t_env *env)
{
	print_custom_error(err);
	if (env)
		destroy_and_free(env);
	return (0);
}
