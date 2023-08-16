/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:01 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/16 15:57:15 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "philo.h"

static int	create_philo_array(t_data *data)
{
	return (malloc2(data->num_philos, (void **) &data->philos));
}

static t_philo	*get_left_philo(t_data *data, unsigned int index)
{
	index = (index - 1 + data->num_philos) % data->num_philos;
	return (&data->philos[index]);
}

void	reserve_fork(t_philo *philo, t_fork *fork)
{
	if (fork->reserved_for != 0)
		return ;
	fork->reserved_for = philo->id;
}

void	reserve_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return ;
	reserve_fork(philo, &philo->fork);
	reserve_fork(philo, &philo->left_philo->fork);
}

void	print_forks(t_data *data)
{
	unsigned int	i;
	t_philo			*philo;

	i = 0;
	while (i < data->num_philos)
	{
		philo = &data->philos[i];
		printf("(%u) %u|%u ", philo->id, philo->fork.belongs_to, philo->fork.reserved_for);
		i++;
	}
	printf("\n");
}

static void	spawn_philos(t_data *data)
{
	unsigned int	i;
	unsigned long	time;
	t_philo			*philo;

	i = 0;
	time = get_time();
	while (i < data->num_philos)
	{
		philo = &data->philos[i];
		philo->id = i + 1;
		philo->last_eaten = time;
		philo->activity = THINKING;
		philo->fork.belongs_to = 0;
		philo->fork.reserved_for = 0;
		philo->left_philo = get_left_philo(data, i);
		philo->data = data;
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		philo = &data->philos[i];
		reserve_forks(philo);
		// printf("%u - l %u|%u r %u|%u\n", philo->id, philo->left_philo->id, philo->left_philo->fork.reserved_for, philo->id, philo->fork.reserved_for);
		i++;
	}
	print_forks(data);
	// exit(0);
}

static int	spawn_threads(t_data *data)
{
	unsigned int	i;
	t_philo			*philo;

	i = 0;
	while (i < data->num_philos)
	{
		philo = &data->philos[i];
		if (pthread_create(&philo->thread, NULL, thread_callback, philo))
		{
			mutex_lock(&data->lock_should_terminate);
			data->should_terminate = 1;
			mutex_unlock(&data->lock_should_terminate);
			return (1);
		}
		i++;
	}
	return (0);
}

int	setup(t_data *data)
{
	if (create_philo_array(data))
	{
		printf("Error creating philo array.\n");
		return (1);
	}
	spawn_philos(data);
	if (init_mutexes(data))
	{
		destroy_mutexes(data);
		free(data->philos);
		printf("Error initializing mutexes.\n");
		return (2);
	}
	if (spawn_threads(data))
	{
		cleanup(data);
		printf("Error spawning threads.\n");
		return (3);
	}
	return (0);
}
