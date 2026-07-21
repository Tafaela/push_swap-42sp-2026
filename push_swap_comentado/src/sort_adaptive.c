/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_adaptive.c                                    :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * SORT_ADAPTIVE.C - Estratégia "Adaptive" (padrão do programa): escolhe
 * sozinha o melhor algoritmo, baseado no tamanho da pilha e no grau de
 * desordem
 * ============================================================================
 * É a estratégia usada quando o usuário NÃO passa nenhuma flag explícita
 * (--simple, --medium, --complex) — o programa "decide por conta própria"
 * qual algoritmo é mais adequado para aquele caso específico.
 * ============================================================================
 */

#include "push_swap.h"

/*
 * sort_adaptive: recebe "name" e "complexity" por ponteiro-para-ponteiro
 * (char **) porque precisa MODIFICAR os próprios ponteiros de quem
 * chamou (run_sort, em strategy.c) — assim, run_sort fica sabendo, depois
 * da chamada, qual algoritmo foi realmente escolhido e qual sua
 * complexidade, para poder exibir isso corretamente no relatório de
 * benchmark (print_benchmark, em benchmark.c).
 *
 * Lógica de decisão:
 *   1. Calcula o grau de desordem da pilha (compute_disorder, de
 *      disorder.c) — um valor entre 0.0 (já ordenada) e 1.0 (totalmente
 *      invertida).
 *   2. *name é sempre setado como "Adaptive" (o nome da estratégia
 *      "guarda-chuva" — mesmo que o algoritmo real usado por dentro seja
 *      outro, o usuário pediu "Adaptive").
 *   3. Se a pilha for pequena (size_a <= 5), usa sort_simple
 *      diretamente, já que para poucos elementos o overhead dos
 *      algoritmos mais sofisticados não compensa.
 *   4. Se a pilha estiver pouco desordenada (disorder < 0.2 = menos de
 *      20% dos pares fora de ordem), também usa sort_simple — já que uma
 *      pilha quase ordenada é resolvida rapidamente até por um algoritmo
 *      "ingênuo".
 *   5. Se a desordem for moderada (0.2 <= disorder < 0.5), usa
 *      sort_medium (estratégia de chunks, O(n*sqrt(n))) — um meio-termo
 *      entre simplicidade e eficiência.
 *   6. Para qualquer desordem maior (disorder >= 0.5, ou seja, pilha bem
 *      embaralhada), usa sort_complex (algoritmo de custo mínimo/turco ou
 *      radix sort para pilhas grandes, O(n log n)) — o algoritmo mais
 *      sofisticado, que compensa seu maior custo computacional gerando
 *      MENOS operações de push_swap quando a pilha está realmente
 *      bagunçada.
 *
 * Em cada ramo, *complexity é setado com a notação Big-O correspondente
 * ao algoritmo escolhido, para fins de relatório no modo --bench.
 */
void	sort_adaptive(t_ps *ps, char **name, char **complexity)
{
	double	disorder;

	disorder = compute_disorder(ps->a, ps->size_a);
	*name = "Adaptive";
	if (ps->size_a <= 5)
	{
		*complexity = "O(n^2)";
		sort_simple(ps);
		return ;
	}
	if (disorder < 0.2)
	{
		*complexity = "O(n^2)";
		sort_simple(ps);
		return ;
	}
	if (disorder < 0.5)
	{
		*complexity = "O(n*sqrt(n))";
		sort_medium(ps);
		return ;
	}
	*complexity = "O(n log n)";
	sort_complex(ps);
}
