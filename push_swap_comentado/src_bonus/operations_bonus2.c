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

/*
 * ============================================================================
 * OPERATIONS_BONUS2.C - Executa "ra", "rb", "rr", "rra", "rrb", "rrr" no
 * checker
 * ============================================================================
 * Reimplementação das rotações diretamente sobre a lista (mesma lógica
 * de list_rotate_up/list_rotate_down em rotate_utils.c do push_swap
 * principal), mas duplicada aqui como funções "static" porque o checker
 * é um binário independente.
 * ============================================================================
 */

/*
 * do_ra: gira a pilha A para cima — o topo vai para o final da lista.
 * Sem efeito se A tiver menos de 2 elementos.
 * (Mesma lógica de list_rotate_up, ver comentários detalhados em
 * src/rotate_utils.c.)
 */
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

/*
 * do_rb: o mesmo que do_ra, mas para a pilha B.
 */
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

/*
 * do_rra: gira a pilha A para baixo — o último elemento vira o novo topo
 * (inverso de do_ra). Sem efeito se A tiver menos de 2 elementos.
 * (Mesma lógica de list_rotate_down, ver src/rotate_utils.c.)
 */
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

/*
 * do_rrb: o mesmo que do_rra, mas para a pilha B.
 */
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

/*
 * exec_op_rot: função de despacho para as 6 operações de rotação.
 * Chamada por exec_op (operations_bonus.c) quando a operação lida não é
 * nenhuma das de swap/push.
 *   - "rr" executa do_ra seguido de do_rb.
 *   - "rrr" executa do_rra seguido de do_rrb.
 * Se "op" não corresponder a NENHUMA operação válida do push_swap,
 * retorna 0 (indicando string desconhecida — o checker deve reportar
 * "Error" nesse caso). Caso contrário, retorna 1.
 */
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
