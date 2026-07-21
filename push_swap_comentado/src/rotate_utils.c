/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_utils.c                                     :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * ROTATE_UTILS.C - Rotação "crua" da lista encadeada (sem contar/imprimir)
 * ============================================================================
 * Estas duas funções fazem a manipulação PURA de ponteiros para girar a
 * lista. Elas não sabem nada sobre "ps" (a struct de estado), não
 * incrementam contadores e não imprimem nada — são usadas POR DENTRO das
 * funções op_ra/op_rb/op_rr/op_rra/op_rrb/op_rrr (nos arquivos
 * operations_rotate.c e operations_rrotate.c), que são as responsáveis
 * por contar e imprimir a operação.
 *
 * Separar a lógica assim (rotação pura aqui, contabilidade lá) segue o
 * princípio de responsabilidade única: cada função faz uma coisa só.
 * ============================================================================
 */

#include "push_swap.h"

/*
 * list_rotate_up: implementa a operação "ra"/"rb" — gira a pilha PARA
 * CIMA, ou seja, o primeiro elemento (topo) vai para o FINAL da lista, e
 * o segundo elemento passa a ser o novo topo.
 *
 * Exemplo visual (topo à esquerda): [1, 2, 3, 4] -> depois de rotate_up:
 * [2, 3, 4, 1]
 *
 * Passos:
 *   1. Se a pilha estiver vazia ou tiver só 1 elemento, não há o que
 *      girar (não muda nada).
 *   2. Guarda o antigo topo em "tmp" e avança *stack para o segundo
 *      elemento (que se torna o novo topo).
 *   3. Desconecta "tmp" do resto da lista (tmp->next = NULL), já que ele
 *      vai virar o último elemento.
 *   4. Percorre a lista (a partir do novo topo) até achar o último nó
 *      atual (aquele cujo "next" é NULL).
 *   5. Conecta esse último nó ao antigo topo (tmp), que agora se torna o
 *      novo último elemento da lista.
 */
void	list_rotate_up(t_stack **stack)
{
	t_stack	*tmp;
	t_stack	*last;

	if (!*stack || !(*stack)->next)
		return ;
	tmp = *stack;
	*stack = (*stack)->next;
	tmp->next = NULL;
	last = *stack;
	while (last->next)
		last = last->next;
	last->next = tmp;
}

/*
 * list_rotate_down: implementa a operação "rra"/"rrb" — gira a pilha PARA
 * BAIXO (o inverso de list_rotate_up): o ÚLTIMO elemento da lista vira o
 * novo topo.
 *
 * Exemplo visual: [1, 2, 3, 4] -> depois de rotate_down: [4, 1, 2, 3]
 *
 * Passos:
 *   1. Se a pilha estiver vazia ou tiver só 1 elemento, não faz nada.
 *   2. Percorre a lista até "tmp" chegar no último nó, guardando em
 *      "prev" o penúltimo nó (o nó anterior a "tmp") no caminho.
 *   3. Desconecta o último nó do penúltimo (prev->next = NULL) — agora o
 *      penúltimo nó é o novo "fim" da lista.
 *   4. Faz o antigo último nó (tmp) apontar para o antigo topo (*stack),
 *      e atualiza *stack para que tmp seja o novo topo.
 */
void	list_rotate_down(t_stack **stack)
{
	t_stack	*tmp;
	t_stack	*prev;

	if (!*stack || !(*stack)->next)
		return ;
	tmp = *stack;
	prev = NULL;
	while (tmp->next)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = NULL;
	tmp->next = *stack;
	*stack = tmp;
}
