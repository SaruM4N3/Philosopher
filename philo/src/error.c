/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:06:52 by zsonie            #+#    #+#             */
/*   Updated: 2025/05/13 15:19:16 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "error.h"

void print_custom_error(int err)
{
	if (err == ERR_ARG)
    {
        printf(ERR_MESSAGE ARG_MESSAGE, RED, YELLOW, GREEN, RESET);
    }
    else
        printf(ERR_MESSAGE "%sUnknown error\n%s", RED, RESET);
}

char    *print_bool(bool i)
{
    if (i == 1)
        return ("true");
    else
        return ("false");
}
