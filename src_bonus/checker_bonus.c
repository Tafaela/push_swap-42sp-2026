/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static int	process_lines(t_ps *ps)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		if (!exec_op(ps, line))
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_ps	ps;

	if (argc < 2)
		return (0);
	ps.a = NULL;
	ps.b = NULL;
	if (!parse_args_b(&ps, argc, argv))
	{
		ft_putstr_fd_b("Error\n", 2);
		return (1);
	}
	if (!process_lines(&ps))
	{
		free_stack_b(&ps.a);
		free_stack_b(&ps.b);
		ft_putstr_fd_b("Error\n", 2);
		return (1);
	}
	if (is_sorted_b(ps.a) && !ps.b)
		ft_putstr_fd_b("OK\n", 1);
	else
		ft_putstr_fd_b("KO\n", 1);
	free_stack_b(&ps.a);
	free_stack_b(&ps.b);
	return (0);
}
