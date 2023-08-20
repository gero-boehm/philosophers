/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:18:43 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/20 12:27:31 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pick_up_fork(t_philo *philo, t_fork *fork)
{
	fork->in_use = 1;
	announce(philo, TOOK_FORK);
}

static void	put_down_fork(t_fork *fork)
{
	mutex_lock(&fork->lock);
	fork->in_use = 0;
	mutex_unlock(&fork->lock);
}

void	pick_up_forks(t_philo *philo)
{
	pick_up_fork(philo, &philo->fork);
	pick_up_fork(philo, &philo->left_philo->fork);
}

void	put_down_forks(t_philo *philo)
{
	put_down_fork(&philo->fork);
	put_down_fork(&philo->left_philo->fork);
}
