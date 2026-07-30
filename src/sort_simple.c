/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:30:59 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:31:00 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	selection_sort_loop(t_ps *ps)
{
	int	i;
	int	total;
	int	min_pos;

	total = ps->size_a;
	i = 0;
	while (i < total - 1)
	{
		min_pos = find_min_pos(ps->a);
		rotate_to_top_a(ps, min_pos);
		op_pb(ps, 1);
		i++;
	}
	while (ps->b)
		op_pa(ps, 1);
}

void	sort_simple(t_ps *ps)
{
	if (ps->size_a <= 1)
		return ;
	if (ps->size_a == 2)
	{
		if (ps->a->index > ps->a->next->index)
			op_sa(ps, 1);
		return ;
	}
	if (ps->size_a == 3)
	{
		sort_three(ps);
		return ;
	}
	selection_sort_loop(ps);
}
