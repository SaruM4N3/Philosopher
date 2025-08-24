/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:34:06 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/24 13:08:23 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "error.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define EAT 1001
# define FORK 1002
# define SLEEP 1003
# define THINK 1004
# define DEAD 1005

//STRUCTS
typedef struct s_fork
{
	int				id;
	bool			is_available;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_info
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				start_time;
	t_fork			*last_fork;

	bool			simulation_ended;
	pthread_mutex_t	sim_mutex;

	pthread_mutex_t print_mutex;
}					t_info;
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	int				last_eat_time;
	bool			is_eating;
	bool			is_sleeping;
	bool			is_dead;
	t_info			*info;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	sleep_mutex;
	pthread_mutex_t	dead_mutex;
}					t_philo;

typedef struct s_env
{
	t_info			*info;
	t_philo			*philos;
}					t_env;

// FUNCTIONS

//philo.c
bool				grab_forks(t_philo *p);
void				philo_dead(t_philo *p);
void				*life(void *philo);

//monitor.c

void				*monitor_routine(void *env_ptr);

//display.c
void				print_action(t_philo *philo, int action);
void				*print_test(void *philo);
void				*print_test_first_philo(void *philo);
long long			timestamp_in_ms(void);

//init.c
t_env				init_env(char **av);
bool				init_philosophers(t_env *env);
bool				init_thread(t_philo *philo);

//utils.c
void				ft_putchar(char c);
void				ft_putstr(char *str);
int					ft_atoi(const char *str);
int					ft_strlen(char *str);

//utils2.c
void				precise_usleep(long long milliseconds);
bool				validate_input(t_info *info, char **av);
long long			get_current_time(t_info *info);

//simulation.c
bool				init_simulation(t_env *env, char **av);
bool				launch_simulation(t_env *env);
void				set_simulation_end(t_info *info, bool end);

#endif
