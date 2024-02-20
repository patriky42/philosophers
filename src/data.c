/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:45:17 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/20 13:43:46 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *str)
{
	int	num;
	int	sign;
	int	i;

	num = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - 48;
		i++;
	}
	return (num * sign);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (free_and_destroy(data, NULL, -1));
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (free_and_destroy(data, NULL, -1));
	if (pthread_mutex_init(&data->start, NULL) != 0)
		return (free_and_destroy(data, NULL, -1));
	return (0);
}

/*Esta funccion da a cada philo la info de comer, ddrmir, etc...*/
int	giving_data(t_data *data, char **argv)
{
	data->someone_died = 0;
	data->start_time = get_time();
	data->philos_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philos_num);
	if (!data->fork)
		return (-1);
	return (init_mutex(data));
}
