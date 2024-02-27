/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:58:51 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/27 15:24:57 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_philo(t_data *data)
{
	t_philo	*philo;
	int		count;

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
		philo[count].must_eat = data->must_eat;
		philo[count].last_eat = get_time();
		count++;
	}
	return (philo);
}

int	giving_data(t_data *data, char **av)
{
	data->someone_died = 0;
	data->start_time = get_time();
	data->philos_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (av[5])
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
	data->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philos_num);
	if (!data->fork)
		return (-1);
	return (init_mutex(data));
}

void	*if_only_one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->fork[philo->fork_right]);
	printing(2, philo);
	ft_sleep(philo->data->time_to_die);
	printf(BRED "%lld Philo has died 💀\n" RESET, (get_time()
			- philo->data->start_time));
	return (NULL);
}
