/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-balb <ael-balb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:58:20 by ael-balb          #+#    #+#             */
/*   Updated: 2023/02/26 21:35:49 by ael-balb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_readline(int fd, char *line)
{
	char	*str;
	ssize_t	i;

	i = 1;
	str = malloc(BUFFER_SIZE + 1);
	if (!str)
		return (0);
	if (!line)
		line = ft_strdup("");
	while (!ft_strchr(line) && i != 0)
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i < 0)
		{
			free(str);
			free(line);
			line = NULL;
			return (NULL);
		}
		str[i] = '\0';
		line = ft_strjoin(line, str);
	}
	free(str);
	return (line);
}

char	*ft_showline(char **line)
{
	int	i;

	i = 0;
	if (line[0][i] == '\0')
	{
		free(*line);
		*line = NULL;
		return (NULL);
	}
	while (line[0][i] != '\n' && line[0][i] != '\0')
		i++;
	return (ft_substr(*line, 0, (i + 1)));
}

char	*ft_rest(char *line)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	str = ft_substr(line, (i + 1), ft_strlen(line));
	free(line);
	line = NULL;
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*line[10240];
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = ft_readline(fd, line[fd]);
	if (line[fd] == NULL)
		return (NULL);
	str = ft_showline(&line[fd]);
	if (str == NULL)
		return (NULL);
	line[fd] = ft_rest(line[fd]);
	return (str);
}
// int main()
// {
// 	int fd;
// 	int fg;
// 	fd = open ("file.txt", O_RDONLY);
// 	printf ("%s",get_next_line(fd));
// 	fg = open ("filw2.txt", O_RDONLY);
// 	printf ("%s",get_next_line(fg));
// }
