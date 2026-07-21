/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_bonus.c                                 :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

/*
 * ============================================================================
 * OPERATIONS_BONUS.C - Executa "sa", "sb", "ss", "pa", "pb" no checker
 * ============================================================================
 * Diferente das funções op_* do push_swap principal (operations_*.c),
 * estas funções "do_*" NÃO imprimem nada e NÃO contam operações — o
 * checker só precisa EXECUTAR a operação sobre as pilhas para depois
 * verificar o resultado final (is_sorted_b + pilha B vazia).
 * ============================================================================
 */

/*
 * do_sa: troca os dois primeiros elementos do topo da pilha A. Mesma
 * lógica de swap_top_two (operations_swap.c no push_swap principal), mas
 * "solta" (inline) aqui, sem uma função auxiliar reaproveitável, já que o
 * checker não tem uma pilha B compartilhando essa lógica no mesmo lugar
 * (do_sb tem sua própria cópia, ver abaixo).
 * Sem efeito se A tiver menos de 2 elementos.
 */
void	do_sa(t_ps *ps)
{
	t_stack	*tmp;

	if (!ps->a || !ps->a->next)
		return ;
	tmp = ps->a->next;
	ps->a->next = tmp->next;
	tmp->next = ps->a;
	ps->a = tmp;
}

/*
 * do_sb: o mesmo que do_sa, mas para a pilha B.
 */
void	do_sb(t_ps *ps)
{
	t_stack	*tmp;

	if (!ps->b || !ps->b->next)
		return ;
	tmp = ps->b->next;
	ps->b->next = tmp->next;
	tmp->next = ps->b;
	ps->b = tmp;
}

/*
 * do_pa: retira o nó do topo de B e o insere no topo de A. Sem efeito se
 * B estiver vazia.
 */
void	do_pa(t_ps *ps)
{
	t_stack	*node;

	if (!ps->b)
		return ;
	node = pop_node_b(&ps->b);
	push_node_b(&ps->a, node);
}

/*
 * do_pb: retira o nó do topo de A e o insere no topo de B. Sem efeito se
 * A estiver vazia.
 */
void	do_pb(t_ps *ps)
{
	t_stack	*node;

	if (!ps->a)
		return ;
	node = pop_node_b(&ps->a);
	push_node_b(&ps->b, node);
}

/*
 * exec_op: função de despacho (dispatcher) chamada por process_lines
 * (checker_bonus.c) para cada linha lida da entrada padrão. Compara a
 * string "op" (ex: "sa", "pb") com cada operação conhecida, chamando a
 * função correspondente.
 *   - "ss" executa do_sa seguido de do_sb (mesmo comportamento combinado
 *     que "ss" tem no push_swap principal).
 *   - Se "op" não for nenhuma das operações de swap/push, delega para
 *     exec_op_rot (operations_bonus2.c), que trata as operações de
 *     rotação (ra, rb, rr, rra, rrb, rrr).
 *   - Se NENHUMA função reconhecer "op" (nem aqui, nem em exec_op_rot),
 *     retorna 0 — sinalizando ao chamador (process_lines) que a
 *     sequência de operações recebida é inválida (o que deve resultar em
 *     "Error" impresso pelo checker).
 * Retorna 1 se a operação foi reconhecida e executada (mesmo que não
 * tenha tido efeito, como "sa" numa pilha vazia).
 */
int	exec_op(t_ps *ps, char *op)
{
	if (ft_strcmp_b(op, "sa") == 0)
		do_sa(ps);
	else if (ft_strcmp_b(op, "sb") == 0)
		do_sb(ps);
	else if (ft_strcmp_b(op, "ss") == 0)
	{
		do_sa(ps);
		do_sb(ps);
	}
	else if (ft_strcmp_b(op, "pa") == 0)
		do_pa(ps);
	else if (ft_strcmp_b(op, "pb") == 0)
		do_pb(ps);
	else if (!exec_op_rot(ps, op))
		return (0);
	return (1);
}
