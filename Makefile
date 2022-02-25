YELLOW		=	$(shell tput -Txterm setaf 3)
GREEN		=	$(shell tput -Txterm setaf 2)
BLUE		=	$(shell tput -Txterm setaf 4)
RESET		=	$(shell tput -Txterm sgr0)

DIR_LIBFT	=	libft

NAME		= 	minishell

CC			=	gcc

#vmware
#RL_FLAG		=	-L/Users/$(USER)/homebrew/opt/readline/lib -I/Users/$(USER)/homebrew/opt/readline/include

#Leo42
#RL_FLAG		=	-L /usr/local/Cellar/readline/8.1.2/lib -I /usr/local/Cellar/readline/8.1.2/include

#pablo42
RL_FLAG		=	-L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include


SAN_FLAG	=	#-fsanitize=address -fdiagnostics-color=always
DEBUG_FLAG	=	-g3# -O0

FLAG		=	$(RL_FLAG) $(SAN_FLAG) $(DEBUG_FLAG) -Wall -Werror -Wextra -I. -L/usr/include -lreadline -o $(NAME)

DIR_S		=	src
INC			=	inc

SOURCES_C	=	myshell.c \
				myshell_loop.c \
				utils.c \
				utils2.c \
				utils3.c \
				parser.c \
				parser_tools.c \
				expander.c \
				lexer.c \
				executer.c \
				heredoc.c \
				builtins1.c \
				builtins2.c \
				builtins3.c \
				environment.c \
				environment2.c \
				signals.c \
				export.c \
				cleanup.c \
				tokenizer.c \
				tokenizer_rules.c \
				tokenizer_rules2.c \
				error.c \
				echo.c \
				init_params.c \
				exec_aux.c \
				redir.c

SRCS		= 	$(addprefix $(DIR_S)/, $(SOURCES_C)) \

OBJS		=	$(SRCS:%.c=%.o)

all:			$(NAME)

$(NAME):		$(OBJS) inc/myshell.h
				@echo "${YELLOW}... compiling libft... ${RESET}"
				@make -C $(DIR_LIBFT)
				@echo "${YELLOW}... compiling minishell... ${RESET}"
				$(CC) $(OBJS) $(FLAG) -L $(DIR_LIBFT) $(DIR_LIBFT)/libft.a
				@echo "${GREEN}DONE ${RESET}"

$(DIR_O)/%.o:	$(DIR_S)/%.c $(INC)/minishell.h

run:			$(NAME)
				./minishell

clean:
				make -C $(DIR_LIBFT) clean
				rm -f $(OBJS) $(DIR_O)
				@echo "${GREEN} Cleaned ${RESET}"

fclean:			clean
				make -C $(DIR_LIBFT) fclean
				rm -f $(NAME)
				@echo "${GREEN} fcleaned ... Done!${RESET}"

re:				fclean all
				@echo "${GREEN} ... deleted and recompiled ... Done!${RESET}"
