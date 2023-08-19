/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:47:18 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/18 13:06:53 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

void	*thread_callback(void *arg)
{
	t_philo			*philo;

	philo = arg;
	usleep((philo->id % 2 == 0) * 1000);
	usleep((philo->id % 3 == 0) * 4000);
	while (1)
	{
		if (should_philo_die(philo))
			die(philo);
		if (should_terminate(philo))
			return (NULL);
		execute_activity(philo);
		usleep(1000);
	}
	return (NULL);
}
