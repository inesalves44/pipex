/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 00:01:49 by idias-al          #+#    #+#             */
/*   Updated: 2023/01/15 10:53:58 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex_bonus.h"

int	do_pipes(t_bonus *bonus)
{
	int	i;

	bonus->pipes = (int *)malloc(sizeof(int) * 2 * \
			(bonus->args - 4 - bonus->aux));
	if (!bonus->pipes)
		return (total_error("pipe error", "", "", 1));
	i = 0;
	while (i < (bonus->args - 4 - bonus->aux))
	{
		if (pipe(bonus->pipes + (2 * i)) < 0)
			return (total_error("pipe error", "", "", 1));
		i++;
	}
	return (0);
}

char	*get_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

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
