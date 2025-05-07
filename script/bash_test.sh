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
export EXP="'this should expand $HOME'"
export Q0='""this should print 2 double quotes""'
export Q1="'"''"'this should print 2 double quotes'"''"'"
export Q2="''this should print 2 single quotes''"
export Q3='"'""'"this should print 2 single quotes"'""'"'
export Q4='this should not expand $HOME'"'$HOME'"'$Q1'
export Q5="this should not expand $SOME_VAR"
export Q6="this_should_not__$HOME-something"

while read -r line; do
#	cmd="$line"
#	line="ls"
#	valgrind ./minishell <<< $line &>mini_out.txt
	./minishell <<< $line &>mini_out.txt
	cat mini_out.txt | sed '/minishell : /d'  >mini_out_f.txt
	/bin/bash <<< $line &> bash_out.txt
	if [[ -n $(cmp mini_out_f.txt bash_out.txt) ]]; then
		echo -e "${RED}the outputs are not the same ${NC}$line"
#		exit 1
	else
		echo -e "${GREEN}$(cat mini_out_f.txt)"
	fi
done < inputs.txt
#cat mini_out.txt | sed '/minishell : /d'  >mini_out_f.txt
#a = cmp mini_out_f.txt bash_out.txt
#if(a == 0)
#{
#	echo "good"
#}
