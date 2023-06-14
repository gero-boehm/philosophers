/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_shared.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:58:53 by gbohm             #+#    #+#             */
/*   Updated: 2023/06/14 10:25:15 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_SHARED_H
# define PHILO_SHARED_H

# include "philodef.h"

int		init_mutexes(t_data *data);
void	destroy_mutexes(t_data *data);
void	mutex_lock(t_mutex *mutex);
void	mutex_unlock(t_mutex *mutex);

#endif