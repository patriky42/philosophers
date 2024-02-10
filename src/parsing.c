/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:15:53 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/10 11:15:43 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int is_digit(char **argv)
{
	int i;
	int j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (2);
			j++;
		}
		i++;
	}
	return (0);
}

int check_errors(char **argv)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '0' && !argv[i][1])
		{
			ft_error(2);
			return (2);
		}
		if (is_digit(argv) != 0)
		{
			ft_error(2);
			return (2);
		}
		i++;
	}
	return (0);
}
