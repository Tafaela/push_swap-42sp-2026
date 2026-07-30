/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static int	has_duplicate_b(t_stack *stack, int val)
{
	while (stack)
	{
		if (stack->value == val)
			return (1);
		stack = stack->next;
	}
	return (0);
}

static int	append_node_b(t_stack **head, t_stack **tail, int val)
{
	t_stack	*node;

	if (has_duplicate_b(*head, val))
	{
		free_stack_b(head);
		return (0);
	}
	node = new_node_b(val);
	if (!node)
	{
		free_stack_b(head);
		return (0);
	}
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
	return (1);
}

int	parse_args_b(t_ps *ps, int argc, char **argv)
{
	int		i;
	int		val;
	t_stack	*head;
	t_stack	*tail;

	head = NULL;
	tail = NULL;
	i = 1;
	while (i < argc)
	{
		if (!ft_atoi_safe_b(argv[i], &val))
		{
			free_stack_b(&head);
			return (0);
		}
		if (!append_node_b(&head, &tail, val))
			return (0);
		i++;
	}
	ps->a = head;
	return (1);
}

int	is_sorted_b(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}
