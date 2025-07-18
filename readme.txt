how to use ft_malloc

call ft_malloc with size to malloc it will return malloced size
if failed it  will free prevoius malloc if exist exit

call void config_malloc(void *ptr, int isfailed) function to free all malloced but use parameter NULL on ptr and 0 on isfailed

new update 30/06/2025 functions :

c_split ( refactor for norminette )
check_syntax ( refactor for norminette )
found_pipe ( refactor for norminette  and remove check for error already exist on check_syntax )
heredoc_delimiter ( refactor for norminette )


new update 08/07/2025 :

change logic of c_split for data->args in parsing from (split -> expande) to (expande -> split)
but we back to first logic if we found later cmd built in (export) then back (split -> expande)
add new export function - new split 




new update 09/07/2025 :

after new logic of split add this check in parsing
on line @147
static  int executable(t_data *data)

	int is_a_file = 0;

	if (!data->rdl_args || !data->rdl_args[0])
		return (1);

cuz found error on test minishell : ""

change logic of c_split and rm_quotes_expand to handle this cases like bash :

export a="test0               test1                  test2"
echo $HOME$a$HOME"$a"$HOME
output : /home/yoel-youtest0 test1 test2/home/yoel-youtest0               test1                  test2/home/yoel-you

minishell : export a="          ls         -l         "
minishell : $a
total 188
drwxr-xr-x 2 yoel-you 2024_rabat    242 Jul  9 16:58 cmds
drwxr-xr-x 2 yoel-you 2024_rabat   4096 Jul  9 17:31 costum_utils
-rw-r--r-- 1 yoel-you 2024_rabat   2964 Jul  9 15:54 Makefile
-rwxr-xr-x 1 yoel-you 2024_rabat 122776 Jul  9 17:31 minishell
-rw-r--r-- 1 yoel-you 2024_rabat   6305 Jul  9 15:54 minishell.c
-rw-r--r-- 1 yoel-you 2024_rabat   4028 Jul  9 17:05 minishell.h
-rw-r--r-- 1 yoel-you 2024_rabat  12160 Jul  9 16:58 minishell.o
-rw-r--r-- 1 yoel-you 2024_rabat   7347 Jul  9 15:54 parsing.c
-rw-r--r-- 1 yoel-you 2024_rabat  18752 Jul  9 16:58 parsing.o
-rw-r--r-- 1 yoel-you 2024_rabat    756 Jul  9 15:54 readme.txt
drwxr-xr-x 2 yoel-you 2024_rabat   4096 Jul  9 16:58 utils
minishell : "$a"
          ls         -l         : command not found


slove this :
export a="1       '        2  3'"
		
		
minishell : export a="hell'o"
minishell : echo $a
Segmentation fault (core dumped)

13/07/2025

fix echo $jjjj test fixed (done)

jjjj dosn't exist


fix this : fixed (done)
minishell : echo '$jjjj         heloo'"$dsfsdvsdv" $HOME
$jjjj heloo /home/yoel-youOME


tests need some fix :fixed (done)
95
111 expand ? doesn't fixed yet
128 echo $USER$var\$USER$USER\$USERtest$USER 


fix this : fixed (done)
yoel-you@c1r7p1:~$ echo $?
0
yoel-you@c1r7p1:~$ echo $?$?
00
yoel-you@c1r7p1:~$ echo $?$?$?
000
yoel-you@c1r7p1:~$ echo $?$?$?
000
yoel-you@c1r7p1:~$ sdgfdag
sdgfdag: command not found
yoel-you@c1r7p1:~$ echo $?$?$?
127127127
===================================================
- ayoub 15_07 modified/added the following files:

	modified:   Makefile
	modified:   TO_DO
	modified:   cmds/ft_cd.c
	modified:   cmds/ft_export.c
	modified:   cmds/ft_pwd.c
	modified:   costum_utils/ft_pipes.c
	modified:   minishell.c
	modified:   minishell.h
	modified:   parsing.c
	added   :   costum_utils/ft_getenv.c
===================================================
- ayoub 17_07 modified/added the following files:

	modified:   cmds/ft_unset.c
	modified:   costum_utils/ft_getenv.c
	modified:   costum_utils/ft_isheredoc.c
	modified:   costum_utils/ft_putstr.c
	modified:   costum_utils/ft_setup.c
	modified:   minishell.c
	modified:   minishell.h
	modified:   parsing.c
	costum_utils/ft_free.c
	costum_utils/ft_read_line_gnl.c
	utils/ft_itoa.c
	utils/ft_strcpy.c
====================================================
- ayoub 17_07 modified/added the following files:
	modified:   Makefile
	modified:   cmds/ft_export.c
	modified:   cmds/ft_unset.c
	modified:   costum_utils/ft_all_redirections.c
	modified:   costum_utils/ft_duplicate.c
	modified:   costum_utils/ft_free.c
	modified:   costum_utils/ft_isheredoc.c
	modified:   minishell.c
	modified:   minishell.h
	Added   : costum_utils/ft_strdup_env.c
- Ayoub 18_07 modified added the following files:
	modified:   Makefile
	modified:   costum_utils/custom_split.c
	deleted:    costum_utils/ft_isheredoc.c
	modified:   costum_utils/ft_pipes.c
	modified:   minishell.h
	Added   :  
		costum_utils/ft_here_doc.c
	costum_utils/ft_here_doc_utils.c
	costum_utils/t_heredoc.c
