# cShell
A shell written in C

For the OS and networks course

Instructions to use: 
  -> clone the repo
  -> cd to the repository's directory
  -> make
  -> execute ./csh
  
main() resides in cShell.c

the main loop resides in loop.c

cd, echo, pwd, ls reside in their respective .c files.

all the headers are in header.h

The shell prompt includes the username and system name along with the pwd relative to the address the shell runs from (hereafter reffered to as home_dir)

cd works with '.', '..', '~' and ralative/ absolute paths.

ls works with any permutations of the flags -a and -l. It also supports multiple arguments.

pinfo by default gives the process info of the shell.
If an argument is specified it gives process info of the process with the pid of the argument.

nightswatch :
  interrupt - prints the number of times each CPU thread has been interrupted by the keyboard controller, by default in intervals of 1 second. It exits on pressing q.
  newborn - prints the pid of the process most recently created on the system, by default in intervals of 1 second. It exits on pressing q.

history :
  outputs the n latest commands run on the shell. default value of n is 10 and the maximum value is 20.