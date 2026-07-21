/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium2.c                                     :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * SORT_MEDIUM2.C - Continuação da estratégia "Medium": laço de chunks e
 * extração final
 * ============================================================================
 */

#include "push_swap.h"

/*
 * push_all_chunks: percorre TODO o intervalo de índices [0, size_a - 1]
 * em passos de tamanho "chunk_size" (calculado como sqrt(n) em
 * sort_medium), chamando push_chunk (sort_medium.c) para cada faixa.
 *
 * Exemplo: se size_a = 20 e chunk_size = 5, os chunks processados serão
 * [0,4], [5,9], [10,14], [15,19] — cada um tratado por sua vez, do menor
 * para o maior. Ao final, A fica praticamente vazia e B contém todos os
 * elementos, organizados em blocos (cada chunk foi parcialmente
 * organizado dentro de si mesmo pela heurística de push_chunk).
 *
 * "if (max > max_idx) max = max_idx": garante que o último chunk não
 * ultrapasse o índice máximo válido, caso size_a não seja múltiplo exato
 * de chunk_size (ex: 20 elementos com chunks de 6 -> último chunk seria
 * [18,23], mas é limitado para [18,19]).
 */
static void	push_all_chunks(t_ps *ps, int chunk_size)
{
	int	i;
	int	min;
	int	max;
	int	max_idx;

	max_idx = ps->size_a - 1;
	i = 0;
	while (i <= max_idx)
	{
		min = i;
		max = i + chunk_size - 1;
		if (max > max_idx)
			max = max_idx;
		push_chunk(ps, min, max);
		i += chunk_size;
	}
}

/*
 * extract_all: depois que todos os chunks foram empurrados para B, esta
 * função esvazia B de volta para A, sempre pegando o MAIOR elemento
 * restante em B (find_max_pos) e girando B até ele chegar ao topo
 * (rotate_to_top_b), depois empurrando-o para A com op_pa.
 *
 * Por que sempre o MAIOR? Porque empurrar (op_pa) coloca o elemento no
 * TOPO de A. Se sempre pegarmos o maior valor restante em B e o
 * colocarmos no topo de A, o próximo maior valor (menor que o anterior)
 * será empurrado por cima dele — e assim sucessivamente, os valores vão
 * se empilhando em A em ordem CRESCENTE do topo para o fundo, que é
 * exatamente a ordem final desejada.
 */
static void	extract_all(t_ps *ps)
{
	while (ps->b)
	{
		rotate_to_top_b(ps, find_max_pos(ps->b));
		op_pa(ps, 1);
	}
}

/*
 * sort_medium: função de entrada da estratégia "Medium".
 *   - Para pilhas pequenas (size_a <= 3), delega para sort_simple, que já
 *     resolve esses casos de forma ótima/direta (não vale a pena usar
 *     chunks para tão poucos elementos).
 *   - Para pilhas maiores, calcula o tamanho ideal do chunk
 *     (ft_sqrt_ceil), empurra todos os elementos organizados em chunks
 *     para B (push_all_chunks) e depois extrai tudo de volta para A em
 *     ordem (extract_all).
 */
void	sort_medium(t_ps *ps)
{
	if (ps->size_a <= 3)
	{
		sort_simple(ps);
		return ;
	}
	push_all_chunks(ps, ft_sqrt_ceil(ps->size_a));
	extract_all(ps);
}
