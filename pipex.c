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
    {
        handle_errors("args not enough");
        exit(1);
    }
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
    char **argv_content = ft_split((char *)argv[2], ' ');
    char *cmd_path = get_command_path(argv_content[0], env);
    if (id == 0)
    {

        int ex = execve("sdkdkdk", argv_content, NULL);
        if (ex == -1)
        {
            free_split(argv_content);
            free(cmd_path);
            exit_hundel();
        }
    }
    else {
        wait(NULL);
    }
    free_split(argv_content);
    free(cmd_path);
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
        return (cmd);
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

void    handle_errors(char *err)
{
    write(2, "Error: ", 7);
    write(2, err, ft_strlen(err));
    write(2, "\n", 1);
}
// int main(int argc, char const *argv[],char *env[])
// {
//     (void) argc;
//     (void) argv;

    // if (access(argv[1], F_OK | X_OK) != 0 )
    // {
    //     perror("Error: ");
    //     exit(1);
    // }
    // char *test = find_path_env(env);
    // printf("%s\n",test);
    // free(test);
    // char *path_env = find_path_env(env);
    // char *command_path = get_command_path(argv[1]);
    // free(path_env);
                                                // printf("done");
                                            // int success = access(argv[1], F_OK | X_OK);
                                            // if (success == -1)
                                            // {
                                            //     printf("command not found: %s\n",argv[1]);
                                            //     int i = 0;
                                            //     while (env[i])
                                            //     {
                                                    
                                            //         printf("%s\n",ft_split(env[i],'=')[0]);
                                            //         i++;
                                            //     }
                                                
                                            // }
                                            // printf("%d\n",success);
    // int j = 0;
    // while (env[j])
    // {
    //     printf("%s\n",env[j]);
    //     j++;
    // }
    // // int i  = access("/bin/ls",F_OK | X_OK);
    // // printf("\n%d\n",i);
//     return 0;
// }


// solution

// void free_split(char **arr)
// {
//     int i;

//     if (!arr)
//         return;
        
//     i = 0;
//     while (arr[i])
//     {
//         free(arr[i]);
//         i++;
//     }
//     free(arr);
//     arr = NULL;  // Good practice though not necessary here since arr is passed by value
// }

// char *find_path(char **env)
// {
//     int i;
//     char **env_col;
//     char *returned_str;

//     i = 0;
//     while (env[i])
//     {
//         env_col = ft_split(env[i], '=');
//         if (!env_col)  // Handle allocation failure
//             return (NULL);
            
//         if (env_col[0] && ft_strcmp(env_col[0], "PATH") == 0)
//         {
//             if (!env_col[1])  // Check if second part exists
//             {
//                 free_split(env_col);
//                 return (NULL);
//             }
//             returned_str = ft_strdup(env_col[1]);
//             free_split(env_col);
//             return (returned_str);
//         }
//         free_split(env_col);  // Free if no match
//         i++;
//     }
//     return (NULL);
// }