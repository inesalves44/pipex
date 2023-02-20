# pipex (42 lvl - 2)

## Overview:

This project is a part of the 42 school common core, level 2.

The objective of this project is to simulate shell pipes in C:

 ```
< input  cmd1 | cmd2 > output
 ```
 
Where input and output represent files and cmd1 and cmd 2 represent shell commands. 

## Mandatory

For the mandatory part you can run it with: 
 ```
make all 
 ```
 
After having the executable you can run it: 

 ```
./pipex input cmd1 cmd2 output
 ```
 
Notes: As in shell you have to have the input file created, the output file will be created if it does not exist. cmd1 and cmd2 are the shell commands. 

This program works with forks and pipes in C.

## Bonus

For the bonus you can run with: 
 ```
make bonus
 ```

The bonus has two parts:

### 1) Multiple pipes

Like this: 

 ```
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
 ```
 
you can run it like: ./pipex input cmd1 cmd2 cmd3 ... cmdn output

### 2) Here doc 
For the second part we have to deal with:

 ```
cmd << LIMITER | cmd1 >> file
 ```
 
This is a command that will prompt you to write input in the terminal and then end when you write only the delimeter.

Example:

 ```
cat << end || sed s/hi/ola/g

cmdor heredoc> hi

cmdor heredoc> hello

cmdor heredoc> ola

cmdor heredoc> hi

cmdor heredoc> end

hi

hello

ola

hi
 ```
you can run it like: 
 ```
$> ./pipex here_doc LIMITER cmd cmd1 file
 ```
 
In the example above the limiter would be end!

## Other Make Commands
 ```
 make clean - clean the objects
 make fclean - clean executable and any library, also runs clean
 make re - runs clean and fclean and then runs all to create the executable
 make rebonus - runs clean and fclean and then runs all to create the executable for bonus
 ```

## Useful Links

[Explaining pipes in C](https://www.youtube.com/watch?v=6xbLgZpOBi8)

Thank you for reading. Any doubts slack me: [idias-al](https://profile.intra.42.fr/users/idias-al).
