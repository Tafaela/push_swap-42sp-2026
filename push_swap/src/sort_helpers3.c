/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:31:26 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:31:27 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_best_below(t_ps *ps, int idx, int *pos_out)
{
	t_stack	*tmp;
	int		best_idx;
	int		pos;

	tmp = ps->b;
	best_idx = -1;
	pos = 0;
	while (tmp)
	{
		if (tmp->index < idx && (best_idx == -1 || tmp->index > best_idx))
		{
			best_idx = tmp->index;
			*pos_out = pos;
		}
		pos++;
		tmp = tmp->next;
	}
	return (best_idx != -1);
}

int	find_target_pos_b(t_ps *ps, int idx)
{
	int	pos;

	pos = 0;
	if (find_best_below(ps, idx, &pos))
		return (pos);
	return (find_max_pos(ps->b));
}
