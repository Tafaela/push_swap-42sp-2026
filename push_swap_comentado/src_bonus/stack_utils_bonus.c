/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils_bonus.c                                :+:      :+:    :+:  */
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
 * STACK_UTILS_BONUS.C - Operações básicas sobre a lista encadeada (checker)
 * ============================================================================
 * Versões praticamente idênticas às de stack_utils.c do push_swap
 * principal, mas sem o campo "index" (o checker não precisa dele).
 * ============================================================================
 */

/*
 * new_node_b: aloca um novo nó t_stack, define "value" com o valor
 * recebido e "next" como NULL. Retorna NULL se o malloc falhar.
 */
t_stack	*new_node_b(int value)
{
	t_stack	*node;

	node = (t_stack *)malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->value = value;
	node->next = NULL;
	return (node);
}

/*
 * push_node_b: insere "node" no topo da pilha apontada por *stack (LIFO).
 */
void	push_node_b(t_stack **stack, t_stack *node)
{
	if (!stack || !node)
		return ;
	node->next = *stack;
	*stack = node;
}

/*
 * pop_node_b: remove e retorna o nó do topo da pilha apontada por
 * *stack. Retorna NULL se a pilha estiver vazia.
 */
t_stack	*pop_node_b(t_stack **stack)
{
	t_stack	*node;

	if (!stack || !*stack)
		return (NULL);
	node = *stack;
	*stack = (*stack)->next;
	node->next = NULL;
	return (node);
}

/*
 * free_stack_b: libera todos os nós da pilha, um por um, guardando o
 * próximo nó antes de dar free no atual (para não perder a referência).
 * Ao final, *stack fica NULL.
 */
void	free_stack_b(t_stack **stack)
{
	t_stack	*tmp;

	if (!stack)
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}
