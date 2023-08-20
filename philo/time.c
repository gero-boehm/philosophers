/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:28:53 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/20 12:29:32 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "philodef.h"

unsigned long	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

unsigned long	get_time_since_last_eaten(t_philo *philo)
{
	unsigned long	time;

	time = get_time();
	return (time - philo->last_eaten);
}

unsigned long	get_time_since_activity_start(t_philo *philo)
{
	unsigned long	time;

	time = get_time();
	return (time - philo->activity_start);
}
