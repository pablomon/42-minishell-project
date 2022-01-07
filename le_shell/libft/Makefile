SRCS		=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
				ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strlcat.c \
				ft_strlcpy.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_isalpha.c \
				ft_isdigit.c ft_isprint.c ft_isascii.c ft_isalnum.c ft_strncmp.c \
				ft_atoi.c ft_tolower.c ft_toupper.c ft_calloc.c ft_substr.c \
				ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_putchar_fd.c \
				ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c \
				ft_isspace.c ft_ischarset.c ft_putstr.c ft_strcmp.c ft_memdel.c \
				ft_atol.c ft_strtok.c ft_strcpy.c ft_strcat.c  ft_strnew.c \
				ft_strncpy.c ft_getline.c ft_strndup.c \

SRCS_BONUS	=	ft_lstadd_front.c ft_lstsize.c ft_lstnew.c ft_lstlast.c \
				ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
				ft_lstmap.c \

OBJS		=	${SRCS:.c=.o}

OBJS_BONUS	=	${SRCS_BONUS:.c=.o}
NAME		=	libft.a
CC			=	gcc
RM			=	rm -f
CFLAGS		= 	-Wall -Werror -Wextra
.c.o:
			${CC} ${FLAGS} -c $< -o ${<:.c=.o}


$(NAME):	${OBJS}
				ar rc ${NAME} ${OBJS}
				ranlib ${NAME}

bonus:		${OBJS} ${OBJS_BONUS}
				ar rc ${NAME} ${OBJS} ${OBJS_BONUS}
				ranlib ${NAME}

all:		${NAME}
clean:
			${RM} ${OBJS}
fclean:		clean
			${RM} ${NAME}

re:			fclean bonus

.PHONY:		bonus all clean fclean re
