/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:58:53 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/17 12:49:44 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philodef.h"

// fork.c
void    pick_up_forks(t_philo *philo);
void    put_down_forks(t_philo *philo);

// philo.c
int     malloc2(size_t size, void **ptr);
unsigned long   get_time(void);
int     parse(char **argv, t_data *data);
unsigned long   get_time_since_last_eaten(t_philo *philo);
unsigned long   get_time_since_activity_start(t_philo *philo);
int     is_philo_eating(t_philo *philo);
int     is_philo_sleeping(t_philo *philo);
int     is_philo_thinking(t_philo *philo);
int     should_philo_die(t_philo *philo);
void    announce_activity(t_philo *philo);
void announce_death(t_philo *philo);
void    terminate(t_philo *philo);
void    die(t_philo *philo);
int     should_terminate(t_philo *philo);
int     is_philo_satiated(t_philo *philo);
void    finish_eating(t_philo *philo);
void    switch_activity(t_philo *philo, t_activity activity);
int is_philo_done_eating(t_philo *philo);
int is_philo_done_sleeping(t_philo *philo);
int     is_fork_available(t_philo *philo);
int     are_forks_available(t_philo *philo);
int     can_philo_eat(t_philo *philo);
void execute_activity(t_philo *philo);
void    wait_for_threads(t_data *data);
int     cleanup(t_data *data);

// callback.c
void    *thread_callback(void *arg);

// setup.c
int     setup(t_data *data);

// mutex/destroy.c
void    destroy_mutexes(t_data *data);

// mutex/init.c
int     init_mutexes(t_data *data);

// mutex/lock.c
void    mutex_lock(t_mutex *mutex);
void    mutex_unlock(t_mutex *mutex);

// parse.c
int     parse_num(char *str, unsigned int *result);

void	announce(t_philo *philo, t_action action);
void	pick_up_fork(t_philo *philo);

#endif