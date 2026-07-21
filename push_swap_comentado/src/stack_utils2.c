/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils2.c                                     :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * STACK_UTILS2.C - Liberação da struct de estado completa
 * ============================================================================
 * Arquivo pequeno, separado de stack_utils.c só por organização: contém a
 * função que libera TUDO relacionado ao estado do programa (t_ps), e não
 * apenas uma pilha isolada.
 * ============================================================================
 */

#include "push_swap.h"

/*
 * free_ps: libera as duas pilhas (A e B) guardadas dentro da struct de
 * estado "ps". É chamada no final de main() (tanto no caminho de sucesso
 * quanto nos caminhos de erro/pilha já ordenada) para garantir que nenhuma
 * memória fique vazando (memory leak) quando o programa termina.
 * Reaproveita free_stack (de stack_utils.c) para cada pilha individualmente.
 */
void	free_ps(t_ps *ps)
{
	if (!ps)
		return ;
	free_stack(&ps->a);
	free_stack(&ps->b);
}
