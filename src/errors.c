/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:45:10 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/12 10:24:57 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void print_error_exit(char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

int ft_error(int n)
{
	if (n == 1)
		return (1);
	if (n == 2)
	{
		printf("Wrong parameters\n");
		return (2);
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
