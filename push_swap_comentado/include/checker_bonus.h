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

/*
 * ============================================================================
 * CHECKER_BONUS.H - Header do programa "checker" (parte bônus)
 * ============================================================================
 * O checker é um segundo programa (independente do push_swap principal)
 * que serve para VALIDAR se uma sequência de operações realmente ordena a
 * pilha. Funcionamento: o checker recebe os mesmos números do push_swap
 * como argumento, e depois LÊ pela entrada padrão (stdin) uma lista de
 * operações (sa, pb, ra, etc.), uma por linha. Ele executa cada operação
 * e, no final, imprime "OK" se a pilha A ficou ordenada e B vazia, ou "KO"
 * caso contrário.
 *
 * Observação importante: este header usa nomes de tipos IGUAIS aos do
 * push_swap.h (t_stack, t_ps), mas com definições DIFERENTES (mais
 * simples, sem os contadores de operação nem o campo "index"). Por isso
 * as funções aqui têm o sufixo "_b" (de "bonus"/"checker") e este .h nunca
 * é incluído no mesmo arquivo .c junto com push_swap.h — evitando conflito
 * de nomes.
 * ============================================================================
 */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

/*
 * Versão simplificada de t_stack para o checker: aqui só precisamos do
 * valor e do ponteiro para o próximo nó. Não precisamos do campo "index"
 * porque o checker não faz nenhum cálculo de custo/estratégia, apenas
 * executa as operações que recebe e verifica o resultado final.
 */
typedef struct s_stack
{
	int				value;
	struct s_stack	*next;
}	t_stack;

/* Estado do checker: só precisa dos ponteiros para o topo das pilhas A e B */
typedef struct s_ps
{
	t_stack	*a;
	t_stack	*b;
}	t_ps;

/* stack: criação, inserção, remoção e liberação de nós (checker_bonus.c) */
t_stack	*new_node_b(int value);
void	push_node_b(t_stack **stack, t_stack *node);
t_stack	*pop_node_b(t_stack **stack);
void	free_stack_b(t_stack **stack);

/* parse: valida os argumentos do checker e verifica se a pilha A está
 * ordenada (parse_bonus.c) */
int		parse_args_b(t_ps *ps, int argc, char **argv);
int		is_sorted_b(t_stack *stack);

/* operations: interpretam uma string lida do stdin (ex: "pa", "rrb") e
 * executam a operação correspondente (operations_bonus.c,
 * operations_bonus2.c) */
int		exec_op(t_ps *ps, char *op);
int		exec_op_rot(t_ps *ps, char *op);

/* utils: escrever string em fd, atoi seguro, strcmp, e a função
 * get_next_line (lê uma linha por vez da entrada padrão — usada para ler
 * as operações digitadas/enviadas ao checker) (ft_utils_bonus.c,
 * ft_atoi_bonus.c, gnl_bonus.c) */
void	ft_putstr_fd_b(char *s, int fd);
int		ft_atoi_safe_b(char *str, int *result);
int		ft_strcmp_b(char *s1, char *s2);
char	*get_next_line(int fd);

#endif
