/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-haya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 07:26:24 by mel-haya          #+#    #+#             */
/*   Updated: 2019/10/27 18:32:58 by mel-haya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *first;
	t_list *a;

	first = ft_lstnew(f(lst));
	if (!lst || !f)
		return (NULL);
	a = first;
	while (lst->next)
	{
		lst = lst->next;
		if (!(a->next = ft_lstnew(f(lst))))
		{
			ft_lstclear(&a, del);
			return (NULL);
		}
		a = a->next;
	}
	return (first);
}
