/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_available.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:33:52 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/20 12:34:11 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philodef.h"

static int	is_fork_available(t_philo *philo)
{
	return (!philo->fork.in_use);
}

int	are_forks_available(t_philo *philo)
{
	return (is_fork_available(philo) && is_fork_available(philo->left_philo));
}
