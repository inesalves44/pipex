/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 23:35:48 by idias-al          #+#    #+#             */
/*   Updated: 2023/01/02 15:15:11 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex_bonus.h"

int	total_error(const char *str1, const char *str2, \
		const char *str3, unsigned int ret)
{
	write(2, "pipex: ", 7);
	write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	write(2, str3, ft_strlen(str3));
	write(2, "\n", 1);
	exit (ret);
}

char	*free_str(char *str)
{
	free(str);
	str = NULL;
	return (NULL);
}

char	**free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free_str(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	return (NULL);
}

void	close_fd(t_bonus *bonus)
{
	int	i;

	i = 0;
	while (i < 2 * (bonus->args - 4 - bonus->aux))
	{
		close(bonus->pipes[i]);
		i++;
	}
}
