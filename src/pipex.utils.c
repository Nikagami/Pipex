/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:37:40 by aafounas          #+#    #+#             */
/*   Updated: 2024/07/22 16:29:21 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_path_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	return (envp[i] + 5);
}

char	*find_command_path(char *cmd, char *path_str)
{
	char	**file_paths;
	char	*file_path;
	char	*part_path;
	int		i;

	i = 0;
	file_paths = ft_split(path_str, ':');
	while (file_paths[i])
	{
		part_path = ft_strjoin(file_paths[i], "/");
		file_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (file_path && access(file_path, F_OK) == 0)
		{
			free_array(file_paths);
			return (file_path);
		}
		free(file_path);
		i++;
	}
	free_array(file_paths);
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	*path_str;
	char	*file_path;

	path_str = get_path_from_env(envp);
	if (path_str == NULL)
		return (NULL);
	file_path = find_command_path(cmd, path_str);
	return (file_path);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	error(char *msg, char **envp)
{
	(void)envp;
	perror(msg);
	exit(EXIT_FAILURE);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(argv, ' ');
	if (!cmd)
		error("split failed", envp);
	path = find_path(cmd[0], envp);
	if (!path || execve(path, cmd, envp) == -1)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error("execution failed", envp);
	}
}

/*char	*find_path(char *cmd, char **envp)
{
	char	**file_paths;
	char	*file_path;
	int		i;
	char	*part_path;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	file_paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (file_paths[i])
	{
		part_path = ft_strjoin(file_paths[i], "/");
		file_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (file_path && access(file_path, F_OK) == 0)
		{
			free_array(file_paths);
			return (file_path);
		}
		free(file_path);
		i++;
	}
	free_array(file_paths);
	return (NULL);
}*/