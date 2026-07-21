/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_adaptive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:38:26 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:38:27 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_adaptive(t_ps *ps, char **name, char **complexity)
{
	double	disorder;

	disorder = compute_disorder(ps->a, ps->size_a);
	*name = "Adaptive";
	if (ps->size_a <= 5)
	{
		*complexity = "O(n^2)";
		sort_simple(ps);
		return ;
	}
	if (disorder < 0.2)
	{
		*complexity = "O(n^2)";
		sort_simple(ps);
		return ;
	}
	if (disorder < 0.5)
	{
		*complexity = "O(n*sqrt(n))";
		sort_medium(ps);
		return ;
	}
	*complexity = "O(n log n)";
	sort_complex(ps);
}
