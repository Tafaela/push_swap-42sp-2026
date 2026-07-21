/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rotate.c                                :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * OPERATIONS_ROTATE.C - Operações "ra", "rb" e "rr"
 * ============================================================================
 * ra: gira a pilha A para cima (o topo vai para o final da pilha).
 * rb: gira a pilha B para cima.
 * rr: faz ra e rb ao mesmo tempo, contando como UMA única operação.
 * A rotação em si (manipulação de ponteiros) está implementada em
 * list_rotate_up (rotate_utils.c) — aqui só cuidamos da contabilidade e
 * da impressão.
 * ============================================================================
 */

#include "push_swap.h"

/*
 * op_ra ("rotate a"): gira A para cima. Se A tiver menos de 2 elementos,
 * não há nada a girar (não faz sentido, e list_rotate_up também protegeria
 * contra isso, mas a checagem aqui evita incrementar contadores à toa).
 */
void	op_ra(t_ps *ps, int print)
{
	if (!ps->a || !ps->a->next)
		return ;
	list_rotate_up(&ps->a);
	ps->op_ra++;
	ps->total_ops++;
	if (print)
		ft_putstr_fd("ra\n", 1);
}

/*
 * op_rb ("rotate b"): gira B para cima. Mesma lógica de op_ra, mas para
 * a pilha B.
 */
void	op_rb(t_ps *ps, int print)
{
	if (!ps->b || !ps->b->next)
		return ;
	list_rotate_up(&ps->b);
	ps->op_rb++;
	ps->total_ops++;
	if (print)
		ft_putstr_fd("rb\n", 1);
}

/*
 * op_rr: gira A e B para cima simultaneamente, contando como UMA única
 * operação (assim como "ss", é mais "barato" que fazer ra + rb
 * separadamente quando os dois giros são necessários ao mesmo tempo).
 * Assim como em op_ss, não há checagem prévia de tamanho aqui porque
 * list_rotate_up já lida com pilhas de 0 ou 1 elemento sem quebrar nada.
 */
void	op_rr(t_ps *ps, int print)
{
	list_rotate_up(&ps->a);
	list_rotate_up(&ps->b);
	ps->op_rr++;
	ps->total_ops++;
	if (print)
		ft_putstr_fd("rr\n", 1);
}
