/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:38:59 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:39:00 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_ra(t_ps *ps, int print)
{
	if (!ps->a || !ps->a->next)
		return ;
	list_rotate_up(&ps->a);
	ps->op_ra++;
	ps->total_ops++;
	if (print)
		ft_putstr_fd("ra\n", 1);
}

void	op_rb(t_ps *ps, int print)
{
	if (!ps->b || !ps->b->next)
		return ;
	list_rotate_up(&ps->b);
	ps->op_rb++;
	ps->total_ops++;
	if (print)
		ft_putstr_fd("rb\n", 1);
}

void	op_rr(t_ps *ps, int print)
{
	list_rotate_up(&ps->a);
	list_rotate_up(&ps->b);
	ps->op_rr++;
	ps->total_ops++;
	if (print)
		ft_putstr_fd("rr\n", 1);
}
