/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rijal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:24:27 by hznagui           #+#    #+#             */
/*   Updated: 2023/04/01 12:35:05 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main() {
    char *input;
    
    while (1)
    {
        input = readline("minishell : ");
        printf("You entered: %s\n", input);
    }
    return 0;
}