/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:31:05 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:31:06 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	cmp_pattern(int a, int b, int c)
{
	if (a < b && b < c)
		return (0);
	if (a > b && b < c && a < c)
		return (1);
	if (a < b && b > c && a < c)
		return (2);
	if (a > b && b > c)
		return (3);
	if (a < b && b > c && a > c)
		return (4);
	return (5);
}

static void	apply_case(t_ps *ps, int code)
{
	if (code == 1)
		op_sa(ps, 1);
	else if (code == 2)
	{
		op_ra(ps, 1);
		op_sa(ps, 1);
		op_rra(ps, 1);
	}
	else if (code == 3)
	{
		op_sa(ps, 1);
		op_rra(ps, 1);
	}
	else if (code == 4)
		op_rra(ps, 1);
	else if (code == 5)
		op_ra(ps, 1);
}

void	sort_three(t_ps *ps)
{
	int	a;
	int	b;
	int	c;

	if (!ps->a || !ps->a->next)
		return ;
	a = ps->a->index;
	b = ps->a->next->index;
	if (!ps->a->next->next)
	{
		if (a > b)
			op_sa(ps, 1);
		return ;
	}
	c = ps->a->next->next->index;
	apply_case(ps, cmp_pattern(a, b, c));
}
