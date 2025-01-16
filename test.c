#include "pipex.h"

int main(int argc, char const *argv[],char *env[])
{
	// char **res = ft_split(argv[1], ' ');
	// int  i = 0;
	// while (res[i])
	// {
	// 	printf("%s\n",res[i]);
	// 	i++;
	// }
	char *arg[] = {"awk 'BEGIN { print Hello World }' '{ sum += $1 }; END { print sum }'", NULL};
	int suc = execve("/bin/awk", arg, env);
	
}
