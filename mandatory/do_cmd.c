/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:58:43 by idias-al          #+#    #+#             */
/*   Updated: 2023/01/10 22:17:22 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

char	**get_command(char *arg)
{
	int		i;
	char	**commands;

	i = ft_strlen(arg);
	while (arg[i] != 39 && arg[i] != 34 && i != 0)
		i--;
	if (i == 0)
		commands = ft_split(arg, ' ');
	else
	{
		if (arg[i] == 39)
			commands = ft_split(arg, 39);
		else
			commands = ft_split(arg, 34);
	}
	return (commands);
}

char	*check_command(char *command)
{
	char	*temp;
	char	*aux;
	char	**final;
	int		i;

	i = 0;
	temp = ft_strdup(command);
	while (temp[i] != '\0')
	{
		if (temp[i] == ' ')
		{
			final = ft_split(temp, ' ');
			free_str(temp);
			aux = ft_strdup(final[0]);
			free_split(final);
			return (aux);
		}
		i++;
	}
	return (temp);
}

char	*find_path(char *final, char **paths)
{
	char	*temp;
	char	*cmd;
	int		i;

	if (access(final, F_OK) == 0)
	{
		cmd = ft_strdup(final);
		return (cmd);
	}
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(temp, final);
		free_str(temp);
		if (access(cmd, F_OK) == 0)
			return (cmd);
		free_str(cmd);
		i++;
	}
	return (NULL);
}

int	do_cmd(char *arg, char *envp[], char *path)
{
	t_commands	commands;

	if (!arg)
		return (total_error("Error when parsing the commands:", \
					strerror(errno), "", 1));
	commands.paths = ft_split(path, ':');
	commands.commands = get_command(arg);
	commands.final = check_command(commands.commands[0]);
	commands.cmd = find_path(commands.final, commands.paths);
	commands.paths = free_split(commands.paths);
	commands.final = free_str(commands.final);
	if (!commands.cmd)
	{
		commands.commands = free_split(commands.commands);
		return (total_error("command not found: ", arg, "", 127));
	}
	if (execve(commands.cmd, commands.commands, envp) < 0)
	{
		commands.cmd = free_str(commands.cmd);
		commands.commands = free_split(commands.commands);
		return (total_error("execve failed", "", "", 127));
	}
	return (0);
}
