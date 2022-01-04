/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharboul <sharboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:25:39 by sharboul          #+#    #+#             */
/*   Updated: 2022/01/04 16:26:31 by sharboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "pipex.h"

static t_pipe	*ft_new_pipe(void)
{
	int		fd[2];
	t_pipe	*p;

	pipe(fd);
	p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	p->ip = fd[0];
	p->op = fd[1];
	return (p);
}

void	*ft_free_pipes(t_pipes *pipes)
{
	while (pipes->arr[pipes->size])
		free(pipes->arr[pipes->size--]);
	free(pipes);
	return (NULL);
}

t_pipes	*ft_new_pipes(int size)
{
	t_pipes	*pipes;
	size_t	len;

	len = 0;
	pipes = malloc(sizeof(*pipes));
	if (!pipes)
		return (NULL);
	pipes->arr = malloc(sizeof(*pipes->arr) * (size + 1));
	if (!pipes->arr)
	{
		free(pipes);
		return (NULL);
	}
	while (pipes->arr[len])
	{
		pipes->arr[len] = ft_new_pipe();
		if (!pipes->arr[len])
			return (ft_free_pipes(pipes));
		len++;
	}
	pipes->arr[len] = NULL;
	pipes->size = len;
	return (pipes);
}
