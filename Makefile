# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/13 16:24:40 by aennaqad          #+#    #+#              #
#    Updated: 2024/10/05 14:22:51 by mes-salh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS =  -Wall -Werror -Wextra #-fsanitize=address -g
RM = rm -rf
SRCS = 	parsing/syntaxe_cheks/utils_libft.c \
			parsing/syntaxe_cheks/utils_libft_two.c \
			parsing/syntaxe_cheks/check_parser.c \
			minishell.c \
			parsing/garbage_col.c\
			parsing/heredoc/handle_heredoc.c \
			parsing/heredoc/utils_herdoc.c \
			parsing/Parser/cmd_tools.c \
			parsing/Parser/new_parser.c \
			parsing/Parser/utilsParser.c  \
			parsing/Parser/parser.c \
			parsing/Parser/parser_tools.c \
			parsing/Parser/tokens_tools.c \
			parsing/Parser/utillsTwoParser.c \
			parsing/Lexer/to_tokens.c \
			parsing/Lexer/toknizer.c \
			parsing/Expender/utils_expander.c \
 			parsing/Expender/expanding.c \
			parsing/f_parsing.c \
			parsing/signals_handle/signals_minishell.c \
			execution/built-in/built_in.c execution/built-in/helpers.c\
			execution/built-in/pwd.c \
			execution/built-in/cd.c execution/built-in/helpers1.c execution/built-in/helpers3.c \
			execution/built-in/helpers2.c execution/built-in/env.c execution/built-in/echo.c \
			execution/built-in/export.c execution/built-in/unset.c execution/built-in/exit.c \
			execution/exec/exec.c execution/exec/helpers.c execution/exec/pipex.c execution/exec/helpers2.c execution/execution.c \
			execution/exec/redir.c execution/exec/helpers3.c execution/exec/safe_syscall.c  execution/built-in/export2.c execution/tools.c \
			execution/built-in/export_tools.c execution/exec/helpers4.c execution/built-in/ft_atoi.c execution/built-in/export_utils.c

OBJS = $(SRCS:.c=.o)

READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include

NAME = minishell
H_MOND = minishell.h

%.o: %.c $(H_MOND)
	$(CC) $(CFLAGS) -I ${READLINE_I} -c $< -o $@


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L ${READLINE_L} -lreadline -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re go
