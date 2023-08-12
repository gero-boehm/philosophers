/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:15:02 by gbohm             #+#    #+#             */
/*   Updated: 2023/06/14 10:16:11 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philodef.h"

void	mutex_lock(t_mutex *mutex)
{
	pthread_mutex_lock(&mutex->mutex);
	mutex->locked = 1;
}

void	mutex_unlock(t_mutex *mutex)
{
	mutex->locked = 0;
	pthread_mutex_unlock(&mutex->mutex);
}
