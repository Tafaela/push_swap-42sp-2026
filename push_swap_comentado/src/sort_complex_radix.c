/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex_radix.c                               :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * SORT_COMPLEX_RADIX.C - Radix Sort adaptado para pilhas (bit a bit)
 * ============================================================================
 * Usado para pilhas MUITO grandes (mais de 200 elementos, ver
 * sort_complex.c), onde o algoritmo de custo mínimo (turco) começaria a
 * ficar caro demais. O Radix Sort tem complexidade O(n * bits), sendo
 * "bits" a quantidade de bits necessária para representar o maior índice
 * — geralmente muito menor que n, tornando esse algoritmo muito eficiente
 * para pilhas grandes.
 *
 * A ideia do Radix Sort binário: em vez de comparar valores diretamente,
 * olhamos BIT POR BIT (do menos significativo ao mais significativo) de
 * cada índice. Em cada rodada (para cada bit), separamos os elementos em
 * dois grupos — os que têm aquele bit 0 e os que têm aquele bit 1 — sem
 * bagunçar a ordem relativa entre eles (isso é o que garante que o
 * algoritmo funcione: "stable partitioning"). Depois de processar todos
 * os bits, a pilha está ordenada.
 * ============================================================================
 */

#include "push_swap.h"

/*
 * get_max_bits: calcula quantos bits são necessários para representar o
 * maior índice possível (size - 1, já que os índices vão de 0 a n-1).
 * Usa deslocamento de bits (>>=) para "contar" quantas vezes é possível
 * dividir por 2 até chegar a 0 — que é exatamente o número de bits
 * necessários.
 * Exemplo: size = 9 -> max índice = 8 (0b1000) -> precisa de 4 bits.
 */
static int	get_max_bits(int size)
{
	int	bits;
	int	max;

	max = size - 1;
	bits = 0;
	while (max > 0)
	{
		bits++;
		max >>= 1;
	}
	return (bits);
}

/*
 * radix_sort: função principal deste arquivo.
 *
 * Para cada bit "bit" (começando pelo menos significativo, bit 0, até
 * max_bits - 1):
 *   1. Percorre TODOS os elementos de A (i de 0 até size-1). Para cada
 *      um, olha o TOPO de A (ps->a) e testa o bit correspondente do seu
 *      índice: "(ps->a->index >> bit) & 1" desloca o índice "bit"
 *      posições para a direita e isola o bit menos significativo
 *      resultante — ou seja, verifica se o bit na posição "bit" do
 *      índice é 1 ou 0.
 *      - Se o bit for 1: gira A (op_ra) — isso "manda o elemento para o
 *        fim da fila" de A sem tirá-lo da pilha, deixando-o para ser
 *        processado depois.
 *      - Se o bit for 0: empurra (op_pb) o elemento para B — os
 *        elementos com bit 0 vão se acumulando em B, mantendo a ordem
 *        relativa entre si (pois sempre pegamos do topo de A, na ordem
 *        em que estavam).
 *   2. Depois de processar TODOS os elementos de A nessa rodada (alguns
 *      foram girados de volta para A, os com bit 0 foram para B), o
 *      laço "while (ps->b) op_pa" devolve tudo de B para A. Como B só
 *      recebeu elementos com bit 0 (na ordem correta), e A já tinha
 *      "sobrado" só os elementos com bit 1 (na ordem correta, por terem
 *      sido apenas girados, nunca removidos), o resultado é que A fica
 *      reorganizada: primeiro os elementos com bit 0 (que voltaram de B),
 *      seguidos pelos elementos com bit 1 — ambos os grupos mantendo a
 *      ordem relativa entre si (essa é a propriedade fundamental do
 *      radix sort: "estabilidade").
 *   3. Passa para o próximo bit (mais significativo) e repete.
 *
 * Depois de processar todos os "max_bits" bits, do menos ao mais
 * significativo, a pilha A está completamente ordenada.
 */
void	radix_sort(t_ps *ps)
{
	int	max_bits;
	int	bit;
	int	i;
	int	size;

	size = ps->size_a;
	max_bits = get_max_bits(size);
	bit = 0;
	while (bit < max_bits)
	{
		i = 0;
		while (i < size)
		{
			if ((ps->a->index >> bit) & 1)
				op_ra(ps, 1);
			else
				op_pb(ps, 1);
			i++;
		}
		while (ps->b)
			op_pa(ps, 1);
		bit++;
	}
}
