/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 00:01:49 by idias-al          #+#    #+#             */
/*   Updated: 2023/01/10 21:44:30 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

char	*get_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int	check_child1(char *file, char *cmd, char *envp[], int fd[])
{
	int		file1;
	char	*path;

	file1 = open(file, O_RDONLY);
	if (file1 < 0)
		return (total_error(file, ": ", strerror(errno), 1));
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	dup2(file1, 0);
	path = get_path(envp);
	return (do_cmd(cmd, envp, path));
}

int	check_child2(char *file, char *cmd, char *envp[], int fd[])
{
	int		file2;
	char	*path;

	file2 = open(file, O_TRUNC | O_CREAT | O_RDWR, 0000666);
	if (file2 < 0)
		return (total_error(file, ": ", strerror(errno), 1));
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	dup2(file2, 1);
	path = get_path(envp);
	return (do_cmd(cmd, envp, path));
}

int	first_step(char *argv[], char *envp[], int fd[])
{
	int	status;
	int	cpid1;
	int	cpid2;

	cpid1 = fork();
	if (cpid1 == -1)
		return (total_error("fork failed", "", "", 1));
	else if (cpid1 == 0)
		check_child1(argv[1], argv[2], envp, fd);
	cpid2 = fork();
	if (cpid2 == -1)
		return (total_error("fork failed", "", "", 1));
	else if (cpid2 == 0)
		check_child2(argv[4], argv[3], envp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(cpid1, NULL, 0);
	waitpid(cpid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	int		ret;

	if (argc != 5)
		return (total_error("has to be 4 arguments", "", "", 1));
	if (pipe(fd) < 0)
		return (total_error("pipe error", "", "", 1));
	ret = first_step(argv, envp, fd);
	return (ret);
}
