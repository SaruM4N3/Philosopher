/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:34:06 by zsonie            #+#    #+#             */
/*   Updated: 2025/09/21 01:03:20 by zsonie           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

# define EAT 4201
# define FORK 4202
# define SLEEP 4203
# define THINK 4204
# define DEAD 4205

enum				e_env_state
{
	starting,
	running,
	stopped
};

// STRUCTS
typedef struct s_mut
{
	int				value;
	pthread_mutex_t	mutex;
}					t_mut;

typedef struct s_fork
{
	t_mut			*is_available;
}					t_fork;

typedef struct s_philo
{
	struct s_env	*env_data;

	int				id;
	int				must_eat;
	int				meals_count;
	time_t			self_death_time;

	t_mut			*is_ready;

	t_fork			*right_fork;
	t_fork			*left_fork;
}					t_philo;

typedef struct s_env
{
	pthread_t		*threads;

	int				nb_philo;
	int				nb_must_eat;

	t_mut			*finished;
	t_mut			*can_print;
	t_mut			*state;

	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start_time;

	t_philo			*philosophers;
	t_fork			*forks;
}					t_env;

// FUNCTIONS
// action.c
void				*philo_eat(t_philo *philo);
void				*philo_sleep(t_philo *philo);
void				*philo_death_check(void *philo_ptr);

// init.c
t_env				init_env(int ac, char **av);
bool				init_philosophers(t_env *env);
bool				init_forks(t_env *env);
bool				init_threads(t_env *env);
bool				init_all(t_env *env);

// fork.c
void				*grab_forks(t_philo *philo);
void				release_forks(t_philo *philo);

// monitor.c
void				*monitor_routine(void *env_ptr);
void				*monitor_checker(void *philo_ptr);

// mut.c
t_mut				*init_mut(int value);
void				set_val_mut(t_mut *mut, int new_val);
int					get_val_mut(t_mut *mut);
void				destroy_mut(t_mut *mut);

// philo.c
void				*philo_routine(void *philo_ptr);

// utils.c
int					ft_atoi(const char *str);
void				print_action(t_philo *philo, int action);

// utils2.c
time_t				timestamp_in_ms(void);
time_t				get_current_time(t_env *env_data);
int					ft_wait(unsigned int milliseconds, t_philo *philo);
void				*ft_calloc(size_t nmemb, size_t size);

#endif
