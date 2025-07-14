/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:17:42 by yhajbi            #+#    #+#             */
/*   Updated: 2025/07/14 14:10:44 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static t_gc_mutex	**get_mutex_gc_head(void)
{
	static t_gc_mutex	*head;

	head = NULL;
	return (&head);
}

int	gc_mutex_init(pthread_mutex_t **mutex)
{
	t_gc_mutex	**head;
	t_gc_mutex	*node;

	head = get_mutex_gc_head();
	*mutex = gc_malloc(sizeof(pthread_mutex_t));
	if (!*mutex)
		return (-1);
	if (pthread_mutex_init(*mutex, NULL) != 0)
		return (-1);
	node = gc_malloc(sizeof(t_gc_mutex));
	if (!node)
	{
		pthread_mutex_destroy(*mutex);
		return (-1);
	}
	node->ptr = *mutex;
	node->next = *head;
	*head = node;
	return (0);
}

void	gc_mutex_destroy_all(void)
{
	t_gc_mutex	**head;
	t_gc_mutex	*current;
	t_gc_mutex	*next;

	head = get_mutex_gc_head();
	current = *head;
	while (current)
	{
		next = current->next;
		if (current->ptr)
			pthread_mutex_destroy(current->ptr);
		current = next;
	}
	*head = NULL;
}

int	gc_mutex_register(pthread_mutex_t *mutex)
{
	t_gc_mutex	**head;
	t_gc_mutex	*node;

	head = get_mutex_gc_head();
	node = gc_malloc(sizeof(t_gc_mutex));
	if (!node)
		return (-1);
	node->ptr = mutex;
	node->next = *head;
	*head = node;
	return (0);
}
