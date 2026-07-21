/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_swap.c                                  :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * OPERATIONS_SWAP.C - Operações "sa", "sb" e "ss"
 * ============================================================================
 * sa: troca os dois primeiros elementos (topo) da pilha A entre si.
 * sb: troca os dois primeiros elementos (topo) da pilha B entre si.
 * ss: faz sa e sb ao mesmo tempo (equivale a chamar as duas, mas conta
 *     como UMA única operação no total de custo).
 * ============================================================================
 */

#include "push_swap.h"

/*
 * swap_top_two: função auxiliar (privada a este arquivo, por isso
 * "static") que troca a posição dos dois primeiros nós de QUALQUER pilha
 * recebida. Reaproveitada tanto por op_sa quanto por op_sb (e
 * indiretamente por op_ss), evitando duplicar a lógica de troca.
 *
 * Se a pilha tiver 0 ou 1 elemento, não há o que trocar — retorna sem
 * fazer nada.
 *
 * Passos da troca (visual, topo à esquerda): [1, 2, 3] -> [2, 1, 3]
 *   1. tmp aponta para o segundo nó (o que vai virar o novo topo).
 *   2. O antigo topo (*stack) passa a apontar para o que estava DEPOIS do
 *      segundo nó (tmp->next) — ou seja, "pula" o segundo nó da cadeia.
 *   3. tmp (o novo topo) passa a apontar para o antigo topo.
 *   4. *stack é atualizado para apontar para tmp (o novo topo).
 */
static void	swap_top_two(t_stack **stack)
{
	t_stack	*tmp;

	if (!*stack || !(*stack)->next)
		return ;
	tmp = (*stack)->next;
	(*stack)->next = tmp->next;
	tmp->next = *stack;
	*stack = tmp;
}

/*
 * op_sa ("swap a"): troca os dois primeiros elementos de A. Se A tiver
 * menos de 2 elementos, não faz nada (nem imprime, nem conta).
 */
void	op_sa(t_ps *ps, int print)
{
	if (!ps->a || !ps->a->next)
		return ;
	swap_top_two(&ps->a);
	ps->op_sa++;
	ps->total_ops++;
	if (print)
		ft_putstr_fd("sa\n", 1);
}

/*
 * op_sb ("swap b"): troca os dois primeiros elementos de B. Se B tiver
 * menos de 2 elementos, não faz nada.
 */
void	op_sb(t_ps *ps, int print)
{
	if (!ps->b || !ps->b->next)
		return ;
	swap_top_two(&ps->b);
	ps->op_sb++;
	ps->total_ops++;
	if (print)
		ft_putstr_fd("sb\n", 1);
}

/*
 * op_ss: executa swap_top_two em A e em B na mesma chamada. Note que,
 * diferente de op_sa/op_sb, aqui NÃO há checagem de tamanho mínimo antes
 * de chamar swap_top_two — mas isso não é um problema, porque
 * swap_top_two já faz essa checagem internamente (se a pilha tiver menos
 * de 2 elementos, simplesmente não faz nada).
 * Conta como UMA única operação (op_ss++, total_ops++), mesmo afetando
 * as duas pilhas — essa é a vantagem de "ss": custa o mesmo que "sa"
 * sozinho, mas faz o trabalho de "sa" + "sb".
 */
void	op_ss(t_ps *ps, int print)
{
	swap_top_two(&ps->a);
	swap_top_two(&ps->b);
	ps->op_ss++;
	ps->total_ops++;
	if (print)
		ft_putstr_fd("ss\n", 1);
}
