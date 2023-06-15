/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:29:17 by gbohm             #+#    #+#             */
/*   Updated: 2023/06/14 10:32:58 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <limits.h>

static size_t	_strlen(char *str)
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

int	parse_num(char *str, unsigned int *result)
{
	long	tmp;

	if (_strlen(str) > 10)
		return (1);
	tmp = 0;
	while(*str)
	{
		if (!is_digit(*str))
			return (2);
		tmp = tmp * 10 + *str - '0';
		str++;
	}
	if(tmp > INT_MAX)
		return (3);
	*result = tmp;
	return (0);
}
