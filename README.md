# minishell

Minishell is a project where a team of 2 people have to recreate certain features from bash.


pouet

## Idée pour parser:
Save each command (separated by ';' or '|') in a link list.

The following process will be applied to each command:
	1. split by ' ', '<', '>' and '>>'
	2. parse the command and it's arguments
	3. if '<' after or '|' before => launch program with stdin filled in.
		- *Priority to '<' over '|'
	4. else launch the program
	5. if '|', '>' or '>>' after, save the stdout for the next program
	6. else print stdout
