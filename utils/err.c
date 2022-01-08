/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharboul <sharboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 13:21:24 by sharboul          #+#    #+#             */
/*   Updated: 2022/01/08 13:31:12 by sharboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int	ft_perror(char *type)
{
	perror(type);
	return (1);
}

int	ft_printerr(char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	write(2, str, len);
	return (1);
}
