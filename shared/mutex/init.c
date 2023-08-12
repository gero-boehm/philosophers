/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:12:25 by gbohm             #+#    #+#             */
/*   Updated: 2023/07/20 21:31:55 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philodef.h"

static int	init_mutex(t_mutex *mutex)
{
	if (pthread_mutex_init(&mutex->mutex, NULL))
		return (1);
	mutex->initialized = 1;
	mutex->locked = 0;
	return (0);
}

static int	init_philo_mutexes(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (init_mutex(&data->philos[i].fork.lock))
			return (1);
		i++;
	}
	return (0);
}

int	init_mutexes(t_data *data)
{
	if (init_mutex(&data->lock_time_to_die))
		return (1);
	if (init_mutex(&data->lock_time_to_eat))
		return (2);
	if (init_mutex(&data->lock_time_to_sleep))
		return (3);
	if (init_mutex(&data->lock_num_eat))
		return (4);
	if (init_mutex(&data->lock_num_philos_hungry))
		return (5);
	if (init_mutex(&data->lock_should_terminate))
		return (6);
	if (init_philo_mutexes(data))
		return (7);
	return (0);
}
