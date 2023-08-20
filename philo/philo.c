/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:00:46 by gbohm             #+#    #+#             */
/*   Updated: 2023/08/20 12:45:46 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"


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

int main(int argc, char **argv) {
	t_data data;

	if (argc < 5 || argc > 6)
		return (printf("Incorrect argument count.\n"), 1);
	if (parse(argv, &data))
		return (printf("An argument is incorrectly formatted.\n"), 2);
	if (setup(&data))
		return (3);
	cleanup(&data);
	return (0);
}
