/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * SORT_SIMPLE.C - Estratégia "Simple": funciona para qualquer tamanho,
 * mas é ineficiente para pilhas grandes (usada como baseline/fallback)
 * ============================================================================
 * Trata casos pequenos (0, 1, 2 ou 3 elementos) de forma especializada e
 * direta (a maneira mais barata possível), e usa um selection sort
 * simples (via pilha B) para tamanhos maiores.
 * ============================================================================
 */

#include "push_swap.h"

/*
 * selection_sort_loop: implementa uma ORDENAÇÃO POR SELEÇÃO clássica,
 * adaptada para pilhas. A ideia do selection sort é: repetidamente,
 * encontrar o MENOR elemento restante e movê-lo para o lugar certo.
 *
 * Aqui, "mover para o lugar certo" significa:
 *   1. Achar a posição do menor elemento ainda em A (find_min_pos).
 *   2. Girar A até esse menor elemento chegar ao topo (rotate_to_top_a —
 *      ela escolhe automaticamente girar para cima ou para baixo,
 *      dependendo de qual caminho é mais curto).
 *   3. Empurrar esse elemento (agora no topo) para B com op_pb. Como B é
 *      uma pilha (LIFO), e estamos sempre empurrando o PRÓXIMO menor
 *      elemento restante em A, B acaba ficando com os elementos em ordem
 *      DECRESCENTE do topo para o fundo (o primeiro que foi empurrado é o
 *      menor de todos, e fica no fundo de B; o último empurrado, maior,
 *      fica no topo de B).
 *
 * Isso se repete "total - 1" vezes (deixamos 1 elemento sobrando em A de
 * propósito — não precisa mover o último, pois ele já ficará sozinho e
 * correto).
 *
 * Por fim, o segundo laço (while ps->b) devolve todos os elementos de B
 * para A com op_pa. Como B estava em ordem decrescente do topo para o
 * fundo, ao "despilhar" (pop do topo) e empurrar em A repetidamente, os
 * elementos chegam em A já em ordem CRESCENTE — reconstituindo a pilha A
 * ordenada.
 *
 * Esse algoritmo é simples de entender, mas caro: é O(n²) no pior caso
 * (para cada um dos n elementos, pode ser necessário girar a pilha várias
 * vezes até achar/mover o mínimo). Por isso só é usado na estratégia
 * "Simple" ou como fallback.
 */
static void	selection_sort_loop(t_ps *ps)
{
	int	i;
	int	total;
	int	min_pos;

	total = ps->size_a;
	i = 0;
	while (i < total - 1)
	{
		min_pos = find_min_pos(ps->a);
		rotate_to_top_a(ps, min_pos);
		op_pb(ps, 1);
		i++;
	}
	while (ps->b)
		op_pa(ps, 1);
}

/*
 * sort_simple: função de entrada da estratégia "Simple". Trata os casos
 * pequenos de forma direta (mais barata que rodar o selection sort geral)
 * e delega para selection_sort_loop apenas quando a pilha é grande.
 *
 * Casos tratados:
 *   - size_a <= 1: já está ordenada por definição (0 ou 1 elemento),
 *     não faz nada.
 *   - size_a == 2: só precisa verificar se os dois elementos estão fora
 *     de ordem (index do primeiro maior que o do segundo) e, se estiver,
 *     dar um único "sa" (swap) para trocar de posição. Uma única operação
 *     resolve o caso de 2 elementos.
 *   - size_a == 3: delega para sort_three (sort_simple_three.c), que
 *     resolve o caso de 3 elementos com o mínimo de operações possível
 *     (no máximo 2 ou 3 operações, dependendo do padrão).
 *   - qualquer outro tamanho (4 ou mais): usa o selection sort genérico.
 */
void	sort_simple(t_ps *ps)
{
	if (ps->size_a <= 1)
		return ;
	if (ps->size_a == 2)
	{
		if (ps->a->index > ps->a->next->index)
			op_sa(ps, 1);
		return ;
	}
	if (ps->size_a == 3)
	{
		sort_three(ps);
		return ;
	}
	selection_sort_loop(ps);
}
