/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex_insert.c                              :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * SORT_COMPLEX_INSERT.C - Etapa final do algoritmo turco: devolve tudo
 * de B para A, na posição certa
 * ============================================================================
 * Depois que turk_sort (sort_complex.c) já reduziu A a 3 ou menos
 * elementos (ordenados por sort_simple) e moveu todo o resto para B de
 * forma organizada, esta função devolve, um a um, cada elemento de B
 * para A, sempre inserindo na posição correta para manter A ordenada.
 * ============================================================================
 */

#include "push_swap.h"

/*
 * find_pos_to_insert_a: dado o índice do elemento no TOPO de B (b_idx),
 * encontra em A a posição onde ele deveria ser inserido para manter A
 * ordenada (crescente do topo ao fundo, que é o objetivo final).
 *
 * A regra: procurar em A o MENOR índice que ainda seja MAIOR que b_idx
 * (ou seja, o "vizinho de cima" mais próximo — o próximo valor maior já
 * presente em A). Se colocarmos b_idx logo ABAIXO desse vizinho (girando
 * A até ele estar no topo e então fazendo "pa"), a ordem se mantém.
 *
 * Se nenhum elemento de A for maior que b_idx (b_idx é o maior valor
 * restante), o destino passa a ser a posição do MENOR elemento de A
 * (find_min_pos) — nesse caso, b_idx deve ir "por baixo de tudo",
 * ficando junto ao menor elemento.
 */
static int	find_pos_to_insert_a(t_ps *ps, int b_idx)
{
	t_stack	*tmp;
	int		best_idx;
	int		best_pos;
	int		pos;

	tmp = ps->a;
	best_idx = -1;
	best_pos = 0;
	pos = 0;
	while (tmp)
	{
		if (tmp->index > b_idx)
		{
			if (best_idx == -1 || tmp->index < best_idx)
			{
				best_idx = tmp->index;
				best_pos = pos;
			}
		}
		pos++;
		tmp = tmp->next;
	}
	if (best_idx == -1)
		return (find_min_pos(ps->a));
	return (best_pos);
}

/*
 * push_back_to_a: função principal deste arquivo, chamada por turk_sort
 * como último passo do algoritmo "Complex".
 *
 * Enquanto B não estiver vazia:
 *   1. Olha o elemento no topo de B (ps->b->index) e descobre onde ele
 *      deveria entrar em A (find_pos_to_insert_a).
 *   2. Gira A (pelo caminho mais curto, via rotate_to_top_a) até essa
 *      posição de destino chegar ao topo de A.
 *   3. Empurra (op_pa) o elemento de B para o topo de A — como o "vizinho
 *      de cima" correto já está no topo de A, o elemento entra
 *      exatamente no lugar certo, mantendo a ordem.
 *
 * Ao final, quando B fica vazia, uma última chamada de rotate_to_top_a
 * gira A até que o MENOR elemento de toda a pilha esteja no topo. Isso é
 * necessário porque, mesmo com todos os valores na ordem relativa
 * correta, a pilha pode estar "girada" (ex: [3,4,5,1,2] em vez de
 * [1,2,3,4,5] — mesma ordem circular, mas começando no lugar errado).
 * Colocar o menor elemento no topo garante que a pilha fique realmente
 * ordenada de cima para baixo, como o projeto exige.
 */
void	push_back_to_a(t_ps *ps)
{
	int	pos;

	while (ps->b)
	{
		pos = find_pos_to_insert_a(ps, ps->b->index);
		rotate_to_top_a(ps, pos);
		op_pa(ps, 1);
	}
	rotate_to_top_a(ps, find_min_pos(ps->a));
}
