/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:58:21 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/27 16:48:26 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	if (pthread_mutex_init(&data->died, NULL) != 0)
		return (free_and_destroy(data, NULL, -1));
	if (pthread_mutex_init(&data->to_die, NULL) != 0)
		return (free_and_destroy(data, NULL, -1));
	if (pthread_mutex_init(&data->has_eaten, NULL) != 0)
		return (free_and_destroy(data, NULL, -1));
	return (0);
}

int	create_one_philo(t_data *data, t_philo *philo)
{
	pthread_t	the_philo;

	if (pthread_create(&the_philo, NULL, &if_only_one_philo, philo) != 0)
	{
		printf("Can't create the_philo\n");
		return (free_and_destroy(data, philo, -1));
	}
	pthread_join(the_philo, NULL);
	return (0);
}

int	create_control(t_data *data, t_philo *philo)
{
	pthread_t	control;

	if (pthread_create(&control, NULL, &check_philo, philo) != 0)
	{
		printf("Can't control if someone died\n");
		return (free_and_destroy(data, philo, -1));
	}
	pthread_join(control, NULL);
	return (0);
}

int	ft_create_thread(t_data *data, t_philo *philos)
{
	pthread_t	*threads;
	int			count_threads;

	count_threads = 0;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * data->philos_num);
	if (!threads)
		return (free_and_destroy(data, philos, -1));
	pthread_mutex_lock(&data->start);
	while (data->philos_num > count_threads)
	{
		if (pthread_create(&threads[count_threads], NULL, &routine,
				&philos[count_threads]) != 0)
			return (free_and_destroy(data, philos, -1));
		count_threads++;
	}
	pthread_mutex_unlock(&data->start);
	create_control(data, philos);
	count_threads = 0;
	while (threads[count_threads])
	{
		pthread_join(threads[count_threads], NULL);
		count_threads++;
	}
	free(threads);
	return (0);
}
