CC = cc
FLAGS = -Werror -Wextra -Wall
NAME = minishell
SRC = minishell.c parsing.c remove_space.c ft_split.c ft_strjoin.c ft_strjoinf.c ft_echo.c ft_pwd.c ft_cd.c ft_export.c ft_unset.c ft_env.c
OBJ = $(SRC:.c=.o)

%.o : %.c
	$(CC) $(FLAGS) -g -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -lreadline -g -o $(NAME)

all : $(NAME)

clean : 
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
