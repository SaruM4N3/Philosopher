/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:34:06 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/14 03:01:33 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define EAT 4201
# define FORK 4202
# define SLEEP 4203
# define THINK 4204
# define DEAD 4205

// STRUCTS
typedef struct s_fork
{
	int				id;
	bool			is_available;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_philo
{
	struct s_env	*env_data;
	pthread_t		philo_thread;

	int				id;
	int				meals_count;
	enum			philo_state
	{
		alive,
		dead
	} philo_state;

	bool			started;
	bool			eating;
	time_t			self_death_time;

	pthread_mutex_t	mutex;
	t_fork			*right_fork;
	t_fork			*left_fork;
}					t_philo;

typedef struct s_env
{
	pthread_t		*threads;

	int				number_of_philosophers;
	int				number_of_times_each_philosopher_must_eat;
	int				finished;

	enum			state
	{
		starting,
		running,
		stoping,
		stoped
	} state;

	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start_time;

	t_philo			*philosophers;
	t_fork			*forks;
	pthread_mutex_t	sim_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	print_mutex;
}					t_env;

// FUNCTIONS

// action.c
void				*philo_eat(t_philo *philo);
void				*philo_sleep(t_philo *philo);
void				*philo_death_check(void *philo_ptr);

// init.c
t_env				init_env(char **av, int ac);
bool				init_philosophers(t_env *env);
bool				init_forks(t_env *env);
bool				init_threads(t_env *env);
bool				init_all(char **av, int ac, t_env *env);

// fork.c
void				*grab_forks(t_philo *philo);
void				release_forks(t_philo *philo);

// monitor.c
void				*monitor_routine(void *env_ptr);
void				*monitor_checker(void *philo_ptr);

// philo.c
void				*philo_routine(void *philo_ptr);

// utils.c
int					ft_atoi(const char *str);
void				print_action(t_philo *philo, int action);

// utils2.c
time_t				timestamp_in_ms(void);
time_t				get_current_time(t_env *env_data);
int					ft_wait(unsigned int milliseconds);
bool				validate_input(t_env *env_data, char **av, int ac);

#endif
