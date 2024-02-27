/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:01:42 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/27 17:16:36 by pabastid         ###   ########.fr       */
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

int	all_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->has_eaten);
	if (philo->data->must_eat == philo->n_times_has_eat)
	{
		pthread_mutex_unlock(&philo->data->has_eaten);
		return (EXIT_SUCCESS);
	}
	pthread_mutex_unlock(&philo->data->has_eaten);
	return (EXIT_FAILURE);
}

void	check_if_everyone_has_eaten(t_philo *philo)
{
	printing(6, philo);
	pthread_mutex_lock(&philo->data->print);
	philo->data->someone_died = 1;
	pthread_mutex_unlock(&philo->data->print);
}
