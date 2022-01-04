/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharboul <sharboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 09:47:05 by sharboul          #+#    #+#             */
/*   Updated: 2022/01/04 15:54:53 by sharboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# define BUFFER_SIZE 128
# define IFILE ".exec1"
# define OFILE ".exec2"

size_t ft_strlen(char *str);
int ft_perror(char *type);
int ft_printerr(char *str);
void ft_close_pipe(int pipe[2]);
int ft_genfile(int fd, char *str);
int ft_init(char *cmd1, char *cmd2);
void ft_clean(int pipe_fd[2]);
int ft_main(int pfd[2], pid_t pid, char *path);

#endif
