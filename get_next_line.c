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

int ret_substring(char **astr, char **line)
{
	char *tmp;
	char *chr;
	int diff;

	if ((chr = ft_strchr(*astr, (int) '\n')))
	{
		diff = chr - *astr;
		*line = ft_strsub(*astr, 0, diff);
		tmp = ft_strdup((*astr + diff + 1));
		free(*astr);
		*astr = tmp;
		return(1);
	}
	return(0);
}


int		get_next_line(const int fd, char **line)
{
	static char *str;
	char *buf;
	int res;
	int ret;
	char *tmp;

	tmp = &(*str);
	if (fd < 0 || !line)
		return(-1);
	buf = ft_memalloc(sizeof(char) * BUFF_SIZE + 1);
	if (str == NULL)
		str = "";
	if ((ret = ret_substring(&str, line)))
	{
		ft_memdel((void **)&buf);
		return(1);
	}
	else
		while ((ret = read(fd, buf, BUFF_SIZE)) > 0 || ft_strcmp(str, "") != 0)
		{
			str = ft_strjoin(str, buf);
			ft_strclr(buf);
			if (ret_substring(&str, line))
			{
				if (tmp != str)
					free(tmp);
				ft_memdel((void **) &buf);
				return (1);
			}
			else if (ret <= 0)
			{
				ft_memdel((void **) &buf);
				if (ft_isempty(str))
					return(0);
				*line = ft_strdup(str);
				ft_strclr(str);
				return (1);
			}
		}
	return (0);
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