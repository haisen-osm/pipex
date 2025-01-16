#include "pipex.h"

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
    int i;
    char **env_col;
    char *returned_str;

    i = 0;
    while (env[i])
    {
        env_col = ft_split(env[i], '=');
        if (!env_col)
            return (NULL);
        if (env_col[0] && ft_strcmp(env_col[0], "PATH") == 0)
        {
            returned_str = ft_strdup(env_col[1]);
            free_split(env_col);
            return (returned_str);
        }
        free_split(env_col);
        i++;
    }
    return (NULL);
}

static char	*try_path(char **path_dirs, char *cmd)
{
    char	*new_cmd;
    char	*cmd_path;
    int		i;

    i = 0;
    while (path_dirs[i])
    {
        new_cmd = ft_strjoin("/", cmd);
        cmd_path = ft_strjoin(path_dirs[i], new_cmd);
        free(new_cmd);
        if (access(cmd_path, F_OK | X_OK) == 0)
        {
            free_split(path_dirs);
            return (cmd_path);
        }
        free(cmd_path);
        i++;
    }
    return (NULL);
}
char *check_command_existence(char *cmd)
{
    // size_t i = 0;
    
    if (cmd[0] == '/')
    {
        // while (cmd[i] == '/')
        //     i++;
        //         if (i > 1)
            return NULL;
    }
    return (char *)cmd;
}
char *get_command_path(char *cmd, char **env)
{
    char *path;
    char **path_dirs;
    char *cmd_path;

    if (access(cmd, F_OK | X_OK) == 0)
        return (ft_strdup(cmd));
    if (check_command_existence(cmd) == NULL)
        return (NULL);
    path = find_path_env(env);
    if (!path)
        return (NULL);
    path_dirs = ft_split(path, ':');
    free(path);
    if (!path_dirs)
        return (NULL);
    cmd_path = try_path(path_dirs, cmd);
    if (!cmd_path)
        free_split(path_dirs);
    return (cmd_path);
}

static void	cleanup_and_exit(char *error_msg, int exit_code)
{
    if (error_msg)
    {
        write(STDERR_FILENO, "Error: ", 7);
        write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
        write(STDERR_FILENO, "\n", 1);
    }
    exit(exit_code);
}

static void	child_process(int *fd, const char *infile, const char *cmd, char **env)
{
    int	file;

    close(fd[0]);
    file = open(infile, O_RDONLY);
    if (file < 0)
    {
        perror("Input file error");
        exit(EXIT_FAILURE);
    }
    if (dup2(file, STDIN_FILENO) < 0 || dup2(fd[1], STDOUT_FILENO) < 0)
    {
        close(file);
        close(fd[1]);
        cleanup_and_exit("dup2 failed", EXIT_FAILURE);
    }
    close(file);
    close(fd[1]);
    execute_cmd((char *)cmd, env);
    cleanup_and_exit("Command execution failed", EXIT_FAILURE);
}

static void	parent_process(int *fd, const char *outfile, const char *cmd, char **env)
{
    int	file;

    wait(NULL);
    close(fd[1]);
    
    file = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file < 0)
    {
        close(fd[0]);
        perror("Output file error");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(file, STDOUT_FILENO) < 0)
    {
        close(file);
        close(fd[0]);
        cleanup_and_exit("dup2 failed", EXIT_FAILURE);
    }
    close(file);
    close(fd[0]);
    // exit(1);
    execute_cmd((char *)cmd, env);
    cleanup_and_exit("Command execution failed", EXIT_FAILURE);
}

void	execute_cmd(char *cmd, char **env)
{
    char	**argv_content;
    char	*cmd_path;

    if (!cmd || !env)
        cleanup_and_exit("Invalid command or environment", EXIT_FAILURE);

    argv_content = ft_split(cmd, ' ');
    if (!argv_content || !argv_content[0])
    {
        free_split(argv_content);
        cleanup_and_exit("Empty command", EXIT_FAILURE);
    }

    cmd_path = get_command_path(argv_content[0], env); // /usr/local/bin/cat
    if (!cmd_path)
    {
        free_split(argv_content);
        cleanup_and_exit("Command not found", EXIT_FAILURE);
    }

    execve(cmd_path, argv_content, env);
    free(cmd_path);
    free_split(argv_content);
    perror("execve");
    exit(EXIT_FAILURE);
}

int	main(int argc, const char *argv[], char *env[])
{
    int		fd[2];
    pid_t	pid;

    if (argc != 5)
        cleanup_and_exit("Usage: ./pipex infile cmd1 cmd2 outfile\narguments not enough!", EXIT_FAILURE);

    if (pipe(fd) == -1)
        cleanup_and_exit("Pipe creation failed", EXIT_FAILURE);
 
    pid = fork();
    if (pid < 0)
        cleanup_and_exit("Fork failed", EXIT_FAILURE);

    if (pid == 0)
        child_process(fd, argv[1], argv[2], env);
    else
        parent_process(fd, argv[4], argv[3], env);
    return (0);
}
