/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:18:43 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/17 12:49:40 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_fork(t_philo *philo)
{
	philo->fork.in_use = 1;
	announce(philo, TOOK_FORK);
}

static void	put_down_fork(t_philo *philo)
{
	mutex_lock(&philo->fork.lock);
	philo->fork.in_use = 0;
	mutex_unlock(&philo->fork.lock);
}

void	pick_up_forks(t_philo *philo)
{
	pick_up_fork(philo);
	pick_up_fork(philo->left_philo);
}

void	put_down_forks(t_philo *philo)
{
	put_down_fork(philo);
	put_down_fork(philo->left_philo);
}
