/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:20:43 by yhajbi            #+#    #+#             */
/*   Updated: 2025/07/15 15:32:21 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// static int	check_args(int ac, char **av);
static int	has_alpha(char *s);

int	main(int ac, char **av)
{
	t_data	data;

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
		gc_mutex_destroy_all();
		gc_free_all();
		return (printf("Philo: failure error\n"), 1);
	}
	gc_mutex_destroy_all();
	gc_free_all();
	return (0);
}

// static int	check_args(int ac, char **av)
// {
// 	if (ft_atoi(av[1]) <= 0 || has_alpha(av[1]) != 0)
// 		return (-1);
// 	if (ft_atoi(av[2]) <= 0 || has_alpha(av[2]) != 0)
// 		return (-1);
// 	if (ft_atoi(av[3]) <= 0 || has_alpha(av[3]) != 0)
// 		return (-1);
// 	if (ft_atoi(av[4]) <= 0 || has_alpha(av[4]) != 0)
// 		return (-1);
// 	if (ac == 6)
// 	{
// 		if (ft_atoi(av[5]) <= 0 || has_alpha(av[5]) != 0)
// 			return (-1);
// 	}
// 	return (0);
// }

// static int	has_alpha(char *s)
// {
// 	int	i;
// 	int	found_n;

// 	i = 0;
// 	found_n = 0;
// 	while (s[i])
// 	{
// 		if ((s[i] >= '0' && s[i] <= '9') && (s[i + 1] == ' ' || s[i + 1] == '\0'))
// 			found_n++;
// 		if ((s[i] < '0' || s[i] > '9')
// 			&& (s[i] != '+' && s[i] != '-' && s[i] != ' '))
// 			return (-1);
// 		i++;
// 	}
// 	if (found_n > 1)
// 		return (-1);
// 	return (0);
// }
