/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:18:43 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/16 15:59:49 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pick_up_fork(t_philo *philo, t_fork *fork)
{
	fork->belongs_to = philo->id;
	fork->reserved_for = 0;
	announce(philo, TOOK_FORK);
	// print_forks(philo->data);
}

static void	put_down_fork(t_fork *fork)
{
	mutex_lock(&fork->lock);
	fork->belongs_to = 0;
	mutex_unlock(&fork->lock);
}

int	can_pick_up_fork(t_philo *philo, t_fork *fork)
{
	if (fork->reserved_for == philo->id)
		return (1);
	return (fork->reserved_for == 0 && fork->belongs_to == 0);
}

static int try_to_grab_fork(t_philo *philo, t_fork *fork)
{
	int	fork_grabbed;

	mutex_lock(&fork->lock);
	if (can_pick_up_fork(philo, fork))
		pick_up_fork(philo, fork);
	fork_grabbed = fork->belongs_to == philo->id;
	mutex_unlock(&fork->lock);
	return (fork_grabbed);
}

int	try_to_grab_forks(t_philo *philo)
{
	int	forks_grabbed;

	forks_grabbed = 0;
	forks_grabbed += try_to_grab_fork(philo, &philo->fork);
	forks_grabbed += try_to_grab_fork(philo, &philo->left_philo->fork);
	return (forks_grabbed);
}

void	put_down_forks(t_philo *philo)
{
	put_down_fork(&philo->fork);
	put_down_fork(&philo->left_philo->fork);
}
