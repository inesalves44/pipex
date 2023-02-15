/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:57:19 by idias-al          #+#    #+#             */
/*   Updated: 2023/01/10 22:11:20 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "ft_printf.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

char	*get_path(char **envp);
char	**get_command(char *arg);
int		do_cmd(char *arg, char *envp[], char *path);
char	*free_str(char *str);
char	**free_split(char **str);
int		total_error(const char *str1, const char *str2, \
		const char *str3, unsigned int ret);
typedef struct s_commands
{
	char	**paths;
	char	*cmd;
	char	**commands;
	char	*final;
}	t_commands;
#endif
