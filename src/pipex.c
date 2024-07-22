/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:09:48 by aafounas          #+#    #+#             */
/*   Updated: 2024/07/22 16:29:06 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(char **av, char **envp, int *fd)
{
	int	filein;

	filein = open(av[1], O_RDONLY);
	if (filein == -1)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(filein);
	close(fd[0]);
	close(fd[1]);
	execute(av[2], envp);
}

void	child_process_2(char **av, char **envp, int *fd)
{
	int	fileout;

	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fileout);
	close(fd[0]);
	close(fd[1]);
	execute(av[3], envp);
}

int	check_arguments(int ac)
{
	if (ac != 5)
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
		return (1);
	}
	return (0);
}

void	configure_pipes_and_forks(int *fd, char **av, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		error("Pipe, failed", envp);
	pid1 = fork();
	if (pid1 == -1)
		error("Fork, failed", envp);
	if (pid1 == 0)
	{
		close(fd[0]);
		child_process(av, envp, fd);
	}
	pid2 = fork();
	if (pid2 == -1)
		error("Fork, failed", envp);
	if (pid2 == 0)
	{
		close(fd[1]);
		child_process_2(av, envp, fd);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	int	fd[2];

	if (check_arguments(ac))
		return (1);
	configure_pipes_and_forks(fd, av, envp);
	return (0);
}
