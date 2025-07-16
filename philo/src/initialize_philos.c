/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:11:07 by yhajbi            #+#    #+#             */
/*   Updated: 2025/07/16 21:36:33 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	initialize_philos_helper(t_data *data);
static int	fill_philos(t_data *data, int i);
static int	create_threads(t_data *data, pthread_t *monitor_th_id);
static int	join_threads(t_data *data, pthread_t *monitor_th_id);

int	initialize_philos(t_data *data)
{
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
	if (create_threads(data, &monitor_th_id) != 0)
		return (-1);
	if (join_threads(data, &monitor_th_id) != 0)
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
	return (0);
}

static int	fill_philos(t_data *data, int i)
{
	if (gc_mutex_init(&data->philos[i].last_meal_lock) != 0)
		return (-1);
	if (gc_mutex_init(&data->philos[i].meals_eaten_lock) != 0)
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

static int	create_threads(t_data *data, pthread_t *monitor_th_id)
{
	int			i;

	i = -1;
	while (++i < data->n_philos)
		data->philos[i].tid = 0;
	*monitor_th_id = 0;
	i = -1;
	while (++i < data->n_philos)
	{
		data->philos[i].tid = 0;
		if (pthread_create(&data->philos[i].tid,
				NULL, habits, &data->philos[i]) != 0)
			return (-1);
	}
	if (pthread_create(monitor_th_id, NULL, cctv, data) != 0)
		return (-1);
	return (0);
}

static int	join_threads(t_data *data, pthread_t *monitor_th_id)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	while (++i < data->n_philos)
	{
		if (data->philos[i].tid != 0)
		{
			if (pthread_join(data->philos[i].tid, NULL) != 0)
				ret = -1;
		}
	}
	if (*monitor_th_id != 0)
	{
		if (pthread_join(*monitor_th_id, NULL) != 0)
			ret = -1;
	}
	return (ret);
}
