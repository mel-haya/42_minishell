/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 17:12:04 by mhalli            #+#    #+#             */
/*   Updated: 2021/07/08 17:12:05 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
    int         counter;

    counter = 0;
    if (lst)
    {
        while (lst->next != NULL)
        {
            counter++;
            lst = lst->next;
        }
        counter++;
    }
    return (counter);
}
