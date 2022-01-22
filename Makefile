YELLOW		=	$(shell tput -Txterm setaf 3)
GREEN		=	$(shell tput -Txterm setaf 3)
RED			=	$(shell tput -Txterm setaf 3)

LIBFT		=	libft

NAME		= 	minishell

CC			=	gcc

FLAG		=	-g -Wall -Werror -Wextra -I. -L/usr/include -lreadline -o $(NAME)

SANFLAG		=	-fsanitize=adress

DIR_S		=	src

DIR_O		=	obj

DIR_G		=	gnl

INC			=	inc

SOURCES_C	=	myshell.c myshell_loop.c  my_newprocess.c \
				utils.c pipex.c redirection.c utility.c parser.c \
				expander.c lexer.c noninteractive.c executer.c \
				heredoc.c

SOURCES_G	=	get_next_line.c get_next_line_utils.c \

SRCS		= 	$(addprefix $(DIR_S)/, $(SOURCES_C)) \
				$(addprefix $(DIR_G)/, $(SOURCES_G)) \

OBJS		=	$(SRCS:%.c=%.o)

all:			$(NAME)

$(NAME):		$(OBJS)
				@echo "${YELLOW}... compiling minishell... ${RESET}"
				@make -C $(LIBFT)
				@ar rc $(NAME) $(OBJS)
				@ranlib $(NAME)
				$(CC) $(OBJS) $(FLAG) -L $(LIBFT) ./libft/libft.a

$(DIR_O)/%.o:	$(DIR_S)/%.c $(INC)/minishell.h

fast:			$(OBJS)
				$(CC) $(OBJS) $(FLAG) -L $(LIBFT) ./libft/libft.a

clean:
				make -C $(LIBFT) clean
				rm -f $(OBJS) $(DIR_O)
				@echo "${GREEN} Cleaned ${RESET}"

fclean:			clean
				make -C libft/ fclean
				rm -f $(NAME)
				@echo "${GREEN} fcleaned ... Done!${RESET}"

re:				fclean all
				@echo "${GREEN} ... deleted and recompiled ... Done!${RESET}"
