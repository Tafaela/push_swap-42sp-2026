/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:31:38 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:31:39 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min_index(t_stack *stack)
{
	int	min;

	if (!stack)
		return (-1);
	min = stack->index;
	while (stack)
	{
		if (stack->index < min)
			min = stack->index;
		stack = stack->next;
	}
	return (min);
}

int	find_max_index(t_stack *stack)
{
	int	max;

	if (!stack)
		return (-1);
	max = stack->index;
	while (stack)
	{
		if (stack->index > max)
			max = stack->index;
		stack = stack->next;
	}
	return (max);
}

int	find_min_pos(t_stack *stack)
{
	int		min_idx;
	int		pos;

	min_idx = find_min_index(stack);
	pos = 0;
	while (stack)
	{
		if (stack->index == min_idx)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (0);
}

int	find_max_pos(t_stack *stack)
{
	int		max_idx;
	int		pos;

	max_idx = find_max_index(stack);
	pos = 0;
	while (stack)
	{
		if (stack->index == max_idx)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (0);
}
