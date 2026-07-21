/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * SORT_COMPLEX.C - Estratégia "Complex": ponto de entrada do algoritmo de
 * custo mínimo (também chamado de "algoritmo turco"), complexidade
 * aproximada O(n log n)
 * ============================================================================
 * Este arquivo apenas ORQUESTRA as peças implementadas nos outros
 * arquivos sort_complex_*.c: cost (cálculo de custo), move (execução do
 * movimento), insert (devolução final) e radix (alternativa para pilhas
 * muito grandes).
 * ============================================================================
 */

#include "push_swap.h"

/*
 * turk_sort: implementa o "algoritmo turco" propriamente dito.
 *
 * Passos:
 *   1. Empurra 2 elementos de A para B logo de cara (op_pb duas vezes —
 *      a segunda só acontece se ainda sobrar mais de 1 elemento em A).
 *      Isso "dá partida" em B, criando um destino inicial para onde os
 *      próximos elementos de A poderão ser inseridos de forma ordenada.
 *   2. Enquanto A tiver MAIS de 3 elementos, repete o ciclo principal:
 *      a. find_cheapest (sort_complex_cost.c) encontra, entre TODOS os
 *         elementos de A, qual é o mais barato de mover para B agora
 *         (considerando também o custo de girar B até a posição de
 *         inserção certa).
 *      b. move_both_to_top (sort_complex_move.c) executa de fato as
 *         rotações necessárias para colocar esses dois elementos (o de A
 *         e o destino em B) no topo de suas pilhas.
 *      c. op_pb empurra o elemento (agora no topo de A) para o topo de
 *         B, inserindo-o na posição correta.
 *   3. Quando A chega a 3 elementos ou menos, esses últimos são
 *      ordenados diretamente com sort_simple (que resolve o caso de 3
 *      elementos de forma ótima, ver sort_simple_three.c).
 *   4. Por fim, push_back_to_a (sort_complex_insert.c) devolve todos os
 *      elementos de B para A, um a um, sempre na posição correta,
 *      reconstruindo a pilha A totalmente ordenada.
 */
static void	turk_sort(t_ps *ps)
{
	int	best_a;
	int	best_b;

	op_pb(ps, 1);
	if (ps->size_a > 1)
		op_pb(ps, 1);
	while (ps->size_a > 3)
	{
		best_a = 0;
		best_b = 0;
		find_cheapest(ps, &best_a, &best_b);
		move_both_to_top(ps, best_a, best_b);
		op_pb(ps, 1);
	}
	sort_simple(ps);
	push_back_to_a(ps);
}

/*
 * sort_complex: função de entrada da estratégia "Complex".
 *   - size_a <= 3: delega direto para sort_simple (não vale a pena o
 *     overhead do algoritmo turco para tão poucos elementos).
 *   - size_a <= 200: usa turk_sort (algoritmo de custo mínimo,
 *     O(n log n) na prática — mais rápido em número de operações, mas
 *     mais caro computacionalmente por causa de find_cheapest, que é
 *     O(n) a cada passo, dando O(n²) no total; ainda assim, o NÚMERO DE
 *     OPERAÇÕES de push_swap gerado é bem menor que o de sort_medium).
 *   - size_a > 200: troca para radix_sort (sort_complex_radix.c), que é
 *     mais rápido de EXECUTAR (menos cálculo por elemento) para pilhas
 *     muito grandes, mesmo gerando um pouco mais de operações de
 *     push_swap que o algoritmo turco geraria.
 * O valor 200 é um limiar (threshold) escolhido para equilibrar
 * qualidade da ordenação (menos operações) com tempo de execução do
 * próprio programa.
 */
void	sort_complex(t_ps *ps)
{
	if (ps->size_a <= 3)
	{
		sort_simple(ps);
		return ;
	}
	if (ps->size_a <= 200)
		turk_sort(ps);
	else
		radix_sort(ps);
}
