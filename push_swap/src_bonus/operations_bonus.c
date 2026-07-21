/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_bonus.c                                 :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	do_sa(t_ps *ps)
{
	t_stack	*tmp;

	if (!ps->a || !ps->a->next)
		return ;
	tmp = ps->a->next;
	ps->a->next = tmp->next;
	tmp->next = ps->a;
	ps->a = tmp;
}

void	do_sb(t_ps *ps)
{
	t_stack	*tmp;

	if (!ps->b || !ps->b->next)
		return ;
	tmp = ps->b->next;
	ps->b->next = tmp->next;
	tmp->next = ps->b;
	ps->b = tmp;
}

void	do_pa(t_ps *ps)
{
	t_stack	*node;

	if (!ps->b)
		return ;
	node = pop_node_b(&ps->b);
	push_node_b(&ps->a, node);
}

void	do_pb(t_ps *ps)
{
	t_stack	*node;

	if (!ps->a)
		return ;
	node = pop_node_b(&ps->a);
	push_node_b(&ps->b, node);
}

int	exec_op(t_ps *ps, char *op)
{
	if (ft_strcmp_b(op, "sa") == 0)
		do_sa(ps);
	else if (ft_strcmp_b(op, "sb") == 0)
		do_sb(ps);
	else if (ft_strcmp_b(op, "ss") == 0)
	{
		do_sa(ps);
		do_sb(ps);
	}
	else if (ft_strcmp_b(op, "pa") == 0)
		do_pa(ps);
	else if (ft_strcmp_b(op, "pb") == 0)
		do_pb(ps);
	else if (!exec_op_rot(ps, op))
		return (0);
	return (1);
}
