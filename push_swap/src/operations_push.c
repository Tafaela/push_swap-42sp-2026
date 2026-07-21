/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_push.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:39:05 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:39:06 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_pa(t_ps *ps, int print)
{
	t_stack	*node;

	if (!ps->b)
		return ;
	node = pop_node(&ps->b);
	push_node(&ps->a, node);
	ps->size_a++;
	ps->size_b--;
	ps->op_pa++;
	ps->total_ops++;
	if (print)
		ft_putstr_fd("pa\n", 1);
}

void	op_pb(t_ps *ps, int print)
{
	t_stack	*node;

	if (!ps->a)
		return ;
	node = pop_node(&ps->a);
	push_node(&ps->b, node);
	ps->size_a--;
	ps->size_b++;
	ps->op_pb++;
	ps->total_ops++;
	if (print)
		ft_putstr_fd("pb\n", 1);
}
