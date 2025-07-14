/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <yhajbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:45:35 by yhajbi            #+#    #+#             */
/*   Updated: 2025/07/07 11:45:50 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static t_gc_node	**get_gc_head(void)
{
	static t_gc_node	*head = NULL;

	return (&head);
}

void	*gc_malloc(size_t size)
{
	t_gc_node	**head;
	void		*ptr;
	t_gc_node	*node;

	head = get_gc_head();
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = malloc(sizeof(t_gc_node));
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->ptr = ptr;
	node->next = *head;
	*head = node;
	return (ptr);
}

void	gc_free_all(void)
{
	t_gc_node	**head;
	t_gc_node	*current;
	t_gc_node	*next;

	head = get_gc_head();
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	*head = NULL;
}
