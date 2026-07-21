/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex_move.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:31:57 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:31:58 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate_together(t_ps *ps, int *ca, int *cb, int same_up)
{
	while (*ca > 0 && *cb > 0)
	{
		if (same_up)
			op_rr(ps, 1);
		else
			op_rrr(ps, 1);
		(*ca)--;
		(*cb)--;
	}
}

static void	rotate_leftover_a(t_ps *ps, int ca, int ra_up)
{
	while (ca-- > 0)
	{
		if (ra_up)
			op_ra(ps, 1);
		else
			op_rra(ps, 1);
	}
}

static void	rotate_leftover_b(t_ps *ps, int cb, int rb_up)
{
	while (cb-- > 0)
	{
		if (rb_up)
			op_rb(ps, 1);
		else
			op_rrb(ps, 1);
	}
}

void	move_both_to_top(t_ps *ps, int a_pos, int b_pos)
{
	int	ra_up;
	int	rb_up;
	int	ca;
	int	cb;

	ra_up = (a_pos <= ps->size_a / 2);
	rb_up = (b_pos <= ps->size_b / 2);
	if (ra_up)
		ca = a_pos;
	else
		ca = ps->size_a - a_pos;
	if (rb_up)
		cb = b_pos;
	else
		cb = ps->size_b - b_pos;
	if (ra_up == rb_up)
		rotate_together(ps, &ca, &cb, ra_up);
	rotate_leftover_a(ps, ca, ra_up);
	rotate_leftover_b(ps, cb, rb_up);
}
