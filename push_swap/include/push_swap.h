/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

typedef struct s_ps
{
	t_stack	*a;
	t_stack	*b;
	int		size_a;
	int		size_b;
	int		op_sa;
	int		op_sb;
	int		op_ss;
	int		op_pa;
	int		op_pb;
	int		op_ra;
	int		op_rb;
	int		op_rr;
	int		op_rra;
	int		op_rrb;
	int		op_rrr;
	int		total_ops;
}	t_ps;

/* stack utils *//*esse ja foi etendi*/
t_stack	*new_node(int value);
void	push_node(t_stack **stack, t_stack *node);
t_stack	*pop_node(t_stack **stack);
int		stack_size(t_stack *stack);
void	free_stack(t_stack **stack);
void	free_ps(t_ps *ps);

/* parse */
int		parse_args(t_ps *ps, int argc, char **argv, int start);
char	**ft_split(char *s, char c);
void	free_split(char **arr);
int		is_sorted(t_stack *stack);

/* args / strategy */
void	run_sort(t_ps *ps, char *strategy, int bench);
int		is_flag(char *arg);

/* operations */
void	op_sa(t_ps *ps, int print);
void	op_sb(t_ps *ps, int print);
void	op_ss(t_ps *ps, int print);
void	op_pa(t_ps *ps, int print);
void	op_pb(t_ps *ps, int print);
void	op_ra(t_ps *ps, int print);
void	op_rb(t_ps *ps, int print);
void	op_rr(t_ps *ps, int print);
void	op_rra(t_ps *ps, int print);
void	op_rrb(t_ps *ps, int print);
void	op_rrr(t_ps *ps, int print);

/* rotate utils (internal, list-level) */
void	list_rotate_up(t_stack **stack);
void	list_rotate_down(t_stack **stack);

/* disorder */
double	compute_disorder(t_stack *stack, int size);

/* algorithms */
void	sort_simple(t_ps *ps);
void	sort_three(t_ps *ps);
int		ft_sqrt_ceil(int n);
void	push_chunk(t_ps *ps, int min, int max);
void	sort_medium(t_ps *ps);
void	sort_complex(t_ps *ps);
void	radix_sort(t_ps *ps);
int		find_target_in_b(t_ps *ps, int a_idx);
int		calc_cost(t_ps *ps, int a_pos, int b_pos);
void	find_cheapest(t_ps *ps, int *best_a_pos, int *best_b_pos);
void	move_both_to_top(t_ps *ps, int a_pos, int b_pos);
void	push_back_to_a(t_ps *ps);
void	sort_adaptive(t_ps *ps, char **name, char **complexity);

/* utils */
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi_safe(char *str, int *result);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *s);
void	print_benchmark(t_ps *ps, double disorder, char *strategy,
			char *complexity);

/* sort helpers */
int		find_min_index(t_stack *stack);
int		find_max_index(t_stack *stack);
int		find_min_pos(t_stack *stack);
int		find_max_pos(t_stack *stack);
void	rotate_to_top_a(t_ps *ps, int pos);
void	rotate_to_top_b(t_ps *ps, int pos);
int		find_pos_in_b(t_ps *ps, int index);
int		find_target_pos_b(t_ps *ps, int idx);

#endif
