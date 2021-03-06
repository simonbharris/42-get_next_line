/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharris <sharris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 08:28:58 by sharris           #+#    #+#             */
/*   Updated: 2018/09/07 16:04:55 by sharris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** ret_substring
** Pulls a '\n' delimited string from astr and stores it in line
** returns 1 if '\n' was found, 0 otherwise.
*/

static int			ret_substring(char **astr, char **line)
{
	char *tmp;
	char *chr;

	if (*astr == NULL)
		return (0);
	if ((chr = ft_strchr(*astr, (int)'\n')))
	{
		*line = ft_strsub(*astr, 0, chr - *astr);
		tmp = ft_strdup(chr + 1);
		free(*astr);
		*astr = tmp;
		return (1);
	}
	return (0);
}

/*
** empty_buffer
** Empties the rest of the buffer into str
** 0 means nothing was emptied.
** 1 means something was added.
*/

static int			empty_buffer(char *str, char **line)
{
	if (ft_isempty(str))
	{
		*line = ft_strdup("");
		return (0);
	}
	*line = ft_strdup(str);
	ft_strclr(str);
	return (0);
}

/*
** concat_str
** Takes the existing stored string from the static str[fd] and
** adds the buffer read onto it. dynamically reallocing the string
** and managing the memory properly. Lastly, clears the buffer
*/

static void			concat_str(char **str, char buf[])
{
	char *tmp;

	if (*str == NULL)
		*str = ft_strdup("");
	tmp = ft_strdup(*str);
	ft_memdel((void **)&(*str));
	*str = ft_strjoin(tmp, (char *)buf);
	ft_memdel((void **)&tmp);
	ft_strclr((char *)buf);
}

/*
** fetch_file
** fetch_file will search a t_list containing content pointing to t_files
** If a t_file matches the fd, passed into fetch_file, it will return that
** t_file. Otherwise, it adds a new t_file/t_list to the front of the t_list
** and returns that
*/

static t_file		*fetch_file(int fd, t_list **alist)
{
	t_list *tmp;
	t_file *file;

	tmp = *alist;
	while (tmp)
	{
		if (((t_file *)tmp->content)->fd == fd)
			return ((t_file *)tmp->content);
		tmp = tmp->next;
	}
	file = (t_file *)malloc(sizeof(t_file));
	file->fd = fd;
	file->data = NULL;
	ft_lstadd(alist, ft_lstnew((void *)file, sizeof(t_file)));
	free(file);
	return ((t_file *)(*alist)->content);
}

/*
** get_next_line
** Gets the next line read (as delimited by '\n' or EoF) from the filedes(fd)
** Stores the output string into the address passed through into line.
** Returns:
** -1 (error)
**  0 (no more to read)
**  1 (string returned)
*/

int					get_next_line(const int fd, char **line)
{
	static t_list	*flist;
	char			buf[BUFF_SIZE + 1];
	int				ret;
	t_file			*file;

	bzero(buf, BUFF_SIZE + 1);
	if (fd < 0 || !line || read(fd, buf, 0))
		return (-1);
	file = fetch_file(fd, &flist);
	if (!(ret = ret_substring(&(file->data), line)))
		while ((ret = read(fd, buf, BUFF_SIZE)) > 0
		|| ft_strcmp(file->data, "") != 0)
		{
			concat_str(&file->data, buf);
			if (ret_substring(&(file->data), line) && (ret = 1))
				break ;
			else if (ret <= 0 && (ret = empty_buffer(file->data, line) || 1))
				break ;
			if (ret == -1)
				break ;
		}
	return (ret);
}
