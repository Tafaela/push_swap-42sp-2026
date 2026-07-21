/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex_cost.c                                :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * SORT_COMPLEX_COST.C - O "cérebro" do algoritmo de custo mínimo (usado
 * pela estratégia "Complex" / algoritmo turco, em sort_complex.c)
 * ============================================================================
 * A ideia geral do algoritmo turco (Turkish algorithm): em vez de mover
 * elementos de A para B de forma "cega", a cada passo calculamos, PARA
 * CADA elemento de A, qual seria o CUSTO (número de rotações) de trazê-lo
 * ao topo de A E, ao mesmo tempo, trazer sua "posição de destino" em B ao
 * topo de B — para então fazer "pb" e inserir o elemento de A no lugar
 * certo dentro de B (mantendo B sempre ordenada, do topo ao fundo, de
 * forma decrescente). Escolhemos sempre o elemento de A cujo custo seja
 * o MENOR entre todos, e o movemos. Repetindo isso, o algoritmo insere
 * cada elemento de A no lugar certo de B com o mínimo de rotações
 * possível a cada passo — uma estratégia gulosa (greedy).
 * ============================================================================
 */

#include "push_swap.h"

/*
 * find_target_in_b: dado o índice de um elemento de A ("a_idx"), procura
 * em B qual seria a posição ideal para inserir esse elemento, mantendo B
 * ordenada (decrescente do topo ao fundo). A regra é: encontrar, em B, o
 * MAIOR índice que ainda seja MENOR que a_idx (ou seja, o "vizinho
 * imediatamente abaixo" de a_idx, que já está em B). Se o elemento de A
 * for inserido logo ACIMA desse vizinho, a ordem de B se mantém correta.
 *
 * Se NENHUM elemento de B for menor que a_idx (ou seja, a_idx é o menor
 * valor entre tudo que está em B), a posição de destino passa a ser o
 * TOPO onde está o MAIOR elemento de B (find_max_pos) — nesse caso, o
 * valor de A vai "por cima de tudo" em B.
 *
 * Retorna a POSIÇÃO (contada a partir do topo de B) do elemento de
 * destino encontrado.
 */
int	find_target_in_b(t_ps *ps, int a_idx)
{
	t_stack	*tmp;
	int		best_idx;
	int		best_pos;
	int		pos;

	tmp = ps->b;
	best_idx = -1;
	best_pos = 0;
	pos = 0;
	while (tmp)
	{
		if (tmp->index < a_idx)
		{
			if (best_idx == -1 || tmp->index > best_idx)
			{
				best_idx = tmp->index;
				best_pos = pos;
			}
		}
		pos++;
		tmp = tmp->next;
	}
	if (best_idx == -1)
		return (find_max_pos(ps->b));
	return (best_pos);
}

/*
 * dist_to_top: calcula quantas rotações seriam necessárias para trazer um
 * elemento na posição "pos" ao topo, pelo caminho mais curto (para cima
 * ou para baixo, o que for menor) — a mesma lógica usada em
 * rotate_to_top_a/b (sort_helpers2.c), mas aqui só devolvendo o NÚMERO de
 * rotações (o "custo"), sem executar nada de fato.
 */
static int	dist_to_top(int pos, int size)
{
	if (pos <= size / 2)
		return (pos);
	return (size - pos);
}

/*
 * calc_cost: calcula o custo TOTAL de trazer, ao mesmo tempo, um elemento
 * de A (na posição a_pos) e seu destino em B (na posição b_pos) para o
 * topo das respectivas pilhas.
 *
 * O truque de otimização aqui: se o caminho mais curto para A e para B
 * for na MESMA direção (ambos "para cima" ou ambos "para baixo"), dá para
 * usar as operações combinadas "rr" ou "rrr" para girar as duas pilhas
 * AO MESMO TEMPO — nesse caso, o custo total é o MAIOR entre os dois
 * (porque giramos as duas juntas até a mais lenta terminar; a mais rápida
 * "carona" de graça).
 * Se as direções forem DIFERENTES (uma precisa subir e a outra descer),
 * não dá para combinar — o custo é a SOMA das duas (ca + cb), pois cada
 * uma precisa ser girada separadamente.
 *
 * a_up/b_up: booleano (1 ou 0) indicando se o caminho mais curto para
 * aquela posição é "para cima" (rotação normal) ou "para baixo" (rotação
 * reversa).
 */
int	calc_cost(t_ps *ps, int a_pos, int b_pos)
{
	int	ca;
	int	cb;
	int	a_up;
	int	b_up;

	ca = dist_to_top(a_pos, ps->size_a);
	cb = dist_to_top(b_pos, ps->size_b);
	a_up = (a_pos <= ps->size_a / 2);
	b_up = (b_pos <= ps->size_b / 2);
	if ((a_up && b_up) || (!a_up && !b_up))
	{
		if (ca > cb)
			return (ca);
		return (cb);
	}
	return (ca + cb);
}

/*
 * find_cheapest: percorre TODOS os elementos de A, calculando para cada
 * um o custo de movê-lo (usando find_target_in_b + calc_cost), e guarda
 * (por meio dos ponteiros *best_a_pos e *best_b_pos) a combinação de
 * posições que resultou no MENOR custo encontrado.
 *
 * Essa é a etapa "gulosa" do algoritmo: a cada chamada, escolhemos o
 * melhor movimento IMEDIATO possível (não necessariamente o melhor a
 * longo prazo, mas na prática funciona muito bem na prática para o
 * push_swap).
 *
 * Depois desta função rodar, quem a chamou (turk_sort, em
 * sort_complex.c) usa *best_a_pos e *best_b_pos para de fato mover os
 * dois elementos ao topo (move_both_to_top, em sort_complex_move.c) e
 * então executar "pb".
 */
void	find_cheapest(t_ps *ps, int *best_a_pos, int *best_b_pos)
{
	t_stack	*cur;
	int		a_pos;
	int		b_pos;
	int		cost;
	int		min_cost;

	min_cost = -1;
	a_pos = 0;
	cur = ps->a;
	while (cur)
	{
		b_pos = find_target_in_b(ps, cur->index);
		cost = calc_cost(ps, a_pos, b_pos);
		if (min_cost == -1 || cost < min_cost)
		{
			min_cost = cost;
			*best_a_pos = a_pos;
			*best_b_pos = b_pos;
		}
		a_pos++;
		cur = cur->next;
	}
}
