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