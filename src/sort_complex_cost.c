/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex_cost.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:38:06 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:38:08 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_target_in_b(t_ps *ps, int a_idx)
{
	t_stack	*tmp;
	int		best_idx;
	int		best_pos;
	int		pos;

	tmp = ps->b;
	best_idx = -1;
	best_pos = 0;
	pos = 0;
	while (tmp)
	{
		if (tmp->index < a_idx)
		{
			if (best_idx == -1 || tmp->index > best_idx)
			{
				best_idx = tmp->index;
				best_pos = pos;
			}
		}
		pos++;
		tmp = tmp->next;
	}
	if (best_idx == -1)
		return (find_max_pos(ps->b));
	return (best_pos);
}

static int	dist_to_top(int pos, int size)
{
	if (pos <= size / 2)
		return (pos);
	return (size - pos);
}

int	calc_cost(t_ps *ps, int a_pos, int b_pos)
{
	int	ca;
	int	cb;
	int	a_up;
	int	b_up;

	ca = dist_to_top(a_pos, ps->size_a);
	cb = dist_to_top(b_pos, ps->size_b);
	a_up = (a_pos <= ps->size_a / 2);
	b_up = (b_pos <= ps->size_b / 2);
	if ((a_up && b_up) || (!a_up && !b_up))
	{
		if (ca > cb)
			return (ca);
		return (cb);
	}
	return (ca + cb);
}

void	find_cheapest(t_ps *ps, int *best_a_pos, int *best_b_pos)
{
	t_stack	*cur;
	int		a_pos;
	int		b_pos;
	int		cost;
	int		min_cost;

	min_cost = -1;
	a_pos = 0;
	cur = ps->a;
	while (cur)
	{
		b_pos = find_target_in_b(ps, cur->index);
		cost = calc_cost(ps, a_pos, b_pos);
		if (min_cost == -1 || cost < min_cost)
		{
			min_cost = cost;
			*best_a_pos = a_pos;
			*best_b_pos = b_pos;
		}
		a_pos++;
		cur = cur->next;
	}
}
