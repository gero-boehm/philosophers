/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:00:46 by gbohm             #+#    #+#             */
/*   Updated: 2023/06/14 10:51:50 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "philo.h"

#include <string.h>


#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define ORANGE	"\033[38;5;208m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define RESET	"\033[0m"

int	malloc2(size_t size, void **ptr)
{
	*ptr = malloc(size);
	return (*ptr == NULL);
}

unsigned long	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

int	parse(char **argv, t_data *data)
{
	if (parse_num(argv[1], &data->num_philos))
		return (1);
	if (parse_num(argv[2], &data->time_to_die))
		return (2);
	if (parse_num(argv[3], &data->time_to_eat))
		return (3);
	if (parse_num(argv[4], &data->time_to_sleep))
		return (4);
	if (argv[5] == NULL)
		data->num_eat = 0;
	else if (parse_num(argv[5], &data->num_eat))
		return (5);
	data->should_terminate = 0;
	return (0);
}

t_philo	*get_left_philo(t_data *data, unsigned int index)
{
	index = (index - 1 + data->num_philos) % data->num_philos;
	return (&data->philos[index]);
}

int	create_philo_array(t_data *data)
{
	return (malloc2(data->num_philos, (void **) &data->philos));
}

void	spawn_philos(t_data *data)
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
		philo->fork.in_use = 0;
		philo->left_philo = get_left_philo(data, i);
		philo->data = data;
		i++;
	}
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

int	is_philo_eating(t_philo *philo)
{
	return (philo->activity == EATING);
}

int	is_philo_sleeping(t_philo *philo)
{
	return (philo->activity == SLEEPING);
}

int	is_philo_thinking(t_philo *philo)
{
	return (philo->activity == THINKING);
}

int	should_philo_die(t_philo *philo)
{
	unsigned long	time;
	int				should_die;

	// printf(ORANGE "eating: %d\n" RESET, is_philo_eating(philo));
	if (is_philo_eating(philo))
		return (0);
	time = get_time_since_last_eaten(philo);
	// printf(ORANGE "last eaten: %lu\n" RESET, time);
	mutex_lock(&philo->data->lock_time_to_die);
	should_die = time >= philo->data->time_to_die;
	// printf(ORANGE "ttd: %u\n" RESET, philo->data->time_to_die);
	// printf(ORANGE "should die: %d\n" RESET, time >= philo->data->time_to_die);
	mutex_unlock(&philo->data->lock_time_to_die);
	return (should_die);
}

void	announce_activity(t_philo *philo)
{
	char	*str;

	str = "";
	if (is_philo_eating(philo))
	{
		str = "eating";
		printf("%lu %u has taken a fork\n", philo->activity_start, philo->id);
	}
	else if (is_philo_sleeping(philo))
		str = "sleeping";
	else if (is_philo_thinking(philo))
		str = "thinking";
	printf("%lu %u is %s\n", philo->activity_start, philo->id, str);
}

void announce_death(t_philo *philo)
{
	unsigned long	time;

	time = get_time();
	printf("%lu %u died\n", time, philo->id);
}

void	terminate(t_philo *philo)
{
	mutex_lock(&philo->data->lock_should_terminate);
	if (philo->data->should_terminate)
	{
		mutex_unlock(&philo->data->lock_should_terminate);
		return;
	}
	// printf(ORANGE "terminate\n" RESET);
	philo->data->should_terminate = 1;
	mutex_unlock(&philo->data->lock_should_terminate);
	announce_death(philo);
}

int	should_terminate(t_philo *philo)
{
	int	should_terminate;
	mutex_lock(&philo->data->lock_should_terminate);
	should_terminate = philo->data->should_terminate;
	mutex_unlock(&philo->data->lock_should_terminate);
	return (should_terminate);
}

void	switch_activity(t_philo *philo, t_activity activity)
{
	unsigned long	time;

	time = get_time();
	if (is_philo_eating(philo))
	{
		put_down_forks(philo);
		philo->num_eaten++;
		philo->last_eaten = time;
	}
	philo->activity = activity;
	philo->activity_start = time;
	announce_activity(philo);
}

int is_philo_done_eating(t_philo *philo)
{
	unsigned long	time;
	int				is_done;

	if (!is_philo_eating(philo))
		return (0);
	time = get_time_since_activity_start(philo);
	mutex_lock(&philo->data->lock_time_to_eat);
	is_done = time >= philo->data->time_to_eat;
	mutex_unlock(&philo->data->lock_time_to_eat);
	return (is_done);
}

int is_philo_done_sleeping(t_philo *philo)
{
	unsigned long	time;
	int				is_done;

	if (!is_philo_sleeping(philo))
		return (0);
	time = get_time_since_activity_start(philo);
	mutex_lock(&philo->data->lock_time_to_sleep);
	is_done = time >= philo->data->time_to_sleep;
	mutex_unlock(&philo->data->lock_time_to_sleep);
	return (is_done);
}

int	is_fork_available(t_philo *philo)
{
	return (!philo->fork.in_use);
}

int	are_forks_available(t_philo *philo)
{
	return (is_fork_available(philo) && is_fork_available(philo->left_philo));
}

int	is_philo_satiated(t_philo *philo)
{
	int	is_satiated;

	mutex_lock(&philo->data->lock_num_eat);
	if (philo->data->num_eat == 0)
		is_satiated = 0;
	else
		is_satiated = philo->num_eaten == philo->data->num_eat;
	mutex_unlock(&philo->data->lock_num_eat);
	return (is_satiated);
}

int	can_philo_eat(t_philo *philo)
{
	int	picked_up_forks;

	if (is_philo_eating(philo) || is_philo_sleeping(philo))
		return (0);
	picked_up_forks = 0;
	mutex_lock(&philo->fork.lock);
	mutex_lock(&philo->left_philo->fork.lock);
	if (!is_philo_satiated(philo) && are_forks_available(philo))
	{
		pick_up_forks(philo);
		picked_up_forks = 1;
	}
	mutex_unlock(&philo->fork.lock);
	mutex_unlock(&philo->left_philo->fork.lock);
	return (picked_up_forks);
}

void execute_activity(t_philo *philo)
{
	if(is_philo_done_eating(philo))
		switch_activity(philo, SLEEPING);
	else if(is_philo_done_sleeping(philo))
		switch_activity(philo, THINKING);
	if(can_philo_eat(philo))
		switch_activity(philo, EATING);
	usleep(1000);
}

void	*thread_callback(void *arg)
{
	t_philo			*philo;

	philo = arg;
	while (1)
	{
		if (should_philo_die(philo))
			terminate(philo);
		if (should_terminate(philo))
			return (NULL);
		execute_activity(philo);
	}
	return (NULL);
}

int	spawn_threads(t_data *data)
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

void	wait_for_threads(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	cleanup(t_data *data)
{
	wait_for_threads(data);
	destroy_mutexes(data);
	free(data->philos);
	return (0);
}

int main(int argc, char **argv) {
	t_data data;

	if (argc < 5 || argc > 6)
		return (printf("Incorrect argument count.\n"), 1);
	if (parse(argv, &data))
		return (printf("An argument is incorrectly formatted.\n"), 2);
	if (create_philo_array(&data))
	{
		printf("Error creating philo array.\n");
		return (4);
	}
	spawn_philos(&data);
	if (init_mutexes(&data))
	{
		destroy_mutexes(&data);
		free(data.philos);
		printf("Error initializing mutexes.\n");
		return (5);
	}
	if (spawn_threads(&data))
	{
		cleanup(&data);
		printf("Error spawning threads.\n");
		return (6);
	}
	cleanup(&data);
	return (0);
}
