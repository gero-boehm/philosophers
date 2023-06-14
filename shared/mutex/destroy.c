/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:10:49 by gbohm             #+#    #+#             */
/*   Updated: 2023/06/14 10:19:24 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutex(t_mutex *mutex)
{
	if (!mutex->initialized)
		return ;
	if (mutex->locked)
		mutex_unlock(mutex);
	pthread_mutex_destroy(&mutex->mutex);
}

static void destroy_philo_mutexes(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->num_philos)
	{
		destroy_mutex(&data->philos[i].fork.lock);
		i++;
	}
}

void	destroy_mutexes(t_data *data)
{
	destroy_mutex(&data->lock_time_to_die);
	destroy_mutex(&data->lock_time_to_eat);
	destroy_mutex(&data->lock_time_to_sleep);
	destroy_mutex(&data->lock_num_eat);
	destroy_mutex(&data->lock_should_terminate);
	destroy_philo_mutexes(data);
}
