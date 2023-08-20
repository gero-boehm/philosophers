/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:37:45 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/20 15:25:48 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		mutex_lock(&philo->fork.lock);
		mutex_lock(&philo->left_philo->fork.lock);
	}
	else
	{
		mutex_lock(&philo->left_philo->fork.lock);
		mutex_lock(&philo->fork.lock);
	}
}

static void	unlock_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		mutex_unlock(&philo->fork.lock);
		mutex_unlock(&philo->left_philo->fork.lock);
	}
	else
	{
		mutex_unlock(&philo->left_philo->fork.lock);
		mutex_unlock(&philo->fork.lock);
	}
}

void	finish_eating(t_philo *philo)
{
	put_down_forks(philo);
	philo->num_eaten++;
	mutex_lock(&philo->data->lock_num_philos_hungry);
	if (is_philo_satiated(philo))
		philo->data->num_philos_hungry--;
	if (philo->data->num_philos_hungry == 0)
		terminate(philo);
	mutex_unlock(&philo->data->lock_num_philos_hungry);
}

int	can_philo_eat(t_philo *philo)
{
	int	picked_up_forks;

	if (is_philo_eating(philo) || is_philo_sleeping(philo)
		|| is_philo_single(philo->data))
		return (0);
	picked_up_forks = 0;
	lock_forks(philo);
	if (are_forks_available(philo))
	{
		pick_up_forks(philo);
		picked_up_forks = 1;
	}
	unlock_forks(philo);
	return (picked_up_forks);
}
