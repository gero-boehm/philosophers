/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:29:17 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/20 14:45:23 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <limits.h>
#include "philo.h"

static size_t	str_len(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	parse_num(char *str, unsigned int *result)
{
	long	tmp;

	if (str_len(str) > 10)
		return (1);
	tmp = 0;
	while (*str)
	{
		if (!is_digit(*str))
			return (2);
		tmp = tmp * 10 + *str - '0';
		str++;
	}
	if (tmp > INT_MAX)
		return (3);
	*result = tmp;
	return (0);
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
	else
	{
		if (parse_num(argv[5], &data->num_eat))
			return (5);
		if (data->num_eat == 0)
			return (6);
	}
	data->num_philos_hungry = data->num_philos;
	data->simulation_start = get_time();
	data->simulation_ended = 0;
	data->should_terminate = 0;
	return (0);
}
