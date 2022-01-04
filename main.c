/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharboul <sharboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 09:47:05 by sharboul          #+#    #+#             */
/*   Updated: 2022/01/04 15:13:22 by sharboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	pid_t	pid;
	int		pipe_fd[2];

	if (argc < 5)
		return (ft_printerr("Not enough arguments gived\n"));
	if (ft_init(argv[2], argv[3]))
	{
		ft_clean(pipe_fd);
		return (1);
	}
	if (pipe(pipe_fd) == -1)
		return (ft_perror("pipe"));
	pid = fork();
	if (pid == -1)
	{
		ft_clean(pipe_fd);
		return (ft_perror("fork"));
	}
	if (pid == 0)
		ft_main(pipe_fd, pid, argv[0]);
	else
	{
		ft_main(pipe_fd, pid, argv[4]);
		wait(0);
		ft_clean(pipe_fd);
	}
}
