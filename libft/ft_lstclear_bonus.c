/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 02:04:03 by mel-haya          #+#    #+#             */
/*   Updated: 2019/10/23 19:15:12 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *next;
	t_list *to_del;

	to_del = *lst;
	next = NULL;
	while (to_del)
	{
		next = to_del->next;
		ft_lstdelone(to_del, del);
		to_del = next;
	}
	*lst = NULL;
}
