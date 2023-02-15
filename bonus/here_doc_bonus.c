/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:30:03 by idias-al          #+#    #+#             */
/*   Updated: 2023/01/16 15:00:58 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex_bonus.h"

int	checking_child_here(t_bonus bonus, char *argv[], char *envp[])
{
	do_pipes(&bonus);
	while (bonus.index < (bonus.args - bonus.aux - 3))
	{
		bonus.pid = fork();
		if (bonus.pid < 0)
			return (total_error("fork failed", "", "", 1));
		else if (bonus.pid == 0)
		{
			if (bonus.index == 0)
				child_in(bonus, argv[2 + bonus.aux], envp);
			else if (bonus.index == bonus.args - 4 - bonus.aux)
				child_out(bonus, argv[2 + bonus.index + bonus.aux], envp);
			else
				child_mid(bonus, argv[2 + bonus.index + bonus.aux], envp);
		}
		bonus.index++;
	}
	close_fd(&bonus);
	waitpid(-1, &bonus.status, 0);
	return (end_struct(&bonus));
}

int	heredoc(char *argv[], char *envp[], int argc)
{
	t_bonus	doc;
	char	*buf;
	int		fd;

	doc.args = argc;
	fd = open(argv[1], O_CREAT | O_WRONLY | O_APPEND, 0000644);
	if (fd < 0)
		return (total_error("here_doc file error", " : ", strerror(errno), 1));
	while (1)
	{
		write(1, "heredoc>", 9);
		buf = get_next_line(0);
		write(fd, buf, ft_strlen(buf));
		if (ft_strlen(buf) == (ft_strlen(argv[2]) + 1) && \
				!ft_strncmp(buf, argv[2], ft_strlen(argv[2])))
			break ;
		free_str(buf);
	}
	free_str(buf);
	doc.ret = files_open(&doc, argv);
	doc.index = 0;
	doc.aux = 1;
	doc.ret = checking_child_here(doc, argv, envp);
	unlink(argv[1]);
	return (doc.ret);
}
