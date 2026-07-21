/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rrotate.c                               :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * OPERATIONS_RROTATE.C - Operações "rra", "rrb" e "rrr"
 * ============================================================================
 * rra: gira a pilha A para baixo (o último elemento vira o novo topo) —
 *      é o INVERSO de "ra".
 * rrb: gira a pilha B para baixo — inverso de "rb".
 * rrr: faz rra e rrb ao mesmo tempo, contando como UMA única operação —
 *      inverso de "rr".
 * A rotação em si está em list_rotate_down (rotate_utils.c); aqui só
 * cuidamos da contabilidade e impressão, seguindo o mesmo padrão dos
 * outros arquivos de operations_*.c.
 * ============================================================================
 */

#include "push_swap.h"

/*
 * op_rra ("reverse rotate a"): gira A para baixo. Sem efeito se A tiver
 * menos de 2 elementos.
 */
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

/*
 * op_rrb ("reverse rotate b"): gira B para baixo. Sem efeito se B tiver
 * menos de 2 elementos.
 */
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

/*
 * op_rrr: gira A e B para baixo simultaneamente, contando como UMA única
 * operação (o "combo" mais barato quando ambas as pilhas precisam girar
 * para baixo ao mesmo tempo).
 */
void	op_rrr(t_ps *ps, int print)
{
	list_rotate_down(&ps->a);
	list_rotate_down(&ps->b);
	ps->op_rrr++;
	ps->total_ops++;
	if (print)
		ft_putstr_fd("rrr\n", 1);
}
