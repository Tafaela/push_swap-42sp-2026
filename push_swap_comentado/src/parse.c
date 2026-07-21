/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * PARSE.C - Leitura e validação dos argumentos do terminal
 * ============================================================================
 * Responsável por transformar os argumentos de texto (argv), como
 * "3" "1" "2", em uma pilha A (lista encadeada de t_stack) já validada:
 * sem valores repetidos, sem overflow de int, e com o campo "index" de
 * cada nó já calculado (posição relativa do valor dentro do conjunto).
 * ============================================================================
 */

#include "push_swap.h"

/*
 * has_duplicate: percorre a pilha que já foi montada até agora e verifica
 * se "val" já existe nela. O push_swap NÃO aceita números repetidos (regra
 * do projeto), então essa checagem é chamada antes de inserir cada novo
 * valor.
 * Retorna 1 se encontrou duplicata, 0 caso contrário.
 */
static int	has_duplicate(t_stack *stack, int val)
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
 * assign_indices: depois que a pilha A inteira já foi montada com os
 * valores originais, esta função calcula, para CADA nó, quantos outros
 * nós têm valor menor que ele. Esse número vira o "index" do nó — ou
 * seja, transforma os valores brutos (que podem ser negativos, grandes,
 * espalhados) em um ranking de 0 a n-1.
 *
 * Por exemplo, para a pilha [5, -3, 100]:
 *   -3  é o menor  -> index 0
 *   5   é o meio    -> index 1
 *   100 é o maior   -> index 2
 *
 * Isso é O(n²) (dois laços aninhados: para cada nó "cur", percorre TODOS
 * os nós "cmp" de novo), mas simplifica MUITO os algoritmos de ordenação
 * depois, porque eles passam a trabalhar só com índices 0..n-1 em vez de
 * valores arbitrários de int.
 */
static void	assign_indices(t_ps *ps)
{
	t_stack	*cur;
	t_stack	*cmp;
	int		idx;

	cur = ps->a;
	while (cur)
	{
		idx = 0;
		cmp = ps->a;
		while (cmp)
		{
			if (cmp->value < cur->value)
				idx++;
			cmp = cmp->next;
		}
		cur->index = idx;
		cur = cur->next;
	}
}

/*
 * append_node: adiciona um novo valor ao FINAL da pilha que está sendo
 * construída (por isso mantemos dois ponteiros, *head para o início e
 * *tail para o último nó já inserido — assim não precisamos percorrer a
 * lista inteira toda vez que formos inserir um elemento novo).
 *
 * Passos:
 *   1. Se o valor já existe na pilha (duplicata), libera tudo que já foi
 *      alocado até agora e retorna erro (0).
 *   2. Tenta alocar um novo nó (new_node faz o malloc). Se falhar (malloc
 *      retornou NULL, sem memória disponível), libera tudo e retorna erro.
 *   3. Se a lista ainda está vazia (*head é NULL), o novo nó vira o head.
 *      Caso contrário, encaixa o novo nó depois do tail atual.
 *   4. Atualiza *tail para apontar para o nó recém-inserido.
 */
static int	append_node(t_stack **head, t_stack **tail, int val)
{
	t_stack	*node;

	if (has_duplicate(*head, val))
	{
		free_stack(head);
		return (0);
	}
	node = new_node(val);
	if (!node)
	{
		free_stack(head);
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
 * parse_args: função principal deste arquivo, chamada por main().
 * Percorre argv a partir do índice "start" (que pula as flags do tipo
 * --bench já tratadas em main.c) e, para cada argumento:
 *   1. Converte a string para int com ft_atoi_safe, que valida se é um
 *      número válido e se cabe em um int (sem overflow). Se não for
 *      válido, aborta e retorna erro.
 *   2. Chama append_node para inserir esse valor no final da lista
 *      (checando duplicata e alocação).
 * Ao final, se tudo deu certo:
 *   - ps->a recebe a lista montada (head).
 *   - ps->size_a é calculado com stack_size (conta quantos nós há).
 *   - assign_indices calcula o índice relativo de cada nó.
 * Retorna 1 em caso de sucesso, 0 em caso de qualquer erro.
 */
int	parse_args(t_ps *ps, int argc, char **argv, int start)
{
	int		i;
	int		val;
	t_stack	*head;
	t_stack	*tail;

	head = NULL;
	tail = NULL;
	i = start;
	while (i < argc)
	{
		if (!ft_atoi_safe(argv[i], &val))
		{
			free_stack(&head);
			return (0);
		}
		if (!append_node(&head, &tail, val))
			return (0);
		i++;
	}
	ps->a = head;
	ps->size_a = stack_size(ps->a);
	assign_indices(ps);
	return (1);
}

/*
 * is_sorted: verifica se a pilha está em ORDEM CRESCENTE do topo até o
 * final, comparando cada nó com o próximo. Assim que encontra um par onde
 * o valor do nó atual é MAIOR que o do próximo, sabemos que está fora de
 * ordem e retornamos 0 (falso) imediatamente.
 * Se percorrer a pilha inteira sem achar nenhuma inversão, está ordenada:
 * retorna 1 (verdadeiro).
 * Uma pilha vazia ou com um único elemento é considerada ordenada por
 * definição (o laço "while (stack && stack->next)" nem entra no corpo
 * nesses casos, e cai direto no "return (1)").
 */
int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}
