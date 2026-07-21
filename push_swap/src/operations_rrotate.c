/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rrotate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:38:53 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:38:54 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_rra(t_ps *ps, int print)
{
	if (!ps->a || !ps->a->next)
		return ;
	list_rotate_down(&ps->a);
	ps->op_rra++;
	ps->total_ops++;
	if (print)
		ft_putstr_fd("rra\n", 1);
}

void	op_rrb(t_ps *ps, int print)
{
	if (!ps->b || !ps->b->next)
		return ;
	list_rotate_down(&ps->b);
	ps->op_rrb++;
	ps->total_ops++;
	if (print)
		ft_putstr_fd("rrb\n", 1);
}

void	op_rrr(t_ps *ps, int print)
{
	list_rotate_down(&ps->a);
	list_rotate_down(&ps->b);
	ps->op_rrr++;
	ps->total_ops++;
	if (print)
		ft_putstr_fd("rrr\n", 1);
}
