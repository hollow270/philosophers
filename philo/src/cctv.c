/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cctv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usf <usf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:13:01 by yhajbi            #+#    #+#             */
/*   Updated: 2025/07/15 12:53:08 by usf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*cctv(void *args)
{
	int			i;
	t_data		*data;

	data = (t_data *)args;
	while (!get_state(data))
	{
		i = 0;
		while (i < data->n_philos)
		{
			if (get_current_time()
				- get_last_meal(&data->philos[i]) >= data->lifespan)
				return (print_habit(&data->philos[i], "died"),
					set_state(data, 1), NULL);
			i++;
		}
		if (compare_meals_eaten(data))
		{
			set_state(data, 1);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

time_t	get_last_meal(t_philo *philo)
{
	time_t	tmp;

	if (pthread_mutex_lock(philo->last_meal_lock) != 0)
		return (-1);
	tmp = philo->last_meal_time;
	if (pthread_mutex_unlock(philo->last_meal_lock) != 0)
		return (-1);
	return (tmp);
}

void	set_last_meal(t_philo *philo, time_t time)
{
	if (pthread_mutex_lock(philo->last_meal_lock) != 0)
		return ;
	philo->last_meal_time = time;
	if (pthread_mutex_unlock(philo->last_meal_lock) != 0)
		return ;
}

int	compare_meals_eaten(t_data *data)
{
	int	i;
	int	count;

	if (data->n_meals <= 0)
		return (0);
	i = 0;
	count = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_lock(data->philos[i].meals_eaten_lock) != 0)
			return (-1);
		if (data->philos[i].meals_eaten >= data->n_meals)
			count++;
		if (pthread_mutex_unlock(data->philos[i].meals_eaten_lock) != 0)
			return (-1);
		i++;
	}
	if (count >= data->n_philos)
		return (1);
	return (0);
}

int	increment_meals_eaten(t_philo *philo)
{
	if (pthread_mutex_lock(philo->meals_eaten_lock) != 0)
		return (-1);
	philo->meals_eaten++;
	if (pthread_mutex_unlock(philo->meals_eaten_lock) != 0)
		return (-1);
	return (0);
}
