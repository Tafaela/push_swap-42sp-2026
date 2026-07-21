/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers1.c                                    :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * SORT_HELPERS1.C - Encontrar o menor/maior valor (e sua posição) numa pilha
 * ============================================================================
 * Estas quatro funções são blocos de construção usados por praticamente
 * todos os algoritmos de ordenação: para decidir a próxima operação, é
 * frequente precisar saber "qual é o menor elemento?" ou "em que posição
 * (contando a partir do topo, começando em 0) ele está?".
 *
 * Lembrete: "index" aqui é o índice relativo calculado em parse.c
 * (assign_indices) — não confundir com "pos", que é a POSIÇÃO física do
 * nó dentro da lista (quantos nós de distância do topo).
 * ============================================================================
 */

#include "push_swap.h"

/*
 * find_min_index: percorre a pilha inteira e retorna o MENOR valor de
 * "index" encontrado (não a posição — o valor do índice em si). Se a
 * pilha estiver vazia, retorna -1 como sinalizador de "não existe".
 */
int	find_min_index(t_stack *stack)
{
	int	min;

	if (!stack)
		return (-1);
	min = stack->index;
	while (stack)
	{
		if (stack->index < min)
			min = stack->index;
		stack = stack->next;
	}
	return (min);
}

/*
 * find_max_index: o espelho de find_min_index — retorna o MAIOR valor de
 * "index" encontrado na pilha. Retorna -1 se a pilha estiver vazia.
 */
int	find_max_index(t_stack *stack)
{
	int	max;

	if (!stack)
		return (-1);
	max = stack->index;
	while (stack)
	{
		if (stack->index > max)
			max = stack->index;
		stack = stack->next;
	}
	return (max);
}

/*
 * find_min_pos: primeiro descobre qual é o valor do menor índice
 * (find_min_index), depois percorre a pilha DE NOVO contando a posição
 * (começando em 0 no topo) até encontrar o nó que tem esse índice mínimo,
 * retornando essa posição.
 * É essa posição (contada a partir do topo) que é usada depois por
 * rotate_to_top_a/b para saber quantas rotações são necessárias.
 */
int	find_min_pos(t_stack *stack)
{
	int		min_idx;
	int		pos;

	min_idx = find_min_index(stack);
	pos = 0;
	while (stack)
	{
		if (stack->index == min_idx)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (0);
}

/*
 * find_max_pos: o espelho de find_min_pos — encontra a posição (a partir
 * do topo) do elemento com o MAIOR índice.
 */
int	find_max_pos(t_stack *stack)
{
	int		max_idx;
	int		pos;

	max_idx = find_max_index(stack);
	pos = 0;
	while (stack)
	{
		if (stack->index == max_idx)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (0);
}
