/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:19:50 by yhajbi            #+#    #+#             */
/*   Updated: 2025/07/14 14:26:35 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	get_state(t_data *data)
{
	int	tmp;

	if (pthread_mutex_lock(data->terminated_lock) != 0)
		return (-1);
	tmp = data->terminated;
	if (pthread_mutex_unlock(data->terminated_lock) != 0)
		return (-1);
	return (tmp);
}

void	set_state(t_data *data, int val)
{
	if (pthread_mutex_lock(data->terminated_lock) != 0)
		return ;
	data->terminated = val;
	if (pthread_mutex_unlock(data->terminated_lock) != 0)
		return ;
}

void	print_habit(t_philo *philo, char *msg)
{
	static int	i;

	if (pthread_mutex_lock(philo->data->print_lock) != 0)
		return ;
	if (!i)
		printf("%ld %d %s\n",
			get_current_time() - philo->start_time, philo->id + 1, msg);
	if (pthread_mutex_unlock(philo->data->print_lock) != 0)
		return ;
	if (!strcmp("died", msg))
		i++;
}
