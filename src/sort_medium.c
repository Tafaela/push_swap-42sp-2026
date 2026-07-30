/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:31:19 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:31:20 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_sqrt_ceil(int n)
{
	int	i;

	i = 1;
	while (i * i < n)
		i++;
	return (i);
}

static int	count_in_range(t_stack *stack, int min, int max)
{
	int	count;

	count = 0;
	while (stack)
	{
		if (stack->index >= min && stack->index <= max)
			count++;
		stack = stack->next;
	}
	return (count);
}

static int	top_is_in_range(t_ps *ps, int min, int max)
{
	if (!ps->a)
		return (0);
	return (ps->a->index >= min && ps->a->index <= max);
}

void	push_chunk(t_ps *ps, int min, int max)
{
	int	pushed;
	int	total;
	int	mid;

	total = count_in_range(ps->a, min, max);
	pushed = 0;
	mid = (min + max) / 2;
	while (pushed < total)
	{
		if (top_is_in_range(ps, min, max))
		{
			op_pb(ps, 1);
			pushed++;
			if (ps->b && ps->b->index <= mid)
				op_rb(ps, 1);
		}
		else
			op_ra(ps, 1);
	}
}
