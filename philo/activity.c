/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:38:37 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/20 12:44:46 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

void	switch_activity(t_philo *philo, t_activity activity)
{
	unsigned long	time;

	time = get_time();
	if (is_philo_eating(philo))
		finish_eating(philo);
	philo->activity = activity;
	philo->activity_start = time;
	if (is_philo_eating(philo))
		philo->last_eaten = time;
	announce_activity(philo);
	if (is_philo_thinking(philo))
		usleep(4000);
}

void	execute_activity(t_philo *philo)
{
	if(is_philo_done_eating(philo))
		switch_activity(philo, SLEEPING);
	else if(is_philo_done_sleeping(philo))
		switch_activity(philo, THINKING);
	if(can_philo_eat(philo))
		switch_activity(philo, EATING);
}
