/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:39:40 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:39:41 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_disorder(double disorder)
{
	int	whole;
	int	frac;

	whole = (int)(disorder * 100);
	frac = (int)(disorder * 10000) % 100;
	if (frac < 0)
		frac = -frac;
	ft_putstr_fd("[bench] disorder: ", 2);
	ft_putnbr_fd(whole, 2);
	ft_putstr_fd(".", 2);
	if (frac < 10)
		ft_putstr_fd("0", 2);
	ft_putnbr_fd(frac, 2);
	ft_putstr_fd("%\n", 2);
}

static void	print_op_counts(t_ps *ps)
{
	ft_putstr_fd("[bench] sa: ", 2);
	ft_putnbr_fd(ps->op_sa, 2);
	ft_putstr_fd(" sb: ", 2);
	ft_putnbr_fd(ps->op_sb, 2);
	ft_putstr_fd(" ss: ", 2);
	ft_putnbr_fd(ps->op_ss, 2);
	ft_putstr_fd(" pa: ", 2);
	ft_putnbr_fd(ps->op_pa, 2);
	ft_putstr_fd(" pb: ", 2);
	ft_putnbr_fd(ps->op_pb, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("[bench] ra: ", 2);
	ft_putnbr_fd(ps->op_ra, 2);
	ft_putstr_fd(" rb: ", 2);
	ft_putnbr_fd(ps->op_rb, 2);
	ft_putstr_fd(" rr: ", 2);
	ft_putnbr_fd(ps->op_rr, 2);
	ft_putstr_fd(" rra: ", 2);
	ft_putnbr_fd(ps->op_rra, 2);
	ft_putstr_fd(" rrb: ", 2);
	ft_putnbr_fd(ps->op_rrb, 2);
	ft_putstr_fd(" rrr: ", 2);
	ft_putnbr_fd(ps->op_rrr, 2);
	ft_putstr_fd("\n", 2);
}

void	print_benchmark(t_ps *ps, double disorder, char *strategy,
			char *complexity)
{
	print_disorder(disorder);
	ft_putstr_fd("[bench] strategy: ", 2);
	ft_putstr_fd(strategy, 2);
	ft_putstr_fd(" / ", 2);
	ft_putstr_fd(complexity, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("[bench] total_ops: ", 2);
	ft_putnbr_fd(ps->total_ops, 2);
	ft_putstr_fd("\n", 2);
	print_op_counts(ps);
}
