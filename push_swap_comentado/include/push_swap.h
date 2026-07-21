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

/*
 * ============================================================================
 * PUSH_SWAP.H - Header principal do projeto
 * ============================================================================
 * Este arquivo é o "contrato" do programa: aqui ficam declaradas todas as
 * structs (tipos de dados) e os protótipos (assinaturas) de todas as funções
 * usadas no projeto. Todo arquivo .c que precisa usar essas funções ou
 * structs faz "#include push_swap.h" para enxergá-las.
 *
 * Não existe código executável aqui, apenas DECLARAÇÕES. A implementação
 * (o corpo de cada função) está espalhada nos arquivos .c da pasta src/.
 * ============================================================================
 */

/*
 * Include guard: evita que este arquivo seja colado (via #include) mais de
 * uma vez no mesmo arquivo .c durante a compilação, o que geraria erro de
 * "redefinição". Se PUSH_SWAP_H ainda não foi definido, o pré-processador
 * define agora e processa o conteúdo; se já foi definido (porque outro
 * #include já trouxe esse header antes), tudo entre #ifndef e #endif é
 * ignorado.
 */
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>	/* malloc, free, exit, atoi                          */
# include <unistd.h>	/* write (usada para imprimir sa, pb, ra, etc.)      */
# include <limits.h>	/* INT_MIN, INT_MAX (limites do tipo int)            */

/*
 * ----------------------------------------------------------------------
 * t_stack: representa UM elemento (nó) de uma lista encadeada.
 * As duas pilhas (A e B) do push_swap são, na prática, implementadas como
 * listas ligadas simples: cada nó aponta para o próximo nó da pilha.
 * ----------------------------------------------------------------------
 * value : o número em si (o valor que o usuário passou como argumento).
 * index : a posição RELATIVA do número depois que os valores originais são
 *         "traduzidos" para um intervalo de 0 a n-1 (índice de ordenação).
 *         Isso facilita comparações e cálculos de custo sem se importar
 *         com os valores originais (que podem ser negativos, grandes, etc).
 * next  : ponteiro para o próximo nó da pilha. O último nó aponta para NULL.
 * ----------------------------------------------------------------------
 */
typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

/*
 * ----------------------------------------------------------------------
 * t_ps ("push_swap state"): struct "guarda-chuva" que centraliza TODO o
 * estado do programa. Em vez de passar várias variáveis soltas para cada
 * função, passamos um único ponteiro para t_ps, que contém:
 * ----------------------------------------------------------------------
 * a, b       : ponteiros para o início (topo) das pilhas A e B.
 * size_a     : quantidade atual de elementos na pilha A.
 * size_b     : quantidade atual de elementos na pilha B.
 * op_sa..op_rrr : contadores de quantas vezes cada operação (sa, sb, ss,
 *              pa, pb, ra, rb, rr, rra, rrb, rrr) foi executada. Servem
 *              para estatísticas/benchmark (saber o custo de cada tipo
 *              de operação usada pelo algoritmo).
 * total_ops  : soma total de operações executadas (o "custo" final do
 *              algoritmo de ordenação, usado para avaliar performance).
 * ----------------------------------------------------------------------
 */
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

/*
 * ============================================================================
 * PROTÓTIPOS DE FUNÇÕES, agrupados por responsabilidade.
 * Cada grupo abaixo corresponde (na maioria das vezes) a um arquivo .c
 * específico dentro de src/. Ao ler um protótipo aqui, vá até o arquivo .c
 * correspondente para ver a implementação comentada em detalhe.
 * ============================================================================
 */

/* stack utils: criação, inserção, remoção e liberação de nós/pilhas
 * (implementadas em stack_utils.c e stack_utils2.c) */
t_stack	*new_node(int value);
void	push_node(t_stack **stack, t_stack *node);
t_stack	*pop_node(t_stack **stack);
int		stack_size(t_stack *stack);
void	free_stack(t_stack **stack);
void	free_ps(t_ps *ps);

/* parse: leitura e validação dos argumentos passados no terminal
 * (implementadas em parse.c) */
int		parse_args(t_ps *ps, int argc, char **argv, int start);
int		is_sorted(t_stack *stack);

/* args / strategy: decide qual algoritmo de ordenação usar
 * (implementadas em strategy.c) */
void	run_sort(t_ps *ps, char *strategy, int bench);
int		is_flag(char *arg);

/* operations: as 11 operações "oficiais" do push_swap (sa, sb, ss, pa, pb,
 * ra, rb, rr, rra, rrb, rrr), cada uma manipulando as pilhas A e B
 * (implementadas em operations_push.c, operations_swap.c,
 * operations_rotate.c, operations_rrotate.c) */
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

/* rotate utils (internas, operam direto na lista encadeada, sem contar
 * operações nem imprimir nada — usadas por dentro das funções op_*)
 * (implementadas em rotate_utils.c) */
void	list_rotate_up(t_stack **stack);
void	list_rotate_down(t_stack **stack);

/* disorder: calcula o quão "desordenada" está a pilha (usado no benchmark
 * para decidir/registrar a dificuldade do caso de teste)
 * (implementada em disorder.c) */
double	compute_disorder(t_stack *stack, int size);

/* algoritmos de ordenação: cada função implementa uma estratégia diferente
 * dependendo do tamanho da pilha (3, <=5, <=100 elementos, ou "adaptativa"
 * escolhendo entre custo-mínimo e radix sort para pilhas grandes).
 * (implementadas em sort_simple.c, sort_simple_three.c, sort_medium.c,
 * sort_medium2.c, sort_complex.c, sort_complex_cost.c,
 * sort_complex_insert.c, sort_complex_move.c, sort_complex_radix.c,
 * sort_adaptive.c) */
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

/* utils: funções auxiliares "tipo libft" reimplementadas aqui (escrever em
 * fd, converter número para string, atoi seguro contra overflow, strcmp,
 * strlen) mais a impressão do relatório de benchmark
 * (implementadas em ft_str.c, ft_nbr.c, ft_atoi.c, benchmark.c) */
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi_safe(char *str, int *result);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *s);
void	print_benchmark(t_ps *ps, double disorder, char *strategy,
			char *complexity);

/* sort helpers: funções de apoio usadas pelos algoritmos de ordenação para
 * achar índices de mínimo/máximo e posições, e para girar (rotacionar) a
 * pilha até um elemento específico chegar ao topo pelo caminho mais curto
 * (implementadas em sort_helpers1.c, sort_helpers2.c, sort_helpers3.c) */
int		find_min_index(t_stack *stack);
int		find_max_index(t_stack *stack);
int		find_min_pos(t_stack *stack);
int		find_max_pos(t_stack *stack);
void	rotate_to_top_a(t_ps *ps, int pos);
void	rotate_to_top_b(t_ps *ps, int pos);
int		find_pos_in_b(t_ps *ps, int index);
int		find_target_pos_b(t_ps *ps, int idx);

#endif
