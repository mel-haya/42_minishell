/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:18:11 by mel-haya          #+#    #+#             */
/*   Updated: 2019/10/25 09:42:53 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *a;

	if (alst == NULL)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	a = ft_lstlast(*alst);
	a->next = new;
}
