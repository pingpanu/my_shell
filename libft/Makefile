# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pingpanu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/05 23:00:53 by pingpanu          #+#    #+#              #
#    Updated: 2022/03/05 23:13:10 by pingpanu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

SRC = ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
      ft_atoi.c ft_strncmp.c ft_strchr.c ft_strrchr.c ft_strlen.c ft_strlcat.c ft_strlcpy.c \
      ft_strnstr.c ft_strdup.c ft_memcmp.c ft_memset.c ft_memcpy.c ft_memchr.c ft_memmove.c \
      ft_bzero.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_split.c \
      ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	ft_lstclear.c ft_lstiter.c ft_lstmap.c \

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(BONUS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	@ echo "compile library libft.a"
	@ ar rc $(NAME) $^
	@ echo "done"

%.o : %.c
	@ gcc -c $(FLAGS) $^ -I ./

bonus : $(OBJ) $(OBJ_BONUS)
	@ echo "compile library libft.a with bonus"
	@ ar rc $(NAME) $^ $^
	@ echo "done"

.PHONY : all bonus clean fclean re rebonus

clean :
	rm -f *.o

fclean : clean
	rm -f $(NAME)

re : fclean all

rebonus : fclean bonus
