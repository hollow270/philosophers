/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:20:43 by yhajbi            #+#    #+#             */
/*   Updated: 2025/07/14 12:47:56 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	check_args(int ac, char **av);

// int	main(int ac, char **av)
// {
// 	t_data	data;

// 	if (ac != 5 && ac != 6)
// 		return (printf("Invalid arguments\n"), 1);
// 	if (check_args(ac, av) != 0)
// 		return (printf("Invalid arguments\n"), 1);
// 	data.n_philos = ft_atoi(av[1]);
// 	data.lifespan = ft_atoi(av[2]);
// 	data.eating_duration = ft_atoi(av[3]);
// 	data.sleeping_duration = ft_atoi(av[4]);
// 	data.n_meals = -1;
// 	if (ac == 6)
// 		data.n_meals = ft_atoi(av[5]);
// 	data.forks = gc_malloc(sizeof(pthread_mutex_t) * data.n_philos);
// 	if (!data.forks)
// 		return (1);
// 	data.philos = gc_malloc(sizeof(t_philo) * data.n_philos);
// 	if (!data.philos)
// 		return (gc_free_all(), 1);
// 	if (initialize_philos(&data) != 0)
// 		return (gc_free_all(), printf("Philo: failure error\n"), 1);
// 	gc_free_all();
// 	return (0);
// }

/* Modified main function to use mutex garbage collection */
int main(int ac, char **av)
{
    t_data data;
    
    if (ac != 5 && ac != 6)
        return (printf("Invalid arguments\n"), 1);
    if (check_args(ac, av) != 0)
        return (printf("Invalid arguments\n"), 1);
    
    data.n_philos = ft_atoi(av[1]);
    data.lifespan = ft_atoi(av[2]);
    data.eating_duration = ft_atoi(av[3]);
    data.sleeping_duration = ft_atoi(av[4]);
    data.n_meals = -1;
    if (ac == 6)
        data.n_meals = ft_atoi(av[5]);
    
    data.philos = gc_malloc(sizeof(t_philo) * data.n_philos);
    if (!data.philos)
        return (gc_free_all(), 1);
    
    if (initialize_philos(&data) != 0)
    {
        gc_mutex_destroy_all();  // Destroy all mutexes
        gc_free_all();           // Free all memory
        return (printf("Philo: failure error\n"), 1);
    }
    
    gc_mutex_destroy_all();      // Clean up all mutexes
    gc_free_all();               // Clean up all memory
    return (0);
}

static int	check_args(int ac, char **av)
{
	if (ft_atoi(av[1]) <= 0)
		return (-1);
	if (ft_atoi(av[2]) <= 0)
		return (-1);
	if (ft_atoi(av[3]) <= 0)
		return (-1);
	if (ft_atoi(av[4]) <= 0)
		return (-1);
	if (ac == 6)
	{
		if (ft_atoi(av[5]) <= 0)
			return (-1);
	}
	return (0);
}
