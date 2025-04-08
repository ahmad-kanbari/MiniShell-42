# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/29 04:32:19 by akanbari          #+#    #+#              #
#    Updated: 2024/02/04 17:00:33 by mhaile           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			minishell

FILES	= 		main.c utils2.c utils.c general_utils.c clean.c \
		  		signals/signals.c signals/signals2.c \
				validating/tokens_utils.c validating/init_valid_line.c \
				env/env_utils.c env/env_utils2.c env/env_utils3.c env/env_lst.c \
				validating/valid_utils2.c validating/validate_syntax.c \
				parsing/bin.c parsing/commands.c parsing/parse_tokens.c parsing/parsing_comands.c \
				parsing/tokens1_utils.c parsing/tokens2_utils.c parsing/quotes.c \
				parsing/no_quotes.c parsing/double_quotes.c parsing/replace_env.c \
				exec/exec_commands.c exec/execution.c exec/exec_utils.c exec/exec_cmd_utils.c\
				exec/process_args.c exec/exec_redirect.c exec/redirect_utils.c \
				builtin/echo.c builtin/env.c builtin/pwd.c builtin/cd.c builtin/cd_utils.c \
				builtin/export.c builtin/export_utils.c builtin/unset.c builtin/exit.c \
				
# Colors:
GREEN		=	\e[92;5;118m
GRAY		=	\e[33;2;37m
RED         =   \e[91m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m

SRCS_FOLDER = 	src

SRCS =			$(addprefix $(SRCS_FOLDER)/, $(FILES))
OBJS =			$(SRCS:.c=.o)

HEADER = 		-I include

LIBFT =			./libft/libft.a

CC = 			cc

CFLAGS =		-Wall -Wextra -Werror -g3  -I /usr/local/opt/readline/include 
LINKS =			-lreadline -L /usr/local/opt/readline/lib
LINKS2 =		 -I .brew/opt/readline/include 
RM =			rm -rf

all: 			$(NAME)

%.o: %.c
				@printf "$(CURSIVE)$(GRAY)	~ Making object file $(notdir $@) from source file $(notdir $<) ... $(RESET)\n"
				@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):  		$(OBJS)
				@${MAKE} -C ./libft
				@printf "$(CURSIVE)$(GRAY) 	- Compiling $(NAME)... $(RESET)\n"
		 		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LINKS) -o $(NAME) $(LINKS2)
				@printf "$(GREEN)    - Minishell Executable ready.\n$(RESET)"

clean:
				@${MAKE} clean -C ./libft
				@${RM} ${OBJS} ${OBJS_BONUS}
				@printf "$(CURSIVE)$(GRAY)	- Removing object files ... $(RESET)\n"
				@printf "$(RED)    - Object files removed.$(RESET)\n"

fclean: 		clean
				@${RM} ${NAME}
				@${MAKE} fclean -C ./libft
				@printf "$(CURSIVE)$(GRAY)	- Removing $(NAME)... $(RESET)\n"
				@printf "$(RED)    - Executable & Archives removed.$(RESET)\n"

re: 			fclean all
				@printf "$(CURSIVE)$(GRAY)	- Remaking $(NAME)... $(RESET)\n"
				
rebonus: 		fclean bonus

.PHONY: 		all clean fclean re
