/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:58:53 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/20 14:14:15 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philodef.h"

// fork_available.c
int				are_forks_available(t_philo *philo);

// is_philo2.c
int				is_philo_done_eating(t_philo *philo);
int				is_philo_done_sleeping(t_philo *philo);

// announce.c
void			announce(t_philo *philo, t_action action);
void			announce_activity(t_philo *philo);

// fork.c
void			pick_up_forks(t_philo *philo);
void			put_down_forks(t_philo *philo);

// malloc2.c
int				malloc2(size_t size, void **ptr);

// activity.c
void			switch_activity(t_philo *philo, t_activity activity);
void			execute_activity(t_philo *philo);

// callback.c
void			*thread_callback(void *arg);

// eat.c
void			finish_eating(t_philo *philo);
int				can_philo_eat(t_philo *philo);

// setup.c
int				setup(t_data *data);

// time.c
unsigned long	get_time(void);
unsigned long	get_time_since_last_eaten(t_philo *philo);
unsigned long	get_time_since_activity_start(t_philo *philo);

// cleanup.c
void			wait_for_threads(t_data *data);
int				cleanup(t_data *data);

// is_philo.c
int				is_philo_eating(t_philo *philo);
int				is_philo_sleeping(t_philo *philo);
int				is_philo_thinking(t_philo *philo);
int				is_philo_satiated(t_philo *philo);
int				is_philo_single(t_data *data);

// mutex/destroy.c
void			destroy_mutexes(t_data *data);

// mutex/init.c
int				init_mutexes(t_data *data);

// mutex/lock.c
void			mutex_lock(t_mutex *mutex);
void			mutex_unlock(t_mutex *mutex);

// parse.c
int				parse(char **argv, t_data *data);

// terminate.c
void			terminate(t_philo *philo);
void			die(t_philo *philo);
int				should_terminate(t_philo *philo);
int				should_philo_die(t_philo *philo);

#endif
