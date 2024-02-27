/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:00:17 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/27 16:37:15 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printing(int n, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (n == 1 && someone_died(philo) == 0)
	{
		printf("%lld %d has taken left fork 🍴 %d\n", (get_time()
				- philo->data->start_time), philo->num_philo, philo->fork_left);
	}
	else if (n == 2 && someone_died(philo) == 0)
	{
		printf("%lld %d has taken right fork 🍴 %d \n", (get_time()
				- philo->data->start_time), philo->num_philo,
			philo->fork_right);
	}
	else if (n == 3 && someone_died(philo) == 0)
	{
		printf(YEL "%lld %d is eating 🥗\n" RESET, (get_time()
				- philo->data->start_time), philo->num_philo);
	}
	continue_printing(n, philo);
}

void	continue_printing(int n, t_philo *philo)
{
	if (n == 4 && someone_died(philo) == 0)
	{
		printf(BLU "%lld %d is sleeping 💤\n" RESET, (get_time()
				- philo->data->start_time), philo->num_philo);
	}
	else if (n == 5 && someone_died(philo) == 0)
	{
		printf(CYN "%lld %d is thinking 💭\n" RESET, (get_time()
				- philo->data->start_time), philo->num_philo);
	}
	else if (n == 6)
		printf(MAG "Everyone has eaten enough! 🥣 \n" RESET);
	pthread_mutex_unlock(&philo->data->print);
}
