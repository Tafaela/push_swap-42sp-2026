/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:30:42 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:30:43 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_flag(char *arg)
{
	if (ft_strcmp(arg, "--simple") == 0)
		return (1);
	if (ft_strcmp(arg, "--medium") == 0)
		return (1);
	if (ft_strcmp(arg, "--complex") == 0)
		return (1);
	if (ft_strcmp(arg, "--adaptive") == 0)
		return (1);
	if (ft_strcmp(arg, "--bench") == 0)
		return (1);
	return (0);
}

static void	sorted_complexity(char *strategy, char **complexity)
{
	if (ft_strcmp(strategy, "Medium") == 0)
		*complexity = "O(n*sqrt(n))";
	else if (ft_strcmp(strategy, "Complex") == 0)
		*complexity = "O(n log n)";
}

static void	dispatch_sort(t_ps *ps, char *strategy, char **name,
			char **complexity)
{
	if (ft_strcmp(strategy, "Simple") == 0)
		sort_simple(ps);
	else if (ft_strcmp(strategy, "Medium") == 0)
	{
		*complexity = "O(n*sqrt(n))";
		sort_medium(ps);
	}
	else if (ft_strcmp(strategy, "Complex") == 0)
	{
		*complexity = "O(n log n)";
		sort_complex(ps);
	}
	else
		sort_adaptive(ps, name, complexity);
}

void	run_sort(t_ps *ps, char *strategy, int bench)
{
	double	disorder;
	char	*name;
	char	*complexity;

	disorder = compute_disorder(ps->a, ps->size_a);
	name = strategy;
	complexity = "O(n^2)";
	if (is_sorted(ps->a))
		sorted_complexity(strategy, &complexity);
	else
		dispatch_sort(ps, strategy, &name, &complexity);
	if (bench)
		print_benchmark(ps, disorder, name, complexity);
}
