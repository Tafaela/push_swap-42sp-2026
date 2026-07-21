/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:31:32 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:31:33 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_to_top_a(t_ps *ps, int pos)
{
	int	size;

	size = ps->size_a;
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			op_ra(ps, 1);
	}
	else
	{
		pos = size - pos;
		while (pos-- > 0)
			op_rra(ps, 1);
	}
}

void	rotate_to_top_b(t_ps *ps, int pos)
{
	int	size;

	size = ps->size_b;
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			op_rb(ps, 1);
	}
	else
	{
		pos = size - pos;
		while (pos-- > 0)
			op_rrb(ps, 1);
	}
}

int	find_pos_in_b(t_ps *ps, int index)
{
	t_stack	*tmp;
	int		pos;

	tmp = ps->b;
	pos = 0;
	while (tmp)
	{
		if (tmp->index == index)
			return (pos);
		pos++;
		tmp = tmp->next;
	}
	return (-1);
}
