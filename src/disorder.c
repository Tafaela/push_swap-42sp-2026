/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:39:33 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:39:34 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

double	compute_disorder(t_stack *stack, int size)
{
	t_stack	*cur;
	t_stack	*cmp;
	long	mistakes;
	long	total_pairs;

	if (!stack || size <= 1)
		return (0.0);
	mistakes = 0;
	total_pairs = 0;
	cur = stack;
	while (cur)
	{
		cmp = cur->next;
		while (cmp)
		{
			total_pairs++;
			if (cur->value > cmp->value)
				mistakes++;
			cmp = cmp->next;
		}
		cur = cur->next;
	}
	if (total_pairs == 0)
		return (0.0);
	return ((double)mistakes / (double)total_pairs);
}
