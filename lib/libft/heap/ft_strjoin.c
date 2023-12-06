/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 22:11:13 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/06 00:26:35 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lib_42.h"

void	free_flags(char *s1, char *s2, int flag[])
{
	if (flag[0] == 1)
	{
		if (s1)
			free(s1);
		s1 = NULL;
	}
	if (flag[1] == 1)
	{
		if (s2)
			free(s2);
		s2 = NULL;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	t_join	data;

	data.i = -1;
	data.j = -1;
	data.flag[0] = 0;
	data.flag[1] = 0;
	if (!s1)
	{
		s1 = ft_strdup("");
		data.flag[0] = 1;
	}
	if (!s2)
	{
		s2 = ft_strdup("");
		data.flag[1] = 1;
	}
	data.str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!data.str)
		return (free_flags(s1, s2, data.flag), NULL);
	while (s1[++data.i])
		data.str[data.i] = s1[data.i];
	while (s2[++data.j])
		data.str[data.i + data.j] = s2[data.j];
	return (free_flags(s1, s2, data.flag), data.str);
}

char	*join_em(char *s1, char *s2, int _free)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (_free == 1 || _free == 3)
	{
		if (s1)
			free(s1);
		s1 = NULL;
	}
	if (_free == 2 || _free == 3)
	{
		if (s2)
			free(s2);
		s2 = NULL;
	}
	return (str);
}
