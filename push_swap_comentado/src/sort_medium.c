/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * SORT_MEDIUM.C - Estratégia "Medium": ordenação por "chunks" (faixas de
 * índice), complexidade aproximada O(n * sqrt(n))
 * ============================================================================
 * A ideia geral (implementada junto com sort_medium2.c): dividir o
 * intervalo de índices [0, n-1] em pedaços ("chunks") de tamanho
 * aproximadamente sqrt(n). Para cada chunk, em ordem (do menor para o
 * maior), varremos A e empurramos para B todos os elementos que
 * pertencem a esse chunk — sempre que empurramos um elemento que é menor
 * que o "meio" do chunk, damos uma rotação extra em B (op_rb) para deixar
 * B parcialmente organizada por dentro do chunk. No final (em
 * sort_medium2.c), os elementos são retirados de B em ordem decrescente
 * (sempre pegando o maior) e empurrados de volta para A, reconstruindo a
 * pilha A já ordenada.
 * ============================================================================
 */

#include "push_swap.h"

/*
 * ft_sqrt_ceil: calcula a raiz quadrada de "n", arredondada para CIMA
 * (ceil), sem usar a biblioteca math.h (o projeto push_swap não pode usar
 * funções externas de matemática). A abordagem é simples: vai testando
 * i = 1, 2, 3... até encontrar o primeiro i tal que i*i não seja menor
 * que n (ou seja, i*i >= n). Esse i é a raiz quadrada arredondada para
 * cima.
 * Usada para decidir o tamanho de cada "chunk" (pedaço) em que a pilha
 * será dividida — dividir em blocos de tamanho ~sqrt(n) é o que garante
 * a complexidade O(n*sqrt(n)) desse algoritmo.
 */
int	ft_sqrt_ceil(int n)
{
	int	i;

	i = 1;
	while (i * i < n)
		i++;
	return (i);
}

/*
 * count_in_range: conta quantos nós da pilha "stack" têm o campo "index"
 * dentro do intervalo [min, max] (inclusive nos dois extremos). Usada
 * para saber, antes de começar a empurrar elementos, quantos elementos
 * pertencem ao chunk atual (para sabermos quando parar de empurrar).
 */
static int	count_in_range(t_stack *stack, int min, int max)
{
	int	count;

	count = 0;
	while (stack)
	{
		if (stack->index >= min && stack->index <= max)
			count++;
		stack = stack->next;
	}
	return (count);
}

/*
 * top_is_in_range: verifica se o elemento no TOPO de A pertence ao
 * intervalo [min, max] do chunk que estamos processando no momento.
 */
static int	top_is_in_range(t_ps *ps, int min, int max)
{
	if (!ps->a)
		return (0);
	return (ps->a->index >= min && ps->a->index <= max);
}

/*
 * push_chunk: processa um único chunk (faixa de índices [min, max]),
 * movendo TODOS os elementos de A que pertencem a essa faixa para B.
 *
 * Passos:
 *   1. Conta quantos elementos do chunk existem em A (total), usando
 *      count_in_range — isso define quantas vezes o laço principal deve
 *      rodar até terminar o chunk.
 *   2. "mid" é o ponto médio do intervalo [min, max].
 *   3. Enquanto ainda não empurramos todos os elementos do chunk
 *      (pushed < total):
 *      - Se o topo de A já pertence ao chunk (top_is_in_range), empurra
 *        (op_pb) esse elemento para B e incrementa "pushed". Depois,
 *        se o elemento que acabou de chegar ao topo de B tem índice
 *        MENOR OU IGUAL ao meio do chunk, aplicamos uma rotação extra em
 *        B (op_rb) — isso é uma heurística para deixar os elementos
 *        "menores que a metade" do chunk mais embaixo em B, ajudando a
 *        manter B parcialmente organizada e reduzindo o trabalho de
 *        extract_all mais tarde (em sort_medium2.c).
 *      - Se o topo de A NÃO pertence ao chunk atual, giramos A (op_ra)
 *        para trazer o próximo candidato ao topo, sem gastar nenhum
 *        "pushed" nessa iteração.
 */
void	push_chunk(t_ps *ps, int min, int max)
{
	int	pushed;
	int	total;
	int	mid;

	total = count_in_range(ps->a, min, max);
	pushed = 0;
	mid = (min + max) / 2;
	while (pushed < total)
	{
		if (top_is_in_range(ps, min, max))
		{
			op_pb(ps, 1);
			pushed++;
			if (ps->b && ps->b->index <= mid)
				op_rb(ps, 1);
		}
		else
			op_ra(ps, 1);
	}
}
