/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:47:18 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/12 17:25:49 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

void	*thread_callback(void *arg)
{
	t_philo			*philo;

	philo = arg;
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
