/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 09:54:18 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/10 12:22:47 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
	t_data *data;
	t_philo *philo;

	if (5 == argc || 6 == argc)
	{
		if (check_errors(argv) != 0)
			return (-1);
		data = (t_data *)malloc(sizeof(t_data)); // TODO: no protegemos este Malloc?
		if (giving_data(data, argv) != 0)
			return (free_and_destroy(data, NULL, -1));
		philo = create_philo(data);
		if (!philo)
			return (free_and_destroy(data, philo, -1));
		if (ft_atoi(argv[1]) == 1)
			create_one_philo(data, philo);
	}
	else
	{
		/*error_exit("Wrong input:\n" G "✅ ./philo 5 800 200 200 [7] ✅\n"
				   "      t_die t_eat t_sleep [meals_limit]" RST);*/
		ft_error(2);
		return (2);
	}
	return (0);
}

/*NAME := philo
SRC := src/parsing.c src/errors.c src/data.c src/time_control.c\
src/free_and_destroy.c src/create.c src/printing.c\
main.c
OBJ := $(SRC:.c=.o)
DEP := $(SRC:.c=.d)
CC := gcc
CFLAGS := -Wall -Werror -Wextra -g -MMD -pthread
RM := rm -rf
LIBS := -lpthread
HEADER := inc/
INCLUDE := -I $(HEADER)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all: $(OBJ)
	$(MAKE) $(NAME)

-include $(DEP)
$(NAME): $(OBJ) Makefile
	$(CC) $(CFLAGS) $(LIBS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(DEP)

fclean:
	$(MAKE) clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus*/
