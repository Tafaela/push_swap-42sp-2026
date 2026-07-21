/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * DISORDER.C - Mede o quão "fora de ordem" está a pilha (só para stats)
 * ============================================================================
 * Esta métrica NÃO é usada pelos algoritmos de ordenação para decidir o
 * que fazer — é usada só pelo modo --bench, para dar contexto sobre o
 * quão embaralhado estava o caso de teste (ajuda a comparar diferentes
 * execuções: uma pilha quase ordenada deveria custar poucas operações; uma
 * pilha totalmente embaralhada deveria custar mais).
 * ============================================================================
 */

#include "push_swap.h"

/*
 * compute_disorder: calcula a fração de "pares fora de ordem" (também
 * chamado de número de inversões) sobre o total de pares possíveis.
 *
 * A ideia: para cada par de elementos (cur, cmp) onde cur vem ANTES de
 * cmp na pilha, se cur->value for MAIOR que cmp->value, isso é uma
 * "inversão" (um erro de ordem) — conta como 1 em "mistakes".
 * "total_pairs" conta TODOS os pares possíveis (não só os invertidos).
 *
 * O resultado final é mistakes / total_pairs:
 *   - 0.0  -> pilha perfeitamente ordenada (nenhum par invertido).
 *   - 1.0  -> pilha completamente invertida (todo par está na ordem
 *             errada, ex: pilha em ordem decrescente).
 *   - valores intermediários -> quanto mais perto de 1.0, mais
 *             "bagunçada" está a pilha.
 *
 * Implementação: dois laços aninhados (O(n²)): para cada nó "cur", olha
 * para TODOS os nós que vêm depois dele ("cmp", começando em cur->next)
 * e verifica se formam um par invertido.
 *
 * Casos especiais:
 *   - Pilha vazia ou com 0/1 elemento: não há pares possíveis, retorna
 *     0.0 diretamente (evita divisão por zero mais adiante).
 *   - Se por algum motivo total_pairs desse zero mesmo com mais de um
 *     elemento (não deveria acontecer na prática), a função também
 *     protege contra divisão por zero antes de calcular a fração final.
 */
double	compute_disorder(t_stack *stack, int size)
{
	t_stack	*cur;
	t_stack	*cmp;
	long	mistakes;
	long	total_pairs;

	if (!stack || size <= 1)
		return (0.0);
	mistakes = 0;
	total_pairs = 0;
	cur = stack;
	while (cur)
	{
		cmp = cur->next;
		while (cmp)
		{
			total_pairs++;
			if (cur->value > cmp->value)
				mistakes++;
			cmp = cmp->next;
		}
		cur = cur->next;
	}
	if (total_pairs == 0)
		return (0.0);
	return ((double)mistakes / (double)total_pairs);
}
