/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:34:06 by zsonie            #+#    #+#             */
/*   Updated: 2025/08/25 15:18:11 by zsonie           ###   ########lyon.fr   */
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

# define EAT 4201
# define FORK 4202
# define SLEEP 4203
# define THINK 4204
# define DEAD 4205

//STRUCTS
typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_philo
{
	struct s_env	*env_data;
	pthread_t		thread;

	int				id;
	int				meals_count;
	int				current_state;
	int				last_eat_time;
	int				self_death_time;

	bool			is_eating;

	pthread_mutex_t	mutex;
	t_fork			*left_fork;
	t_fork			*right_fork;
}					t_philo;

typedef struct s_env
{
	pthread_t		*thread;

	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	
	int				start_time;
	bool			dead;
	bool 			finished;
	
	t_philo			*philosophers;
	t_fork			*forks;
	pthread_mutex_t	sim_mutex;
	pthread_mutex_t print_mutex;
}					t_env;



// FUNCTIONS

//philo.c
void				grab_forks(t_philo *p);

//display.c
void				print_action(t_philo *philo, int action);
void				*print_test(void *philo);
void				*print_test_first_philo(void *philo);

//init.c
t_env				init_env(char **av, int ac);
bool				init_philosophers(t_env *env);
bool				init_forks(t_env *env);
bool				init_threads(t_env *env);

//utils.c
int					ft_atoi(const char *str);
int					ft_strlen(char *str);

//utils2.c
long long			get_current_time(t_env *env_data);
void				precise_usleep(long long milliseconds);
bool				validate_input(t_env *env_data, char **av);


#endif
