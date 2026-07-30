/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:31:11 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:31:12 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_all_chunks(t_ps *ps, int chunk_size)
{
	int	i;
	int	min;
	int	max;
	int	max_idx;

	max_idx = ps->size_a - 1;
	i = 0;
	while (i <= max_idx)
	{
		min = i;
		max = i + chunk_size - 1;
		if (max > max_idx)
			max = max_idx;
		push_chunk(ps, min, max);
		i += chunk_size;
	}
}

static void	extract_all(t_ps *ps)
{
	while (ps->b)
	{
		rotate_to_top_b(ps, find_max_pos(ps->b));
		op_pa(ps, 1);
	}
}

void	sort_medium(t_ps *ps)
{
	if (ps->size_a <= 3)
	{
		sort_simple(ps);
		return ;
	}
	push_all_chunks(ps, ft_sqrt_ceil(ps->size_a));
	extract_all(ps);
}
