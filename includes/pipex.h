/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:15:51 by aafounas          #+#    #+#             */
/*   Updated: 2024/07/22 14:44:18 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../Libft/libft.h"

char	*find_path(char *cmd, char **envp);
void	free_array(char **arr);
void	error(char *cmd, char **envp);
void	execute(char *argv, char **envp);

#endif
