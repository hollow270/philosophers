/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   habits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usf <usf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:17:03 by yhajbi            #+#    #+#             */
/*   Updated: 2025/07/15 12:56:01 by usf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*habits(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->data->n_philos == 1)
	{
		if (pthread_mutex_lock(philo->r_fork) != 0)
			return (NULL);
		print_habit(philo, "has taken a fork");
		precise_sleep(philo->data->lifespan);
		if (pthread_mutex_unlock(philo->r_fork) != 0)
			return (NULL);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(100);
	while (!get_state(philo->data))
	{
		philo_eat(philo);
		increment_meals_eaten(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	precise_sleep(time_t time)
{
	time_t	start;

	start = get_current_time();
	if (start == -1)
		return ;
	while (get_current_time() - start < time)
		usleep(100);
}

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2)
	{
		if (pthread_mutex_lock(philo->l_fork) != 0)
			return ;
		print_habit(philo, "has taken a fork");
		if (pthread_mutex_lock(philo->r_fork) != 0)
			return ;
		print_habit(philo, "has taken a fork");
	}
	else
	{
		if (pthread_mutex_lock(philo->r_fork) != 0)
			return ;
		print_habit(philo, "has taken a fork");
		if (pthread_mutex_lock(philo->l_fork) != 0)
			return ;
		print_habit(philo, "has taken a fork");
	}
	set_last_meal(philo, get_current_time());
	print_habit(philo, "is eating");
	precise_sleep(philo->data->eating_duration);
	if (pthread_mutex_unlock(philo->l_fork) != 0)
		return ;
	if (pthread_mutex_unlock(philo->r_fork) != 0)
		return ;
}

void	philo_sleep(t_philo *philo)
{
	print_habit(philo, "is sleeping");
	precise_sleep(philo->data->sleeping_duration);
}

void	philo_think(t_philo *philo)
{
	print_habit(philo, "is thinking");
	precise_sleep(1);
}
