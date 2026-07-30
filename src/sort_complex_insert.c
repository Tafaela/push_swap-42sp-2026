/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex_insert.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:33:03 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:33:04 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_pos_to_insert_a(t_ps *ps, int b_idx)
{
	t_stack	*tmp;
	int		best_idx;
	int		best_pos;
	int		pos;

	tmp = ps->a;
	best_idx = -1;
	best_pos = 0;
	pos = 0;
	while (tmp)
	{
		if (tmp->index > b_idx)
		{
			if (best_idx == -1 || tmp->index < best_idx)
			{
				best_idx = tmp->index;
				best_pos = pos;
			}
		}
		pos++;
		tmp = tmp->next;
	}
	if (best_idx == -1)
		return (find_min_pos(ps->a));
	return (best_pos);
}

void	push_back_to_a(t_ps *ps)
{
	int	pos;

	while (ps->b)
	{
		pos = find_pos_to_insert_a(ps, ps->b->index);
		rotate_to_top_a(ps, pos);
		op_pa(ps, 1);
	}
	rotate_to_top_a(ps, find_min_pos(ps->a));
}
