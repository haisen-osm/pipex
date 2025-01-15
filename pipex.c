#include "pipex.h"

void exit_hundel()
{
    perror("Error");
    exit(EXIT_FAILURE);
}

int main (int argc, const char *argv[], char *env[])
{
    (void)argv;
    if (argc != 5)
        handle_errors("args not enough", 1);
    int fd[2];
    
    if(pipe(fd) == -1)
    {
        perror("Error:");
        exit(1);
    }
    int id = fork();
    if (id < 0)
    {
        perror("Error:");
        exit(1);
    }
    // char **argv_content = ft_split((char *)argv[2], ' ');
    // char *cmd_path = get_command_path(argv_content[0], env);
    if (id == 0)
    {
        close(fd[0]);
        // if (!argv_content || !argv_content[0])
        //     handle_errors("Invalid command format", 1);
        int file = open(argv[1], O_RDONLY);
        if (file < 0)
            exit_hundel();
        dup2(file, 0);
        dup2(fd[1], 1);
        close(fd[1]);
        execute_cmd((char *)argv[2],env);
        // int ex = execve(cmd_path, argv_content, env);
        // if (ex == -1)
        // {
        //     free_split(argv_content);
        //     free(cmd_path);
        //     exit_hundel();
        // }
    }
    else {
        wait(NULL);
        close(fd[1]);
        // argv_content = ft_split((char *)argv[3], ' ');
        // cmd_path = get_command_path(argv_content[0], env);
        // if (!argv_content || !argv_content[0])
        //     handle_errors("Invalid command format", 1);
        int file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (file < 0)
            exit_hundel();
        dup2(fd[0], 0);
        dup2(file, 1);
        close(fd[0]);
        execute_cmd((char *)argv[3],env);
        // int ex = execve(cmd_path, argv_content, env);
        // if (ex == -1)
        // {
        //     free_split(argv_content);
        //     free(cmd_path);
        //     exit_hundel();
        // }
    }
    // free_split(argv_content);
    // free(cmd_path);
}

void    execute_cmd(char *cmd, char **env)
{  
    char **argv_content;
    char *cmd_path;

    argv_content = ft_split(cmd, ' ');
    if (!argv_content)
        handle_errors("ft_split failed at allocation", 1);
    cmd_path = get_command_path(argv_content[0], env);
    if (!cmd_path)
    {
        free_split(argv_content);
        handle_errors("can't get command path", 1);
    }
    int check_exe_success = execve(cmd_path, argv_content, env);
    if (check_exe_success == -1)
    {
        free_split(argv_content);
        free(cmd_path);
        handle_errors("error while excuting command",1);
    }
}

void    free_split(char **arr)
{
    int i;

    if (arr == NULL)
        return ;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}
int ft_strcmp(char *s1, char *s2)
{
   	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);    
}
char *find_path_env(char **env)
{
    int i  = 0;
    while (env[i])
    {
        char **env_col = ft_split(env[i], '=');
        if (ft_strcmp(env_col[0],"PATH") == 0)
        {
            char *returned_str = ft_strdup(env_col[1]);
            free_split(env_col);
            return (returned_str);
        }
        free_split(env_col);
        i++;
    }
    return (NULL);
    
}

char *get_command_path(char *cmd, char **env)
{
    if (access(cmd, F_OK | X_OK) == 0)
        return (ft_strdup(cmd));
    char *path = find_path_env(env);
    if (!path)
        return NULL;
    char **ft_split_path = ft_split(path, ':');
    free(path);
    if (!ft_split_path)
        return NULL;
    int i = 0;
    while (ft_split_path[i])
    {
        char *new_cmd = ft_strjoin("/", cmd);
        char *cmd_path = ft_strjoin(ft_split_path[i], new_cmd);
        free(new_cmd); 

        if (access(cmd_path, F_OK | X_OK) == 0)
        {
            free_split(ft_split_path); 
            return (cmd_path); 
        }
        free(cmd_path); 
        i++;
    }
    free_split(ft_split_path);
    return NULL;
}

void    handle_errors(char *err, int flag)
{
    write(2, "Error: ", 7);
    write(2, err, ft_strlen(err));
    write(2, "\n", 1);
    if (flag == 1)
    exit(1);
}
