/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	assign_indices(t_ps *ps)
{
	t_stack	*cur;
	t_stack	*cmp;
	int		idx;

	cur = ps->a;
	while (cur)
	{
		idx = 0;
		cmp = ps->a;
		while (cmp)
		{
			if (cmp->value < cur->value)
				idx++;
			cmp = cmp->next;
		}
		cur->index = idx;
		cur = cur->next;
	}
}

int	parse_args(t_ps *ps, int argc, char **argv, int start)
{
	int		i;
	t_stack	*head;
	t_stack	*tail;

	head = NULL;
	tail = NULL;
	i = start;
	while (i < argc)
	{
		if (!parse_one_arg(argv[i], &head, &tail))
			return (0);
		i++;
	}
	ps->a = head;
	ps->size_a = stack_size(ps->a);
	assign_indices(ps);
	return (1);
}

int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}
