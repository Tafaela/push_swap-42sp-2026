/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rermacor <rermacor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:30:48 by bramos            #+#    #+#             */
/*   Updated: 2026/07/21 17:48:45 by rermacor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
/*libera as duas listas de uma vez*/
void	free_ps(t_ps *ps)
{
	if (!ps)
		return ;
	free_stack(&ps->a);
	free_stack(&ps->b);
}
