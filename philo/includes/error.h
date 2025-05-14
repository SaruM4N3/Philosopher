/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:11:22 by zsonie            #+#    #+#             */
/*   Updated: 2025/05/13 15:18:31 by zsonie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

//Colors
#define	RED	"\e[31m"
#define	GREEN  "\e[32m"
#define	YELLOW "\e[33m"
#define	RESET  "\e[0m"

//Error
#define	ERR_ARG 1001
//Messages
#define ERR_MESSAGE "ERROR :\t"
#define ARG_MESSAGE "%sWrong nbr of arguments...\n\n\
%sPls procced as follow:\n%s./philosopher \
number_of_philosophers \
time_to_die time_to_eat \
time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n%s"

//Functions
void print_custom_error(int err);
char *print_bool(bool i);

#endif