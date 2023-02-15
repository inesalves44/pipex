/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_fork_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:35:51 by idias-al          #+#    #+#             */
/*   Updated: 2023/01/11 00:17:21 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex_bonus.h"

void	free_strings(t_bonus *bonus)
{
	free_split(bonus->paths_split);
	if (!bonus->cmd)
		free_split(bonus->commands);
	free_str(bonus->final);
	free(bonus->pipes);
	bonus->pipes = NULL;
	close(bonus->input);
	close(bonus->output);
}

int	child_in(t_bonus bonus, char *argv, char *envp[])
{
	dup2(bonus.input, 0);
	dup2(bonus.pipes[1], 1);
	close_fd(&bonus);
	bonus.paths = get_path(envp);
	bonus.paths_split = ft_split(bonus.paths, ':');
	bonus.commands = get_command(argv);
	bonus.final = check_command(bonus.commands[0]);
	bonus.cmd = find_path(bonus.final, bonus.paths_split);
	free_strings(&bonus);
	if (!bonus.cmd)
		return (total_error("command not found: ", argv, "", 127));
	if (execve(bonus.cmd, bonus.commands, envp) < 0)
	{
		free_str(bonus.cmd);
		free_split(bonus.commands);
		return (total_error("execve error", "", "", 127));
	}
	return (0);
}

int	child_out(t_bonus bonus, char *argv, char *envp[])
{
	dup2(bonus.pipes[2 * bonus.index - 2], 0);
	dup2(bonus.output, 1);
	close_fd(&bonus);
	bonus.paths = get_path(envp);
	bonus.paths_split = ft_split(bonus.paths, ':');
	bonus.commands = get_command(argv);
	bonus.final = check_command(bonus.commands[0]);
	bonus.cmd = find_path(bonus.final, bonus.paths_split);
	free_strings(&bonus);
	if (!bonus.cmd)
		return (total_error("command not found: ", argv, \
					"", 127));
	if (execve(bonus.cmd, bonus.commands, envp) < 0)
	{
		free_split(bonus.commands);
		free_str(bonus.cmd);
		return (total_error("execve error", "", "", 127));
	}
	return (0);
}

int	child_mid(t_bonus bonus, char *argv, char *envp[])
{
	dup2(bonus.pipes[2 * bonus.index - 2], 0);
	dup2(bonus.pipes[2 * bonus.index + 1], 1);
	close_fd(&bonus);
	bonus.paths = get_path(envp);
	bonus.paths_split = ft_split(bonus.paths, ':');
	bonus.commands = get_command(argv);
	bonus.final = check_command(bonus.commands[0]);
	bonus.cmd = find_path(bonus.final, bonus.paths_split);
	free_strings(&bonus);
	if (!bonus.cmd)
		return (total_error("command not found: ", argv, \
					"", 127));
	if (execve(bonus.cmd, bonus.commands, envp) < 0)
	{
		free_split(bonus.commands);
		free_str(bonus.cmd);
		return (total_error("execve error", "", "", 127));
	}
	return (0);
}
