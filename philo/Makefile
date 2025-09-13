# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zsonie <zsonie@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 13:19:44 by zsonie            #+#    #+#              #
#    Updated: 2025/09/13 18:12:34 by zsonie           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = philosopher
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

INC = -I includes
SRCDIR = src
OBJDIR = obj

SRCS = src/action.c\
		src/error.c\
		src/init.c\
		src/main.c\
		src/philo.c\
		src/monitor.c\
		src/utils.c\
		src/utils2.c\

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)Making executable$(RESET)"
	@$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIB) -o $(NAME) 

$(OBJDIR)/%.o: %.c | $(OBJDIR) 
	@echo "$(YELLOW)Converting $(GREEN)$< $(YELLOW)to $(GREEN)$@$(RESET)"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)/src

clean:
	@echo "$(RED)Cleaning $(GREEN)$(OBJDIR) $(RED)dir"
	@$(RM) $(OBJS)
	@$(RM) -r $(OBJDIR)

fclean: clean
	@echo "$(RED)Full clean"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re debug

.DEFAULT_GOAL = all
# COLORS
RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
RESET  = \033[0m