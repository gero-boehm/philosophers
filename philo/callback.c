/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:47:18 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/16 15:59:54 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

void	*thread_callback(void *arg)
{
	t_philo			*philo;

	philo = arg;
	// if (philo->id % 2 == 1)
	// 	usleep(500);
	while (1)
	{
		if (should_terminate(philo))
			return (NULL);
		if (should_philo_die(philo))
			return (die(philo), NULL);
		execute_activity(philo);
		usleep(200);
	}
	return (NULL);
}
