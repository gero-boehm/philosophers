/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philodef.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:58:53 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/12 17:28:47 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILODEF_H
# define PHILODEF_H

# include <pthread.h>

typedef struct s_data t_data;
typedef struct s_philo t_philo;

typedef enum e_activity {
	EATING,
	SLEEPING,
	THINKING
}	t_activity;

typedef struct s_mutex {
	pthread_mutex_t	mutex;
	int				initialized;
	int				locked;
}	t_mutex;

typedef struct	s_fork
{
	int		in_use;
	t_mutex	lock;
}	t_fork;

struct s_philo {
	unsigned int	id;
	unsigned int	num_eaten;
	unsigned long	last_eaten;
	unsigned long	activity_start;
	t_activity		activity;
	t_fork			fork;
	t_philo			*left_philo;
	pthread_t		thread;
	t_data			*data;
};

struct s_data {
	unsigned int	num_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	num_eat;
	unsigned int	num_philos_hungry;
	unsigned int	simulation_start;
	int				should_terminate;
	t_mutex			lock_time_to_die;
	t_mutex			lock_time_to_eat;
	t_mutex			lock_time_to_sleep;
	t_mutex			lock_num_eat;
	t_mutex			lock_num_philos_hungry;
	t_mutex			lock_simulation_start;
	t_mutex			lock_should_terminate;
	t_philo			*philos;
};

#endif