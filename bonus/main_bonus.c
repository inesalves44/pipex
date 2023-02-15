/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:07:01 by idias-al          #+#    #+#             */
/*   Updated: 2023/01/15 12:00:48 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex_bonus.h"

int	files_open(t_bonus *bonus, char *argv[])
{
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		bonus->input = open(argv[1], O_RDONLY);
		if (bonus->input < 0)
			return (total_error("input file error", " : ", strerror(errno), 1));
		bonus->output = open(argv[bonus->args - 1], \
				O_APPEND | O_CREAT | O_RDWR, 0000666);
		if (bonus->output < 0)
			return (total_error(argv[bonus->args - 1], ": ", \
					strerror(errno), 1));
	}
	else
	{
		bonus->input = open(argv[1], O_RDONLY);
		if (bonus->input < 0)
			return (total_error(argv[1], ": ", strerror(errno), 1));
		bonus->output = open(argv[bonus->args - 1], \
				O_TRUNC | O_CREAT | O_RDWR, 0000666);
		if (bonus->output < 0)
			return (total_error(argv[bonus->args - 1], ": ", \
					strerror(errno), 1));
	}
	return (0);
}

int	end_struct(t_bonus *bonus)
{
	free(bonus->pipes);
	bonus->pipes = NULL;
	close(bonus->input);
	close(bonus->output);
	if (WIFEXITED(bonus->status))
		return (WEXITSTATUS(bonus->status));
	return (0);
}

int	checking_child(t_bonus bonus, char *argv[], char *envp[])
{
	while (bonus.index < (bonus.args - 3))
	{
		bonus.pid = fork();
		if (bonus.pid < 0)
			return (total_error("fork failed", "", "", 1));
		else if (bonus.pid == 0)
		{
			if (bonus.index == 0)
				child_in(bonus, argv[2], envp);
			else if (bonus.index == bonus.args - 4)
				child_out(bonus, argv[2 + bonus.index], envp);
			else
				child_mid(bonus, argv[2 + bonus.index], envp);
		}
		bonus.index++;
	}
	close_fd(&bonus);
	waitpid(-1, &bonus.status, 0);
	return (end_struct(&bonus));
}

int	start_struct(t_bonus *bonus, int argc, char *argv[])
{
	int	ret;

	ret = 0;
	bonus->args = argc;
	ret = files_open(bonus, argv);
	if (ret)
		return (ret);
	bonus->aux = 0;
	ret = do_pipes(bonus);
	if (ret)
		return (ret);
	bonus->index = 0;
	return (ret);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_bonus	bonus;

	if (argc < 5)
		return (total_error("has to be at least 4 args", "", "", 1));
	if (!ft_strncmp(argv[1], "here_doc", 8))
		return (heredoc(argv, envp, argc));
	bonus.ret = start_struct(&bonus, argc, argv);
	bonus.ret = checking_child(bonus, argv, envp);
	return (bonus.ret);
}
