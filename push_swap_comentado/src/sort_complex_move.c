/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex_move.c                                :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * SORT_COMPLEX_MOVE.C - Executa de fato o movimento escolhido por
 * find_cheapest: gira A e B até os elementos-alvo chegarem ao topo
 * ============================================================================
 * Esta é a parte que "paga" o custo calculado em sort_complex_cost.c: usa
 * as operações combinadas (rr/rrr) sempre que possível, e completa com
 * rotações individuais (ra/rra/rb/rrb) o que sobrar.
 * ============================================================================
 */

#include "push_swap.h"

/*
 * rotate_together: executa rotações COMBINADAS (rr se same_up for
 * verdadeiro — ambas as pilhas giram para cima; rrr se same_up for falso
 * — ambas giram para baixo) enquanto AMBOS os contadores restantes (*ca e
 * *cb) forem maiores que zero. Cada chamada de rr/rrr gira A e B ao
 * mesmo tempo, "gastando" 1 de cada contador por vez — assim,
 * aproveitamos a operação combinada (que custa o mesmo que uma rotação
 * simples) para adiantar as duas pilhas simultaneamente, até que uma
 * delas termine (fique com contador 0).
 * *ca e *cb são ponteiros porque a função precisa MODIFICAR os valores
 * originais (decrementá-los) para que quem chamou saiba quanto ainda
 * falta girar em cada pilha individualmente.
 */
static void	rotate_together(t_ps *ps, int *ca, int *cb, int same_up)
{
	while (*ca > 0 && *cb > 0)
	{
		if (same_up)
			op_rr(ps, 1);
		else
			op_rrr(ps, 1);
		(*ca)--;
		(*cb)--;
	}
}

/*
 * rotate_leftover_a: depois que rotate_together "gastou" o que dava para
 * combinar, esta função termina de girar A sozinha (o que sobrou de "ca"
 * rotações), usando ra (para cima) ou rra (para baixo) conforme "ra_up".
 */
static void	rotate_leftover_a(t_ps *ps, int ca, int ra_up)
{
	while (ca-- > 0)
	{
		if (ra_up)
			op_ra(ps, 1);
		else
			op_rra(ps, 1);
	}
}

/*
 * rotate_leftover_b: o mesmo que rotate_leftover_a, mas para a pilha B
 * (usa rb/rrb).
 */
static void	rotate_leftover_b(t_ps *ps, int cb, int rb_up)
{
	while (cb-- > 0)
	{
		if (rb_up)
			op_rb(ps, 1);
		else
			op_rrb(ps, 1);
	}
}

/*
 * move_both_to_top: função principal deste arquivo, chamada por turk_sort
 * (sort_complex.c) logo após find_cheapest ter decidido as melhores
 * posições (a_pos em A, b_pos em B).
 *
 * Passos:
 *   1. Decide, para cada pilha, se o caminho mais curto é "para cima"
 *      (ra_up/rb_up) — ou seja, se a posição está na metade de cima da
 *      pilha (pos <= size/2).
 *   2. Calcula quantas rotações (ca/cb) cada pilha precisa: se o caminho
 *      é "para cima", é a própria posição (pos); se é "para baixo", é
 *      (size - pos).
 *   3. Se as DUAS pilhas precisam girar na MESMA direção (ra_up == rb_up
 *      — ambas para cima ou ambas para baixo), tenta aproveitar ao
 *      máximo com rotate_together (operações combinadas rr/rrr, que
 *      "matam dois coelhos com uma cajadada" e custam o mesmo que uma
 *      rotação isolada).
 *   4. O que sobrar depois de rotate_together (uma das pilhas pode
 *      precisar de mais rotações que a outra) é completado
 *      individualmente por rotate_leftover_a e rotate_leftover_b.
 *      Observação: se as direções forem diferentes (ra_up != rb_up), o
 *      passo 3 é pulado inteiramente (rotate_together nem é chamado —
 *      "if (ra_up == rb_up)" protege isso), e ca/cb permanecem com seus
 *      valores completos, sendo executados do zero por
 *      rotate_leftover_a/b.
 *
 * Ao final desta função, o elemento desejado de A e seu destino em B
 * estão ambos no topo de suas respectivas pilhas, prontos para o "pb"
 * que turk_sort executa em seguida.
 */
void	move_both_to_top(t_ps *ps, int a_pos, int b_pos)
{
	int	ra_up;
	int	rb_up;
	int	ca;
	int	cb;

	ra_up = (a_pos <= ps->size_a / 2);
	rb_up = (b_pos <= ps->size_b / 2);
	if (ra_up)
		ca = a_pos;
	else
		ca = ps->size_a - a_pos;
	if (rb_up)
		cb = b_pos;
	else
		cb = ps->size_b - b_pos;
	if (ra_up == rb_up)
		rotate_together(ps, &ca, &cb, ra_up);
	rotate_leftover_a(ps, ca, ra_up);
	rotate_leftover_b(ps, cb, rb_up);
}
