# CC = cc
# FLAGS = -Werror -Wextra -Wall
# NAME = minishell
# SRC = minishell.c parsing.c ./utils/ft_calloc.c ./costum_utils/ft_putstr.c ./costum_utils/ft_check_spaces.c \
# ./costum_utils/ft_duplicate.c ./utils/ft_strdup.c ./utils/ft_strldup.c ./utils/ft_split.c ./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_strcmp.c \
# ./utils/ft_strncmp.c ./utils/ft_strchr.c ./costum_utils/ft_strjoin.c ./cmds/ft_echo.c ./cmds/ft_pwd.c ./cmds/ft_cd.c ./cmds/ft_export.c ./cmds/ft_unset.c \
# ./cmds/ft_env.c ./costum_utils/ft_isspace_to_space.c ./cmds/ft_exit.c ./costum_utils/skip_quotes_split.c ./costum_utils/custom_atoi.c \
# ./costum_utils/heredoc_delimiter.c ./costum_utils/found_pipe.c ./costum_utils/ft_here_doc.c ./costum_utils/rm_quotes_expand.c \
# ./costum_utils/rm_quotes.c ./utils/ft_isalnum.c ./utils/ft_isalpha.c ./costum_utils/c_atoi.c ./costum_utils/ft_all_redirections.c ./costum_utils/ft_pipes.c \
# ./costum_utils/ft_setup.c ./costum_utils/ft_malloc.c ./utils/ft_memset.c ./costum_utils/signals_handler.c ./costum_utils/check_syntax.c

# OBJ = $(SRC:.c=.o)

# %.o : %.c
# 	$(CC) $(FLAGS) -g -c $< -o $@

# $(NAME) : $(OBJ)
# 	$(CC) $(FLAGS) $(OBJ) -lreadline -g -o $(NAME)
# #	$(CC) $(FLAGS) $(OBJ) -lreadline -fsanitize=address -O1 -fno-omit-frame-pointer -g -o $(NAME)

# all : $(NAME)

# clean : 
# 	rm -f $(OBJ)

# fclean : clean
# 	rm -f $(NAME)

# re : fclean all

# .PHONY : all clean fclean re


CC = cc
FLAGS = -Werror -Wextra -Wall -g
NAME = minishell
SRC = minishell.c parsing.c ./utils/ft_calloc.c ./costum_utils/ft_putstr.c ./costum_utils/ft_check_spaces.c ./utils/ft_substr.c \
./costum_utils/ft_duplicate.c ./utils/ft_strdup.c ./utils/ft_strldup.c ./utils/ft_split.c ./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_strcmp.c \
./utils/ft_strncmp.c ./utils/ft_strchr.c ./cmds/ft_echo.c ./cmds/ft_pwd.c ./cmds/ft_cd.c ./cmds/ft_export.c ./cmds/ft_unset.c \
./cmds/ft_env.c ./costum_utils/ft_isspace_to_space.c ./cmds/ft_exit.c ./costum_utils/skip_quotes_split.c ./costum_utils/redirections_parsing_utils.c \
./costum_utils/heredoc_delimiter.c ./costum_utils/found_pipe.c ./costum_utils/ft_here_doc.c ./costum_utils/ft_strdup_env.c ./costum_utils/t_heredoc.c \
./utils/ft_isalnum.c ./utils/ft_isalpha.c ./costum_utils/utils_atoi.c ./costum_utils/ft_pipes.c ./costum_utils/found_quotes.c \
./costum_utils/ft_setup.c ./costum_utils/ft_malloc.c ./utils/ft_memset.c ./costum_utils/signals_handler.c ./costum_utils/check_syntax.c ./utils/ft_get_next_line.c \
./costum_utils/custom_split.c ./costum_utils/custom_split_utils.c ./costum_utils/ft_getenv.c ./costum_utils/ft_free.c ./costum_utils/ft_here_doc_utils.c \
./costum_utils/ft_read_line_gnl.c ./utils/ft_itoa.c ./utils/ft_strcpy.c ./costum_utils/c_strncmp.c ./costum_utils/ft_malloc_utils.c ./costum_utils/redirections_parsing.c \
./costum_utils/redirections_execution.c

OBJ = $(SRC:.c=.o)

READLINE_INCLUDE = -I/usr/local/opt/readline/include
READLINE_LIB = -L/usr/local/opt/readline/lib -lreadline

%.o : %.c
	$(CC) $(FLAGS) $(READLINE_INCLUDE) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(READLINE_LIB) -o $(NAME)

all : $(NAME)

clean : 
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
