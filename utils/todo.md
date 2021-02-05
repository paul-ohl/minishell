Leaks on ctrl+D
Leaks on redirections :(
Crash when exit is not alone (ex: echo bonjour; exit)


# Parser rework
- Écrire la [grammaire du parser](https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/utilities/V3_chap02.html)
- Séparer lexer et parser
- Organiser le parser avec un binary tree comme dans [cet exemple](https://www.gaudry.be/langages-analyse-syntaxique-ast.html#docStruct)

# Errors
- Return 127 when command not found
- Reset to 0 when command success

# Other work needed
- recoder [Les fonctions d'environnement](https://www.gnu.org/software/libc/manual/html_node/Environment-Access.html)
