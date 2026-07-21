/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple_three.c                                :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * SORT_SIMPLE_THREE.C - Caso especial: ordenar exatamente 3 elementos
 * ============================================================================
 * Ordenar 3 elementos é um caso clássico que pode ser resolvido com uma
 * "tabela de decisão": existem apenas 6 arranjos possíveis para 3 valores
 * distintos (3! = 6 permutações), e para cada um existe uma sequência
 * ÓTIMA (mínima) de operações que resolve. Esse arquivo implementa
 * exatamente essa tabela.
 * ============================================================================
 */

#include "push_swap.h"

/*
 * cmp_pattern: recebe os três índices (a, b, c — na ordem em que estão
 * empilhados, do topo para baixo) e devolve um "código" de 0 a 5
 * representando qual dos 6 padrões de desordem se aplica:
 *
 *   código 0: a < b < c            -> já está ordenado, nada a fazer.
 *   código 1: b é o menor          -> (a > b, b < c, a < c) basta 1 swap.
 *   código 2: c é o menor          -> (a < b, b > c, a < c) padrão
 *                                     "vale" no meio, resolve com
 *                                     ra + sa + rra.
 *   código 3: ordem totalmente decrescente (a > b > c) -> sa + rra.
 *   código 4: a é o maior, no meio -> (a < b, b > c, a > c) resolve só
 *                                     com rra.
 *   código 5: qualquer outro caso restante -> resolve só com ra.
 *
 * Essa é uma implementação de "case matching" manual: em vez de comparar
 * valores numéricos quaisquer, aqui trabalhamos com os "index" (0, 1, 2)
 * já atribuídos em parse.c, o que torna as comparações mais simples e
 * exaustivas de enumerar.
 */
static int	cmp_pattern(int a, int b, int c)
{
	if (a < b && b < c)
		return (0);
	if (a > b && b < c && a < c)
		return (1);
	if (a < b && b > c && a < c)
		return (2);
	if (a > b && b > c)
		return (3);
	if (a < b && b > c && a > c)
		return (4);
	return (5);
}

/*
 * apply_case: dado o "código" retornado por cmp_pattern, executa a
 * sequência de operações correspondente (a menor sequência possível para
 * cada caso). Se o código for 0 (já ordenado), nenhum "if" bate e a
 * função não faz nada, corretamente.
 */
static void	apply_case(t_ps *ps, int code)
{
	if (code == 1)
		op_sa(ps, 1);
	else if (code == 2)
	{
		op_ra(ps, 1);
		op_sa(ps, 1);
		op_rra(ps, 1);
	}
	else if (code == 3)
	{
		op_sa(ps, 1);
		op_rra(ps, 1);
	}
	else if (code == 4)
		op_rra(ps, 1);
	else if (code == 5)
		op_ra(ps, 1);
}

/*
 * sort_three: função de entrada, chamada tanto por sort_simple (quando
 * size_a == 3) quanto potencialmente por outros algoritmos que precisem
 * resolver um sub-caso de 3 elementos.
 *
 * Proteções/casos especiais:
 *   - Se A estiver vazia ou tiver só 1 elemento (!ps->a->next), não há o
 *     que ordenar, retorna direto.
 *   - Se A tiver exatamente 2 elementos (!ps->a->next->next, ou seja, o
 *     segundo nó não tem um terceiro depois), trata como o caso de 2
 *     elementos: compara os índices e, se estiverem invertidos, faz um
 *     único "sa".
 *   - Caso contrário (3 ou mais — na prática, esta função só é chamada
 *     com exatamente 3), lê os três índices do topo (a, b, c) e delega
 *     para cmp_pattern + apply_case resolverem com a sequência mínima de
 *     operações.
 */
void	sort_three(t_ps *ps)
{
	int	a;
	int	b;
	int	c;

	if (!ps->a || !ps->a->next)
		return ;
	a = ps->a->index;
	b = ps->a->next->index;
	if (!ps->a->next->next)
	{
		if (a > b)
			op_sa(ps, 1);
		return ;
	}
	c = ps->a->next->next->index;
	apply_case(ps, cmp_pattern(a, b, c));
}
