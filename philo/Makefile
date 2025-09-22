# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 13:19:44 by zsonie            #+#    #+#              #
#    Updated: 2025/09/22 03:49:43 by zsonie           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
RM = rm -f

INC = -I includes
OBJDIR = obj

SRCS = src/action.c\
		src/error.c\
		src/fork.c\
		src/init.c\
		src/main.c\
		src/philo.c\
		src/monitor.c\
		src/mut.c\
		src/time_utils.c\
		src/utils.c

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(GREEN)Making executable$(RESET)\n"
	@$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIB) -o $(NAME) 

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@printf "$(YELLOW)Converting $(GREEN)$< $(YELLOW)to $(GREEN)$@$(RESET)\n"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)/src

$(OBJS): Makefile

-include $(OBJS:.o=.d)

clean:
	@printf "$(RED)Cleaning $(GREEN)$(OBJDIR) $(RED)dir$(RESET)\n"
	@$(RM) $(OBJS)
	@$(RM) -r $(OBJDIR)

fclean: clean
	@printf "$(RED)Full clean$(RESET)\n"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.DEFAULT_GOAL = all
# COLORS
RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
RESET  = \033[0m