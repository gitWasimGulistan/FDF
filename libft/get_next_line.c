/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgulista <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 12:25:22 by wgulista          #+#    #+#             */
/*   Updated: 2016/04/20 01:39:30 by wgulista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		line_len(char *str, int c)
{
	int				i;

	i = 0;
	while (str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (0);
}

int		check_line(char **save, char *tmp, char **line)
{
	if (ft_strchr(*save, '\n'))
	{
		if (!(*line = ft_strsub(*save, 0, line_len(*save, '\n'))))
			return (-1);
		tmp = ft_strdup(ft_strchr(*save, '\n') + 1);
		free(*save);
		*save = tmp;
		return (1);
	}
	return (0);
}

int		get_next_line(int const fd, char **line)
{
	static char		*save[256];
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	int				rd;

	if (fd < 0 || fd > 256 || line == NULL || BUFF_SIZE < 0)
		return (-1);
	if (save[fd] == NULL)
		save[fd] = ft_strdup("");
	while ((rd = read(fd, buff, BUFF_SIZE)) > 0 && rd != 0)
	{
		buff[rd] = '\0';
		tmp = ft_strjoin(save[fd], buff);
		free(save[fd]);
		save[fd] = tmp;
		if (ft_strchr(save[fd], '\n'))
			break ;
	}
	if (rd == -1 || save[fd] == NULL)
		return (-1);
	if (check_line(&save[fd], tmp, line) == 1)
		return (1);
	if (!(*line = ft_strdup(save[fd])))
		return (-1);
	(rd) ? 0 : free(save[fd]);
	return (rd ? 1 : 0);
}