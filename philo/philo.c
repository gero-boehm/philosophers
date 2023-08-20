/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:00:46 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/20 14:14:50 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (printf("Incorrect argument count.\n"), 1);
	if (parse(argv, &data))
		return (printf("An argument is incorrectly formatted.\n"), 2);
	if (setup(&data))
		return (3);
	cleanup(&data);
	return (0);
}
