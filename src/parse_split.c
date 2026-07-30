/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* parse_split.c                                         :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

static int	process_token(char *token, t_stack **head, t_stack **tail)
{
	int	val;

	if (!ft_atoi_safe(token, &val))
	{
		free_stack(head);
		return (0);
	}
	if (!append_node(head, tail, val))
		return (0);
	return (1);
}

int	parse_one_arg(char *arg, t_stack **head, t_stack **tail)
{
	char	**tokens;
	int		i;

	tokens = ft_split(arg, ' ');
	if (!tokens || !tokens[0])
	{
		free_split(tokens);
		free_stack(head);
		return (0);
	}
	i = 0;
	while (tokens[i])
	{
		if (!process_token(tokens[i], head, tail))
		{
			free_split(tokens);
			return (0);
		}
		i++;
	}
	free_split(tokens);
	return (1);
}
