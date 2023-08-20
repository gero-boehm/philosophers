/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   announce.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:30:33 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/20 14:18:07 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

static char	*get_message_for_action(t_action action)
{
	if (action == TOOK_FORK)
		return ("has taken a fork");
	else if (action == STARTED_EATING)
		return ("is eating");
	else if (action == STARTED_SLEEPING)
		return ("is sleeping");
	else if (action == STARTED_THINKING)
		return ("is thinking");
	else if (action == DIED)
		return ("died");
	return ("");
}

void	announce(t_philo *philo, t_action action)
{
	unsigned long	time;
	char			*message;

	mutex_lock(&philo->data->lock_simulation_ended);
	mutex_lock(&philo->data->lock_simulation_start);
	if (philo->data->simulation_ended)
	{
		mutex_unlock(&philo->data->lock_simulation_ended);
		mutex_unlock(&philo->data->lock_simulation_start);
		return ;
	}
	if (action == DIED)
		philo->data->simulation_ended = 1;
	mutex_unlock(&philo->data->lock_simulation_ended);
	time = get_time() - philo->data->simulation_start;
	message = get_message_for_action(action);
	printf("%lu %u %s\n", time, philo->id, message);
	mutex_unlock(&philo->data->lock_simulation_start);
}

void	announce_activity(t_philo *philo)
{
	if (is_philo_eating(philo))
		announce(philo, STARTED_EATING);
	else if (is_philo_sleeping(philo))
		announce(philo, STARTED_SLEEPING);
	else if (is_philo_thinking(philo))
		announce(philo, STARTED_THINKING);
}
