/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_stack
{
	int				value;
	struct s_stack	*next;
}	t_stack;

typedef struct s_ps
{
	t_stack	*a;
	t_stack	*b;
}	t_ps;

/* stack */
t_stack	*new_node_b(int value);
void	push_node_b(t_stack **stack, t_stack *node);
t_stack	*pop_node_b(t_stack **stack);
void	free_stack_b(t_stack **stack);

/* parse */
int		parse_args_b(t_ps *ps, int argc, char **argv);
int		is_sorted_b(t_stack *stack);

/* operations */
int		exec_op(t_ps *ps, char *op);
int		exec_op_rot(t_ps *ps, char *op);

/* utils */
void	ft_putstr_fd_b(char *s, int fd);
int		ft_atoi_safe_b(char *str, int *result);
int		ft_strcmp_b(char *s1, char *s2);
char	*get_next_line(int fd);

#endif
