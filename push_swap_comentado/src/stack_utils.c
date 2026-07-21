/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * STACK_UTILS.C - Operações básicas de baixo nível sobre a lista encadeada
 * ============================================================================
 * Este arquivo contém as funções "de infraestrutura" que todo o resto do
 * projeto usa por baixo dos panos para manipular pilhas: criar nó, colocar
 * no topo, tirar do topo, contar tamanho e liberar tudo da memória.
 * Nenhuma dessas funções sabe nada sobre "ordenar" — elas só manipulam a
 * estrutura de dados em si (a lista encadeada).
 * ============================================================================
 */

#include "push_swap.h"

/*
 * new_node: aloca (malloc) um novo nó t_stack na memória dinâmica (heap) e
 * inicializa seus campos:
 *   value -> o valor recebido por parâmetro.
 *   index -> começa em 0 (será calculado depois, em parse.c, por
 *            assign_indices, com base no valor comparado aos outros).
 *   next  -> começa em NULL (ainda não está ligado a nenhuma pilha).
 * Se o malloc falhar (memória insuficiente), retorna NULL — e quem chamou
 * essa função é responsável por tratar esse erro (ver append_node em
 * parse.c).
 */
t_stack	*new_node(int value)
{
	t_stack	*node;

	node = (t_stack *)malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->value = value;
	node->index = 0;
	node->next = NULL;
	return (node);
}

/*
 * push_node: insere "node" no TOPO da pilha apontada por *stack (operação
 * clássica de pilha: LIFO — Last In, First Out). O novo nó passa a apontar
 * para o antigo topo, e o ponteiro da pilha passa a apontar para o novo
 * nó. Isso é O(1) (tempo constante), pois não precisamos percorrer a
 * lista.
 *
 * stack é um "ponteiro para ponteiro" (t_stack **) porque precisamos
 * MODIFICAR o próprio ponteiro que representa "o topo da pilha" (por
 * exemplo, ps->a) — se recebêssemos só t_stack *stack, qualquer alteração
 * feita dentro da função seria perdida ao retornar (C passa parâmetros por
 * valor).
 */
void	push_node(t_stack **stack, t_stack *node)
{
	if (!stack || !node)
		return ;
	node->next = *stack;
	*stack = node;
}

/*
 * pop_node: remove e retorna o nó do TOPO da pilha apontada por *stack.
 * O novo topo passa a ser o antigo "segundo" elemento (*stack)->next.
 * O nó removido tem seu campo "next" limpo (setado para NULL) antes de
 * ser devolvido, para que ele não continue "ligado" à pilha antiga por
 * engano (evita bugs se esse nó for reaproveitado em outro lugar).
 * Se a pilha estiver vazia (ou o ponteiro for inválido), retorna NULL.
 */
t_stack	*pop_node(t_stack **stack)
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
 * stack_size: percorre a lista inteira do início ao fim, contando quantos
 * nós existem. Usada, por exemplo, para manter ps->size_a e ps->size_b
 * sempre atualizados depois de cada push/pop.
 */
int	stack_size(t_stack *stack)
{
	int	size;

	size = 0;
	while (stack)
	{
		size++;
		stack = stack->next;
	}
	return (size);
}

/*
 * free_stack: libera (free) TODOS os nós da pilha, um por um, começando
 * pelo topo. Antes de dar free em cada nó, guardamos o ponteiro para o
 * PRÓXIMO nó em "tmp" — senão, depois de liberar o nó atual, não teríamos
 * mais como saber qual era o próximo (acessar memória já liberada é
 * comportamento indefinido / bug grave em C).
 * Ao final, *stack fica NULL, indicando que a pilha está vazia.
 */
void	free_stack(t_stack **stack)
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
