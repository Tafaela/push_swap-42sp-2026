/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers3.c                                    :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * SORT_HELPERS3.C - Encontra, dentro de B, o "melhor candidato" para
 * receber um valor de A logo abaixo dele
 * ============================================================================
 * Observação: as funções deste arquivo (find_target_pos_b) implementam a
 * mesma ideia central do algoritmo de custo mínimo usado em
 * sort_complex_cost.c (achar, em B, o maior valor que ainda é menor que
 * um valor de referência), mas nenhuma outra parte do projeto chama
 * find_target_pos_b diretamente — provavelmente foi uma implementação
 * alternativa/anterior à versão usada de fato (find_target_in_b, em
 * sort_complex_cost.c). Fica documentada aqui pois faz parte do header e
 * pode ser cobrada na correção/defesa.
 * ============================================================================
 */

#include "push_swap.h"

/*
 * find_best_below: percorre a pilha B procurando o elemento cujo índice
 * seja o MAIOR valor possível que ainda seja MENOR que "idx" (ou seja, o
 * "vizinho de baixo" mais próximo de idx dentro de B). Essa é
 * exatamente a lógica usada para decidir onde, em B, um valor de A
 * deveria ser inserido para manter B ordenada de forma decrescente do
 * topo ao fundo.
 *
 * *pos_out (passado por referência) recebe a posição desse melhor
 * candidato encontrado. A função retorna 1 (verdadeiro) se achou algum
 * candidato válido, ou 0 se NENHUM elemento de B tem índice menor que
 * "idx" (nesse caso, idx é o menor valor entre A e B, e o candidato certo
 * seria "o maior de B" — tratado depois, em find_target_pos_b).
 */
static int	find_best_below(t_ps *ps, int idx, int *pos_out)
{
	t_stack	*tmp;
	int		best_idx;
	int		pos;

	tmp = ps->b;
	best_idx = -1;
	pos = 0;
	while (tmp)
	{
		if (tmp->index < idx && (best_idx == -1 || tmp->index > best_idx))
		{
			best_idx = tmp->index;
			*pos_out = pos;
		}
		pos++;
		tmp = tmp->next;
	}
	return (best_idx != -1);
}

/*
 * find_target_pos_b: função pública deste arquivo. Tenta achar o melhor
 * "vizinho de baixo" em B (find_best_below); se existir, retorna a
 * posição dele. Se não existir (idx é menor que tudo em B), o candidato
 * certo passa a ser o MAIOR elemento de B (find_max_pos, de
 * sort_helpers1.c) — pois nesse caso o valor de A deveria ficar no topo
 * de B, "empurrando" o maior elemento de B para logo abaixo dele.
 */
int	find_target_pos_b(t_ps *ps, int idx)
{
	int	pos;

	pos = 0;
	if (find_best_below(ps, idx, &pos))
		return (pos);
	return (find_max_pos(ps->b));
}
