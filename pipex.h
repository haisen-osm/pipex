#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t ft_strlen(const char *str);
char    *ft_strdup(const char *str);
char *ft_strjoin(char *s1, char *s2);
void    free_split(char **arr);
int ft_strcmp(char *s1, char *s2);
char *find_path_env(char **env);
char *get_command_path(char *cmd, char **env);
void    handle_errors(char *err, int flag);
void    execute_cmd(char *cmd, char **env);

#endif