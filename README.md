# Minishell

A simple Unix-like shell project written in C.

---

## Description

Minishell is a minimal shell implementation designed to work on Unix-like operating systems such as Ubuntu. It supports basic shell commands, piping, redirections, and environment variable handling.

---

## Requirements

- Unix-like OS (e.g., Ubuntu, Debian, macOS)  
- GCC or compatible C compiler  
- Make utility  

---

## Installation and Running

### 1. Clone the repository

git clone https://github.com/your-username/Minishell.git
cd Minishell
make
make clean   # to clean env and get executable file

lunch it :
  ./minishell  

  and enjoy use cmds on minishell like bash

example :
minishell> echo Hello World
Hello World
minishell> ls -l > output.txt
minishell> cat output.txt
# Shows the detailed list of files
minishell> ls -l | grep minishell
minishell> exit

