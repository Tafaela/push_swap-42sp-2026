/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_push.c                                  :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * OPERATIONS_PUSH.C - Operações "pa" e "pb"
 * ============================================================================
 * pa: move o elemento do topo da pilha B para o topo da pilha A.
 * pb: move o elemento do topo da pilha A para o topo da pilha B.
 * Estas são as ÚNICAS operações que transferem elementos ENTRE as duas
 * pilhas (todas as outras operações — swap, rotate — atuam dentro de uma
 * única pilha).
 *
 * Todas as funções op_* deste projeto seguem o mesmo "esqueleto":
 *   1. Checa se a operação é possível (pilha de origem não vazia).
 *   2. Executa a manipulação de ponteiros.
 *   3. Atualiza os contadores de tamanho e de operações em "ps".
 *   4. Se "print" for verdadeiro, imprime o nome da operação (isso é
 *      usado para desligar a impressão durante o benchmark, quando só
 *      queremos contar as operações sem poluir a tela).
 * ============================================================================
 */

#include "push_swap.h"

/*
 * op_pa ("push a"): retira o nó do topo de B (pop_node) e o insere no
 * topo de A (push_node). Se B estiver vazia, não há nada para mover —
 * a função simplesmente retorna sem fazer nada (nem imprime, nem conta).
 * Atualiza size_a (+1) e size_b (-1), incrementa o contador op_pa e o
 * contador geral total_ops.
 */
void	op_pa(t_ps *ps, int print)
{
	t_stack	*node;

	if (!ps->b)
		return ;
	node = pop_node(&ps->b);
	push_node(&ps->a, node);
	ps->size_a++;
	ps->size_b--;
	ps->op_pa++;
	ps->total_ops++;
	if (print)
		ft_putstr_fd("pa\n", 1);
}

/*
 * op_pb ("push b"): o inverso de op_pa — retira o topo de A e insere no
 * topo de B. Se A estiver vazia, não faz nada.
 * Atualiza size_a (-1) e size_b (+1), incrementa op_pb e total_ops.
 */
void	op_pb(t_ps *ps, int print)
{
	t_stack	*node;

	if (!ps->a)
		return ;
	node = pop_node(&ps->a);
	push_node(&ps->b, node);
	ps->size_a--;
	ps->size_b++;
	ps->op_pb++;
	ps->total_ops++;
	if (print)
		ft_putstr_fd("pb\n", 1);
}
