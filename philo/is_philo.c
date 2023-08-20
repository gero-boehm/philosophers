/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:35:01 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/20 12:36:53 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_eating(t_philo *philo)
{
	return (philo->activity == EATING);
}

int	is_philo_sleeping(t_philo *philo)
{
	return (philo->activity == SLEEPING);
}

int	is_philo_thinking(t_philo *philo)
{
	return (philo->activity == THINKING);
}

int	is_philo_satiated(t_philo *philo)
{
	int	is_satiated;

	mutex_lock(&philo->data->lock_num_eat);
	if (philo->data->num_eat == 0)
		is_satiated = 0;
	else
		is_satiated = philo->num_eaten == philo->data->num_eat;
	mutex_unlock(&philo->data->lock_num_eat);
	return (is_satiated);
}

int	is_philo_single(t_data *data)
{
	int	is_single;

	mutex_lock(&data->lock_num_philos);
	is_single = data->num_philos == 1;
	mutex_unlock(&data->lock_num_philos);
	return (is_single);
}
