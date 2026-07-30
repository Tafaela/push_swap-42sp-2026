/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_bonus2.c                                :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void	do_ra(t_ps *ps)
{
	t_stack	*tmp;
	t_stack	*last;

	if (!ps->a || !ps->a->next)
		return ;
	tmp = ps->a;
	ps->a = ps->a->next;
	tmp->next = NULL;
	last = ps->a;
	while (last->next)
		last = last->next;
	last->next = tmp;
}

static void	do_rb(t_ps *ps)
{
	t_stack	*tmp;
	t_stack	*last;

	if (!ps->b || !ps->b->next)
		return ;
	tmp = ps->b;
	ps->b = ps->b->next;
	tmp->next = NULL;
	last = ps->b;
	while (last->next)
		last = last->next;
	last->next = tmp;
}

static void	do_rra(t_ps *ps)
{
	t_stack	*tmp;
	t_stack	*prev;

	if (!ps->a || !ps->a->next)
		return ;
	tmp = ps->a;
	prev = NULL;
	while (tmp->next)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = NULL;
	tmp->next = ps->a;
	ps->a = tmp;
}

static void	do_rrb(t_ps *ps)
{
	t_stack	*tmp;
	t_stack	*prev;

	if (!ps->b || !ps->b->next)
		return ;
	tmp = ps->b;
	prev = NULL;
	while (tmp->next)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = NULL;
	tmp->next = ps->b;
	ps->b = tmp;
}

int	exec_op_rot(t_ps *ps, char *op)
{
	if (ft_strcmp_b(op, "ra") == 0)
		do_ra(ps);
	else if (ft_strcmp_b(op, "rb") == 0)
		do_rb(ps);
	else if (ft_strcmp_b(op, "rr") == 0)
	{
		do_ra(ps);
		do_rb(ps);
	}
	else if (ft_strcmp_b(op, "rra") == 0)
		do_rra(ps);
	else if (ft_strcmp_b(op, "rrb") == 0)
		do_rrb(ps);
	else if (ft_strcmp_b(op, "rrr") == 0)
	{
		do_rra(ps);
		do_rrb(ps);
	}
	else
		return (0);
	return (1);
}
