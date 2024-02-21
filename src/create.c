/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:18:50 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/21 14:23:49 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// TODO: no debeeria en esta funcion crear los pthreads de cada philo?
t_philo	*create_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = ft_calloc((data->philos_num), sizeof(t_philo));
	if (!philo)
		exit(1);
	while (i < data->philos_num)
	{
		philo[i].num_philo = i + 1;
		philo[i].fork_left = i;
		philo[i].fork_right = i + 1;
		if (i + 1 == data->philos_num)
			philo[i].fork_right = 0;
		philo[i].data = data;
		philo[i].last_eat = get_time();
		i++;
	}
	return (philo);
}

void	*if_only_one_philo(void *argv)
{
	t_philo	*philo;

	philo = (t_philo *)argv;
	pthread_mutex_lock(&philo->data->fork[philo->fork_right]);
	printing(2, philo);
	ft_sleep(philo->data->time_to_die);
	// TODO: porque lo pone a dormir seguro
	printf(BRED "%lld Philo has died 💀\n" RESET,
			(get_time() // TODO: cuando printea esto?
			- philo->data->start_time));
	return (NULL);
}

int	create_one_philo(t_data *data, t_philo *philo)
{
	pthread_t	the_philo;

	if (pthread_create(&the_philo, NULL, &if_only_one_philo, philo) != 0)
	{
		printf("Can't create the philo\n");
		return (free_and_destroy(data, philo, 0));
	}
	pthread_join(the_philo, NULL);
	return (0);
}

static void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->fork_left]);
	printing(1, philo);
	pthread_mutex_lock(&philo->data->fork[philo->fork_right]);
	printing(2, philo);
	printing(3, philo);
	ft_sleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->start);
	philo->last_eat = get_time();
	philo->n_times_has_eat++;
	pthread_mutex_unlock(&philo->data->start);
	pthread_mutex_unlock(&philo->data->fork[philo->fork_left]);
	pthread_mutex_unlock(&philo->data->fork[philo->fork_right]);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num_philo % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(&philo->data->start);
	while (philo->data->someone_died == 0)
	{
		pthread_mutex_unlock(&philo->data->start);
		is_eating(philo);
		printing(4, philo);
		ft_sleep(philo->data->time_sleep);
		printing(5, philo);
		pthread_mutex_lock(&philo->data->start);
		if (philo->data->must_eat)
			if (philo->data->must_eat == philo->n_times_has_eat)
				break ;
	}
	pthread_mutex_unlock(&philo->data->start);
	return (NULL);
}

int	ft_create_thread(t_data *data, t_philo *philos)
{
	pthread_t	*threads;
	int			count_threads;

	count_threads = 0;
	threads = ft_calloc((data->philos_num), sizeof(pthread_t));
	if (!threads)
		return (free_and_destroy(data, philos, 0));
	pthread_mutex_lock(&data->start);
	while (data->philos_num > count_threads)
	{
		if (pthread_create(&threads[count_threads], NULL, &routine,
				&philos[count_threads]) != 0)
			return (free_and_destroy(data, philos, 0));
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
