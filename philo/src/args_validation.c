/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:31:36 by yhajbi            #+#    #+#             */
/*   Updated: 2025/07/15 15:35:37 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	is_valid_char(char c, char prev_c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c == ' ')
		return (1);
	if ((c == '+' || c == '-') && (prev_c == ' ' || prev_c == '\0'))
		return (1);
	return (0);
}

static int	has_single_number(char *s)
{
	int	i;
	int	in_number;
	int	number_count;

	i = 0;
	in_number = 0;
	number_count = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			if (!in_number)
			{
				in_number = 1;
				number_count++;
			}
		}
		else if (s[i] == ' ')
			in_number = 0;
		else if (s[i] == '+' || s[i] == '-')
			in_number = 0;
		i++;
	}
	return (number_count == 1);
}

static int	has_valid_end(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	i--;
	while (i >= 0 && s[i] == ' ')
		i--;
	if (i >= 0 && (s[i] == '+' || s[i] == '-'))
		return (0);
	return (1);
}

static int	is_valid_arg(char *s)
{
	int	i;
	char	prev_c;

	if (!s || *s == '\0')
		return (-1);
	i = 0;
	prev_c = '\0';
	while (s[i])
	{
		if (!is_valid_char(s[i], prev_c))
			return (-1);
		prev_c = s[i];
		i++;
	}
	if (!has_single_number(s) || !has_valid_end(s))
		return (-1);
	return (0);
}

int	check_args(int ac, char **av)
{
	if (ft_atoi(av[1]) <= 0 || is_valid_arg(av[1]) != 0)
		return (-1);
	if (ft_atoi(av[2]) <= 0 || is_valid_arg(av[2]) != 0)
		return (-1);
	if (ft_atoi(av[3]) <= 0 || is_valid_arg(av[3]) != 0)
		return (-1);
	if (ft_atoi(av[4]) <= 0 || is_valid_arg(av[4]) != 0)
		return (-1);
	if (ac == 6)
	{
		if (ft_atoi(av[5]) <= 0 || is_valid_arg(av[5]) != 0)
			return (-1);
	}
	return (0);
}