/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:00:45 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/27 17:30:06 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	someone_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->died);
	if (philo->data->someone_died == 0)
	{
		pthread_mutex_unlock(&philo->data->died);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->died);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num_philo % 2 == 0)
		usleep(1000);
	while (someone_died(philo) == 0)
	{
		is_eating(philo);
		pthread_mutex_lock(&philo->data->start);
		printing(4, philo);
		pthread_mutex_unlock(&philo->data->start);
		ft_sleep(philo->data->time_sleep);
		pthread_mutex_lock(&philo->data->start);
		printing(5, philo);
		pthread_mutex_unlock(&philo->data->start);
		if (philo->must_eat > 0 && (all_eaten(philo) == EXIT_SUCCESS))
			break ;
	}
	return (NULL);
}

void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->fork_left]);
	printing(1, philo);
	pthread_mutex_lock(&philo->data->fork[philo->fork_right]);
	printing(2, philo);
	printing(3, philo);
	ft_sleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->to_die);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->data->to_die);
	pthread_mutex_lock(&philo->data->has_eaten);
	philo->n_times_has_eat++;
	pthread_mutex_unlock(&philo->data->has_eaten);
	pthread_mutex_unlock(&philo->data->fork[philo->fork_left]);
	pthread_mutex_unlock(&philo->data->fork[philo->fork_right]);
}

int	check_if_someone_is_dead(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->data->to_die);
	if (time_dif(get_time(), philo[i].last_eat) > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->to_die);
		if (philo->must_eat != philo->n_times_has_eat)
		{
			pthread_mutex_lock(&philo->data->print);
			printf(BRED "%lld Philo %d has died 💀\n" RESET, (get_time()
					- philo->data->start_time), (i + 1));
			pthread_mutex_unlock(&philo->data->print);
		}
		pthread_mutex_lock(&philo->data->died);
		philo->data->someone_died = 1;
		pthread_mutex_unlock(&philo->data->died);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->to_die);
	return (0);
}

void	*check_philo(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (someone_died(philo) == 0)
	{
		i = -1;
		while (++i < philo->data->philos_num)
		{
			if (check_if_someone_is_dead(philo, i) == 1)
				break ;
		}
		usleep(100);
	}
	i = 0;
	while (i < philo->data->philos_num)
	{
		if (all_eaten(philo) == EXIT_SUCCESS)
			i++;
		else
			break ;
	}
	if (i == philo->data->philos_num)
		printing(6, philo);
	return (NULL);
}
