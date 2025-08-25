/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:11:22 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/25 17:41:34 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>
# include "philo.h"

//Colors
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define CYAN "\033[36m"
# define RESET "\e[0m"

//Error
# define ERR_ARG 1001
# define ERR_TIME 1002
# define ERR_PTR (void *)1

//Messages
# define ERR_MESSAGE "ERROR :\t"
# define ERR_TIME_MESSAGE "%sGettimeofday error occured\n%s"
# define ARG_MESSAGE "%sWrong nbr of arguments...\n\n\
%sPls procced as follow:\n%s./philosopher \
number_of_philosophers \
time_to_die time_to_eat \
time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n%s"

//Functions
void	print_custom_error(int err);
void	print_custom_bool(char *message, bool b);
char	*colored_bool(bool b);
char	*print_bool(bool b);
int		error_exit(int err, t_env *env);
void    destroy_and_free(t_env *env);

#endif