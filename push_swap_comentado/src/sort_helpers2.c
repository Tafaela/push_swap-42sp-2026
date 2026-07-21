/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers2.c                                    :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * SORT_HELPERS2.C - Gira a pilha até um elemento chegar ao topo, pelo
 * caminho MAIS CURTO (menor número de operações)
 * ============================================================================
 */

#include "push_swap.h"

/*
 * rotate_to_top_a: recebe "pos" (a posição, contada a partir do topo, de
 * um elemento que queremos trazer para o topo de A) e decide o caminho
 * mais barato para chegar lá:
 *   - Se "pos" está na METADE DE CIMA da pilha (pos <= size/2), é mais
 *     rápido girar PARA CIMA (op_ra) "pos" vezes — o elemento "sobe" até
 *     o topo.
 *   - Caso contrário, é mais rápido girar PARA BAIXO (op_rra). Nesse
 *     caso, o número de rotações necessárias é (size - pos): por
 *     exemplo, numa pilha de 10 elementos, se o elemento está na posição
 *     8 (perto do fundo), em vez de fazer 8 rotações para cima, fazemos
 *     apenas 10 - 8 = 2 rotações para baixo.
 *
 * "while (pos-- > 0)": um idioma comum em C para "repita X vezes". A
 * cada iteração, testa se pos é > 0, e SÓ DEPOIS decrementa pos (efeito
 * pós-decremento) — então o laço roda exatamente "pos" vezes (o valor
 * inicial de pos).
 */
void	rotate_to_top_a(t_ps *ps, int pos)
{
	int	size;

	size = ps->size_a;
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			op_ra(ps, 1);
	}
	else
	{
		pos = size - pos;
		while (pos-- > 0)
			op_rra(ps, 1);
	}
}

/*
 * rotate_to_top_b: exatamente a mesma lógica de rotate_to_top_a, mas
 * aplicada à pilha B (usa op_rb/op_rrb em vez de op_ra/op_rra).
 */
void	rotate_to_top_b(t_ps *ps, int pos)
{
	int	size;

	size = ps->size_b;
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			op_rb(ps, 1);
	}
	else
	{
		pos = size - pos;
		while (pos-- > 0)
			op_rrb(ps, 1);
	}
}

/*
 * find_pos_in_b: percorre a pilha B procurando o nó cujo "index" seja
 * igual ao valor procurado, retornando sua posição (contada a partir do
 * topo, começando em 0). Se não encontrar (não deveria acontecer em uso
 * normal, já que sabemos que o índice existe em algum lugar), retorna -1.
 */
int	find_pos_in_b(t_ps *ps, int index)
{
	t_stack	*tmp;
	int		pos;

	tmp = ps->b;
	pos = 0;
	while (tmp)
	{
		if (tmp->index == index)
			return (pos);
		pos++;
		tmp = tmp->next;
	}
	return (-1);
}
