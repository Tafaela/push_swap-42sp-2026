/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:31:45 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:31:46 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	turk_sort(t_ps *ps)
{
	int	best_a;
	int	best_b;

	op_pb(ps, 1);
	if (ps->size_a > 1)
		op_pb(ps, 1);
	while (ps->size_a > 3)
	{
		best_a = 0;
		best_b = 0;
		find_cheapest(ps, &best_a, &best_b);
		move_both_to_top(ps, best_a, best_b);
		op_pb(ps, 1);
	}
	sort_simple(ps);
	push_back_to_a(ps);
}

void	sort_complex(t_ps *ps)
{
	if (ps->size_a <= 3)
	{
		sort_simple(ps);
		return ;
	}
	if (ps->size_a <= 700)
		turk_sort(ps);
	else
		radix_sort(ps);
}
