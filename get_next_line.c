/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharris <sharris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 08:28:58 by sharris           #+#    #+#             */
/*   Updated: 2018/08/19 08:31:29 by sharris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Pulls a '\n' delimited string from astr and stores it in line
*/

static int ret_substring(char **astr, char **line)
{
	char *tmp;
	char *chr;

	if ((chr = ft_strchr(*astr, (int) '\n')))
	{
		*line = ft_strsub(*astr, 0, chr - *astr);
		tmp = ft_strdup(chr + 1);
		free(*astr);
		*astr = tmp;
		return(1);
	}
	return(0);
}

int		get_next_line(const int fd, char **line)
{
	static char *str = NULL;
	char *buf;
	int ret;
	char *tmp;

	if (fd < 0 || !line)
		return(-1);
	buf = ft_memalloc(sizeof(char) * BUFF_SIZE + 1);
	if (str == NULL)
		str = ft_strdup("");
	if (!(ret = ret_substring(&str, line)))
	{
		ret = 0;
		while ((ret = read(fd, buf, BUFF_SIZE)) > 0 || ft_strcmp(str, "") != 0)
		{
			tmp = ft_strdup(str);
			ft_memdel((void **)&str);
			str = ft_strjoin(tmp, buf);
			ft_memdel((void **)&tmp);
			ft_strclr(buf);
			if (ret_substring(&str, line) && (ret = 1))
				break ;
			else if (ret <= 0)
			{
				if (ft_isempty(str) && !(ret = 0))
					break ;
				*line = ft_strdup(str);
				ft_strclr(str);
				ret = 1;
				break ;
			}
		}
	}
	ft_memdel((void **) &buf);
	return (ret);
}

/*

* Store read information into a buffer
* Check that buffer for a \n
*  If no \n is found, amend the string onto a return value.
*  If \n is found, return that line
?		How to deal with values that remain?
	?       Perhaps we can move the memory to the start, 
	?       or shuffle the pinter forward until we hit a /0. If we hit a /0, then we can 
	?		append that onto a new string

*/