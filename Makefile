# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 12:15:51 by pabastid          #+#    #+#              #
#    Updated: 2024/02/10 12:31:10 by pabastid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME := philo
SRC :=  src/parsing.c src/errors.c src/data.c src/time_control.c\
src/free_and_destroy.c src/create.c src/printing.c\
main.c 
OBJ := $(SRC:.c=.o)
DEP := $(SRC:.c=.d)CFLAGS := -Wall -Werror -Wextra -g -MMD -fsanitize='address,undefined'
CC := gcc
CFLAGS := -Wall -Werror -Wextra -g -MMD -pthread
RM := rm -rf
LIBS := -lpthread 
HEADER := inc/
INCLUDE := -I $(HEADER)

###################
#COLORS

COLOR_RESET = \033[0m
COLOR_BOLD = \033[1m
COLOR_UNDERLINE = \033[4m
COLOR_RED = \033[31m
COLOR_GREEN = \033[32m
COLOR_YELLOW = \033[33m
COLOR_BLUE = \033[34m
COLOR_MAGENTA = \033[35m
COLOR_CYAN = \033[36m

###################


$(BUILD_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all: $(OBJ)
	@$(MAKE) $(NAME)

$(LIBS):
	@$(MAKE) -C libftprintf

-include $(DEP)
$(NAME): $(LIBS) $(OBJ) Makefile
	@$(CC) $(CFLAGS) $(LIBPATH) $(OBJ) -o $(NAME)
	@echo "$(COLOR_BOLD)$(COLOR_GREEN)... 🤩 philosophers compiled  ... $(COLOR_RESET)"

clean:
	$(RM) $(OBJ)
	$(RM) $(DEP)

fclean:
	$(MAKE) clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus