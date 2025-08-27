/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:11:38 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/21 13:38:36 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stddef.h>

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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		ft_strlen(char *str)
{
	int len;
	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_putstr(char *str)
{
	int len;
	len = ft_strlen(str);
	write(1, str, len);
}
