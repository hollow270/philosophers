/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:11:07 by yhajbi            #+#    #+#             */
/*   Updated: 2025/07/14 14:25:58 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	initialize_philos_helper(t_data *data);
static int	fill_philos(t_data *data, int i);

int	initialize_philos(t_data *data)
{
	int			i;
	pthread_t	monitor_th_id;

	if (gc_mutex_init(&data->print_lock) != 0)
		return (-1);
	if (gc_mutex_init(&data->terminated_lock) != 0)
		return (-1);
	set_state(data, 0);
	data->forks = gc_malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		return (-1);
	if (initialize_philos_helper(data) != 0)
		return (-1);
	if (pthread_create(&monitor_th_id, NULL, cctv, data) != 0)
		return (-1);
	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_join(data->philos[i].tid, NULL) != 0)
			return (-1);
	}
	if (pthread_join(monitor_th_id, NULL) != 0)
		return (-1);
	return (0);
}

static int	initialize_philos_helper(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (-1);
		if (gc_mutex_register(&data->forks[i]) != 0)
			return (-1);
	}
	i = 0;
	while (i < data->n_philos)
	{
		if (fill_philos(data, i) != 0)
			return (-1);
		i++;
	}
	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_create(&data->philos[i].tid,
				NULL, habits, &data->philos[i]) != 0)
			return (-1);
	}
	return (0);
}

static int	fill_philos(t_data *data, int i)
{
	if (gc_mutex_init(&data->philos[i].last_meal_lock) != 0)
		return (-1);
	data->philos[i].id = i;
	data->philos[i].start_time = get_current_time();
	if (data->philos[i].start_time == -1)
		return (-1);
	data->philos[i].last_meal_time = get_current_time();
	if (data->philos[i].last_meal_time == -1)
		return (-1);
	data->philos[i].data = data;
	data->philos[i].r_fork = &data->forks[i];
	data->philos[i].l_fork = &data->forks[(i + 1) % data->n_philos];
	data->philos[i].meals_eaten = 0;
	return (0);
}

time_t	get_current_time(void)
{
	struct timeval	ac;

	if (gettimeofday(&ac, NULL) != 0)
		return (-1);
	return (ac.tv_sec * 1000 + ac.tv_usec / 1000);
}
