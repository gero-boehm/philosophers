/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_philo2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:35:01 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/20 12:36:48 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_philo_done_eating(t_philo *philo)
{
	unsigned long	time;
	int				is_done;

	if (!is_philo_eating(philo))
		return (0);
	time = get_time_since_activity_start(philo);
	mutex_lock(&philo->data->lock_time_to_eat);
	is_done = time >= philo->data->time_to_eat - 1;
	mutex_unlock(&philo->data->lock_time_to_eat);
	return (is_done);
}

int is_philo_done_sleeping(t_philo *philo)
{
	unsigned long	time;
	int				is_done;

	if (!is_philo_sleeping(philo))
		return (0);
	time = get_time_since_activity_start(philo);
	mutex_lock(&philo->data->lock_time_to_sleep);
	is_done = time >= philo->data->time_to_sleep - 1;
	mutex_unlock(&philo->data->lock_time_to_sleep);
	return (is_done);
}
