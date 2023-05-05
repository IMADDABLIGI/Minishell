/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 01:36:49 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/05 18:30:16 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

int	ft_getfile(t_list *data, t_store *store, int i, t_list *ptr)
{
	int	output;

	output = 0;
	while ((data) && (data->tatto != 4))
	{
		if (data->tatto == 6)
			output = open(data->next->arg, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (data->tatto == 8)
			output = open(data->next->arg, O_WRONLY | O_APPEND | O_CREAT, 0644);
		data = data->next;
	}
	if (output != 0)
		return (output);

	if (i == store->count)
		return (0);
	else if (i == 1)
		output = open("/tmp/input", O_WRONLY | O_TRUNC);
	else if ((i % 2) == 0)
		output = open("/tmp/output", O_WRONLY | O_TRUNC);
	else if ((i % 2) != 0)
		output = open("/tmp/input", O_WRONLY | O_TRUNC);
	return (output);
}

//---------------------------------------------------------------------------//

void	ft_checkinput(t_list *data, int input, int i)
{

	while (data && (data->tatto != 4))
	{
		if (data->tatto == 5)
		{
			if ((open(data->next->arg, O_RDONLY)) < 0)
				exit (0);
			if ((open(data->next->arg, O_RDONLY)) >= 0)
			{
				input = open(data->next->arg, O_RDONLY);
				dup2(input, STDIN_FILENO);
				close(input); 
			}
		}
		if (data->tatto == 7)
		{
			input = ft_here_doc(data, 0, NULL);
			dup2(input, STDIN_FILENO);
			close(input); 
		}
		data = data->next;
	}




	if (input)
		return ;


	else
	{
		if (i == 1)
		return ;
		if ((i % 2) == 0)
			input = open("/tmp/input", O_RDONLY);
		else if ((i % 2) != 0)
			input = open("/tmp/output", O_RDONLY);
		dup2(input, STDIN_FILENO);
		close(input);
	}
}













//----------------------------------------------------------------------------//

void	ft_redirect(t_list *data, t_store *store, int i, t_data *a)
{
	int     output;
	t_list  *ptr;

	ptr = data;
	ft_checkinput(data, 0, i);

	if (!(ptr->tatto == 1))
	{
		while (ptr && (ptr->tatto != 1))
		{
			if (ptr->tatto == 4)
				exit (0);
			ptr = ptr->next;
		}
		if (ptr && (ptr->tatto != 1))
			exit (0);
	}

	if (ft_check_builtins(ptr) == 0)
	{
		store->path = ft_getpath(ptr->arg);
		store->arg = ft_arg(ptr);
	}

	if ((output = ft_getfile(data, store, i, data)))
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}

	if (ft_check_builtins(ptr) == 1)
	{
		ft_execute_builtins(ptr,a);
		exit(0);
	}

	execve(store->path, store->arg, a->env22);
	perror("execve");
	exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------------//
