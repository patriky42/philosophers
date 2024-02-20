/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:55:35 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/20 13:43:51 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_and_destroy(t_data *data, t_philo *philo, int out)
{
	int	i;

	i = -1;
	if (philo)
		free(philo);
	if (data)
	{
		if (data->fork)
		{
			while (++i < data->philos_num)
				pthread_mutex_destroy(&data->fork[i]);
			free(data->fork);
		}
		pthread_mutex_unlock(&data->print);
		pthread_mutex_destroy(&data->print);
		pthread_mutex_unlock(&data->start);
		pthread_mutex_destroy(&data->start);
		free(data);
	}
	return (out);
}
