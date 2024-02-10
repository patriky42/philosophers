/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:18:50 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/10 12:12:18 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo *create_philo(t_data *data)
{
	t_philo *philo;
	int count;

	count = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * data->philos_num);
	if (!philo)
		return (NULL);
	while (count < data->philos_num)
	{
		philo[count].num_philo = count + 1;
		philo[count].fork_left = count;
		philo[count].fork_right = count + 1;
		if (count + 1 == data->philos_num)
			philo[count].fork_right = 0;
		philo[count].data = data;
		philo[count].last_eat = get_time();
		count++;
	}
	return (philo);
}

void *if_only_one_philo(void *argv)
{
	t_philo *philo;

	philo = (t_philo *)argv;
	pthread_mutex_lock(&philo->data->fork[philo->fork_right]);
	printing(2, philo);
	ft_sleep(philo->data->time_to_die);
	printf(BRED "%lld Philo has died 💀\n" RESET,
		   (get_time() - philo->data->start_time));
	return (NULL);
}

int create_one_philo(t_data *data, t_philo *philo)
{
	pthread_t the_philo;

	if (pthread_create(&the_philo, NULL, &if_only_one_philo, philo) != 0)
	{
		printf("Can't create the philo\n");
		return (free_and_destroy(data, philo, -1));
	}
	pthread_join(the_philo, NULL);
	return (0);
}
