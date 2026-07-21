/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:  */
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
 * PARSE_BONUS.C - Leitura e validação dos argumentos do checker
 * ============================================================================
 * Praticamente idêntico a parse.c do push_swap principal, mas sem
 * calcular "index" (o checker não precisa de índices relativos — ele só
 * compara valores reais diretamente em is_sorted_b).
 * ============================================================================
 */

/*
 * has_duplicate_b: verifica se "val" já existe na pilha construída até
 * agora (o checker, assim como o push_swap, não aceita números
 * repetidos).
 */
static int	has_duplicate_b(t_stack *stack, int val)
{
	while (stack)
	{
		if (stack->value == val)
			return (1);
		stack = stack->next;
	}
	return (0);
}

/*
 * append_node_b: insere um novo valor no FINAL da pilha sendo construída
 * (mantendo *head e *tail para evitar percorrer a lista inteira a cada
 * inserção). Rejeita duplicatas e trata falha de malloc, liberando o que
 * já foi alocado em caso de erro.
 */
static int	append_node_b(t_stack **head, t_stack **tail, int val)
{
	t_stack	*node;

	if (has_duplicate_b(*head, val))
	{
		free_stack_b(head);
		return (0);
	}
	node = new_node_b(val);
	if (!node)
	{
		free_stack_b(head);
		return (0);
	}
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
	return (1);
}

/*
 * parse_args_b: lê todos os argumentos de argv[1] em diante (note que
 * aqui começamos direto em "i = 1" — o checker não tem flags como
 * --bench, então não precisa de um "start" configurável como em
 * parse_args do push_swap), convertendo cada um com ft_atoi_safe_b e
 * inserindo na pilha A com append_node_b.
 * Retorna 1 em caso de sucesso, 0 se qualquer argumento for inválido,
 * duplicado, ou se a alocação de memória falhar.
 */
int	parse_args_b(t_ps *ps, int argc, char **argv)
{
	int		i;
	int		val;
	t_stack	*head;
	t_stack	*tail;

	head = NULL;
	tail = NULL;
	i = 1;
	while (i < argc)
	{
		if (!ft_atoi_safe_b(argv[i], &val))
		{
			free_stack_b(&head);
			return (0);
		}
		if (!append_node_b(&head, &tail, val))
			return (0);
		i++;
	}
	ps->a = head;
	return (1);
}

/*
 * is_sorted_b: verifica se a pilha está em ordem crescente do topo até o
 * fim, comparando cada nó com o próximo (idêntico a is_sorted em
 * parse.c). Usada ao final da execução do checker para decidir se
 * imprime "OK" ou "KO".
 */
int	is_sorted_b(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}
