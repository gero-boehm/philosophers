/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:31:32 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/20 14:14:30 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	terminate(t_philo *philo)
{
	mutex_lock(&philo->data->lock_should_terminate);
	if (philo->data->should_terminate)
	{
		mutex_unlock(&philo->data->lock_should_terminate);
		return ;
	}
	philo->data->should_terminate = 1;
	mutex_unlock(&philo->data->lock_should_terminate);
}

void	die(t_philo *philo)
{
	terminate(philo);
	announce(philo, DIED);
}

int	should_terminate(t_philo *philo)
{
	int	should_terminate;

	mutex_lock(&philo->data->lock_should_terminate);
	should_terminate = philo->data->should_terminate;
	mutex_unlock(&philo->data->lock_should_terminate);
	return (should_terminate);
}

int	should_philo_die(t_philo *philo)
{
	unsigned long	time;
	int				should_die;

	if (is_philo_eating(philo))
		return (0);
	time = get_time_since_last_eaten(philo);
	mutex_lock(&philo->data->lock_time_to_die);
	should_die = time >= philo->data->time_to_die + 7;
	mutex_unlock(&philo->data->lock_time_to_die);
	return (should_die);
}
