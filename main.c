/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharboul <sharboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:25:39 by sharboul          #+#    #+#             */
/*   Updated: 2022/01/10 16:10:16 by sharboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "utils/utils.h"

static int	execute(char *argv[], size_t argc, size_t len, int fd[2])
{
	if (len == 2)
		fd[0] = open(argv[1], O_RDONLY);
	else if (len + 1 == argc - 1)
	{
		if (access(argv[argc - 1], F_OK) == 0)
			unlink(argv[argc - 1]);
		fd[1] = open(argv[argc - 1], O_CREAT | O_WRONLY, 0666);
	}
	if (fd[0] < 0 || fd[1] < 0)
		return (1);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	return (0);
}

static void	pass(int p[2], int fd[2], size_t *len)
{
	wait(NULL);
	close(p[1]);
	fd[0] = p[0];
	*len = *len + 1;
}

static int	setup(int p[2], int fd[2])
{
	if (pipe(p) == -1)
		return (ft_perror("pipe"));
	fd[1] = p[1];
	return (fork());
}

static int	ft_main(char *argv[], char *params[4], char *envs[], size_t argc)
{
	size_t	len;
	int		p[2];
	int		fd[2];
	pid_t	pid;

	len = 2;
	while (len < argc - 1)
	{
		pid = setup(p, fd);
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			params[2] = argv[len];
			if (execute(argv, argc, len, fd) != 0)
				exit(ft_perror("execute"));
			if (execve(*params, params, envs) == -1)
				exit(ft_perror("execve"));
			exit(0);
		}
		else
			pass(p, fd, &len);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envs[])
{
	char		*params[4];

	params[0] = "/bin/bash";
	params[1] = "-c";
	params[3] = NULL;
	if (argc < 5)
		return (ft_printerr("Error: Invalid number of input"));
	if (ft_main(argv, params, envs, argc) != 0)
		return (ft_perror("ft_main"));
}
