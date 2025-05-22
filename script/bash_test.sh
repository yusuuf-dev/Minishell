#!/bin/bash
#rm bash_out.txt
#rm mini_out.txt
#rm mini_out_f.txt
#touch bash_out.txt
#touch mini_out.txt
#touch mini_out_f.txt

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'
#ls >bash_out.txt
#echo "test output" >>bash_out.txt
#ls /somwhere >>bash_out.txt

#valgrind ./minishell < inputs.txt >>mini_out.txt

#for i in inputs.txt
#	read inputs


#./minishell < list_of_commands.txt > minishell_out.txt
#	cat mini_out.txt | sed '/minishell : /d'  >mini_out_f.txt
#	awk -F "bash: " '{print $2}'

# OLD_TEST

export EXP="'this should expand $HOME'"
export Q0='""this should print 2 double quotes""'
export Q1="'"''"'this should print 2 double quotes'"''"'"
export Q2="''this should print 2 single quotes''"
export Q3='"'""'"this should print 2 single quotes"'""'"'
export Q4='this should not expand $HOME'"'$HOME'"'$Q1'
export Q5="this should not expand $SOME_VAR"
export Q6="this_should_not__$HOME-something"

	
while read -r line; do
##	cmd="$line"
##	line="ls"
##	valgrind ./minishell <<< $line &>mini_out.txt
	./minishell <<< $line &>temp/mini_out.txt
	cat temp/mini_out.txt | sed '/minishell : /d'  >temp/mini_out_f.txt
	/bin/bash <<< $line &> temp/bash_out.txt
	if [[ -n $(cmp temp/mini_out_f.txt temp/bash_out.txt) ]]; then
		echo -e "${RED}the outputs are not the same ${NC}$line"
##		exit 1
	else
		echo -e "${GREEN}$(cat temp/mini_out_f.txt)"
	fi
done < tests/inputs.txt
unset EXP Q0 Q1 Q2 Q3 Q4 Q5 Q6

#=========================EXPORT================================
prefix_mini="minishell: "
#suffix=""
prefix_bash="/bin/bash: "
#prefix_bash_line=""
while read -r line; do
	echo "" > temp/mini_out_f.txt
	echo "" > temp/bash_out_f.txt
	echo "" > temp/mini_out_t.txt
	/bin/bash <<< "echo "$line | tr '#' '\n'"" > temp/current_command.txt
	./minishell < temp/current_command.txt 2>&1 | sed '/minishell : /d' &> temp/mini_out.txt
#	cat mini_out_t.txt > mini_out.txt
	while read -r mini; do
		mini_out=${mini#"$prefix_mini"}
		echo "${mini_out}" >> temp/mini_out_f.txt
	done < temp/mini_out.txt
	/bin/bash < temp/current_command.txt &> temp/bash_out.txt
	while read -r bbash; do
		bash_out=${bbash#"$prefix_bash"}
		bash_out_f=${bash_out#line*: }
		echo "${bash_out_f}" >> temp/bash_out_f.txt
	done < temp/bash_out.txt
	if [[ -n $(cmp temp/mini_out_f.txt temp/bash_out_f.txt) ]]; then
		echo -e "${RED}the outputs are not the same, ran:\n"$(cat temp/current_command.txt)""
		#exit 1
	else
		echo -e "====================================================================\n${GREEN}$(cat temp/current_command.txt)"
	fi
## the command will be stored as follows : echo 'export %;echo $?' | tr ';' '\n' > current_command where ';' will be a seperator for each command
## next the bash will read the line and replace each ';' with new line, save it in another file "current_command"
## and then run the bash and minishell based on the current_command file;
## then parse the output, remove the uncesseary stuff, like 'minishell' and 'bash', then cmp the output of both
##

done < tests/list_of_export.txt

while read -r line; do
	echo "" > temp/mini_out_f.txt
	echo "" > temp/bash_out_f.txt
	echo "" > temp/mini_out_t.txt
	/bin/bash <<< "echo "$line | tr '#' '\n'"" > temp/current_command.txt
	./minishell < temp/current_command.txt &> temp/mini_out.txt
	echo "$?" >> temp/mini_out.txt
	cat temp/mini_out.txt | sed '/minishell : /d' > temp/mini_out_t.txt
	cat temp/mini_out_t.txt | sed '/exit/d' > temp/mini_out.txt
	while read -r mini; do
		mini_out=${mini#"$prefix_mini"}
		echo "${mini_out}" >> temp/mini_out_f.txt
	done < temp/mini_out.txt
	/bin/bash < temp/current_command.txt &> temp/bash_out_t.txt
	echo "$?" >> temp/bash_out_t.txt
	cat temp/bash_out_t.txt | sed '/exit/d' > temp/bash_out.txt
	while read -r bbash; do
		bash_out=${bbash#"$prefix_bash"}
		bash_out_f=${bash_out#line*: }
		echo "${bash_out_f}" >> temp/bash_out_f.txt
	done < temp/bash_out.txt
	if [[ -n $(cmp temp/mini_out_f.txt temp/bash_out_f.txt) ]]; then
		echo -e "${RED}the outputs are not the same, ran:\n"$(cat temp/current_command.txt)""
		exit 1
	else
		echo -e "====================================================================\n${GREEN}$(cat temp/current_command.txt)"
	fi
done < tests/list_of_exit.txt
while read -r line; do
	echo "" > temp/mini_out_f.txt
	echo "" > temp/bash_out_f.txt
	/bin/bash <<< "echo "$line | tr '#' '\n'"" > temp/current_command.txt
	./minishell < temp/current_command.txt &> temp/mini_out.txt
	echo "$?" >> temp/mini_out.txt
	cat temp/mini_out.txt | sed '/minishell : /d' > temp/mini_out_t.txt
	while read -r mini; do
		mini_out=${mini#"$prefix_mini"}
		echo "${mini_out}" >> temp/mini_out_f.txt
	done < temp/mini_out_t.txt
	/bin/bash < temp/current_command.txt &> temp/bash_out.txt
	echo "$?" >> temp/bash_out.txt
#	cat bash_out_t.txt | sed '/exit/d' > bash_out.txt
	while read -r bbash; do
		bash_out=${bbash#"$prefix_bash"}
		bash_out_f=${bash_out#line*: }
		echo "${bash_out_f}" >> temp/bash_out_f.txt
	done < temp/bash_out.txt
	if [[ -n $(cmp temp/mini_out_f.txt temp/bash_out_f.txt) ]]; then
		echo -e "${RED}the outputs are not the same, ran:\n"$(cat temp/current_command.txt)""
		exit 1
	else
		echo -e "====================================================================\n${GREEN}$(cat temp/current_command.txt)"
	fi
done < tests/list_of_pipes.txt
#cat mini_out.txt | sed '/minishell : /d'  >mini_out_f.txt
#a = cmp mini_out_f.txt bash_out.txt
#if(a == 0)
#{
#	echo "good"
#}
