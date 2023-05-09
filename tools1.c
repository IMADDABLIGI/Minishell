/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:52:56 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/09 14:12:47 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	nbr_of_words22(t_data *a)
{
	a->k = 0;
	a->lock = 0;
	a->lock1 = 0;
	a->length = 0;
	a->t = '\0';
	while (a->input[a->k])
	{
		if (a->input[a->k] != 39 && a->input[a->k] != 34 && a->input[a->k] != ' '&&a->input[a->k] != '<' && a->input[a->k] != '>' && a->input[a->k] != '|'&& a->lock == 0)
		{
			a->length++;
			a->lock = 1;
		}
		else if (a->input[a->k] == 39 || a->input[a->k] == 34)
		{
			
			if (!a->lock1)
			{
				a->t = a->input[a->k];
				a->lock1 = 1;
				if (a->lock == 1)
					a->length--;
				a->lock = 1;
			}
			else if (a->input[a->k] == a->t && a->lock1)
            {
				a->lock = 0;
                a->lock1 = 0;
				if (!a->input[a->k+1] || a->input[a->k+1] == ' ' ||a->input[a->k+1] == '<' || a->input[a->k+1] == '>' || a->input[a->k+1] == '|')
					a->length++;
            }
		}
		else if ((a->input[a->k] == '<' || a->input[a->k] == '>' || a->input[a->k] == '|') && !a->lock1)
		{
			if ((a->input[a->k] == '<' && a->input[a->k+1] == '<') || (a->input[a->k] == '>' && a->input[a->k+1] == '>'))
				a->k+=1;
			a->length++;
			a->lock = 0;
		}
		else if (a->input[a->k] == ' '  && a->lock == 1 && a->lock1 == 0)
			a->lock = 0;
		a->k++;
	}
	
	return (a->length);
}

char    **free_all22(char **str, int max) 
{
  max--;
    while (max >= 0){
        free(str[max]);
        max--;}
    free (str);
    return (0);
}


static char	**ft_return22(t_data *a)
{
	size_t	end;
	size_t	start;

	a->i = 0;
	start = 0;
	while (a->i < a->length)
	{
		while (a->input[start] == ' ' && a->input[start] != '\0')
			start++;
		end = start;
		if ((a->input[end] == '<' || a->input[end] == '>' || a->input[end] == '|' || a->input[end] == ' '))
		{
				if ((a->input[end] == '<' && a->input[end+1] == '<') || (a->input[end] == '>' && a->input[end+1] == '>'))
					end+=1;
			end++;
		}
		else {
		while ((((a->input[end] != '<' && a->input[end] != '>' && a->input[end] != '|' && a->input[end] != ' ') || a->lock1 == 1) && a->input[end] != '\0'))
		{
			if ((a->input[end] == 39 || a->input[end] == 34) && !a->lock1)
			{
				a->t=a->input[end];
				a->lock1=1;
			}else if (a->lock1 && a->t == a->input[end])
				a->lock1=0;
			end++;
		}
		}
		a->tab[a->i] = ft_substr(a->input, start, end - start);
		if (!a->tab[a->i])
			return (free_all22(a->tab, a->i));
		a->i++;
		start = end;
	}
	a->tab[a->i] = NULL;
	return (a->tab);
}
char	**ft_split22(t_data *a)
{

	if (!a->input)
		return (0);
	// nbr_of_words(a);
	// return(0);
	a->tab = malloc((nbr_of_words22(a) + 1) * (sizeof(char *)));
	if (!a->tab)
		ft_abort(1);
	return (ft_return22(a));
}
/*----------------------------------------------------------------*/
static size_t	leakskiller(char *s, unsigned int start, size_t len)
{
	if (ft_strlen(s + start) >= len)
	{
		return (len);
	}
	else
	{
		return (ft_strlen(s + start));
	}
}
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	o;
	char	*p;

	if (!s)
		return (0);
	if (ft_strlen(s) < (size_t)start)
		return (ft_strdup(""));
	p = malloc((leakskiller(s, start, len) + 1) * sizeof(char));
	if (!p)
		ft_abort(1);
	o = 0;
	while (o < len && s[start + o])
	{
		p[o] = s[start + o];
		o++;
	}
	p[o] = '\0';
	return (p);
}
/*----------------------------------------------------------------*/
char	*ft_strdup(char *s1)
{
	size_t	i;
	size_t	y;
	char	*f;

	y = 0;
	i = ft_strlen(s1);
	f = malloc((i + 1) * sizeof(char));
	if (!f)
		ft_abort(1);
	while (y < i)
	{
		f[y] = s1[y];
		y++;
	}
	f[y] = '\0';
	return (f);
}
/*----------------------------------------------------------------*/
size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/*----------------------------------------------------------------*/
char	*ft_strjoin22(char *s1, char s2)
{
	size_t	i;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	// printf("%s\n",s2);
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + 2));
	if (str == NULL)
		ft_abort(1);
	i = -1;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	free(s1);
		str[i++] = s2;
	str[i] = '\0';
	return (str);
}