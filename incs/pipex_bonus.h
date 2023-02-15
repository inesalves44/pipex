/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:57:19 by idias-al          #+#    #+#             */
/*   Updated: 2023/01/15 10:51:42 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

typedef struct s_bonus
{
	int		args;
	int		input;
	int		output;
	char	*paths;
	int		*pipes;
	pid_t	pid;
	pid_t	cpid1;
	pid_t	cpid2;
	char	**paths_split;
	char	*cmd;
	char	**commands;
	char	*final;
	int		index;
	int		ret;
	int		status;
	int		aux;
}	t_bonus;
void	close_fd(t_bonus *bonus);
int		child_in(t_bonus bonus, char *argv, char *envp[]);
int		child_out(t_bonus bonus, char *argv, char *envp[]);
char	*check_command(char *command);
int		child_mid(t_bonus bonus, char *argv, char *envp[]);
char	*find_path(char *final, char **paths);
char	*get_path(char **envp);
char	**get_command(char *arg);
int		do_cmd(char *arg, char *envp[], char *path);
char	*free_str(char *str);
char	**free_split(char **str);
int		total_error(const char *str1, const char *str2, \
		const char *str3, unsigned int ret);
int		do_pipes(t_bonus *bonus);
int		heredoc(char *argv[], char *envp[], int argc);
int		end_struct(t_bonus *bonus);
int		do_cmd_here(t_bonus bonus, char *arg, char *envp[]);
int		files_open(t_bonus *bonus, char *argv[]);
#endif
