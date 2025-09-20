/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:11:22 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/21 00:08:25 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

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
# define ERR_PTHREAD_CREATE 1003
# define ERR_PTHREAD_JOIN 1004
# define ERR_PTR (void *)1

//Messages
# define ERR_MESSAGE "ERROR :\t"
# define ERR_TIME_MESSAGE "%sGettimeofday failed\n%s"
# define ERR_PCREATE_MESSAGE "%spthread_create failed\n%s"
# define ERR_PJOIN_MESSAGE "%spthread_join failed\n%s"
# define ARG_MESSAGE "%sWrong arguments or nbr of arguments...\n\n\
%sPls procced as follow:\n%s./philosopher \
nb_philo \
time_to_die time_to_eat \
time_to_sleep \
[nb_must_eat]\n%s"

//Functions
void	print_custom_error(int err);
int		error_exit(int err, t_env *env);
void	destroy_and_free(t_env *env);

#endif