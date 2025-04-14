CC = cc
FLAGS = -Werror -Wextra -Wall
NAME = minishell
SRC = minishell.c parsing.c remove_space.c ./utils/ft_strdup.c ./utils/ft_strldup.c ./utils/ft_split.c ./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_strcmp.c ./utils/ft_strncmp.c ./utils/ft_strchr.c ./utils/ft_strjoinf.c ./cmds/ft_echo.c ./cmds/ft_pwd.c ./cmds/ft_cd.c ./cmds/ft_export.c ./cmds/ft_unset.c ./cmds/ft_env.c ./utils/ft_isspace_to_space.c ./cmds/ft_exit.c ft_atoi.c
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
