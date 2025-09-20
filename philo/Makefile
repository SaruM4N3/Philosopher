# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 13:19:44 by zsonie            #+#    #+#              #
#    Updated: 2025/09/19 23:59:16 by zsonie           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -f

INC = -I includes
SRCDIR = src
OBJDIR = obj

SRCS = src/action.c\
		src/error.c\
		src/fork.c\
		src/init.c\
		src/main.c\
		src/philo.c\
		src/monitor.c\
		src/mut.c\
		src/utils.c\
		src/utils2.c\

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(GREEN)Making executable$(RESET)\n"
	@$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIB) -o $(NAME) 

$(OBJDIR)/%.o: %.c includes/philo.h includes/error.h | $(OBJDIR)
	@printf "$(YELLOW)Converting $(GREEN)$< $(YELLOW)to $(GREEN)$@$(RESET)\n"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)/src

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